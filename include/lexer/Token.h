#pragma once
#include <string>

// mapping human-readable names to a set of related options
enum class TokenType {
    // --- Single-character tokens ---
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // --- One or two character tokens ---
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // --- Literals (Data) ---
    IDENTIFIER, STRING_LITERAL, NUMBER,

    // --- Keywords ---
    // (We will add things like IF, WHILE, RETURN here later)
    LET,

    PRINT, END_OF_FILE, ILLEGAL
};

// atomic unit of the language being built rn
struct Token {
    TokenType type;
    std::string lexeme;  // actual raw test
    int line;           // the line on where we can print the "Error on ln" in the future
};