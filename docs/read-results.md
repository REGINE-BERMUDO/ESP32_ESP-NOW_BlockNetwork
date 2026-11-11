# Read your Serial Monitor results

Use the results from your own board during your approved block window.
The shared sketch prints a full summary every five seconds.

| Field | What it tells you |
| :--- | :--- |
| My name | The `OWNER_NAME` entered in your local sketch. |
| My board MAC | The station MAC of the physical board you uploaded to. Copy this into your README. |
| Radio channel | The channel your board is using. Everyone testing together uses `1`. |
| Running for | Seconds since the board started. This is not the date or time of the session. |
| Boards heard | The number of unique other MAC addresses received since startup. |
| Owner / MAC address | Each sender's self-entered name and the source MAC supplied by ESP-NOW. |

Repeated messages from the same MAC do not increase the count. Two boards
with the same owner name still count separately if their MAC addresses differ.
Your own board is excluded. Addresses stay in the list until restart, even
when a board leaves range, so this is not a live attendance counter.

## Fill in your README

1. Copy your own MAC exactly, including all six pairs of hexadecimal digits.
2. Copy the displayed count. List every MAC from that same summary.
3. Check that the number of unique addresses you wrote equals the count.
4. Use the actual scheduled block date and time. Record a separate collection
   or completion time if needed; uptime does not supply either value.
5. Embed your screenshot and link your 30-second video using their actual filenames.

Attendance and radio reception are separate records. For example, if 16
students are present including you, there may be up to 15 other student
boards to hear, but a reception problem can produce a smaller count.
Report what your board received rather than replacing it with attendance.

If the count changes while you are recording, let the devices settle and
capture the evidence again if time allows. Otherwise explain the difference
between captures honestly. The earlier capture should not be presented as
showing a later count.

Names are optional extra information. A name is not verified ownership, and
a repository entry is not proof that a board was present. Only use the
measurements made in the approved room and window. If a list-full warning
appears, the stored count and list are incomplete.

Next: [prepare your results folder](../CONTRIBUTING.md).
