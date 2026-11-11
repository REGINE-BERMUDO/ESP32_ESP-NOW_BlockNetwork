# Shared ESP-NOW firmware

Open [ESPNow_Block_Network.ino](ESPNow_Block_Network/ESPNow_Block_Network.ino)
in Arduino IDE. Keep the sketch inside its matching `ESPNow_Block_Network`
folder so Arduino opens it correctly.

Change only `OWNER_NAME` in your local copy. Every board testing together
keeps channel `1`, `MAGIC = 0xB10C2026`, and the same 40-byte message layout.
The shared file keeps `lastname_firstname` as its placeholder and asks you
to replace it before use.

## What each part does

| Part | Its job |
| :--- | :--- |
| `Message` | Holds the identification value, message counter, and owner name sent over the radio. |
| `BoardRecord` | Stores a received sender's MAC and advertised name. |
| `setup()` | Starts Serial, enables the radio without joining Wi-Fi, sets the channel, reads this board's MAC, and initializes ESP-NOW. |
| `onReceive()` | Passes received packet information to the counting function. The callback form depends on the installed Arduino ESP32 core version. |
| `handleMessage()` | Checks packet size and identification, skips this board, and adds each new MAC once. |
| `boardListLock` | Protects the list shared by the radio callback and main loop. No custom tasks or queues are created. |
| `printSummary()` | Copies the results, then prints names, MAC addresses, and the count. |
| `loop()` | Sends about once per second, with a small random variation, and prints a summary every five seconds. |

The code has tutorial comments for the details. No classmate's name or MAC
needs to be entered manually. The advertised name is self-entered; the MAC
comes from the received packet information.

The list holds up to 100 other boards and warns when full. It is cumulative
since startup, so restart at the beginning of the official window to clear
earlier observations. A successful send request does not prove reception.

See [board setup](../docs/board-setup.md),
[the block-session guide](../docs/block-session.md), and
[how to read the results](../docs/read-results.md).
