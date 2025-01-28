#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

int main() {
    char *command = NULL; // Use dynamic allocation for getline
    size_t len = 0; // Used by getline()
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        printf("$ ");
        fflush(stdout);

        // Read user input dynamically
        ssize_t nread = getline(&command, &len, stdin);
        if (nread == -1) { // Check for EOF or error
            perror("getline");
            break;
        }

        // Remove the newline character at the end
        if (command[nread - 1] == '\n') {
            command[nread - 1] = '\0';
        }

        // Parse the command into arguments using strtok()
        int i = 0;
        char *token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the arguments array

        // Handle empty input
        if (args[0] == NULL) {
            continue;
        }

        // Create a child process to execute the command
        pid = fork();
        if (pid == -1) {
            perror("fork");
            continue;
        }

        if (pid == 0) { // Child process
            execvp(args[0], args); // Execute the command
            perror("execvp"); // If execvp fails
            exit(EXIT_FAILURE);
        } else { // Parent process
            wait(&status); // Wait for the child process to complete
        }
    }

    // Free dynamically allocated memory
    free(command);

    return 0;
}
