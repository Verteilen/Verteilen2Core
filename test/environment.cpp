#include <cassert>
#include <iostream>
#include <utility/environment.h>

int main() {
    std::string test = vertelien2::GetEnvironment("path", "hello");
    std::string test2 = vertelien2::GetEnvironment("path_random", "hello");

    std::cout << "test: " << test.c_str() << std::endl;
    std::cout << "test2: " << test2.c_str() << std::endl;

    assert(strcmp(test.c_str(), "hello") != 0);
    assert(strcmp(test2.c_str(), "hello") == 0);
    return 0;
}