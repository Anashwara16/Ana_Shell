#ifndef SHELL_HPP
#define SHELL_HPP

#include <vector>
#include <string>

// Function declarations
std::vector<std::string> parse_command(const std::string& input);
int execute_command(const std::vector<std::string>& args);
bool is_builtin(const std::string& command);
int handle_builtin(const std::vector<std::string>& args);

#endif // SHELL_HPP