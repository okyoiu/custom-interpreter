#include <gtest/gtest.h>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/AstPrinter.h"

TEST(ParserTest, PrecedenceIsEncodedInTreeStructure) {
    // Test 1: Multiplication before addition
    Lexer lexer1("2 + 3 * 4");
    auto tokens1 = lexer1.tokenize();
    Parser parser1(tokens1);
    ASTNodePtr tree1 = parser1.parse();
    
    AstPrinter printer;
    EXPECT_EQ(printer.print(tree1), "(+ 2 (* 3 4))");

    // Test 2: Parentheses override precedence
    Lexer lexer2("(2 + 3) * 4");
    auto tokens2 = lexer2.tokenize();
    Parser parser2(tokens2);
    ASTNodePtr tree2 = parser2.parse();
    
    EXPECT_EQ(printer.print(tree2), "(* (group (+ 2 3)) 4)");
}