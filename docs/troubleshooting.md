# Common problems

## No Serial Monitor output

Check the board profile and current USB port, open Serial Monitor at
115200 baud, then press and release EN/RESET. If you use an ESP32-S3 through
its native USB connection, check **USB CDC On Boot**. Use a USB data cable.

## The sketch asks me to set OWNER_NAME

Replace `lastname_firstname` near the top of your local sketch with your own
name. Keep the quotation marks and semicolon. Verify and upload again.
Do not commit that local edit over the shared firmware.

## My board hears zero other boards

Zero is normal when testing alone. With classmates nearby, check that all
boards are powered, using channel `1`, `MAGIC = 0xB10C2026`, and the same
40-byte owner-name sketch. The older 8-byte and 28-byte versions are incompatible.
Keep the boards within about five metres and wait at least 30 seconds.
Check that no board has joined a router or hotspot.

## The board keeps restarting or reports brownout

A brownout indicates a supply-voltage drop. Try a known-good short USB data
cable and a direct computer USB port. Keep the brownout protection enabled.
Fix the power problem before collecting evidence.

## My screenshot count differs from attendance

The sketch counts other MAC addresses it received, not the attendance list.
It also excludes your own board. Read [the results guide](read-results.md)
and keep your actual recorded count.

## My recording is longer than 30 seconds

Keep the original, then export a continuous 30-second copy showing your
Serial Monitor results. Do not alter the displayed results. Confirm that
the exported copy plays and has the intended duration before submitting it.

## My files have a different extension

Keep the real format. Renaming `.jpg` to `.png`, or `.mkv` to `.mp4`, does
not convert a file. Use the real extension in your README links. An MP4
copy is the recommended submission video format.

## My picture or video link is broken

Place the evidence beside your personal README. Check the exact filename,
extension, capitalization, and link. The expected names use your surname:
`lastname_serialmonitor.png` and `lastname_serialmonitor.mp4`.

## GitHub will not upload my file

For browser uploads, files must be no larger than 25 MiB each. A 30-second
screen recording at a modest resolution and bitrate is usually easier to
upload. If it exceeds the browser limit, export a smaller readable copy or
ask the owner for help with Git. Do not replace the video with a screenshot.
See [GitHub's file-size guidance](https://docs.github.com/en/repositories/working-with-files/managing-large-files/about-large-files-on-github).

## I cannot fork this repository

If you own it, create a results branch directly in the class repository and
open a PR to `main`. Classmates normally use their own forks. The
[contribution guide](../CONTRIBUTING.md) explains both paths.

## My PR includes files outside my folder

Remove those unintended changes from your branch before requesting review.
Your results PR should contain only your own `lastname_firstname` folder.
Ask for help before resolving a conflict in someone else's files.

Return to [the class starting page](../README.md).
