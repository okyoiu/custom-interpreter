#pragma once
#include <memory>
#include "Visitor.h" // We need the Visitor interface here

// The base class for all expressions in the tree
struct ASTNode {
    virtual ~ASTNode() = default;
    
    // Every node must accept a visitor
    virtual void accept(Visitor& visitor) const = 0;
    
    int line = 0; // Crucial for error reporting later!
};

// A parent strictly owns its children.
using ASTNodePtr = std::unique_ptr<ASTNode>;