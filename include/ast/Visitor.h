#pragma once

// forward declare the structs so the compiler knows they exist
struct Literal;
struct Binary;
struct Unary;
struct Grouping;


struct Visitor {
    virtual ~Visitor() = default;
    // VIRTUAL: Ensures that if a derived class overrides this method, 
    // the derived version will be called even when accessed through a base class pointer.

    virtual void visitLiteral(const Literal& expr) = 0;
    virtual void visitBinary(const Binary& expr) = 0;
    virtual void visitUnary(const Unary& expr) = 0;
    virtual void visitGrouping(const Grouping& expr) = 0;};