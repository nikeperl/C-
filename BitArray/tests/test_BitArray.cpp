#include <gtest/gtest.h>
#include "../src/BitArray.h" // Подключаем заголовочный файл BitArray

// Тестирование конструктора по умолчанию
TEST(BitArrayTest, DefaultConstructor) {
    BitArray bits;
    EXPECT_EQ(bits.size(), 0);
    EXPECT_TRUE(bits.empty());
}

// Тестирование конструктора с заданным числом бит
TEST(BitArrayTest, ConstructorWithSize) {
    BitArray bits(10);
    EXPECT_EQ(bits.size(), 10);
    EXPECT_FALSE(bits.empty());
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(bits[i]); // Проверяем, что все биты по умолчанию ложные
    }
}

// Тестирование конструктора с заданным значением
TEST(BitArrayTest, ConstructorWithValue) {
    BitArray bits(10, 0b1010101010); // 10 бит
    EXPECT_EQ(bits.size(), 10);
    EXPECT_TRUE(bits[0]);
    EXPECT_FALSE(bits[1]);
    EXPECT_TRUE(bits[2]);
    EXPECT_FALSE(bits[3]);
    EXPECT_TRUE(bits[4]);
    EXPECT_FALSE(bits[5]);
    EXPECT_TRUE(bits[6]);
    EXPECT_FALSE(bits[7]);
    EXPECT_TRUE(bits[8]);
    EXPECT_FALSE(bits[9]);
}

// Тестирование метода set
TEST(BitArrayTest, SetMethod) {
    BitArray bits(5);
    bits.set(2, true);
    EXPECT_TRUE(bits[2]);
    bits.set(2, false);
    EXPECT_FALSE(bits[2]);
}

// Тестирование метода reset
TEST(BitArrayTest, ResetMethod) {
    BitArray bits(5);
    bits.set(3, true);
    bits.reset(3);
    EXPECT_FALSE(bits[3]);
}

// Тестирование метода push_back
TEST(BitArrayTest, PushBackMethod) {
    BitArray bits;
    bits.push_back(true);
    bits.push_back(false);
    bits.push_back(true);
    EXPECT_EQ(bits.size(), 3);
    EXPECT_TRUE(bits[0]);
    EXPECT_FALSE(bits[1]);
    EXPECT_TRUE(bits[2]);
}

// Тестирование битовой операции AND
TEST(BitArrayTest, BitwiseAndOperation) {
    BitArray bits1(5, 0b11001);
    BitArray bits2(5, 0b10101);
    bits1 &= bits2;
    EXPECT_EQ(bits1.to_string(), "10001"); // 11001 AND 10101 = 10001
}

// Тестирование метода count
TEST(BitArrayTest, CountMethod) {
    BitArray bits(8, 0b10101010);
    EXPECT_EQ(bits.count(), 4); // Должно быть 4 единичных бита
}

// Тестирование битовой инверсии
TEST(BitArrayTest, BitwiseNotOperation) {
    BitArray bits(5, 0b11001);
    BitArray inverted = ~bits;
    EXPECT_EQ(inverted.to_string(), "00110"); // Инверсия 11001 = 00110
}

// Тестирование метода clear
TEST(BitArrayTest, ClearMethod) {
    BitArray bits(5, 0b11111);
    bits.clear();
    EXPECT_EQ(bits.size(), 0);
    EXPECT_TRUE(bits.empty());
}

// Тестирование на наличие истинных битов
TEST(BitArrayTest, AnyMethod) {
    BitArray bits(5, 0b00000);
    EXPECT_FALSE(bits.any());
    bits.set(0, true);
    EXPECT_TRUE(bits.any());
}

// Тестирование на наличие ложных битов
TEST(BitArrayTest, NoneMethod) {
    BitArray bits(5, 0b11111);
    EXPECT_FALSE(bits.none());
    bits.clear();
    EXPECT_TRUE(bits.none());
}

// Тестирование битового сдвига влево
TEST(BitArrayTest, LeftShiftOperation) {
    BitArray bits(5, 0b00001);
    bits <<= 1; // Сдвинуть влево на 1
    EXPECT_EQ(bits.to_string(), "00010");
}

// Тестирование битового сдвига вправо
TEST(BitArrayTest, RightShiftOperation) {
    BitArray bits(5, 0b00010);
    bits >>= 1; // Сдвинуть вправо на 1
    EXPECT_EQ(bits.to_string(), "00001");
}

// Тестирование оператора равенства
TEST(BitArrayTest, EqualityOperator) {
    BitArray bits1(5, 0b10101);
    BitArray bits2(5, 0b10101);
    BitArray bits3(5, 0b01010);
    EXPECT_TRUE(bits1 == bits2);
    EXPECT_FALSE(bits1 == bits3);
}

// Тестирование оператора неравенства
TEST(BitArrayTest, InequalityOperator) {
    BitArray bits1(5, 0b10101);
    BitArray bits2(5, 0b10101);
    BitArray bits3(5, 0b01010);
    EXPECT_FALSE(bits1 != bits2);
    EXPECT_TRUE(bits1 != bits3);
}

// Добавьте другие тесты по мере необходимости...

// Запуск всех тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
