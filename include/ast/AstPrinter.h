#pragma once
#include "ast/Visitor.h"
#include "ast/Expr.h"
#include <string>

class AstPrinter : public Visitor {
public:
    // The main entry point
    std::string print(const ASTNodePtr& expr);

    // The visitor methods required by the interface
    void visitLiteral(const Literal& expr) override;
    void visitBinary(const Binary& expr) override;
    void visitUnary(const Unary& expr) override;
    void visitGrouping(const Grouping& expr) override;

private:
    std::string m_result;
};