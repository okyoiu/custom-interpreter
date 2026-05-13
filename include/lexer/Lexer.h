#pragma once
#include "Token.h"
#include <string>
#include <vector>

class Lexer {
    public:
        // 'explicit' prevents accidental implicit conversions 
        // (e.g., stops `Lexer l = "string";`) (sets lock on custom-built classes)        
        explicit Lexer(std::string source);
        std::vector<Token> tokenize();


    private:
        const std::string m_source;
        std::vector<Token> m_tokens;

        std::size_t m_start = 0; // marks the first character (index-based)
        std::size_t m_current = 0; // the marker that actually moves (index-based)
        int m_line = 1; // keeping track of which line im currently on (default starts @ 1)

        // scanning engine (reads left-right)
        void scanToken();
        void scanString();
        void scanNumber();
        void scanIdentifierOrKeyword();

        // low-level primitives
        char advance();             // Return the character at m_current, and THEN increment m_current by 1
        char peek() const;          // Return m_source[m_current], without incrementing
        char peekNext() const;      // Return m_source[m_current + 1] without incrementing
        bool match(char expected);  // If peek() == c, calls advance() and returns true else false
        bool isAtEnd() const;       // Return the character at m_current, and THEN increment m_current by 1

        // token construction
        void addToken(TokenType type);  
        void addToken(TokenType type, std::string literal);

        // error handling
        void lexError(const std::string& message) const;

        // some helper functions
        bool isAlpha(char c) const;
        bool isAlphaNumeric(char c) const;
};