#include "BitArray.h"
#include <stdexcept>
#include <cstring>
#include <algorithm>

// Конструкторы, деструкторы и операторы
BitArray::BitArray() : num_bits(0), bits(nullptr) {}

BitArray::~BitArray() {
    delete[] bits;
}

BitArray::BitArray(int num_bits, unsigned long value) : num_bits(num_bits) {
    bits = new unsigned long[(num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8)]();
    bits[0] = value;
}

BitArray::BitArray(const BitArray& b) : num_bits(b.num_bits) {
    bits = new unsigned long[(num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8)];
    std::memcpy(bits, b.bits, sizeof(unsigned long) * ((num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8)));
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        delete[] bits;
        num_bits = b.num_bits;
        bits = new unsigned long[(num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8)];
        std::memcpy(bits, b.bits, sizeof(unsigned long) * ((num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8)));
    }
    return *this;
}



// Swap: меняет значения массива битов местами
void BitArray::swap(BitArray& b) {
    std::swap(num_bits, b.num_bits);
    std::swap(bits, b.bits);
}

// Resize: изменяет размер массива битов
void BitArray::resize(int new_num_bits, bool value) {
    if (new_num_bits < 0) {
        throw std::invalid_argument("Size must be non-negative");
    }

    int old_num_bits = num_bits;
    unsigned long* new_bits = new unsigned long[(new_num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8)]();

    // Копируем существующие данные в новый массив
    if (bits != nullptr) {
        int copy_bits = std::min(old_num_bits, new_num_bits);
        std::memcpy(new_bits, bits, (copy_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8) * sizeof(unsigned long));
        delete[] bits;
    }

    // Если массив увеличился, инициализируем новые биты значением `value`
    if (new_num_bits > old_num_bits) {
        for (int i = old_num_bits; i < new_num_bits; ++i) {
            if (value) {
                new_bits[i / (sizeof(unsigned long) * 8)] |= (1UL << (i % (sizeof(unsigned long) * 8)));
            }
        }
    }

    bits = new_bits;
    num_bits = new_num_bits;
}

// Clear: очищает массив
void BitArray::clear() {
    delete[] bits;
    bits = nullptr;
    num_bits = 0;
}

// Push_back: добавляет бит в конец массива
void BitArray::push_back(bool bit) {
    resize(num_bits + 1, bit);
}



// Bitwise AND operation
BitArray& BitArray::operator&=(const BitArray& b) {
    if (num_bits != b.num_bits) {
        throw std::invalid_argument("BitArray sizes must be equal for &=");
    }
    for (int i = 0; i < (num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8); ++i) {
        bits[i] &= b.bits[i];
    }
    return *this;
}

// Bitwise OR operation
BitArray& BitArray::operator|=(const BitArray& b) {
    if (num_bits != b.num_bits) {
        throw std::invalid_argument("BitArray sizes must be equal for |=");
    }
    for (int i = 0; i < (num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8); ++i) {
        bits[i] |= b.bits[i];
    }
    return *this;
}

// Bitwise XOR operation
BitArray& BitArray::operator^=(const BitArray& b) {
    if (num_bits != b.num_bits) {
        throw std::invalid_argument("BitArray sizes must be equal for ^=");
    }
    for (int i = 0; i < (num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8); ++i) {
        bits[i] ^= b.bits[i];
    }
    return *this;
}



// Left shift with zero fill
BitArray& BitArray::operator<<=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Shift amount must be non-negative");
    }

    if (n == 0) return *this;

    for (int i = num_bits - 1; i >= n; --i) {
        set(i, (*this)[i - n]);
    }
    for (int i = 0; i < n; ++i) {
        set(i, false);
    }

    return *this;
}

// Right shift with zero fill
BitArray& BitArray::operator>>=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Shift amount must be non-negative");
    }

    if (n == 0) return *this;

    for (int i = 0; i < num_bits - n; ++i) {
        set(i, (*this)[i + n]);
    }
    for (int i = num_bits - n; i < num_bits; ++i) {
        set(i, false);
    }

    return *this;
}



// Set a specific bit
BitArray& BitArray::set(int n, bool val) {
    check_index(n);
    if (val) {
        bits[n / (sizeof(unsigned long) * 8)] |= (1UL << (n % (sizeof(unsigned long) * 8)));
    } else {
        bits[n / (sizeof(unsigned long) * 8)] &= ~(1UL << (n % (sizeof(unsigned long) * 8)));
    }
    return *this;
}

// Set all bits to true
BitArray& BitArray::set() {
    for (int i = 0; i < (num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8); ++i) {
        bits[i] = ~0UL;
    }
    return *this;
}

// Reset a specific bit
BitArray& BitArray::reset(int n) {
    return set(n, false);
}

// Reset all bits to false
BitArray& BitArray::reset() {
    for (int i = 0; i < (num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8); ++i) {
        bits[i] = 0UL;
    }
    return *this;
}

// Check if any bit is true
bool BitArray::any() const {
    for (int i = 0; i < (num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8); ++i) {
        if (bits[i] != 0) return true;
    }
    return false;
}

// Check if all bits are false
bool BitArray::none() const {
    return !any();
}

// Bitwise NOT operation
BitArray BitArray::operator~() const {
    BitArray result(*this);
    for (int i = 0; i < (num_bits + sizeof(unsigned long) * 8 - 1) / (sizeof(unsigned long) * 8); ++i) {
        result.bits[i] = ~bits[i];
    }
    return result;
}

// Count the number of bits set to true
int BitArray::count() const {
    int count = 0;
    for (int i = 0; i < num_bits; ++i) {
        if ((*this)[i]) ++count;
    }
    return count;
}



// Get the value of a specific bit
bool BitArray::operator[](int i) const {
    check_index(i);
    return bits[i / (sizeof(unsigned long) * 8)] & (1UL << (i % (sizeof(unsigned long) * 8)));
}



// Get the size of the bit array
int BitArray::size() const {
    return num_bits;
}

// Check if the array is empty
bool BitArray::empty() const {
    return num_bits == 0;
}

// Convert the bit array to a string representation
std::string BitArray::to_string() const {
    std::string result;
    for (int i = 0; i < num_bits; ++i) {
        result += (*this)[i] ? '1' : '0';
    }
    return result;
}




// метод проверки границ индекса
void BitArray::check_index(int i) const {
    if (i < 0 || i >= num_bits) {
        throw std::out_of_range("BitArray index out of bounds");
    }
}



// Операторы вне класса
bool operator==(const BitArray &a, const BitArray &b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}


bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result |= b2;
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray result(b1);
    result ^= b2;
    return result;
}
