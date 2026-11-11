# Submit your own results

Use your own GitHub account. Your pull request should change only your
top-level `lastname_firstname` folder. You do not need write access to the
class repository to contribute through a fork.

## 1. Prepare your folder on your computer

Create a folder using your own name. Copy the
[student README template](docs/student-readme-template.md) into it and save
the copy as `README.md`.

```text
lastname_firstname/
├── README.md
├── lastname_serialmonitor.png
└── lastname_serialmonitor.mp4
```

Replace `lastname` in both evidence filenames with your surname. For example,
`cruz_juan` would use `cruz_serialmonitor.png` and `cruz_serialmonitor.mp4`.
These names are examples, not another student's evidence.

Fill in your actual results, list every MAC address your board heard, and
link the two evidence files in your README. Keep the actual file extension:
changing `.jpg` to `.png` does not convert an image. If your evidence has a
different format, use its real extension and update the README links.

The screenshot and 30-second video must come from your board during your
approved window. See [the evidence guide](docs/block-session.md). Keep your
original recordings elsewhere if you make a 30-second submission clip.

Your local `OWNER_NAME` change belongs on your board. Leave it out of your
results PR so the shared sketch keeps its placeholder for the next student.

## 2. Get your own working branch

### Classmates using a fork

1. Open [the class repository](https://github.com/xavieryyyyyy/esp32_espnow_block_network).
2. Click **Fork**, select your own account, and create the fork.
3. If you already have a fork, use **Sync fork** to bring it up to date.
4. In your fork, open the branch menu, type `results/lastname_firstname`,
   and create that branch from `main`.

### Repository owner or students with write access

Create `results/lastname_firstname` directly in the class repository from
`main`. The owner cannot fork their own repository. Use a separate results
branch and open a PR to `main`, following the same evidence checklist.

## 3. Upload your folder to that branch

1. Check that the selected branch is your results branch.
2. At the top-level file list, choose **Add file → Upload files**.
3. Drag your whole `lastname_firstname` folder into the upload area.
4. Check the paths. All three files must be inside your own folder, not
   loose at the root, inside `students`, or inside another student's folder.
5. Commit with a message such as `Add my ESP-NOW results`.

If you use local Git instead, stage only your folder. Use a commit email
connected to your GitHub account or your GitHub-provided `noreply` address.
Do not use someone else's name or email for your commits.

## 4. Open the pull request

1. Choose **Contribute → Open pull request** in your fork, or open the
   repository's **Pull requests** tab and choose **New pull request**.
2. Set the **base repository** to `xavieryyyyyy/esp32_espnow_block_network`
   and the **base branch** to `main`.
3. Set the **head repository** to your fork, or the class repository if
   you created the branch there. Select your `results/lastname_firstname` branch.
4. Use the title `Add ESP-NOW results: lastname_firstname` and fill in the checklist.
5. Open **Files changed**. Every file should belong to your own results folder.
6. Click **Create pull request** and wait for review.

If corrections are requested, edit the same branch and commit again. The
existing PR updates automatically. Do not create a new PR for each correction.
Ask for help if a conflict involves another student's files.

## 5. Check the merge and submit the shared link

After the PR is merged, open `main` in the class repository. Make sure your
folder, completed README, screenshot, and video are present and open correctly.
A fork or unmerged PR alone does not put your evidence in the shared repository.

Submit this URL in the submission bin:

https://github.com/xavieryyyyyy/esp32_espnow_block_network

## Contributor credit

Students receive credit through their authored commits. When those commits
are merged into `main`, GitHub can link them to the student's account. The
commit email must be connected to that account. Contributor displays may take
time to update, and the contributors graph shows the top 100 authors.

Opening a PR alone does not merge its commits. Contributor credit also does
not grant collaborator, write, or admin access; those permissions are separate.
See [GitHub's contributor guide](https://docs.github.com/en/repositories/viewing-activity-and-data-for-your-repository/viewing-a-projects-contributors)
and [contribution troubleshooting](https://docs.github.com/en/account-and-profile/how-tos/contribution-settings/troubleshooting-missing-contributions).

Return to [the class starting page](README.md).
