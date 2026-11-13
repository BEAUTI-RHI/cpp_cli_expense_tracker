cmake_minimum_required(VERSION 3.16)
project(cli_expense_tracker VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Turn on the compiler's helpful warnings. Your errors.txt showed these are
# already useful to you - this makes them always-on.
add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wshadow)

# All the logic lives in a library so both the program and the tests can use it.
add_library(expense_core
    src/money.cpp
    src/expense.cpp
    src/tracker.cpp
    src/input.cpp
    src/app.cpp
)
target_include_directories(expense_core PUBLIC include)

add_executable(expense_tracker src/main.cpp)
target_link_libraries(expense_tracker PRIVATE expense_core)

enable_testing()
add_executable(run_tests tests/tests.cpp)
target_link_libraries(run_tests PRIVATE expense_core)
add_test(NAME all_tests COMMAND run_tests)
