#pragma once
#include <variant>
#include <string>

using RuntimeValue = std::variant<
    std::monostate, // nil
    bool,           // true/false
    double,         // numbers
    std::string     // strings
>;

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;