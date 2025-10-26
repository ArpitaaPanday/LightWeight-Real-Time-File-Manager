#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#define EVENT_BUF_LEN 1024 * (sizeof(struct inotify_event) + 16)

void log_event(struct inotify_event *event) {
    time_t t = time(NULL);
    printf("[%s] ", ctime(&t));
    if (event->mask & IN_CREATE)
        printf("File created: %s\n", event->name);
    if (event->mask & IN_MODIFY)
        printf("File modified: %s\n", event->name);
    if (event->mask & IN_DELETE)
        printf("File deleted: %s\n", event->name);
    if (event->mask & IN_MOVED_FROM)
        printf("File moved from: %s\n", event->name);
    if (event->mask & IN_MOVED_TO)
        printf("File moved to: %s\n", event->name);
}

int main() {
    int fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    int wd = inotify_add_watch(fd, "/tmp", IN_CREATE | IN_MODIFY | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);
    if (wd < 0) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    char buffer[EVENT_BUF_LEN];
    printf("Monitoring /tmp...\n");

    while (1) {
        int length = read(fd, buffer, EVENT_BUF_LEN);
        if (length < 0) {
            perror("read");
            break;
        }

        int i = 0;
        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (event->len) {
                log_event(event);
            }
            i += sizeof(struct inotify_event) + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
    return 0;
}