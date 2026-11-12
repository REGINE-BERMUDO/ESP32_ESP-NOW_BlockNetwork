# ESP32 ESP-NOW Class Repository

Our class uses this repository for the ESP-NOW block activity. Each board
sends its owner's name and records the MAC addresses of other boards it
hears. The ESP32 does not join a router or hotspot.

**Use your own board, attend your block's approved window, and submit only
the results your board records there.** Everyone submits the same shared
repository link after their own evidence has been merged.

## Follow this order

Prepare your board → attend your block window → capture your own results →
add your folder in a PR → check the merge → submit the shared link.

The `students` page is a directory. Each actual results folder stays at the
repository's top level, as the assignment requires.

## Start here

| What you need to do | Open this guide |
| :--- | :--- |
| Download the sketch and prepare your board | [Board setup](docs/board-setup.md) |
| Follow the lab steps and capture evidence | [Block session](docs/block-session.md) |
| Understand the count, owner names, and MAC list | [Read the results](docs/read-results.md) |
| Fix common board, file, or GitHub problems | [Common problems](docs/troubleshooting.md) |
| Understand the shared code | [Firmware walkthrough](firmware/README.md) |
| Add your own folder through a pull request | [Submit your results](CONTRIBUTING.md) |
| Find a student's results | [Student directory](students/README.md) |
| Review and merge classmates' submissions | [Repository owner guide](docs/maintainer-guide.md) |

## How the folders work

```text
esp32_espnow_block_network/
├── README.md                       Class starting page
├── CONTRIBUTING.md                 How to submit a pull request
├── students/
│   └── README.md                    Directory linking to student folders
├── docs/
│   ├── board-setup.md
│   ├── block-session.md
│   ├── read-results.md
│   ├── troubleshooting.md
│   ├── student-readme-template.md
│   └── maintainer-guide.md
├── firmware/
│   ├── README.md                   Code walkthrough
│   └── ESPNow_Block_Network/
│       └── ESPNow_Block_Network.ino  One shared sketch
├── .github/
│   └── PULL_REQUEST_TEMPLATE.md     Submission checklist
└── lastname_firstname/             Each student adds their own folder by PR
    ├── README.md                   Their actual results
    ├── lastname_serialmonitor.png          Their Serial Monitor screenshot
    └── lastname_serialmonitor.mp4       Their 30-second screen recording
```

Each student, including the repository owner, creates their own
`lastname_firstname` folder through a results pull request. The activity
requires these folders at the **top level**. The `students` folder is a
directory of links; evidence belongs in the student's own top-level folder.
The folder above is an example of what students will add, not a pre-created submission.

Use your surname in both evidence filenames: `lastname_serialmonitor.png`
and `lastname_serialmonitor.mp4`. Keep each file's real extension and make
the links in your README match. The video must be a 30-second screen recording.

Every personal folder contains three files: a completed README, a Serial
Monitor screenshot, and a 30-second screen recording. Copy the
[README template](docs/student-readme-template.md) to begin. Never copy
someone else's results or edit their folder.

## Shared sketch

[Open ESPNow_Block_Network.ino](firmware/ESPNow_Block_Network/ESPNow_Block_Network.ino)

Change only `OWNER_NAME` in your local copy. Keep channel `1`,
`MAGIC = 0xB10C2026`, and the 40-byte message layout the same across the block.
The older 8-byte and 28-byte versions cannot exchange results with this version.

The sketch counts unique other MAC addresses since startup. It excludes
your own board, keeps previously heard addresses until restart, and prints
the summary every five seconds. Names are entered by owners; MAC addresses
are taken from received packets. Names are optional extras in the submission.
There is no block-name filter, so follow the room and window rules.

## Current checks

The owner-name sketch compiled for ESP32 Dev Module and ESP32S3 Dev Module
(native USB CDC enabled) with ESP32 Arduino core 3.3.12. This confirms compilation
only. Each student still needs to test their board and collect their own evidence.
Pending results are not completed submissions.

## Shared submission link

https://github.com/xavieryyyyyy/esp32_espnow_block_network

Submit this URL, not your fork or pull request. First check that your folder
and both evidence files are present in the shared repository.
