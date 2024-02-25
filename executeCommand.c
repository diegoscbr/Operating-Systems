#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void runBatchMode(const char* batchFile) {
    FILE* file = fopen(batchFile, "r");
    if (file == NULL) {
        printf("Error opening batch file.\n");
        return;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) {
        // Remove newline character if present
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        // Execute the command
        pid_t pid = fork();

        if (pid == -1) {
            // Fork failed
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp(line, line, NULL);
            // execlp() will only return if an error occurs
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }

    free(line);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <batchfile>\n", argv[0]);
        return 1;
    }

    runBatchMode(argv[1]);
    return 0;
}

