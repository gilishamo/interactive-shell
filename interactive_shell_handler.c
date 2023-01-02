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

// TODO free interactive shell

void handle_copy(char* src, char* dst) {
    FILE* srcFile = fopen(src, "r");
    if (srcFile == NULL) {
        printf("failed to open source file\n");
        goto cleanup;
    }
    FILE* dstFile = fopen(dst, "w+"); // wil override the dst file
    if (dstFile == NULL) {
        printf("failed to open destionation file\n");
        goto cleanup;
    }

    char c;
    while ((c = fgetc(srcFile)) != EOF) {
        fputc(c, dstFile);
    }

    cleanup:
    fclose(srcFile);
    fclose(dstFile);
    printf("copied source file to destination");
}

void start_shell() {
    char command[COMMAND_MAX_LEN];

    printf("Starting interactive shell, send 'quit' to quit the program\n");

    do {
        printf("# ");
        // read input until new line
        if (fgets(command, COMMAND_MAX_LEN, stdin) != NULL)  { // TODO fix case of input > COMMAND_MAX_LEN
            int index = strlen(command)-1;
            *(command+index) == '\n' ? *(command+index) = '\0' : printf("command is too long"); 
            perform_command(command);
        }
        printf("\n");
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
    } else if (strcmp(*command_split, "copy") == 0) {
        // todo handle copy
        if (*(command_split+1) == NULL || *(command_split+2) == NULL){
            printf("usage: 'copy <src> <dst>'\n");
            goto cleanup;
        } 
        handle_copy(*(command_split+1), *(command_split+2));
    // } else if (strcmp(*command_split, "move") == 0) {
    //     // todo handle move
    // } else if (strcmp(*command_split, "tasklist") == 0) {
    //     // todo handle tasklist
    } else if (strcmp(*command_split, "quit") == 0) {
        // quittign
        // left blamk intentionally 
    } else {
        printf("command '%s' is not supported", *command_split);
    }

    cleanup:
    free_string_arr(command_split);
}