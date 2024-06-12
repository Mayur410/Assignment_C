#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_FILE_PATH "/home/vlsi_S1/.bash_history"
#define MAX_LINE_LENGTH 1024

void print_usage(const char *program_name) {
    printf("Usage: %s [number_of_entries]\n", program_name);
}

int main(int argc, char *argv[]) {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    int lines_to_display = -1; // Display all lines by default

    if (argc > 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (argc == 2) {
        lines_to_display = atoi(argv[1]);
        if (lines_to_display <= 0) {
            print_usage(argv[0]);
            return 1;
        }
    }

    file = fopen(HISTORY_FILE_PATH, "r");
    if (!file) {
        perror("Failed to open history file");
        return 1;
    }

    // Count the total number of lines in the history file
    while (fgets(line, sizeof(line), file)) {
        line_count++;
    }

    // Reset the file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    int start_line = 0;
    if (lines_to_display > 0 && lines_to_display < line_count) {
        start_line = line_count - lines_to_display;
    }

    line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line_count >= start_line) {
            printf("%d %s", line_count + 1, line);
        }
        line_count++;
    }

    fclose(file);
    return 0;
}

