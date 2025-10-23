// Include headers and utility functions as before
// Add functions for recursion, filtering, and file logging

void log_event_to_file(struct inotify_event *event, FILE *logfile) {
    time_t t = time(NULL);
    char *time_str = ctime(&t);
    time_str[strlen(time_str) - 1] = '\0'; // Remove newline
    if (event->mask & IN_CREATE)
        fprintf(logfile, "[%s] File created: %s\n", time_str, event->name);
    // Similar for other events...
}

// Additional functions:
// - scan_subdirectories()
// - add_recursive_watches()
// - filter_by_extension()