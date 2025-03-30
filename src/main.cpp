#include <iostream>
#include <string>

void run_shell() {
    std::string line;

    while (true) {
        std::cout << "cppsh> ";
        std::getline(std::cin, line);
        if (line.empty()) continue;
        if (line == "exit") break;

        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) tokens.push_back(token);

        std::vector<char*> args;
        for (auto& s : tokens) args.push_back(&s[0]);
        args.push_back(nullptr);

        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args.data());
            perror("exec failed");
            exit(1);
        } else {
            wait(nullptr);
        }
    }
}

int main() {
    run_shell();
    return 0;
}
