#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: %s [optional_command]\n", argv[0]);
        return 1;
    }

    // Display prompt
    printf("gush> ");

    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    char *token;
    pid_t pid;
    int status;

    while (fgets(command, MAX_COMMAND_LENGTH, stdin) != NULL) {
        // Remove trailing newline
        command[strcspn(command, "\n")] = 0;

        // Tokenize the command
        int arg_count = 0;
        token = strtok(command, " ");
        while (token != NULL && arg_count < MAX_ARGUMENTS - 1) {
            arguments[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        arguments[arg_count] = NULL;

        // Check for the quit command
        if (strcmp(arguments[0], "./quit") == 0) {
            printf("Exiting gush shell...\n");
            break;
        }

        // Fork a child process
        pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork failed\n");
            return 1;
        } else if (pid == 0) {
            // Child process
            if (execvp(arguments[0], arguments) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }

        // Display prompt again
        printf("gush> ");
    }

    return 0;
}
