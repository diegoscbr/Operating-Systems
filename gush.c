#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "histList.h"

#define GUSH_ROOT "/workspaces/Operating-Systems/"
#define MAX_ARGUMENTS 10
#define MAX_COMMAND_LENGTH 100
char *path[MAX_ARGUMENTS];
int pathCount = 0;

Node* commandHistory = NULL;

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: %s [optional_command]\n", argv[0]);
        return 1;
    }
    /*Batch Mode*/
    else if(argc >1){
        FILE *file = fopen(argv[1], "r"); //open the batch file 
        if (file == NULL) {
            fprintf(stderr, "Error: Could not open file\n");
            return 1;
        }

        
    }
    //Interactive mode
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
            printf("gush> ");
            continue;
        }
            // Check for the cd command
        if (strcmp(arguments[0], "cd") == 0) {
            char *dir = arguments[1];
            if (strcmp(dir, "root") == 0)
            {
                dir = GUSH_ROOT;
            }
            if (chdir(dir) != 0)
            {
                perror("chdir");
            }
            insertAtEnd(&commandHistory, command);
            printf("gush> ");
            continue;
        }
        // Check for the path command
        if (strcmp(arguments[0], "path") == 0)
        {
            // Clear the old path
            pathCount = 0;
            // Add each argument to the path
            for (int i = 1; i < arg_count; i++)
            {
                path[pathCount++] = arguments[i];
            }

            printf("gush> ");
            continue;
        }
    // Search for the command in the directories specified in the path
        char cmd[MAX_COMMAND_LENGTH];
        for (int i = 0; i < pathCount; i++)
        {
            snprintf(cmd, sizeof(cmd), "%s/%s", path[i], arguments[0]);
            if (access(cmd, X_OK) == 0)
            {
                // The command was found in the path
                arguments[0] = cmd;
                break;
            }
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
           // continue;
        }

        // Display prompt again
        printf("gush> ");
    }
     freeList(&commandHistory); // Free the list
    return 0;
}
