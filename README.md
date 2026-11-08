# ESP32 ESP-NOW Block Network

I am using an ESP32 to send messages to the other boards in my block
without connecting to a router or hotspot. My board keeps a list of the
unique MAC addresses it hears.

## My progress

I have verified the sketch in Arduino IDE. I still need to test communication
with the other boards during my block session on **Wednesday, November 11,
2026**. The exact time has not been confirmed, so my results are still pending.

## Setting up my board

[Open ESPNow_Block_Network.ino](firmware/ESPNow_Block_Network/ESPNow_Block_Network.ino)

To upload the sketch, I open it in Arduino IDE, choose my ESP32 board and
port, then click Upload. I set Serial Monitor to **115200 baud**.

My classmates and I need to use the same sketch, message layout, `BLOCK_NAME`,
and `RADIO_CHANNEL`. My code currently uses `BLOCK-A` and channel `1`.
I will confirm these settings with my block before the session.

All the libraries I need come with ESP32 Arduino board support 3.x.
My sketch does not create tasks or queues. It uses a short lock so the
receive callback and the main loop can safely share the MAC address list.

## My plan for the block session

1. I will use my own board and keep it within about five metres of the others.
2. I will restart it once at the beginning to clear any earlier counts.
3. I will keep it powered on for the whole window without connecting it to Wi-Fi.
4. I will wait at least 30 seconds, then record the count and MAC addresses.
5. I will take a Serial Monitor screenshot and record a 30-second screen video.

My board excludes itself from the count. It counts each matching board once,
even if that board sends more messages. The addresses stay in the list until
I restart my board, so the count shows all boards heard since startup.
It does not tell me how many are still nearby.

## My results

[paraguya_yestin](paraguya_yestin/README.md)

I will put my evidence in my own `lastname_firstname` folder at the top level
of this repository. I will use the results recorded by my board and leave
my classmates' folders untouched. My block will submit this same repository link.
