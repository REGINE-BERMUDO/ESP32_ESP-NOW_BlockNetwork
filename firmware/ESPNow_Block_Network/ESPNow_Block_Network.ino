// These headers come with ESP32 board support in Arduino IDE.
// Arduino provides Serial and timing; WiFi starts the radio; esp_now sends
// packets; esp_wifi selects the channel and reads our MAC. The remaining
// headers provide random timing, version checks, and byte-copy functions.
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <esp_system.h>
#include <esp_arduino_version.h>
#include <string.h>

// Before uploading, replace the name below with your own lastname_firstname.
// Keep the quotation marks and semicolon. Your name can have up to 31 characters.
const char OWNER_NAME[] = "lastname_firstname";

// Think of the channel as the frequency everyone is listening on.
// Keep this at 1 on every board taking part together.
const uint8_t RADIO_CHANNEL = 1;

// This number is a label that helps us recognize messages from this sketch.
// It is not a password. Everyone keeps the same value.
const uint32_t MAGIC = 0xB10C2026;

static_assert(sizeof(OWNER_NAME) <= 32,
              "Owner name must be 31 characters or fewer.");

// FF:FF:FF:FF:FF:FF is the broadcast address. One send can reach
// the other ESP-NOW boards listening nearby on the same channel.
const uint8_t BROADCAST_MAC[6] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

// This is the message we send over the radio. All boards need these fields
// in this order so they interpret the received bytes the same way.
// counter tracks our messages; the number of boards is counted using MACs.
struct Message {
  uint32_t magic;
  uint32_t counter;
  char owner[32];
};

static_assert(sizeof(Message) == 40,
              "The message must remain 40 bytes.");

// For each board we hear, remember its source MAC and the name it sends.
// The MAC comes from ESP-NOW. The owner types the name into their sketch.
struct BoardRecord {
  uint8_t mac[6];
  char owner[32];
};

// Store up to 100 unique boards. A warning appears if the list fills up.
const size_t MAX_BOARDS = 100;

BoardRecord heardBoards[MAX_BOARDS] = {};
size_t heardCount = 0;
bool listFull = false;

uint8_t myMac[6] = {};
Message outgoing = {};

// The radio can receive a message while loop() is reading the results.
// This lock lets one part use the shared list at a time.
// We do not need to create our own tasks or queues for this sketch.
portMUX_TYPE boardListLock = portMUX_INITIALIZER_UNLOCKED;

unsigned long lastSend = 0;
unsigned long sendInterval = 1000;
unsigned long lastSummary = 0;


// A MAC is six bytes. Print each as two hexadecimal digits, separated by
// colons, so you can copy the address into your results table.
void printMac(const uint8_t* mac) {
  Serial.printf(
    "%02X:%02X:%02X:%02X:%02X:%02X",
    (unsigned)mac[0], (unsigned)mac[1],
    (unsigned)mac[2], (unsigned)mac[3],
    (unsigned)mac[4], (unsigned)mac[5]
  );
}


// If setup fails, print the reason and stop here. Fix that problem before
// collecting results; an unfinished setup cannot hear the other boards.
void stopWithError(const char* message) {
  Serial.println(message);

  while (true) {
    delay(1000);
  }
}


// Copy up to 31 readable characters and finish the name with a zero byte.
// That ending tells Serial.println where the text stops. Characters outside
// the basic printable ASCII range appear as ? in this version.
void copyOwnerName(char* destination, const char* source) {
  for (size_t i = 0; i < 31; i++) {
    unsigned char character = (unsigned char)source[i];

    if (character == '\0') {
      destination[i] = '\0';
      return;
    }

    destination[i] =
      (character >= 32 && character <= 126)
      ? (char)character
      : '?';
  }

  destination[31] = '\0';
}


