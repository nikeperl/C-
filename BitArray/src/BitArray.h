#ifndef BITARRAY_H
#define BITARRAY_H

#include <string>

class BitArray {
public:
    BitArray();
    ~BitArray();
    explicit BitArray(int num_bits, unsigned long value = 0);
    BitArray(const BitArray& b);
    BitArray& operator=(const BitArray& b);

    void swap(BitArray& b);
    void resize(int num_bits, bool value = false);
    void clear();
    void push_back(bool bit);

    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);

    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;

    BitArray& set(int n, bool val = true);
    BitArray& set();
    BitArray& reset(int n);
    BitArray& reset();
    bool any() const;
    bool none() const;
    BitArray operator~() const;
    int count() const;

    bool operator[](int i) const;

    int size() const;
    bool empty() const;
    std::string to_string() const;

private:
    int num_bits;
    unsigned long* bits; // внутреннее представление массива битов

    void check_index(int i) const; // метод проверки границ индекса
};

// Операторы вне класса
bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);
BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif // BITARRAY_H
