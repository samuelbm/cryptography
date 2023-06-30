#include "fast_large_test.h"
#include "fast_large.h"

void Fast_large_test::Given_a_greater_than_b_When_testing_fast_is_equal_Then_return_false()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    a[1] = 2;
    a[0] = 1;
    b[1] = 1;
    b[0] = 1;
    QVERIFY(!fast_is_equal(a, b, size));
}

void Fast_large_test::Given_a_equals_b_When_testing_fast_is_equal_Then_return_true()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    a[1] = 1;
    a[0] = 1;
    b[1] = 1;
    b[0] = 1;
    QVERIFY(fast_is_equal(a, b, size));
}

void Fast_large_test::Given_a_is_less_than_b_When_testing_fast_is_equal_Then_return_false()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    a[1] = 1;
    a[0] = 1;
    b[1] = 2;
    b[0] = 1;
    QVERIFY(!fast_is_equal(a, b, size));
}

void Fast_large_test::Given_a_greater_than_b_When_testing_fast_is_less_than_Then_return_false()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    a[1] = 2;
    a[0] = 1;
    b[1] = 1;
    b[0] = 1;
    QVERIFY(!fast_is_less_than(a, b, size));
}

void Fast_large_test::Given_a_equals_b_When_testing_fast_is_less_than_Then_return_false()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    a[1] = 1;
    a[0] = 1;
    b[1] = 1;
    b[0] = 1;
    QVERIFY(!fast_is_less_than(a, b, size));
}

void Fast_large_test::Given_a_is_less_than_b_When_testing_fast_is_less_than_Then_return_true()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    a[1] = 1;
    a[0] = 1;
    b[1] = 2;
    b[0] = 1;
    QVERIFY(fast_is_less_than(a, b, size));
}

void Fast_large_test::Given_a_greater_than_b_When_testing_fast_is_less_or_equal_than_Then_return_false()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    a[1] = 2;
    a[0] = 1;
    b[1] = 1;
    b[0] = 1;
    QVERIFY(!fast_is_less_or_equal_than(a, b, size));
}

void Fast_large_test::Given_a_equals_b_When_testing_fast_is_less_or_equal_than_Then_return_true()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    a[1] = 1;
    a[0] = 1;
    b[1] = 1;
    b[0] = 1;
    QVERIFY(fast_is_less_or_equal_than(a, b, size));
}

void Fast_large_test::Given_a_is_less_than_b_When_testing_fast_is_less_or_equal_than_Then_return_true()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    a[1] = 1;
    a[0] = 1;
    b[1] = 2;
    b[0] = 1;
    QVERIFY(fast_is_less_or_equal_than(a, b, size));
}

void Fast_large_test::Given_a_2_2_and_b_1_1_When_testing_fast_substraction_Then_difference_is_1_1()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    uint64_t difference[size + 1];
    uint64_t expected[size + 1];
    Storage storage;
    new_storage(storage, size);
    a[1] = 2;
    a[0] = 2;
    b[1] = 1;
    b[0] = 1;
    expected[1] = 1;
    expected[0] = 1;
    fast_substraction(a, b, difference, size, storage);
    delete_storage(storage);
    QVERIFY(fast_is_equal(difference, expected, size));
}

void Fast_large_test::Given_b_1_FFFFFFFF_and_sum_1_When_testing_fast_addition_mono_Then_sum_is_2_00000000()
{
    uint16_t size = 2;
    uint64_t sum[size];
    uint64_t expected[size];
    uint64_t b = 1;
    sum[1] = 1;
    sum[0] = 4294967295;
    expected[1] = 2;
    expected[0] = 0;
    fast_addition_mono(b, sum, size);
    QVERIFY(fast_is_equal(sum, expected, size));
}

void Fast_large_test::Given_a_1_1_b_1_1_When_testing_fast_multiplication_Then_product_is_0_1_2_1()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    uint64_t product[2*size];
    uint64_t expected[2*size];
    Storage storage;
    new_storage(storage, size);
    a[1] = 1;
    a[0] = 1;
    b[1] = 1;
    b[0] = 1;
    expected[3] = 0;
    expected[2] = 1;
    expected[1] = 2;
    expected[0] = 1;
    fast_multiplication(a, b, product, size, size, storage);
    delete_storage(storage);
    qDebug() << product[3] << product[2] << product[1] << product[0];
    qDebug() << expected[3] << expected[2] << expected[1] << expected[0];
    QVERIFY(fast_is_equal(product, expected, size));
}

static Fast_large_test FAST_LARGE_TEST;
