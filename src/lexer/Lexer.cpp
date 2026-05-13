#include "lexer/Lexer.h"
#include <cctype>
#include <unordered_map>

// Creating the Constructor
Lexer::Lexer(std::string source) : m_source(std::move(source)) {}


// == Low-level primitives ==
bool Lexer::isAtEnd() const {
    return m_current >= m_source.size();}

char Lexer::advance() {
    return m_source[m_current++];
}

char Lexer::peek() const {
    if (isAtEnd()) {
        return '\0';
    }
    // return the character at m_current (do NOT increment)
    return m_source[m_current];
}

char Lexer::peekNext() const {
    if ((m_current + 1) >= m_source.size()) {
        return '\0';
    }
    // return the character at m_current + 1
    return m_source[m_current + 1];
}

bool Lexer::match(char expected) {
    if (isAtEnd()) {
        return false;
    } else if (m_source[m_current] != expected) {
        return false;
    }
    m_current++;
    return true;
}

// == State Machine Logic == 
std::vector<Token> Lexer::tokenize() {
    while (!isAtEnd()) {
        // reseting the start of our word to wherever we are currently
        m_start = m_current;
        scanToken();
    }

    // Adding the End of File token at the very end
    // FIX: resolved - changed () to {} for the constructor to be built in Aggregate Initialization
    m_tokens.push_back(Token{TokenType::END_OF_FILE, "", m_line}); 
    return m_tokens;
}

void Lexer::scanToken() {
    // stepping forward and grabbing the character
    char c = advance();

    // figuring out what character this is
    switch (c) {
        // --- Single Character Tokens ---
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;

        // One or Two Character Tokens
        case '=': 
        // If the NEXT character is an '=', consume it and make an EQUAL_EQUAL token.
            // Otherwise, leave it alone and just make an EQUAL token.
            if (match('=')) {
                addToken(TokenType::EQUAL_EQUAL);
            } else {
                addToken(TokenType::EQUAL);
            }
            break;

        case '!':
            if (match('=')) {
                addToken(TokenType::BANG_EQUAL);
            } else {
                addToken(TokenType::BANG);
            }
            break;

        case '<':
            if (match('=')) {
                addToken(TokenType::LESS_EQUAL);
            } else {
                addToken(TokenType::LESS);
            }
            break;

        case '>':
            if (match('=')) {
                addToken(TokenType::GREATER_EQUAL);
            } else {
                addToken(TokenType::GREATER);
            }
            break;
        
        case '"':
            scanString();
            break;

        // --- Ignored Characters ---
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace
            break;

        case '\n':
            // Newline character! Increment our line counter.
            m_line++;
            break;

            default:
            if (std::isdigit(c)) {
                scanNumber();
            } else if (isAlpha(c)) {
                // If it starts with a letter, it's a word!
                scanIdentifierOrKeyword();
            } else {
                lexError("Unexpected character.");
            }
            break;
    }
}

// Works with when it encounters a String
void Lexer::scanString() {
    // keeps consuming these characters until we hit the closing quote OR the end of file
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            m_line++;
        }
        advance();
    }

    // ERROR FOUND: if we found an EOF before finding a closing quote
    if (isAtEnd()) {
        lexError("Unterminated String.");
        return;
    }

    // We found the closing quote! So now, we step over it
    advance();

    // Extracting the value
    // m_start is opening quote, m_current is AFTER closing quote
    std::size_t startQuote = m_start + 1; // starting INSIDE the quotes
    std::size_t lengthInsideQuotes = m_current - m_start - 2; // Starting cut from inside the string and cutting the rest out

    // note: substr is something that cuts the string to only include what it starts @ and how many characters it includes
    std::string value = m_source.substr(startQuote, lengthInsideQuotes);

    // adding the token
    addToken(TokenType::STRING_LITERAL, value);
}


void Lexer::scanNumber() {
    // 1. Keep eating characters as long as they are numbers (0-9)
    while (std::isdigit(peek())) {
        advance();
    }

    // 2. Look for a fractional part (The Two-Character Lookahead!)
    // We ONLY eat the '.' if the character immediately after it is ALSO a number.
    if (peek() == '.' && std::isdigit(peekNext())) {
        // Eat the '.'
        advance();

        // Eat the rest of the decimal numbers
        while (std::isdigit(peek())) {
            advance();
        }
    }

    // 3. Extract the string
    std::size_t length = m_current - m_start;
    std::string value = m_source.substr(m_start, length);

    // 4. Add the token
    addToken(TokenType::NUMBER, value);
}

// A dictionary mapping strings to their specific Token Types
static const std::unordered_map<std::string, TokenType> KEYWORDS = {
    {"let", TokenType::LET},
};
bool Lexer::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Lexer::isAlphaNumeric(char c) const {
    return isAlpha(c) || std::isdigit(c);
}

void Lexer::scanIdentifierOrKeyword() {
    // 1. Keep eating characters as long as they are letters or numbers
    while (isAlphaNumeric(peek())) {
        advance();
    }

    // 2. Extract the word we just ate
    std::size_t length = m_current - m_start;
    std::string text = m_source.substr(m_start, length);

    // 3. Assume it's a normal variable name (Identifier) by default
    TokenType type = TokenType::IDENTIFIER;

    // 4. Look it up in the dictionary. Is it actually a special Keyword?
    if (KEYWORDS.find(text) != KEYWORDS.end()) {
        // We found it! Change the type to the keyword type (e.g., TokenType::LET)
        type = KEYWORDS.at(text);
    }

    // 5. Add the token
    addToken(type, text);
}

// --- Helper: Add a simple token (like symbols) ---
void Lexer::addToken(TokenType type) {
    // This calls our other addToken function with an empty string
    addToken(type, "");
}

// --- Helper: Add a token with a specific value (like strings/numbers) ---
void Lexer::addToken(TokenType type, std::string literal) {
    (void)literal;
    // We grab the text exactly as it appears in the source code
    std::string text = m_source.substr(m_start, m_current - m_start);
    
    // Create the token and push it to our list
    // Note: We use {} for Aggregate Initialization
    m_tokens.push_back(Token{type, text, m_line});
}

// --- Helper: The Error Reporter ---
void Lexer::lexError(const std::string& message) const {
    // This is what Google Test is looking for in TEST 4
    throw std::runtime_error("[Line " + std::to_string(m_line) + "] Lexer Error: " + message);
}