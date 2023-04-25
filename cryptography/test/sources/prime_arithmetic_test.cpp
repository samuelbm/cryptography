#include "prime_arithmetic_test.h"
#include "prime_arithmetic.h"


Large create_and_initialize_large(uint16_t init_value)
{
    uint16_t n_bits = 16;
    Large large(n_bits);
    for(uint16_t i=0; i<n_bits; i++)
    {
        large[i] = (init_value >> (n_bits - i - 1)) & 1;
    }
    return large;
};

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_equal_Than_return_false()
{
    uint64_t operation_count;
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(~is_equal(a_lesser, b, operation_count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_equal_Than_return_false()
{
    uint64_t operation_count;
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(~is_equal(a_greater, b, operation_count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_equal_Than_return_true()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_equal(a_equal, b, operation_count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_equal_Than_operation_count_is_16()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_equal(a_equal, b, operation_count);
    QCOMPARE(operation_count, 16);
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_than_Than_return_false()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(~is_less_than(a_equal, b, operation_count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_less_than_Than_return_true()
{
    uint64_t operation_count;
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_less_than(a_lesser, b, operation_count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_less_than_Than_return_false()
{
    uint64_t operation_count;
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(~is_less_than(a_greater, b, operation_count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_than_Than_operation_count_is_16()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_less_than(a_equal, b, operation_count);
    QCOMPARE(operation_count, 16);
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_not_equal_Than_return_false()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(~is_not_equal(a_equal, b, operation_count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_not_equal_Than_return_true()
{
    uint64_t operation_count;
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_not_equal(a_lesser, b, operation_count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_not_equal_Than_return_true()
{
    uint64_t operation_count;
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_not_equal(a_greater, b, operation_count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_not_equal_Than_operation_count_is_16()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_not_equal(a_equal, b, operation_count);
    QCOMPARE(operation_count, 16);
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_than_Than_return_false()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_greater_than(a_equal, b, operation_count);
    QVERIFY(~is_greater_than(a_equal, b, operation_count));
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_greater_than_Than_return_true()
{
    uint64_t operation_count;
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_greater_than(a_greater, b, operation_count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_greater_than_Than_return_false()
{
    uint64_t operation_count;
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(~is_greater_than(a_lesser, b, operation_count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_than_Than_operation_count_is_16()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_greater_than(a_equal, b, operation_count);
    QCOMPARE(operation_count, 16);
}

void prime_arithmetic_test::Given_a_greater_than_b_When_testing_is_less_or_equal_Than_return_false()
{
    uint64_t operation_count;
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(~is_less_or_equal(a_greater, b, operation_count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_or_equal_Than_return_true()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_less_or_equal(a_equal, b, operation_count));
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_less_or_equal_Than_return_true()
{
    uint64_t operation_count;
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_less_or_equal(a_lesser, b, operation_count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_less_or_equal_Than_operation_count_is_16()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_less_or_equal(a_equal, b, operation_count);
    QCOMPARE(operation_count, 16);
}

void prime_arithmetic_test::Given_a_lesser_than_b_When_testing_is_greater_or_equal_Than_return_false()
{
    uint64_t operation_count;
    Large a_lesser = create_and_initialize_large(4);
    Large b = create_and_initialize_large(5);
    QVERIFY(~is_greater_or_equal(a_lesser, b, operation_count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_or_equal_Than_return_true()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_greater_or_equal(a_equal, b, operation_count));
}

void prime_arithmetic_test::Given_a_grater_than_b_When_testing_is_graeter_or_equal_Than_return_true()
{
    uint64_t operation_count;
    Large a_greater = create_and_initialize_large(6);
    Large b = create_and_initialize_large(5);
    QVERIFY(is_greater_or_equal(a_greater, b, operation_count));
}

void prime_arithmetic_test::Given_a_equal_b_When_testing_is_greater_or_equal_Than_operation_count_is_16()
{
    uint64_t operation_count;
    Large a_equal = create_and_initialize_large(5);
    Large b = create_and_initialize_large(5);
    is_greater_or_equal(a_equal, b, operation_count);
    QCOMPARE(operation_count, 16);
}

static prime_arithmetic_test PRIME_ARITHMETIC_TEST;
