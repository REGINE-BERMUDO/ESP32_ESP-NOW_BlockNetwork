# Reviewing class submissions

Keep each student's contribution tied to their own GitHub account and
results folder. Students can use forks and pull requests without being
given write access to the class repository.

## Before merging

Check the pull request's **Files changed** tab:

- Every change belongs to the student's own top-level `lastname_firstname` folder.
- The README has their name, board MAC, count, every MAC heard, and actual
  window date and time. The written MAC list agrees with the count.
- The screenshot clearly shows the count and MAC addresses from their board.
- The screen recording is 30 seconds long and shows Serial Monitor.
- The evidence and written results agree. Pending values are not a completed submission.
- The shared firmware and other students' folders are unchanged.
- Evidence filenames use the student's surname, with the real extension,
  and both links open from the personal README.

Ask the student for corrections in the pull request. They should update
their own branch. Evidence review does not replace the instructor's decision
about attendance or whether a board was present during the window.

## Merge and record the submission

1. Prefer **Merge pull request** when available so the student's original
   commits and authorship stay visible. Do not download their files and
   recommit them under your own name.
2. After merging, open the personal folder in the shared repository. Check
   that the README, screenshot, and video open correctly.
3. Add the student and their actual GitHub account to
   [the student directory](../students/README.md). Update the entry when
   files are added or corrected. Use factual descriptions such as
   `Pending` or `README, screenshot, and video present`; these are not grades.
4. Tell the student to submit the shared repository URL.

Do not edit a student's results or another student's folder to resolve a
conflict. Ask the author to correct their own files. Coordinate any shared
firmware change separately so the whole block keeps compatible code.

## Contributor credit and access

There is no separate approval button for contributor credit. GitHub uses
the authorship of commits merged into `main`. Students need a commit email
connected to their own GitHub account. The contributors graph may take time
to refresh and shows the top 100 authors.

Opening a pull request alone does not add its commits to the default branch.
See [GitHub's contributor guide](https://docs.github.com/en/repositories/viewing-activity-and-data-for-your-repository/viewing-a-projects-contributors)
and [missing-contribution help](https://docs.github.com/en/account-and-profile/how-tos/contribution-settings/troubleshooting-missing-contributions).

Being credited as a contributor does not grant collaborator, write, or admin
access. Add someone as a collaborator only when you intend to grant that
permission; it is not needed just to accept their results pull request.

The repository owner also uses a personal results branch and PR. They do
not need to fork their own repository. See [the contribution guide](../CONTRIBUTING.md).

Return to [the class starting page](../README.md).
