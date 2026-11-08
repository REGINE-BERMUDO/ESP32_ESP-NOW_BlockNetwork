# ESP32 ESP-NOW Block Network

Each ESP32 broadcasts a short message and records the unique MAC addresses
of other matching boards it hears. No router or hotspot connection is used.

## Current status

The sketch passed Verify in Arduino IDE, as reported by Yestin Paraguya.
Board-to-board operation and official results are pending the scheduled
block session on **Wednesday, November 11, 2026**. The time window is
still to be recorded.

## Shared sketch

[Open ESPNow_Block_Network.ino](firmware/ESPNow_Block_Network/ESPNow_Block_Network.ino)

Open the sketch in Arduino IDE, select your ESP32 board and port, and upload.
Open Serial Monitor at **115200 baud**.

Before the session, the block must agree on the same sketch, message layout,
`BLOCK_NAME`, and `RADIO_CHANNEL`. The current settings are `BLOCK-A` and
channel `1`; these are defaults awaiting block agreement.

The sketch uses only libraries included with ESP32 Arduino board support
3.x. It creates no custom tasks or queues. A short lock protects the MAC list
shared by the receive callback and the main loop.

## During the approved window

1. Use only your own board and stay within about five metres of the others.
2. Restart once at the start to clear earlier counts.
3. Keep the board powered for the full window. Do not connect it to Wi-Fi.
4. Wait at least 30 seconds before recording the count and addresses.
5. Capture a Serial Monitor screenshot and a 30-second screen video.

The displayed count excludes your own board and counts each other matching
MAC only once since startup. It is a cumulative count, not a live presence count.

## Individual evidence

[paraguya_yestin](paraguya_yestin/README.md)

Each student adds only their own `lastname_firstname` folder at the top level.
Do not edit or copy another student's evidence. All students in the block
submit the same shared repository URL.
