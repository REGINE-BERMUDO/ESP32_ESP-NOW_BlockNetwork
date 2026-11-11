# ESP32 ESP-NOW Block Network

This is the class repository for our ESP-NOW block activity. The shared
sketch lets each ESP32 announce its owner's name and record the MAC addresses
of other boards it hears, without joining a router or hotspot.

Everyone uses this repository. **Each student's measurements must come from
their own board during their own block's scheduled window.** A classmate's
folder or name in this repository is not evidence that their board was heard.

## Before your block window

1. Install Arduino IDE and ESP32 board support. The sketch uses libraries
   included with the board package; WiFiManager is not needed.
2. Download the repository and open the
   [shared sketch](firmware/ESPNow_Block_Network/ESPNow_Block_Network.ino).
3. Change this line in your local copy to your own name:

   ```cpp
   const char OWNER_NAME[] = "lastname_firstname";
   ```

   Use `lastname_firstname`, with no spaces and at most 31 characters.
   The shared copy deliberately stops at startup until this name is changed.
4. Keep `RADIO_CHANNEL = 1`, `MAGIC = 0xB10C2026`, and the message layout
   unchanged. This version sends a 40-byte message containing the owner name.
   The older 8-byte and 28-byte sketches are incompatible; everyone needs this version.
5. Select your actual board and port. For a standard WROOM-32 development
   board, select **ESP32 Dev Module**. For a generic S3 development board,
   select **ESP32S3 Dev Module**; use the exact board profile if supplied by
   its manufacturer. Native USB serial on the S3 may require **USB CDC On Boot**.
6. Verify, upload, and open Serial Monitor at **115200 baud**. Check that
   your name, your board's MAC, and channel `1` appear. Test with a classmate
   before the official window. Testing alone may show zero boards.

Only `OWNER_NAME` differs between students' local sketches. Do not commit
your local name change over the shared firmware. Submit your personal
results folder instead; see [how to contribute](CONTRIBUTING.md).

## During your block window

1. Attend the room and time announced by the instructor. Use only your own board.
2. Place it within about **five metres** of the other boards in your block.
3. Restart once at the beginning to clear counts from earlier testing.
4. Keep your board powered for the **full window**. Do not connect it to Wi-Fi.
5. Wait at least **30 seconds**, then record your board's MAC, the number
   of boards heard, and every MAC address in its results.
6. Take a Serial Monitor screenshot with the count and MAC addresses visible.
   Include your own MAC as well so the evidence identifies your board.
7. Record a **30-second screen video** of Serial Monitor during that window.
8. Write down the actual **date, start time, and end time** of your window.
   The displayed running time is uptime, not the calendar date or clock time.

The sketch counts unique other MAC addresses since startup, excludes its
own MAC, and repeats the summary every five seconds. Repeated messages do
not increase the count. A stored address remains after a board leaves range.
Names are entered by owners and are optional extra information; **MAC
addresses and actual results are required**. The sketch has no block-name
filter, so follow the room and window rules when collecting results.
If the list-full warning appears, the stored count is incomplete.

## Your submission folder

Create your own `lastname_firstname` folder directly at the top level:

```text
esp32_espnow_block_network/
├── README.md
├── CONTRIBUTING.md
├── firmware/
│   └── ESPNow_Block_Network/
│       └── ESPNow_Block_Network.ino
├── docs/
│   └── student-readme-template.md
└── lastname_firstname/          (replace with your own name)
    ├── README.md
    ├── serial-monitor.png
    └── serial-monitor-30s.mp4
```

Copy the [student README template](docs/student-readme-template.md) into
your folder and fill it with your own observations. Include:

- Your name as `lastname_firstname`.
- Your board's MAC address.
- The number of other boards heard.
- Every MAC address heard, including a written list in the README.
- The actual date and time of your block window.
- Your screenshot and 30-second recording from that window.

[Yestin's results folder](paraguya_yestin/README.md) belongs to Yestin.
It is not a template or shared evidence folder. Do not put another student's
folder inside yours, edit another student's folder, or copy their results.
A board absent from the room during the window does not count.

Everyone in each block submits this same repository URL to the submission bin:

https://github.com/xavieryyyyyy/esp32_espnow_block_network

## Verification status

The shared owner-name sketch compiled successfully for **ESP32 Dev Module**
and **ESP32S3 Dev Module** (native USB CDC enabled), using the installed
ESP32 Arduino core **3.3.12**. Compilation does not prove radio communication
or attendance. Test this version between actual boards before recording
official results. Pending personal results are not completed submissions.
