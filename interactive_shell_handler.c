#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interactive_shell_handler.h"
#include "utils.h"

// forward declarations
void perform_command(char *command);
char** split_command(char *command);

typedef struct _interactiveShellHandler {
    char* command; 
} interactiveShellHandler;

interactiveShellHandler* allocate_interactive_shell_handler() {
    interactiveShellHandler *shell;

    shell = (interactiveShellHandler*)malloc(sizeof(interactiveShellHandler));
    if (shell == NULL) {
        printf("ERROR: failed to allocate memmory\n");
        exit(1);
    } 

    return shell;
}

void start_shell() {
    char command[COMMAND_MAX_LEN];

    printf("Starting interactive shell, send 'quit' to quit the program\n");

    do {
        printf("# ");
        // read input until new line
        if (fgets(command, COMMAND_MAX_LEN, stdin) != NULL)  { // TODO fix case of input > COMMAND_MAX_LEN
            perform_command(command);
        }
    } while (strcmp(command, "quit") != 0);
   
    printf("quitting...\n");
}

char** split_command(char *command) {
    return split_str(command, " ");
}

void perform_command(char *command) {
    char **command_split = split_command(command);

     if (strcmp(*command_split, "echo") == 0) {
        char* message = join(command_split+1, " ");
        printf("%s", message);
    }

    free_string_arr(command_split);
}