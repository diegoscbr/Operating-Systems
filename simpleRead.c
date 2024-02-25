#include <stdio.h>
#include <string.h>

#define MAX_CHAR_LEN 80

void copyInputLine(FILE* input, FILE* output) {
    char line[MAX_CHAR_LEN + 1]; // +1 for null terminator
    if (fgets(line, sizeof(line), input) != NULL) {
        // Remove trailing newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        // Cut off at MAX_CHAR_LEN characters
        if (len > MAX_CHAR_LEN) {
            line[MAX_CHAR_LEN] = '\0';
        }
        fprintf(output, "%s\n", line);
    }
}

int main(int argc, char* argv[]) {
    FILE* output = stdout; // default to stdout
    char outputFileName[100] = "";
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            strncpy(outputFileName, argv[i + 1], sizeof(outputFileName) - 1);
            outputFileName[sizeof(outputFileName) - 1] = '\0'; // Ensure null termination
            i++; // Move to the next argument
        }
    }

    if (outputFileName[0] != '\0') {
        output = fopen(outputFileName, "w");
        if (output == NULL) {
            fprintf(stderr, "Error: Unable to open output file '%s'.\n", outputFileName);
            return 1;
        }
    }

    copyInputLine(stdin, output);

    if (output != stdout) {
        fclose(output);
    }

    return 0;
}

