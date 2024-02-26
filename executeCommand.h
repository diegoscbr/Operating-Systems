#ifndef EXECUTE_COMMAND_H
#define EXECUTE_COMMAND_H

void executeCommand(char *arguments[], int arg_count);
void executeCommandWithRedirection(char *commands[], int command_count);
int parseCommands(char *arguments[], int arg_count, char *commands[]);

#endif // EXECUTE_COMMAND_H