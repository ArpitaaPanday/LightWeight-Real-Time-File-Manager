# Step 1: Research & Setup

## Objectives:
- Understand how inotify works using `inotify_init`, `inotify_add_watch`, and `read`.
- Scope the project to start with monitoring a single directory.
- Prepare the Linux test environment.

## Key Learnings:
- `inotify_init()` initializes the inotify instance and returns a file descriptor.
- `inotify_add_watch()` adds a directory or file to be monitored.
- `read()` blocks and waits for events to occur in the watched directory.

## Environment Setup:
- Ensure GCC and necessary libraries are installed.
- Use a Linux environment such as Ubuntu or Debian.
- Test with sample directories like `/tmp` or a created folder.