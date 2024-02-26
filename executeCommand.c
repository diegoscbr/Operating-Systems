#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

int parseCommands(char *arguments[], int arg_count, char *commands[]) {
    int command_count = 0;
    char *command = (char *)malloc(MAX_COMMAND_LENGTH * sizeof(char));
    command[0] = '\0';

    for (int i = 0; i < arg_count; i++) {
        if (strcmp(arguments[i], "|") == 0) {
            // End of command, add it to the commands array
            commands[command_count++] = command;
            command = (char *)malloc(MAX_COMMAND_LENGTH * sizeof(char));
            command[0] = '\0';
        } else {
            // Part of command, append it to the command string
            strcat(command, arguments[i]);
            strcat(command, " ");
        }
    }

    // Add the last command to the commands array
    commands[command_count++] = command;

    return command_count;
}
//executeCommandswithRedirectionAndPipes implementation
void executeCommandWithRedirectionAndPipes(char *commands[], int command_count) {
    int p[2];
    pid_t pid;
    int fd_in = 0;

    for (int i = 0; i < command_count; i++) {
        pipe(p);
        if ((pid = fork()) == -1) {
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            dup2(fd_in, 0); // change the input according to the old one
            if (i < command_count - 1) {
                dup2(p[1], 1);
            }
            close(p[0]);
            // execute the command here
        } else {
            wait(NULL);
            close(p[1]);
            fd_in = p[0]; // save the input for the next command
        }
    }
}


//executeCommand implementation
void executeCommand(char *arguments[], int arg_count) {
    
 // Parse the command line into separate commands
    char *commands[MAX_COMMANDS];
    int command_count = parseCommands(arguments, arg_count, commands);

    // If the command line includes redirection or pipes, execute the commands with redirection and pipes
    if (command_count > 1) {
        executeCommandWithRedirectionAndPipes(commands, command_count);
    } else{
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
            printf("Executing command with arguments: ");
            for (int i = 0; i < arg_count; i++) {
                printf("%s ", arguments[i]);
            }
            printf("\n");
            wait(NULL);
        
        
    } 
    }//end of else
    
}
