#include <iostream>
#include <string>
#include "lexer/Token.h"

void run() {
    std::string line;

    // the REPL: Read, Eval, Print, Loop
    while (true) {
        std::cout << ">> ";

        // if there is no get line input, or if exit, then it leaves
        if (!std::getline(std::cin, line) || line == "exit") {
            std::cout << "\nExiting interpreter...\n";
            break;
        }

        // ignoring the empty lines
        if (line.empty()) continue;

        std::cout << "Processing: " << line << "\n";
    }
}

int main() {
    std::cout << "Custom Scripting Language Interpreter v0.1\n";
    std::cout << "Type 'exit' to quite.\n";
    run();
    return 0;
}
