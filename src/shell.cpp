#include "shell.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

/**
 * Parse input string into command and arguments
 * @param input: raw input string from user
 * @return vector of strings (command + args)
 */
std::vector<std::string> parse_command(const std::string& input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    
    // Split by whitespace
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

/**
 * Check if command is a built-in command
 * @param command: the command to check
 * @return true if it's a built-in, false otherwise
 */
bool is_builtin(const std::string& command) {
    return (command == "cd" || command == "exit");
}

/**
 * Handle built-in commands (cd, exit)
 * @param args: vector of command arguments
 * @return exit code (0 for success, -1 for exit shell)
 */
int handle_builtin(const std::vector<std::string>& args) {
    const std::string& command = args[0];
    
    if (command == "exit") {
        std::cout << "Goodbye!\n";
        return -1; // Signal to exit shell
    }
    
    if (command == "cd") {
        std::string path;
        
        if (args.size() < 2) {
            // No argument provided, go to home directory
            path = getenv("HOME") ? getenv("HOME") : "/";
        } else {
            path = args[1];
        }
        
        if (chdir(path.c_str()) != 0) {
            perror("cd");
            return 1;
        }
        return 0;
    }
    
    return 1; // Unknown built-in
}

/**
 * Execute external command using fork() and execvp()
 * @param args: vector of command arguments
 * @return exit code of the command
 */
int execute_command(const std::vector<std::string>& args) {
    if (args.empty()) {
        return 0;
    }
    
    // Handle built-in commands
    if (is_builtin(args[0])) {
        return handle_builtin(args);
    }
    
    // Prepare arguments for execvp (needs char* array)
    std::vector<char*> argv;
    for (const auto& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr); // execvp requires null-terminated array
    
    // Fork process
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process: execute the command
        if (execvp(argv[0], argv.data()) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        // Parent process: wait for child to complete
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    } else {
        // Fork failed
        perror("fork");
        return 1;
    }
    
    return 0;
}