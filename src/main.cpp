#include <iostream>
#include <cstdlib>
#include "repl.h"
#include "logger.h"

int main(int argc, char* argv[]) {
    // Initialize logging
    Logger::initialize();
    
    Logger::info("Starting anashell v0.1.0");
    
    try {
        // Create and run REPL
        REPL repl;
        int exit_code = repl.run();
        
        Logger::info("Exiting anashell with code: {}", exit_code);
        return exit_code;
    } catch (const std::exception& e) {
        Logger::error("Fatal error: {}", e.what());
        return EXIT_FAILURE;
    }
}
