cmake_minimum_required(VERSION 3.14)
project(InterpreterSystem VERSION 1.0 LANGUAGES CXX)

# 1. Enforcing modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 2. Strict compiler Flags
# quick sum: 
# -Wall        : catches initialized unused variables
# -Wextra      : catches any subtle logical bugs (such as comparing unsigned and signed)
# -pedantic    : disables custome "extensions" person may have and flags them
# -Werror      : treats error as fatal errors (code doesn't compile)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

# 3. Telling compiler where to look for the header files
include_directories(include)

# 4. Creating the main program
add_executable(interpreter src/main.cpp)

# 5. Turn on testing engine
enable_testing()
add_subdirectory(tests)