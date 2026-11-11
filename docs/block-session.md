# During your block session

Attend the room and time announced by the instructor. Use only your own
board and keep it powered for the full window. Your results must come from
that board during that window.

## Collect your results

1. Place your board within about **five metres** of the other boards in your block.
2. Open Serial Monitor at **115200 baud**.
3. Restart once at the beginning to clear earlier counts.
4. Keep the ESP32 disconnected from routers and hotspots throughout the lab.
5. Wait at least **30 seconds** before recording the results.
6. Write down your board's MAC, the number of other boards heard, and every
   MAC address shown. Do not use another student's list.
7. Record the actual date and time of your block window. Include the start,
   end, and timezone so the window is clear.

The sketch prints a summary every five seconds. Its running-time value is
uptime, not the date or clock time. It counts each other MAC once since
startup and keeps addresses even after a board leaves range. Your own board
is excluded. Owner names are self-entered extras; MAC addresses are required.
There is no block-name filter, so only collect results in the approved room
and window. A board absent from the room during that window does not count.

## Capture both evidence files

| File | What it must show |
| :--- | :--- |
| `serial-monitor.png` | Serial Monitor with the count and every MAC heard visible. Include your own MAC so the board is identifiable. |
| `serial-monitor-30s.mp4` | A 30-second screen recording of Serial Monitor during your block window. |

Make the text readable. If the list is long, adjust the Serial Monitor view
before taking the screenshot. The screenshot and video must come from your
own board. Neither file replaces the other.

## Save your submission

Put these three files in your own top-level `lastname_firstname` folder:

```text
lastname_firstname/
├── README.md
├── serial-monitor.png
└── serial-monitor-30s.mp4
```

Copy the [README template](student-readme-template.md), fill in every result,
and add your actual evidence. Do not put another student's folder inside
yours or edit their files.

Next: [submit your folder through a pull request](../CONTRIBUTING.md).
