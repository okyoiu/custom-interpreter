#pragma once
#include "lexer/Token.h"
#include <stdexcept>
#include <string>

class RuntimeError : public std::runtime_error {
    public:
        // We pass the exact Token that caused the error so that we can print the line number
        explicit RuntimeError(const Token& token, const std::string& message) 
            : std::runtime_error(message), m_token(token) {}
        
        const Token& token() const noexcept {
            return m_token;
        }
    private:
        Token m_token; // declaring it as a private member to be used for Class
};