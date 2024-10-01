#include <iostream>

#include "shared_ptr.h"

int main() {
    SharedPtr<int> ptr = new int(3);
    std::cout << ptr.use_count() << '\n';
    std::cout << *ptr << '\n';

    {
        auto ptr2 = ptr;
        std::cout << ptr2.use_count() << '\n';
        std::cout << *ptr2 << '\n';
    }

    std::cout << ptr.use_count() << '\n';
    std::cout << *ptr << '\n';
}