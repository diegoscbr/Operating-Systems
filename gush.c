#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "histList.c"


#define MAX_ARGUMENTS 10
Node* commandHistory = NULL;

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: %s [optional_command]\n", argv[0]);
        return 1;
    }

    // Display prompt
    printf("gush> ");

    char * command = NULL;
    size_t len = 0;
    ssize_t read;
    char *arguments[MAX_ARGUMENTS];
    char *token;
    pid_t pid;
    int status;

  while ((read = getline(&command, &len, stdin)) != -1) {
    // Remove trailing newline
        command[read - 1] = '\0';

        // Tokenize the command
        int arg_count = 0;
        token = strtok(command, " ");
        while (token != NULL && arg_count < MAX_ARGUMENTS - 1) {
            arguments[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        arguments[arg_count] = NULL;

        // Check for the exit command
        if (strcmp(arguments[0], "exit") == 0) {
            printf("Exiting G.eorgetown U.niversity S.H.ell...\n");
            break;
        }

        // Check for the history command
        if (strcmp(arguments[0], "history") == 0) {
            printList(commandHistory);
            continue;
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
            insertAtEnd(&commandHistory, command);
            continue;
        }

        // Display prompt again
        printf("gush> ");
    }
     freeList(&commandHistory); // Free the list
    return 0;
}
