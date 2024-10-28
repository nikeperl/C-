#include "src/BitArray.h"
#include <iostream>
#include <cassert>

void test_bitarray_creation() {
    BitArray ba(10, 5); // массив из 10 бит, первые 5 бит инициализированы
    assert(ba.size() == 10);
    std::cout << "Test passed: BitArray creation\n";
}

void test_bitarray_set() {
    BitArray ba(10);
    ba.set(2);
    assert(ba[2] == true);
    std::cout << "Test passed: BitArray set\n";
}

int main() {
    test_bitarray_creation();
    test_bitarray_set();
    return 0;
}
