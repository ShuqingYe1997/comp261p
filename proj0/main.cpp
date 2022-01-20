#include <iostream>
#include "LLQueue.hpp"

int main() {
    LLQueue<std::string> a;
    a.enqueue("a");
    a.enqueue("b");
    LLQueue<std::string> b = a;
    if (b.front() == "a")
        std::cout<<"Win!"<<std::endl;
    return 0;
}
