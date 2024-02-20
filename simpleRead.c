#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if the file path is provided as a command-line argument
    //if not, it is a readNWrite to stdout
    if (argc < 2) {
        // Prompt for user input
        char line[256];
        printf("Enter text: ");
        fgets(line, sizeof(line), stdin);

        // Print the input to stdout
        printf("Input: %s", line);
        return 0;
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
