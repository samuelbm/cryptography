#include "prime_arithmetic_test.h"
#include "prime_arithmetic.h"


Large& create_and_initialize_large(uint16_t init_value, uint16_t n_bits)
{
    Large* large = new Large(n_bits);
    for(uint16_t i=0; i<n_bits; i++)
    {
        (*large)[i] = (init_value >> i) & 1;
    }
    return *large;
};

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_equal(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_equal(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_equal(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_equal_Than_operation_count_is_16()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_equal(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_less_than(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_less_than_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_less_than(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_less_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_less_than(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_than_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_less_than(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_not_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_not_equal(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_not_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_not_equal(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_not_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_not_equal(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_not_equal_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_not_equal(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_greater_than(a_equal, b, count);
    QVERIFY(!is_greater_than(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_greater_than_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_greater_than(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_greater_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_greater_than(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_than_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_greater_than(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_less_or_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_less_or_equal(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_less_or_equal(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_less_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_less_or_equal(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_or_equal_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_less_or_equal(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_greater_or_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(!is_greater_or_equal(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_greater_or_equal(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_grater_than_b_When_testing_is_graeter_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6, 8);
    Large b = create_and_initialize_large(5, 8);
    QVERIFY(is_greater_or_equal(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_or_equal_Than_operation_count_is_8()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(5, 8);
    is_greater_or_equal(a_equal, b, count);
    QCOMPARE(count.operation, 8);
}

void prime_arithmetic_test::Given_5_and_4_on_8_bits_When_testing_addition_Then_return_9()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(4, 8);
    Large sum = create_and_initialize_large(0, 9);
    Large expected = create_and_initialize_large(9, 9);
    addition(a, b, sum, count);
    QVERIFY(is_equal(sum, expected, count));
}

void prime_arithmetic_test::Given_5_and_4_on_8_bits_When_testing_addition_Then_operation_is_8()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(4, 8);
    Large sum = create_and_initialize_large(0, 9);
    addition(a, b, sum, count);
    QCOMPARE(count.operation, 8);
}

void prime_arithmetic_test::Given_5_and_4_on_8_bits_When_testing_addition_Then_clock_is_0()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(4, 8);
    Large sum = create_and_initialize_large(0, 9);
    addition(a, b, sum, count);
    QCOMPARE(count.clock, 0);
}

void prime_arithmetic_test::Given_9_and_4_on_8_bits_When_testing_substrction_Then_return_5()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(9, 8);
    Large b = create_and_initialize_large(4, 8);
    Large difference = create_and_initialize_large(0, 8);
    Large expected = create_and_initialize_large(5, 8);
    substraction(a, b, difference, count);
    QVERIFY(is_equal(difference, expected, count));
}

void prime_arithmetic_test::Given_9_and_4_on_8_bits_When_testing_substrction_Then_operation_is_8()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(9, 8);
    Large b = create_and_initialize_large(4, 8);
    Large difference = create_and_initialize_large(5, 8);
    substraction(a, b, difference, count);
    QCOMPARE(count.operation, 8);
}

void prime_arithmetic_test::Given_9_and_4_on_8_bits_When_testing_substrction_Then_clock_is_0()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(9, 8);
    Large b = create_and_initialize_large(4, 8);
    Large difference = create_and_initialize_large(5, 8);
    substraction(a, b, difference, count);
    QCOMPARE(count.clock, 0);
}

void prime_arithmetic_test::Given_5_and_6_on_8_bits_When_testing_multiplication_Then_return_30()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(6, 8);
    Large product(32);
    Large expected = create_and_initialize_large(30, 32);

    multiplication(a, b, product, count);
    QVERIFY(is_equal(product, expected, count));
}

void prime_arithmetic_test::Given_5_and_6_on_8_bits_When_testing_multiplication_Then_operation_is_64()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(6, 8);
    Large product(16);
    Large expected = create_and_initialize_large(30, 16);
    multiplication(a, b, product, count);
    QCOMPARE(count.operation, 64);
}

void prime_arithmetic_test::Given_5_and_6_on_8_bits_When_testing_multiplication_Then_clock_is_8()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(6, 8);
    Large product(16);
    Large expected = create_and_initialize_large(30, 8);
    multiplication(a, b, product, count);
    QCOMPARE(count.clock, 8);
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_quotient_is_5()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(17, 8);
    Large b = create_and_initialize_large(3, 8);
    Large quotient(8);
    Large remainder(8);
    Large expected = create_and_initialize_large(5, 8);
    division_modulo(a, b, quotient, remainder, count);
    qDebug() << quotient.toHex() << expected.toHex();
    QVERIFY(is_equal(quotient, expected, count));
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_remainder_is_2()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(17, 8);
    Large b = create_and_initialize_large(3, 8);
    Large quotient(8);
    Large remainder(8);
    Large expected = create_and_initialize_large(2, 8);
    division_modulo(a, b, quotient, remainder, count);
    qDebug() << quotient.toHex() << expected.toHex();
    QVERIFY(is_equal(remainder, expected, count));
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_operation_is_128()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(6, 8);
    Large remainder(8);
    Large quotient(8);
    division_modulo(a, b, quotient, remainder, count);
    QCOMPARE(count.operation, 128);
}

void prime_arithmetic_test::Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_clock_is_8()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5, 8);
    Large b = create_and_initialize_large(6, 8);
    Large remainder(8);
    Large quotient(8);
    division_modulo(a, b, quotient, remainder, count);
    QCOMPARE(count.clock, 8);
}

static prime_arithmetic_test PRIME_ARITHMETIC_TEST;
