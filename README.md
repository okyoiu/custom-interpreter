# Custom Scripting Language Interpreter

A hand-crafted, statically-typed scripting language interpreter built entirely from scratch in modern C++ (C++20). 

This project demonstrates deep systems-level programming, memory management, and compiler theory. It avoids parser generators (like YACC/Bison) in favor of a custom Recursive Descent Parser and manually managed Abstract Syntax Trees (AST).

## Architecture & Pipeline
1. **Lexer (Scanner):** Converts raw string inputs into a stream of strictly-typed `Token` objects.
2. **Parser:** Uses Recursive Descent to transform tokens into an Abstract Syntax Tree (AST) using `std::unique_ptr` for memory-safe ownership.
3. **Evaluator:** Walks the AST to execute logic within scoped lexical environments.

## 🛠️ Tech Stack & Tooling
* **Language:** C++20
* **Build System:** CMake (Strict compliance: `-Wall -Wextra -Werror -pedantic`)
* **Testing:** Google Test (gtest) integrated via `FetchContent`

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