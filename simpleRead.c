#include <stdio.h>

int main(int argc, char *argv[]) {
    // Check if the file path is provided as a command-line argument
    if (argc < 2) {
        printf("Please provide the file path as a command-line argument.\n");
        return 1;
    }

    // Open the file for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Read and print each line from the file
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    printf("\n");
    // Close the file
    fclose(file);

    return 0;
}
