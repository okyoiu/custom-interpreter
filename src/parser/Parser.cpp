#include "parser/Parser.h"

Parser::Parser(const std::vector<Token>& tokens)
    : m_tokens(tokens) {}

ASTNodePtr Parser::parse() {
    // For now, we are just parsing a single expression
    return expression();
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) m_current++;
    return previous();
}

Token Parser::peek() const { 
    return m_tokens[m_current];
}

Token Parser::previous() const {
    // Gets the token we had just consumed
    return m_tokens[m_current - 1];
}

// This one is the most important function
Token Parser::consume(TokenType type, const std::string& message) {
    // Requires a specific token to be next, or else it will just throw an error
    if (check(type)) return advance();
    throw error(peek(), message);
}

// Generating a formatted error message
std::runtime_error Parser::error(Token token, const std::string& message) {
    if (token.type == TokenType::END_OF_FILE) {
        return std::runtime_error("[Line " + std::to_string(token.line) + "] Error at the end: " + message);
    } else {
        return std::runtime_error("[Line " + std::to_string(token.line) + "] Error at '" + token.lexeme + "': " + message);
    }
}


// =======================
/* 
        GRAMMAR RULES
*/
// =======================

ASTNodePtr Parser::expression() {
    // an expression falls through to equality, so we will add assignment (x=5) here
    return equality();
}

ASTNodePtr Parser::equality() {
    // 1. Grabing the left side of the comparison
    ASTNodePtr expr = comparison();

    // 2. While we see a `!=` or `==`, then we shall keep building the tree
    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        Token op = previous();
        ASTNodePtr right = comparison(); // grabbing the right hand side
        // combining them into a new Binary node
        expr = std::make_unique<Binary>(std::move(expr), std::move(op), std::move(right));
    }
    return expr;
}

ASTNodePtr Parser::comparison() {
    ASTNodePtr expr = term();

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
        Token op = previous();
        ASTNodePtr right = term();
        expr = std::make_unique<Binary>(std::move(expr), std::move(op), std::move(right));
    }

    return expr;
}

ASTNodePtr Parser::term() {
    ASTNodePtr expr = factor();

    while (match({TokenType::MINUS, TokenType::PLUS})) {
        Token op = previous();
        ASTNodePtr right = factor();
        expr = std::make_unique<Binary>(std::move(expr), std::move(op), std::move(right));
    }

    return expr;
}

ASTNodePtr Parser::factor() {
    ASTNodePtr expr = unary();

    while (match({TokenType::SLASH, TokenType::STAR})) {
        Token op = previous();
        ASTNodePtr right = unary();
        expr = std::make_unique<Binary>(std::move(expr), std::move(op), std::move(right));
    }

    return expr;
}

ASTNodePtr Parser::unary() {
    // If we see a '!' or '-', it's a unary operation (like -5 or !true)
    if (match({TokenType::BANG, TokenType::MINUS})) {
        Token op = previous();
        ASTNodePtr right = unary(); // Unary calls itself!
        return std::make_unique<Unary>(std::move(op), std::move(right));
    }

    // Otherwise, we've hit rock bottom: a primary value
    return primary();
}

ASTNodePtr Parser::primary() {
    // If it's a number, string, or variable name, wrap it in a Literal node
    if (match({TokenType::NUMBER, TokenType::STRING_LITERAL, TokenType::IDENTIFIER})) {
        return std::make_unique<Literal>(previous());
    }

    // If it's a grouping: '(' expression ')'
    if (match({TokenType::LEFT_PAREN})) {
        ASTNodePtr expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_unique<Grouping>(std::move(expr));
    }

    // If we get here, the parser is looking at a token it doesn't know how to start an expression with.
    throw error(peek(), "Expect expression.");
}


bool Parser::isAtEnd() const {
    return peek().type == TokenType::END_OF_FILE;
}