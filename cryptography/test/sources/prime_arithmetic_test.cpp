#include "prime_arithmetic_test.h"
#include "prime_arithmetic.h"


Large& create_and_initialize_large(uint16_t init_value)
{
    uint16_t n_bits = 16;
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
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(!is_equal(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(!is_equal(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_equal(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_equal_Than_operation_count_is_16()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_equal(a_equal, b, count);
    QCOMPARE(count.operation, 16);
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(!is_less_than(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_less_than_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_less_than(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_less_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(!is_less_than(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_than_Than_operation_count_is_16()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_less_than(a_equal, b, count);
    QCOMPARE(count.operation, 16);
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_not_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(!is_not_equal(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_not_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_not_equal(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_not_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_not_equal(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_not_equal_Than_operation_count_is_16()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_not_equal(a_equal, b, count);
    QCOMPARE(count.operation, 16);
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_greater_than(a_equal, b, count);
    QVERIFY(!is_greater_than(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_greater_than_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_greater_than(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_greater_than_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(!is_greater_than(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_than_Than_operation_count_is_16()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_greater_than(a_equal, b, count);
    QCOMPARE(count.operation, 16);
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_less_or_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(!is_less_or_equal(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_less_or_equal(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_less_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_less_or_equal(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_or_equal_Than_operation_count_is_16()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_less_or_equal(a_equal, b, count);
    QCOMPARE(count.operation, 16);
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_greater_or_equal_Than_return_false()
{
    Count count;
    count_initialization(count);
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(!is_greater_or_equal(a_lesser, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_greater_or_equal(a_equal, b, count));
}

void prime_arithmetic_test::Given_a_grater_than_b_When_testing_is_graeter_or_equal_Than_return_true()
{
    Count count;
    count_initialization(count);
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_greater_or_equal(a_greater, b, count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_or_equal_Than_operation_count_is_16()
{
    Count count;
    count_initialization(count);
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_greater_or_equal(a_equal, b, count);
    QCOMPARE(count.operation, 16);
}

void prime_arithmetic_test::Given_5_and_4_on_16_bits_When_testing_addition_Then_return_9()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5);
    Large b = create_and_initialize_large(4);
    Large sum = create_and_initialize_large(0);
    Large expected = create_and_initialize_large(9);
    addition(a, b, sum, count);
    QVERIFY(is_equal(sum, expected, count));
}

void prime_arithmetic_test::Given_5_and_4_on_16_bits_When_testing_addition_Then_operation_is_17()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5);
    Large b = create_and_initialize_large(4);
    Large sum = create_and_initialize_large(0);
    addition(a, b, sum, count);
    QCOMPARE(count.operation, 17);
}

void prime_arithmetic_test::Given_5_and_4_on_16_bits_When_testing_addition_Then_clock_is_1()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5);
    Large b = create_and_initialize_large(4);
    Large sum = create_and_initialize_large(0);
    addition(a, b, sum, count);
    QCOMPARE(count.clock, 1);
}

void prime_arithmetic_test::Given_9_and_4_on_16_bits_When_testing_substrction_Then_return_5()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(9);
    Large b = create_and_initialize_large(4);
    Large difference = create_and_initialize_large(0);
    Large expected = create_and_initialize_large(5);
    substraction(a, b, difference, count);
    QVERIFY(is_equal(difference, expected, count));
}

void prime_arithmetic_test::Given_9_and_4_on_16_bits_When_testing_substrction_Then_operation_is_17()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(9);
    Large b = create_and_initialize_large(4);
    Large difference = create_and_initialize_large(5);
    substraction(a, b, difference, count);
    QCOMPARE(count.operation, 17);
}

void prime_arithmetic_test::Given_9_and_4_on_16_bits_When_testing_substrction_Then_clock_is_1()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(9);
    Large b = create_and_initialize_large(4);
    Large difference = create_and_initialize_large(5);
    addition(a, b, difference, count);
    QCOMPARE(count.clock, 1);
}

void prime_arithmetic_test::Given_5_and_6_on_16_bits_When_testing_multiplication_Then_return_30()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5);
    Large b = create_and_initialize_large(6);
    Large product(32);
    Large expected(32);
    Large sub_expected = create_and_initialize_large(30);
    expected.insert(sub_expected);
    multiplication(a, b, product, count);
    for(uint16_t i=0; i<32; i++)
    {
        qDebug() << i << product[i] << expected[i];
    }
    QVERIFY(is_equal(product, expected, count));
}

void prime_arithmetic_test::Given_5_and_6_on_16_bits_When_testing_multiplication_Then_operation_is_272()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5);
    Large b = create_and_initialize_large(6);
    Large product(32);
    Large expected(32);
    Large sub_expected = create_and_initialize_large(30);
    expected.insert(sub_expected);
    multiplication(a, b, product, count);
    QCOMPARE(count.operation, 272);
}

void prime_arithmetic_test::Given_5_and_6_on_16_bits_When_testing_multiplication_Then_clock_is_16()
{
    Count count;
    count_initialization(count);
    Large a = create_and_initialize_large(5);
    Large b = create_and_initialize_large(6);
    Large product(32);
    Large expected(32);
    Large sub_expected = create_and_initialize_large(30);
    expected.insert(sub_expected);
    multiplication(a, b, product, count);
    QCOMPARE(count.clock, 16);
}

static prime_arithmetic_test PRIME_ARITHMETIC_TEST;
