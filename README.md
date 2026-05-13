# Custom Scripting Language Interpreter

A hand-crafted, statically-typed scripting language interpreter built entirely from scratch in modern C++ (C++20). 

This project demonstrates deep systems-level programming, memory management, and compiler theory. It avoids parser generators (like YACC/Bison) in favor of a custom Recursive Descent Parser and manually managed Abstract Syntax Trees (AST).

## Project Architecture
The interpreter follows a classic multi-stage pipeline. Currently, the Lexical Analysis phase is complete and fully tested.

| Stage | Responsibility | Status |
| :--- | :--- | :--- |
| **Lexer (Scanner)** | Converts raw characters into a stream of typed Tokens. | **Complete** |
| **Parser** | Validates grammar and builds the Abstract Syntax Tree (AST). | *In Progress* |
| **Evaluator** | Executes the logic within lexical scopes and environments. | *Planned* |

---

## Tech Stack & Requirements
* **Compiler:** C++20 (supports std::unique_ptr, enum class, and advanced string handling).
* **Build System:** CMake (Version 3.10+).
* **Testing Framework:** Google Test (gtest) – Integrated via FetchContent for zero-install portability.
* **Platform:** macOS (Apple Silicon), Linux, or WSL.


## Getting Started

### 1. Prerequisites
Ensure you have a modern C++ compiler and CMake installed:

```bash
# macOS
brew install cmake googletest

# Ubuntu/Debian
sudo apt install build-essential cmake libgtest-dev


## Build Instructions
This project uses CMake for out-of-source builds.

```bash
# 1. Clone the repository
git clone 
cd YOUR_REPO_NAME

# 2. Generate the build files
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# 3. Compile the interpreter and test suite
make -j$(nproc)

# 4. Run the test suite
ctest --output-on-failure

# 5. Start the REPL
./interpreter
```

## Running Testing environment

Verification is baked into the development workflow. To run the Lexer test suite:

```bash
./tests/interpreter_tests
```