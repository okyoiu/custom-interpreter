#pragma once
#include "ast/ASTNode.h"
#include "lexer/Token.h" // We need to know what a Token is
#include <utility>       // For std::move

// --- 1. LITERAL (e.g., 42, "hello") ---
struct Literal : public ASTNode {
    Token value;

    explicit Literal(Token val) : value(std::move(val)) {
        this->line = value.line;
    }

    void accept(Visitor& visitor) const override {
        visitor.visitLiteral(*this);
    }
};

// --- 2. BINARY (e.g., left + right) ---
struct Binary : public ASTNode {
    ASTNodePtr left;
    Token op;
    ASTNodePtr right;

    Binary(ASTNodePtr left, Token op, ASTNodePtr right)
        : left(std::move(left)), op(std::move(op)), right(std::move(right)) {
        this->line = this->op.line;
    }

    void accept(Visitor& visitor) const override {
        visitor.visitBinary(*this);
    }
};

// --- 3. UNARY (e.g., !true, -5) ---
struct Unary : public ASTNode {
    Token op;
    ASTNodePtr operand;

    Unary(Token op, ASTNodePtr operand)
        : op(std::move(op)), operand(std::move(operand)) {
        this->line = this->op.line;
    }

    void accept(Visitor& visitor) const override {
        visitor.visitUnary(*this);
    }
};

// --- 4. GROUPING (e.g., (1 + 2) ) ---
struct Grouping : public ASTNode {
    ASTNodePtr inner;

    explicit Grouping(ASTNodePtr inner) : inner(std::move(inner)) {
        // Grouping doesn't have its own token, so it borrows its child's line
        this->line = this->inner ? this->inner->line : 0; 
    }

    void accept(Visitor& visitor) const override {
        visitor.visitGrouping(*this);
    }
};