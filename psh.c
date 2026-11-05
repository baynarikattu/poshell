#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define ARGS_SIZE 128

/* TODO:
    - add proper PS1
    - add "command not found"
    - add colors
    - add pipes
*/

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            printf("\n");
            break;
        }

        char *args[ARGS_SIZE];
        char *token = strtok(buffer, " \n");
        int i = 0;
        while (token != NULL && i < ARGS_SIZE-1) {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL;

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            return 0;
        } else {
            wait(NULL);
        }
    }
    return 0;
}
