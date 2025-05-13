#include <iostream>
#include "RingBuffer.hpp"

int main() {
    RingBuffer<int, 5> rb;
    std::cout << "Capacity: " << rb.capacity() << "\n";

    // Тест push и pop
    for (int i = 1; i <= 6; ++i) {
        rb.push(i);
        std::cout << "Pushed: " << i << ", size=" << rb.size() << "\n";
    }

    // Range-based for
    std::cout << "Elements in buffer: ";
    for (auto& val : rb) {
        std::cout << val << ' ';
    }
    std::cout << "\n";

    // Доступ по индексу
    if (!rb.empty()) {
        std::cout << "First element = " << rb[0] << "\n";
    }

    int v;
    std::cout << "Popping all: \n";
    while (rb.pop(v)) {
        std::cout << v << ' ';
    }
    std::cout << "\n";

    return 0;
}
