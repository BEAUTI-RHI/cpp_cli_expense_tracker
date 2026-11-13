#include <iostream>

#include "expense/app.hpp"

int main() {
    expense::App app(std::cin, std::cout);
    app.run();
    return 0;
}
