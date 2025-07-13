#include "shell.hpp"
#include <iostream>
#include <string>
#include <vector>

/**
 * Main REPL (Read-Eval-Print Loop) for the minishell
 */
int main() {
    std::string input;
    
    std::cout << "Welcome to MiniShell!\n";
    std::cout << "Type 'exit' to quit.\n\n";
    
    while (true) {
        // Display prompt
        std::cout << "minishell> ";
        
        // Read user input
        if (!std::getline(std::cin, input)) {
            // Handle Ctrl+D (EOF)
            std::cout << "\nGoodbye!\n";
            break;
        }
        
        // Skip empty lines or whitespace-only input
        if (input.empty() || input.find_first_not_of(" \t\n\r") == std::string::npos) {
            continue;
        }
        
        // Parse command into tokens
        std::vector<std::string> args = parse_command(input);
        
        if (args.empty()) {
            continue;
        }
        
        // Execute command
        int result = execute_command(args);
        
        // If execute_command returns -1, it means exit was called
        if (result == -1) {
            break;
        }
    }
    
    return 0;
}