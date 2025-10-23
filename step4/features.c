#include <stdio.h>          // FILE, printf, fprintf
#include <stdlib.h>         // exit(), malloc(), free()
#include <string.h>         // strlen(), strcpy()
#include <time.h>           // time_t, time(), ctime()
#include <sys/inotify.h>    // struct inotify_event, IN_CREATE, etc.
#include <unistd.h>         // close()

// Function to log event details into file
void log_event_to_file(struct inotify_event *event, FILE *logfile) {
    time_t t = time(NULL);
    char *time_str = ctime(&t);
    time_str[strlen(time_str) - 1] = '\0'; // Remove newline

    if (event->mask & IN_CREATE)
        fprintf(logfile, "[%s] File created: %s\n", time_str, event->name);
    if (event->mask & IN_MODIFY)
        fprintf(logfile, "[%s] File modified: %s\n", time_str, event->name);
    if (event->mask & IN_DELETE)
        fprintf(logfile, "[%s] File deleted: %s\n", time_str, event->name);
    if (event->mask & IN_MOVED_FROM)
        fprintf(logfile, "[%s] File moved from: %s\n", time_str, event->name);
    if (event->mask & IN_MOVED_TO)
        fprintf(logfile, "[%s] File moved to: %s\n", time_str, event->name);

    fflush(logfile);
}

int main() {
    FILE *logfile = fopen("events.log", "a");
    if (!logfile) {
        perror("Error opening log file");
        return 1;
    }

    printf("Simulating an event log...\n");

    // Allocate memory manually for struct + file name
    const char *filename = "testfile.txt";
    size_t event_size = sizeof(struct inotify_event) + strlen(filename) + 1;
    struct inotify_event *dummy_event = malloc(event_size);

    if (!dummy_event) {
        perror("malloc failed");
        fclose(logfile);
        return 1;
    }

    dummy_event->mask = IN_CREATE;
    strcpy(dummy_event->name, filename);  // Safely copy name into flexible array

    log_event_to_file(dummy_event, logfile);

    free(dummy_event);
    fclose(logfile);

    printf("Event logged successfully.\n");
    return 0;
}