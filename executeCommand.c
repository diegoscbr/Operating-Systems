#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "executeCommand.h"
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
        // Execute the command
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            execlp(line, line, NULL);
            exit(0);
        } else if (pid > 0) {
            // Parent process
            wait(NULL);
        } else {
            // Fork failed
            printf("Error creating child process.\n");
        }
    }

    free(line);
    fclose(file);
}

int main(){
    runBatchMode("batchfile.txt");
    return 0;                               
}
     
