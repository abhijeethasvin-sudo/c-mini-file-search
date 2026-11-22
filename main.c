#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Count non-overlapping matches of a keyword within one line. */
int count_matches(const char *line, const char *keyword) {
    int count = 0;
    size_t length = strlen(keyword);
    if (length == 0) return 0;

    const char *position = line;
    while ((position = strstr(position, keyword)) != NULL) {
        count++;
        position += length;
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3 || argv[2][0] == '\0') {
        fprintf(stderr, "Usage: %s <file.txt> <keyword>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Could not open file");
        return 1;
    }

    char *line = NULL;
    size_t capacity = 0;
    ssize_t bytes_read;
    int line_number = 0;
    int matching_lines = 0;
    int total_matches = 0;

    printf("Searching for \"%s\" in %s\n", argv[2], argv[1]);
    while ((bytes_read = getline(&line, &capacity, file)) != -1) {
        line_number++;
        int matches = count_matches(line, argv[2]);
        if (matches > 0) {
            matching_lines++;
            total_matches += matches;
            printf("Line %d (%d match%s): %s", line_number, matches,
                   matches == 1 ? "" : "es", line);
            if (bytes_read > 0 && line[bytes_read - 1] != '\n') putchar('\n');
        }
    }

    if (ferror(file)) {
        fprintf(stderr, "Error reading file.\n");
        free(line);
        fclose(file);
        return 1;
    }

    printf("Matching lines: %d | Total matches: %d\n", matching_lines, total_matches);
    free(line);
    fclose(file);
    return 0;
}
