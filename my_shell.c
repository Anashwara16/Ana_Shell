#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

int main() {
    char *command = NULL; 
    size_t len = 0; 
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        printf("$ ");
        fflush(stdout);

        ssize_t nread = getline(&command, &len, stdin);
        if (nread == -1) { 
            perror("getline");
            break;
        }

        if (command[nread - 1] == '\n') {
            command[nread - 1] = '\0';
        }

        int i = 0;
        char *token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue;
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            continue;
        }

        if (pid == 0) { // Child process
            execvp(args[0], args); // Execute command
            perror("execvp");
            exit(EXIT_FAILURE);
        } else { // Parent process
            wait(&status); // Wait for the child process to complete
        }
    }

    free(command);

    return 0;
}
