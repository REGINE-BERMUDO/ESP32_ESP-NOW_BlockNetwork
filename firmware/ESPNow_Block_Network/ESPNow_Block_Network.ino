#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <esp_system.h>
#include <string.h>

// Change this to your actual block name.
// Everyone in your block must use the SAME name.
const char BLOCK_NAME[] = "BLOCK-A";

// Everyone must also use the SAME radio channel.
const uint8_t RADIO_CHANNEL = 1;

// Our message has room for 23 characters plus its ending zero.
static_assert(sizeof(BLOCK_NAME) <= 24,
              "Block name must be 23 characters or fewer.");

// Identifies messages made for this sketch.
const uint32_t MESSAGE_ID = 0x18800001;

// This address means "broadcast to listening boards in range."
const uint8_t BROADCAST_MAC[6] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

// Keep this message layout the same on every board.
struct Message {
  uint32_t messageId;
  char block[24];
};

Message outgoing = {};

// Stores this board's own MAC address.
uint8_t myMac[6] = {};

// Stores unique OTHER boards heard since this board started.
// These are received addresses, not manually entered results.
const size_t MAX_BOARDS = 100;
uint8_t heardMacs[MAX_BOARDS][6] = {};
size_t heardCount = 0;
bool listFull = false;

// The receive callback and loop() can run at the same time.
// This lock protects their shared MAC list.
portMUX_TYPE macListLock = portMUX_INITIALIZER_UNLOCKED;

// Timers let us send and print at different intervals.
unsigned long lastSend = 0;
unsigned long sendInterval = 2000;
unsigned long lastReport = 0;


// Print an address in the format AA:BB:CC:DD:EE:FF.
void printMac(const uint8_t* mac) {
  Serial.printf(
    "%02X:%02X:%02X:%02X:%02X:%02X",
    (unsigned)mac[0], (unsigned)mac[1],
    (unsigned)mac[2], (unsigned)mac[3],
    (unsigned)mac[4], (unsigned)mac[5]
  );
}


// Stop here if a required setup step fails.
void stopWithError(const char* message) {
  Serial.println(message);

  while (true) {
    delay(1000);
  }
}


// The radio calls this function when a message arrives.
void onReceive(const esp_now_recv_info_t* info,
               const uint8_t* data,
               int length) {
  if (info == nullptr || data == nullptr) {
    return;
  }

  // Ignore messages using a different layout.
  if (length != (int)sizeof(Message)) {
    return;
  }

  Message incoming = {};
  memcpy(&incoming, data, sizeof(incoming));

  // Accept only messages from this sketch and our block.
  if (incoming.messageId != MESSAGE_ID ||
      memcmp(incoming.block, outgoing.block,
             sizeof(incoming.block)) != 0) {
    return;
  }

  // Our own board does not count as another board.
  if (memcmp(info->src_addr, myMac, 6) == 0) {
    return;
  }

  portENTER_CRITICAL(&macListLock);

  bool alreadyHeard = false;

  // Check whether we have already recorded this sender.
  for (size_t i = 0; i < heardCount; i++) {
    if (memcmp(heardMacs[i], info->src_addr, 6) == 0) {
      alreadyHeard = true;
      break;
    }
  }

  // Record a new sender only once.
  if (!alreadyHeard) {
    if (heardCount < MAX_BOARDS) {
      memcpy(heardMacs[heardCount], info->src_addr, 6);
      heardCount++;
    } else {
      listFull = true;
    }
  }

  portEXIT_CRITICAL(&macListLock);

  // Leave printing to loop() so this function finishes quickly.
}


// Print the information needed for your results.
void printResults() {
  uint8_t snapshot[MAX_BOARDS][6];
  size_t count;
  bool full;

  // Make a safe copy before printing.
  portENTER_CRITICAL(&macListLock);

  count = heardCount;
  full = listFull;
  memcpy(snapshot, heardMacs, count * sizeof(snapshot[0]));

  portEXIT_CRITICAL(&macListLock);

  Serial.println("\n========== ESP-NOW RESULTS ==========");

  Serial.print("Block: ");
  Serial.println(BLOCK_NAME);

  Serial.print("My board MAC: ");
  printMac(myMac);
  Serial.println();

  Serial.printf("Channel: %u\n", (unsigned)RADIO_CHANNEL);
  Serial.printf("Time since startup: %lu seconds\n",
                millis() / 1000UL);
  Serial.printf("Unique OTHER boards heard: %u\n",
                (unsigned)count);

  if (count == 0) {
    Serial.println("No matching boards heard yet.");
  }

  for (size_t i = 0; i < count; i++) {
    Serial.printf("%u. ", (unsigned)(i + 1));
    printMac(snapshot[i]);
    Serial.println();
  }

  if (full) {
    Serial.println("WARNING: List full; results are incomplete.");
  }

  Serial.println("=====================================\n");
}


void setup() {
  Serial.begin(115200);
  delay(500);

  // Start the radio in station mode.
  // We never call WiFi.begin(), so we do not join a network.
  if (!WiFi.mode(WIFI_STA)) {
    stopWithError("Could not start the radio.");
  }

  // Prevent reconnecting to a previously used Wi-Fi network.
  WiFi.setAutoReconnect(false);
  WiFi.disconnect(false, false);
  delay(100);

  // Set the channel before starting ESP-NOW.
  if (esp_wifi_set_channel(
        RADIO_CHANNEL, WIFI_SECOND_CHAN_NONE) != ESP_OK) {
    stopWithError("Could not set the radio channel.");
  }

  // Read our station MAC address.
  if (esp_wifi_get_mac(WIFI_IF_STA, myMac) != ESP_OK) {
    stopWithError("Could not read this board's MAC.");
  }

  // Prepare the message before enabling reception.
  outgoing.messageId = MESSAGE_ID;
  strcpy(outgoing.block, BLOCK_NAME);

  if (esp_now_init() != ESP_OK) {
    stopWithError("ESP-NOW initialization failed.");
  }

  // Add the broadcast destination.
  // We do not add every classmate as an individual peer.
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, BROADCAST_MAC, 6);
  peer.channel = RADIO_CHANNEL;
  peer.ifidx = WIFI_IF_STA;
  peer.encrypt = false;

  if (esp_now_add_peer(&peer) != ESP_OK) {
    stopWithError("Could not add the broadcast destination.");
  }

  if (esp_now_register_recv_cb(onReceive) != ESP_OK) {
    stopWithError("Could not register the receive function.");
  }

  Serial.println("ESP-NOW ready. No router connection is used.");
  Serial.println("Wait at least 30 seconds during your block window.");

  printResults();
}


void loop() {
  unsigned long now = millis();

  // Broadcast approximately every two seconds.
  if (now - lastSend >= sendInterval) {
    lastSend = now;

    // Small random timing differences reduce simultaneous sends.
    sendInterval = 2000 + (esp_random() % 501);

    esp_err_t result = esp_now_send(
      BROADCAST_MAC,
      reinterpret_cast<const uint8_t*>(&outgoing),
      sizeof(outgoing)
    );

    // Success here means the send request was accepted.
    // Only another board's receive log proves it heard us.
    if (result != ESP_OK) {
      Serial.printf("Send request failed: %d\n", (int)result);
    }
  }

  // Print the complete results every five seconds.
  if (now - lastReport >= 5000) {
    lastReport = now;
    printResults();
  }

  delay(5);
}