// Each received packet passes through these checks before we count it.
// The callback supplies the sender MAC, the message bytes, and their length.
void handleMessage(const uint8_t* mac,
                   const uint8_t* data,
                   int length) {
  if (mac == nullptr || data == nullptr) {
    return;
  }

  // Our message is 40 bytes. Ignore packets with another size, including
  // messages from the older 8-byte and 28-byte sketches.
  if (length != (int)sizeof(Message)) {
    return;
  }

  Message incoming = {};
  memcpy(&incoming, data, sizeof(incoming));

  if (incoming.magic != MAGIC) {
    return;
  }

  // The lab asks how many OTHER boards we heard, so skip our own MAC.
  if (memcmp(mac, myMac, 6) == 0) {
    return;
  }

  BoardRecord received = {};

  // Take the sender MAC from the received packet information. Students only
  // type their names; they do not need to find and enter MAC addresses in code.
  memcpy(received.mac, mac, 6);
  copyOwnerName(received.owner, incoming.owner);

  if (received.owner[0] == '\0') {
    strcpy(received.owner, "unnamed");
  }

  // Hold the shared list briefly while we read or change it.
  portENTER_CRITICAL(&boardListLock);

  size_t existingIndex = heardCount;

  // Look for this MAC in our existing list. Two students could type the same
  // name, but their boards should still be counted separately by MAC.
  for (size_t i = 0; i < heardCount; i++) {
    if (memcmp(heardBoards[i].mac, received.mac, 6) == 0) {
      existingIndex = i;
      break;
    }
  }

  if (existingIndex < heardCount) {
    // We have heard this board before. Update its name and keep the same count.
    memcpy(heardBoards[existingIndex].owner,
           received.owner,
           sizeof(received.owner));
  } else if (heardCount < MAX_BOARDS) {
    // This MAC is new. Save the board and increase the count once.
    heardBoards[heardCount] = received;
    heardCount++;
  } else {
    // Do not write past the array. Let the summary explain that it filled up.
    listFull = true;
  }

  portEXIT_CRITICAL(&boardListLock);
  // The list is available to the other part of the program again.

  // Leave the printing to loop(). Serial output takes longer than updating
  // the list, and this callback should finish quickly.
}


// Arduino ESP32 core 3.x gives us a packet-info object. Its src_addr field
// holds the sender MAC, which we pass to the same counting function below.
#if ESP_ARDUINO_VERSION_MAJOR >= 3

void onReceive(const esp_now_recv_info_t* info,
               const uint8_t* data,
               int length) {
  if (info != nullptr) {
    handleMessage(info->src_addr, data, length);
  }
}

// Older 2.x board packages pass the sender MAC directly instead.
#else

void onReceive(const uint8_t* mac,
               const uint8_t* data,
               int length) {
  handleMessage(mac, data, length);
}

#endif


// Take a copy of the list, then print that copy. New radio messages can
// arrive while the summary is printing without changing this particular list.
void printSummary() {
  // Keep this copy in static storage so the whole array does not have to
  // fit on the function stack each time we print.
  static BoardRecord snapshot[MAX_BOARDS];

  size_t count;
  bool full;

  // Hold the shared list briefly while we read or change it.
  portENTER_CRITICAL(&boardListLock);

  count = heardCount;
  full = listFull;
  memcpy(snapshot, heardBoards, count * sizeof(BoardRecord));

  portEXIT_CRITICAL(&boardListLock);
  // The list is available to the other part of the program again.

  Serial.println("\n========== ESP-NOW RESULTS ==========");

  Serial.print("My name      : ");
  Serial.println(OWNER_NAME);

  Serial.print("My board MAC : ");
  printMac(myMac);
  Serial.println();

  Serial.printf("Radio channel: %u\n",
                (unsigned)RADIO_CHANNEL);

  Serial.printf("Running for  : %lu seconds\n",
                millis() / 1000UL);

  Serial.printf("Boards heard : %u\n",
                (unsigned)count);

  Serial.println("Owner / MAC address:");

  if (count == 0) {
    Serial.println("  None yet.");
  }

  for (size_t i = 0; i < count; i++) {
    Serial.printf("  %u. %s | ",
                  (unsigned)(i + 1),
                  snapshot[i].owner);

    printMac(snapshot[i].mac);
    Serial.println();
  }

  if (full) {
    Serial.println("WARNING: Board list full.");
    Serial.println("The actual number may exceed the stored count.");
  }

  Serial.println("=====================================\n");
}


