#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void executeCommand(char *arguments[], int arg_count) {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return;
    }

    if (pid == 0) {
        // Child process
        if (execvp(arguments[0], arguments) < 0) {
            fprintf(stderr, "Exec failed\n");
            exit(1);
        }
    } else {
        // Parent process
        printf("Executing command with arguments:\n");
        for (int i = 0; i < arg_count; i++) {
            printf("Argument %d: %s\n", i, arguments[i]);
        }
        wait(NULL);
    }
}