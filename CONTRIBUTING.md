# Submit your results

Use your own GitHub account so your commits and pull request belong to you.
You can contribute through a fork without being given write access to this
repository. Change only your own top-level `lastname_firstname` folder.

## 1. Fork the repository

1. Open [the class repository](https://github.com/xavieryyyyyy/esp32_espnow_block_network).
2. Click **Fork**, select your account, and create your copy.
3. If you already have a fork, use **Sync fork** to get the latest shared files.
4. In your fork, create a branch such as `results/lastname_firstname`.

Your fork is your working copy. The class repository is where the final
evidence must appear.

## 2. Prepare your three files

Create this folder on your computer, replacing the example name with yours:

```text
lastname_firstname/
├── README.md
├── serial-monitor.png
└── serial-monitor-30s.mp4
```

Copy the [student README template](docs/student-readme-template.md) into
your folder. Fill in your name, board MAC, count, every MAC heard, and your
actual block-window date and time. Add your screenshot and 30-second video
from that window. See the [evidence instructions](docs/block-session.md).

Your local `OWNER_NAME` edit is for uploading to your board. Do not include
that edit in your pull request or replace the shared sketch with your copy.

## 3. Add the folder to your fork

1. Open your branch in your fork and return to its top-level file list.
2. Choose **Add file → Upload files**.
3. Drag your whole `lastname_firstname` folder into the upload area.
4. Check that GitHub shows each file inside your own folder, not loose at
   the repository root or nested inside another student's folder.
5. Commit the files with a message such as `Add my ESP-NOW results`.

If you use Git locally, stage only your results folder. Make sure your commit
email is connected to your own GitHub account or is your GitHub-provided
`noreply` address. Do not use a classmate's Git name or email.

## 4. Open a pull request

1. In your fork, choose **Contribute → Open pull request**.
2. Set the base repository to `xavieryyyyyy/esp32_espnow_block_network`
   and the base branch to `main`.
3. Set the head to your fork and your results branch.
4. Use a title such as `Add ESP-NOW results: lastname_firstname`.
5. Complete the checklist and inspect **Files changed**. Every changed
   file should be inside your own results folder.
6. Click **Create pull request**. If the owner requests corrections,
   commit them to the same branch; the pull request will update.

The owner will review the evidence and merge the pull request. Do not
change another student's folder to resolve a conflict. Ask for help if a
conflict affects anything outside your own folder.

## 5. Check the shared repository

After the pull request is merged, open the shared repository. Check that
your README, screenshot, and video are all there and open correctly.
An unmerged pull request is not a finished submission.

Submit this same URL as the rest of your block:

https://github.com/xavieryyyyyy/esp32_espnow_block_network

## Contributor credit

GitHub credits commits through their authorship. When your own commits are
merged into `main`, GitHub can link them to your account and show you as a
contributor. Opening a pull request alone does not add your commits to `main`.
The commit email must be connected to your GitHub account. Contributor displays
can take time to update, and the contributors graph shows the top 100 authors.

See [GitHub's contributor guide](https://docs.github.com/en/repositories/viewing-activity-and-data-for-your-repository/viewing-a-projects-contributors)
and [contribution troubleshooting](https://docs.github.com/en/account-and-profile/how-tos/contribution-settings/troubleshooting-missing-contributions).

Contributor credit does not give you collaborator, write, or admin access.
Those permissions are managed separately by the owner. Forks and pull requests
let everyone submit their own work without needing those permissions.
