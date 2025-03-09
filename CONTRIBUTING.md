# Contributing Guidelines
We are excited to have you contribute to our project! Please follow the steps below to help make the process as smooth as possible.

## How to Contribute
You can find areas where you can contribute by checking out the [Issues](https://github.com/emomaxd/zenith/issues) and [Projects](https://github.com/emomaxd/zenith/projects) pages.

### Reporting Bugs
If you find a bug, please open an [issue](https://github.com/emomaxd/zenith/issues) on GitHub. Be sure to include:
- A description of the bug
- Steps to reproduce the bug
- Any relevant error messages or logs

### Feature Requests
If you'd like to suggest a new feature, open an issue and describe the feature in detail. Please explain why you think it would be useful to the project.

## Making Changes

**Fork and Branch**: Fork the repo and create a branch (e.g., fix/bug-123 or feature/new-syntax).
**Code Style**: Follow LLVM’s Coding Standards:
   - Run clang-format -i <file> (uses .clang-format in the repo).
   - Max 80 columns, spaces (4), C++17 conventions.
**Commits**: Write clear messages:

```text
Add support for while loops in Zenith

- Implemented loop parsing in src/parser.cpp
- Added IR emission in src/codegen.cpp
- New test in test/loop_test.cpp
```

If your commit resolves a **reported issue**, mention it in the PR description (not the title or commit message) using GitHub's closing keywords like "Fixes #1234". This will automatically close the issue when the PR is merged. While it might be easier to add it to the commit message, it can flood the issue tracker and distract from the main thread.

Scope: Keep PRs focused—one change per PR.

## Control your commits
Try to make simple PRs that handle one specific topic. Just like for reporting issues, it's better to open 3 different PRs that each address a different issue than one big PR with three commits. This makes it easier to review, approve, and merge the changes independently.

When updating your fork with upstream changes, please use git pull --rebase to avoid creating "merge commits". Those commits unnecessarily pollute the git history when coming from PRs.

Also try to make commits that bring the project from one stable state to another stable state, i.e. if your first commit has a bug that you fixed in the second commit, try to merge them together before making your pull request. This includes fixing build issues or typos, adding documentation, etc.

## License
By contributing to this project, you agree that your contributions will be licensed under the project's existing license.

Thank you for contributing! 
