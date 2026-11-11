#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <esp_system.h>
#include <esp_arduino_version.h>
#include <string.h>

// Change only this name in your local copy before uploading.
// Keep the shared repository copy as lastname_firstname.
const char OWNER_NAME[] = "lastname_firstname";

// Everyone participating together must keep these settings identical.
const uint8_t RADIO_CHANNEL = 1;
const uint32_t MAGIC = 0xB10C2026;
const size_t MAX_BOARDS = 100;

static_assert(sizeof(OWNER_NAME) <= 32,
              "Owner name must be 31 characters or fewer.");

const uint8_t BROADCAST_MAC[6] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

// All boards must use this same 40-byte message layout.
struct Message {
  uint32_t magic;
  uint32_t counter;
  char owner[32];
};
static_assert(sizeof(Message) == 40, "Message layout must remain 40 bytes.");

struct BoardRecord {
  uint8_t mac[6];
  char owner[32];
};

BoardRecord heardBoards[MAX_BOARDS] = {};
size_t heardCount = 0;
bool listFull = false;
uint8_t myMac[6] = {};
Message outgoing = {};

// The radio callback and loop share this list. No custom tasks or queues.
portMUX_TYPE boardListLock = portMUX_INITIALIZER_UNLOCKED;
unsigned long lastSend = 0;
unsigned long sendInterval = 1000;
unsigned long lastSummary = 0;

void printMac(const uint8_t* mac) {
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X",
                (unsigned)mac[0], (unsigned)mac[1], (unsigned)mac[2],
                (unsigned)mac[3], (unsigned)mac[4], (unsigned)mac[5]);
}

void stopWithError(const char* message) {
  Serial.println(message);
  while (true) delay(1000);
}

// Keep the received name terminated and remove terminal control characters.
void copyOwnerName(char* destination, const char* source) {
  for (size_t i = 0; i < 31; i++) {
    unsigned char character = (unsigned char)source[i];
    if (character == '\0') {
      destination[i] = '\0';
      return;
    }
    destination[i] = (character >= 32 && character <= 126)
                       ? (char)character : '?';
  }
  destination[31] = '\0';
}

void handleMessage(const uint8_t* mac, const uint8_t* data, int length) {
  if (mac == nullptr || data == nullptr || length != (int)sizeof(Message)) return;
  Message incoming = {};
  memcpy(&incoming, data, sizeof(incoming));
  if (incoming.magic != MAGIC || memcmp(mac, myMac, 6) == 0) return;

  BoardRecord received = {};
  // Take the real source address from ESP-NOW, not an address in the payload.
  memcpy(received.mac, mac, 6);
  copyOwnerName(received.owner, incoming.owner);
  if (received.owner[0] == '\0') strcpy(received.owner, "unnamed");

  portENTER_CRITICAL(&boardListLock);
  size_t existing = heardCount;
  for (size_t i = 0; i < heardCount; i++) {
    if (memcmp(heardBoards[i].mac, mac, 6) == 0) {
      existing = i;
      break;
    }
  }
  if (existing < heardCount) {
    memcpy(heardBoards[existing].owner, received.owner, sizeof(received.owner));
  } else if (heardCount < MAX_BOARDS) {
    heardBoards[heardCount++] = received;
  } else {
    listFull = true;
  }
  portEXIT_CRITICAL(&boardListLock);
}

#if ESP_ARDUINO_VERSION_MAJOR >= 3
void onReceive(const esp_now_recv_info_t* info, const uint8_t* data, int length) {
  if (info != nullptr) handleMessage(info->src_addr, data, length);
}
#else
void onReceive(const uint8_t* mac, const uint8_t* data, int length) {
  handleMessage(mac, data, length);
}
#endif

void printSummary() {
  // Static storage keeps this larger copy off the loop's stack.
  static BoardRecord snapshot[MAX_BOARDS];
  size_t count;
  bool full;
  portENTER_CRITICAL(&boardListLock);
  count = heardCount;
  full = listFull;
  memcpy(snapshot, heardBoards, count * sizeof(BoardRecord));
  portEXIT_CRITICAL(&boardListLock);

  Serial.println("\n========== ESP-NOW RESULTS ==========");
  Serial.print("My name      : ");
  Serial.println(OWNER_NAME);
  Serial.print("My board MAC : ");
  printMac(myMac);
  Serial.println();
  Serial.printf("Radio channel: %u\n", (unsigned)RADIO_CHANNEL);
  Serial.printf("Running for  : %lu seconds\n", millis() / 1000UL);
  Serial.printf("Boards heard : %u\n", (unsigned)count);
  Serial.println("Owner / MAC address:");
  if (count == 0) Serial.println("  None yet.");
  for (size_t i = 0; i < count; i++) {
    Serial.printf("  %u. %s | ", (unsigned)(i + 1), snapshot[i].owner);
    printMac(snapshot[i].mac);
    Serial.println();
  }
  if (full) Serial.println("WARNING: Board list full; results are incomplete.");
  Serial.println("=====================================\n");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  if (strcmp(OWNER_NAME, "lastname_firstname") == 0) {
    stopWithError("Set OWNER_NAME to your own lastname_firstname, then upload again.");
  }
  // Start the radio without joining a router or hotspot.
  if (!WiFi.mode(WIFI_STA)) stopWithError("Could not start the radio.");
  WiFi.setAutoReconnect(false);
  WiFi.disconnect(false, false);
  delay(100);
  if (esp_wifi_set_channel(RADIO_CHANNEL, WIFI_SECOND_CHAN_NONE) != ESP_OK)
    stopWithError("Could not set the radio channel.");
  if (esp_wifi_get_mac(WIFI_IF_STA, myMac) != ESP_OK)
    stopWithError("Could not read this board's MAC.");
  outgoing.magic = MAGIC;
  strcpy(outgoing.owner, OWNER_NAME);
  if (esp_now_init() != ESP_OK) stopWithError("ESP-NOW initialization failed.");

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, BROADCAST_MAC, 6);
  peer.channel = RADIO_CHANNEL;
  peer.ifidx = WIFI_IF_STA;
  peer.encrypt = false;
  if (esp_now_add_peer(&peer) != ESP_OK)
    stopWithError("Could not add the broadcast peer.");
  if (esp_now_register_recv_cb(onReceive) != ESP_OK)
    stopWithError("Could not register the receive callback.");
  Serial.println("ESP-NOW ready. No router or hotspot connection is used.");
  Serial.println("Names are entered by each owner. Count is unique OTHER boards since startup.");
  Serial.println("Wait at least 30 seconds during your approved block window.");
  printSummary();
}

void loop() {
  unsigned long now = millis();
  if (now - lastSend >= sendInterval) {
    lastSend = now;
    sendInterval = 1000 + (esp_random() % 301);
    outgoing.counter++;
    esp_err_t result = esp_now_send(BROADCAST_MAC,
      reinterpret_cast<const uint8_t*>(&outgoing), sizeof(outgoing));
    // Accepted for sending does not prove another board received the message.
    if (result != ESP_OK) Serial.printf("Send request failed: %d\n", (int)result);
  }
  if (now - lastSummary >= 5000) {
    lastSummary = now;
    printSummary();
  }
  delay(5);
}