void setup() {
  Serial.begin(115200);
  delay(1000);

  // Replace the placeholder at the top before using this on your own board.
  if (strcmp(OWNER_NAME, "lastname_firstname") == 0) {
    stopWithError("Set OWNER_NAME to your own lastname_firstname, then upload again.");
  }

  // Station mode enables the radio that ESP-NOW needs. We never call
  // WiFi.begin(), so the board does not join a router or phone hotspot.
  if (!WiFi.mode(WIFI_STA)) {
    stopWithError("Could not start the radio.");
  }

  // Disconnect any existing connection and prevent automatic reconnection.
  WiFi.setAutoReconnect(false);
  WiFi.disconnect(false, false);
  delay(100);

  // Set the channel before starting ESP-NOW. A board listening on another
  // channel will miss these messages.
  if (esp_wifi_set_channel(
        RADIO_CHANNEL, WIFI_SECOND_CHAN_NONE) != ESP_OK) {
    stopWithError("Could not set the radio channel.");
  }

  // Read this board's station MAC automatically. If you switch from a WROOM
  // to an S3, record the new board's MAC in your evidence.
  if (esp_wifi_get_mac(WIFI_IF_STA, myMac) != ESP_OK) {
    stopWithError("Could not read this board's MAC.");
  }

  // Fill in the fields that stay the same between sends. The counter starts
  // at zero and increases later in loop().
  outgoing.magic = MAGIC;
  outgoing.counter = 0;
  strcpy(outgoing.owner, OWNER_NAME);

  if (esp_now_init() != ESP_OK) {
    stopWithError("ESP-NOW initialization failed.");
  }

  // Register one broadcast destination instead of entering every classmate.
  // {} clears the structure before we fill in the fields we need.
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, BROADCAST_MAC, 6);
  peer.channel = RADIO_CHANNEL;
  peer.ifidx = WIFI_IF_STA;
  peer.encrypt = false;

  if (esp_now_add_peer(&peer) != ESP_OK) {
    stopWithError("Could not add the broadcast peer.");
  }

  // Tell ESP-NOW which function to call whenever a packet arrives.
  if (esp_now_register_recv_cb(onReceive) != ESP_OK) {
    stopWithError("Could not register the receive callback.");
  }

  Serial.println("ESP-NOW ready.");
  Serial.println("No router or hotspot connection is used.");
  Serial.println("Names are entered by each board's owner.");
  Serial.println("Count includes unique OTHER boards since startup.");
  Serial.println("Wait at least 30 seconds during the block window.");

  printSummary();
}


void loop() {
  unsigned long now = millis();

  // millis() reports the time since startup. Subtracting the last-send time
  // lets us send about once a second while still checking other work in loop().
  if (now - lastSend >= sendInterval) {
    lastSend = now;
    // Wait 1,000 to 1,300 ms between sends. The variation helps boards
    // avoid repeatedly transmitting at exactly the same moment.
    sendInterval = 1000 + (esp_random() % 301);

    outgoing.counter++;

    esp_err_t result = esp_now_send(
      BROADCAST_MAC,
      reinterpret_cast<const uint8_t*>(&outgoing),
      sizeof(outgoing)
    );

    // ESP_OK means the send request was accepted. Another board must receive
    // our message before it can include us in its own results.
    if (result != ESP_OK) {
      Serial.printf("Send request failed: %d\n", (int)result);
    }
  }

  // Print the full results every five seconds so you can capture the count
  // and MAC list for your screenshot and 30-second recording.
  if (now - lastSummary >= 5000) {
    lastSummary = now;
    printSummary();
  }

  delay(5); // A short pause before the next pass through loop().
}