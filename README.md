# ESP32 ESP-NOW Block Network

This project lets the ESP32 boards in our block send messages to each other
without a router or hotspot. Each board keeps a list of the unique MAC
addresses it hears.

## Progress

Yestin has verified the sketch in Arduino IDE. Communication between boards
still needs to be tested during our block session on **Wednesday, November 11,
2026**. The exact time has not been confirmed, and the results are still pending.

## Uploading the sketch

[Open ESPNow_Block_Network.ino](firmware/ESPNow_Block_Network/ESPNow_Block_Network.ino)

Open the sketch in Arduino IDE, choose your ESP32 board and port, then upload
it. Set Serial Monitor to **115200 baud**.

Everyone in the block needs the same sketch, message layout, `BLOCK_NAME`,
and `RADIO_CHANNEL`. The code currently uses `BLOCK-A` and channel `1`.
We need to agree on these settings before the session.

All required libraries come with ESP32 Arduino board support 3.x.
The sketch does not create tasks or queues. It uses a short lock so the
receive callback and the main loop can safely share the MAC address list.

## During our block session

1. Use your own board and keep it within about five metres of the others.
2. Restart it once at the beginning to clear any earlier counts.
3. Leave it powered on for the whole window without connecting it to Wi-Fi.
4. Wait at least 30 seconds, then record the count and MAC addresses.
5. Take a Serial Monitor screenshot and record a 30-second screen video.

Your own board is excluded from the count. Each matching board is counted
once, even if it sends more messages. Its address stays in the list until
you restart, so the count does not tell you how many boards are still nearby.

## Individual results

[paraguya_yestin](paraguya_yestin/README.md)

Each student adds their evidence in their own `lastname_firstname` folder
at the top level of this repository. Leave everyone else's folders alone
and use results recorded by your own board. Everyone in the block submits
this same repository link.
