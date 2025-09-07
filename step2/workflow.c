#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>

#define WATCH_DIR "/tmp"

int initialize_inotify() {
    int fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int add_watch(int fd, const char *path) {
    int wd = inotify_add_watch(fd, path, IN_ALL_EVENTS);
    if (wd < 0) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }
    return wd;
}

int main() {
    printf("Step 2 – Design Workflow Implementation\n");

    int fd = initialize_inotify();
    int wd = add_watch(fd, WATCH_DIR);

    printf("Monitoring directory: %s\n", WATCH_DIR);

    // Event handling will be implemented in Step 3

    inotify_rm_watch(fd, wd);
    close(fd);

    return 0;
}
