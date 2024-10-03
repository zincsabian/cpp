#include <iostream>

#include "shared_ptr.h"
#include "unique_ptr.h"

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

    UniquePtr<int> up(new int(10));
    std::cout << "Value: " << *up << '\n';

    UniquePtr<int> up2;
    up2 = std::move(up); // Move assignment
    if (!up) {
        std::cout << "up is now empty" << '\n';
    }

    if (up2) {
        std::cout << "Value after move: " << *up2 << '\n';
    }

    return 0;
}