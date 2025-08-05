#include <Application.hpp>
#include <exception>
#include <iostream>

int main(){
    try {
        Application application("hello", 1200, 800);
        application.run();
    }
    catch (const std::exception &e) {
        std::cerr << e.what();
        return -1;
    }
    return 0;
}
