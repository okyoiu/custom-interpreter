#pragma once
#include "ast/ASTNode.h"
#include "ast/Expr.h"
#include "interpreter/RuntimeValue.h"
#include "interpreter/RuntimeError.h"
#include <string>

class Interpreter : public Visitor {
public:
    // The main entry point
    RuntimeValue interpret(const ASTNodePtr& node);

    // --- Visitor Interface Implementation ---
    void visitLiteral(const Literal& expr) override;
    void visitGrouping(const Grouping& expr) override;
    void visitUnary(const Unary& expr) override;
    void visitBinary(const Binary& expr) override;

private:
    // Visit methods return void, so they write their answers here.
    RuntimeValue m_result;

    // The recursive engine
    RuntimeValue evaluate(const ASTNodePtr& node);

    // --- Semantic Helpers ---
    bool isTruthy(const RuntimeValue& val) const;
    bool isEqual(const RuntimeValue& a, const RuntimeValue& b) const;
    void assertNumber(const Token& op, const RuntimeValue& val) const;
    void assertBothNumbers(const Token& op, const RuntimeValue& a, const RuntimeValue& b) const;
};