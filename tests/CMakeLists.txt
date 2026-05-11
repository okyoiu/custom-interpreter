include(FetchContent)

# download Google Test from GitHub
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# forces Windows to use exact same rules as project
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# downloading the source code and compiling to make available to use
FetchContent_MakeAvailable(googletest)

# creating the test program (built from lexer_test.cpp file only)
add_executable(interpreter_tests lexer_test.cpp)

# linking the Google Test library to the interpreter_tests program
target_link_libraries(interpreter_tests gtest_main)

# pure CMake that searches every single TEST() block writen and registered to master list
include(GoogleTest)
gtest_discover_tests(interpreter_tests)