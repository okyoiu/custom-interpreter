#pragma once
#include <string>

// mapping human-readable names to a set of related options
enum class TokenType {
    PLUS, MINUS, SEMICOLON, EQUAL,
    IDENTIFIER, NUMBER,
    LET, PRINT,
    END_OF_FILE, ILLEGAL
};

// atomic unit of the language being built rn
struct Token {
    TokenType type;
    std::string lexme;  // actual raw test
    int line;           // the line on where we can print the "Error on ln" in the future
};