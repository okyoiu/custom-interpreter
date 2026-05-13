#include <gtest/gtest.h>
#include "../include/lexer/Token.h"
#include "lexer/Lexer.h"

TEST(TokenTest, EnumValues) {
    Token t{TokenType::PLUS, "+", 1};

    // EXPECT_EQ checks if the left side equals the right side
    // if it doesnt, then test fails and prints a red error
    EXPECT_EQ(t.lexeme, "+");
    EXPECT_EQ(t.line, 1);
}

TEST(LexerTest, ParsesSingleCharacterTokens) {

    // Step 1) Arranging the source code to be tested on
    std::string source = "+ - ;";
    Lexer lexer(source);

    // Step 2) Running the machine
    std::vector<Token> tokens = lexer.tokenize();

    // Step 3) Assert: Verify the output
    // We expect 4 tokens: PLUS, MINUS, SEMICOLON, and the End of File (EOF)
    ASSERT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens[0].type, TokenType::PLUS);
    EXPECT_EQ(tokens[1].type, TokenType::MINUS);
    EXPECT_EQ(tokens[2].type, TokenType::SEMICOLON);
    EXPECT_EQ(tokens[3].type, TokenType::END_OF_FILE);
}

TEST(LexerTest, SingleVariableDeclaration) {
    Lexer lexer("let x = 42;");
    auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 6); // let, x, =, 42, ;, EOF

    EXPECT_EQ(tokens[0].type, TokenType::LET);
    EXPECT_EQ(tokens[0].lexeme, "let");

    EXPECT_EQ(tokens[1].type, TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[1].lexeme, "x");

    EXPECT_EQ(tokens[2].type, TokenType::EQUAL);

    EXPECT_EQ(tokens[3].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[3].lexeme, "42");

    EXPECT_EQ(tokens[4].type, TokenType::SEMICOLON);

    EXPECT_EQ(tokens.back().type, TokenType::END_OF_FILE);
}

// --- TEST 2: Lookahead Disambiguation ---
// Validates: match() correctly differentiates single vs. double-character operators
TEST(LexerTest, OperatorDisambiguation) {
    Lexer lexer("= == ! !=");
    auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 5); // =, ==, !, !=, EOF
    EXPECT_EQ(tokens[0].type, TokenType::EQUAL);
    EXPECT_EQ(tokens[1].type, TokenType::EQUAL_EQUAL);
    EXPECT_EQ(tokens[2].type, TokenType::BANG);
    EXPECT_EQ(tokens[3].type, TokenType::BANG_EQUAL);
}

// --- TEST 3: Float Parsing with peekNext() ---
// Validates: integer vs float parsing using our unified NUMBER type
TEST(LexerTest, NumericLiterals) {
    Lexer lexer("42 3.14");
    auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 3); // 42, 3.14, EOF
    EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[0].lexeme, "42");
    EXPECT_EQ(tokens[1].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[1].lexeme, "3.14");
}

// --- TEST 4: Error Recovery Contract ---
// Validates: unterminated string literal produces a thrown exception
TEST(LexerTest, UnterminatedStringThrows) {
    Lexer lexer("\"hello world");
    
    // We expect our lexError() function to throw a std::runtime_error
    EXPECT_THROW(lexer.tokenize(), std::runtime_error);
}