#include <gtest/gtest.h>
#include "../include/lexer/Token.h"

TEST(TokenTest, EnumValues) {
    Token t{TokenType::PLUS, "+", 1};

    // EXPECT_EQ checks if the left side equals the right side
    // if it doesnt, then test fails and prints a red error
    EXPECT_EQ(t.lexme, "+");
    EXPECT_EQ(t.line, 1);
}