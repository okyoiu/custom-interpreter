#include "ast/AstPrinter.h"

std::string AstPrinter::print(const ASTNodePtr& expr) {
    m_result = "";
    if (expr) {
        expr->accept(*this); // This triggers the double-dispatch magic
    }
    return m_result;
}

void AstPrinter::visitLiteral(const Literal& expr) {
    m_result += expr.value.lexeme;
}

void AstPrinter::visitBinary(const Binary& expr) {
    m_result += "(" + expr.op.lexeme + " ";
    expr.left->accept(*this);
    m_result += " ";
    expr.right->accept(*this);
    m_result += ")";
}

void AstPrinter::visitUnary(const Unary& expr) {
    m_result += "(" + expr.op.lexeme + " ";
    expr.operand->accept(*this);
    m_result += ")";
}

void AstPrinter::visitGrouping(const Grouping& expr) {
    m_result += "(group ";
    expr.inner->accept(*this);
    m_result += ")";
}