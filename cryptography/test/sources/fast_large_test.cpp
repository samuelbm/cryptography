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
    QVERIFY(fast_is_equal(product, expected, size));
}

void Fast_large_test::Given_number_number_1_1_carry_0_When_fast_shift_left_Then_number_is_2_2()
{
    uint16_t size = 2;
    uint64_t number[size];
    uint64_t expected[size];
    number[1] = 1;
    number[0] = 1;
    expected[1] = 2;
    expected[0] = 2;
    fast_shift_left(number, size, false);
    QVERIFY(fast_is_equal(number, expected, size));
}

void Fast_large_test::Given_number_number_1_1_carry_1_When_fast_shift_left_Then_number_is_2_3()
{
    uint16_t size = 2;
    uint64_t number[size];
    uint64_t expected[size];
    number[1] = 1;
    number[0] = 1;
    expected[1] = 2;
    expected[0] = 3;
    fast_shift_left(number, size, true);
    QVERIFY(fast_is_equal(number, expected, size));
}

void Fast_large_test::Given_a_1234567890_1234567890_b_1000000_When_testing_fast_division_modulo_Then_quotient_is_5302428713476()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    uint64_t quotient[size];
    uint64_t remainder[size];
    uint64_t expected[size];
    Storage storage;
    new_storage(storage, size);
    a[1] = 1234567890;
    a[0] = 1234567890;
    b[1] = 0;
    b[0] = 1000000;
    expected[1] = 1234;
    expected[0] = 2439070212;
    fast_division_modulo(a, b, quotient, remainder, size, size, storage);
    delete_storage(storage);
    QVERIFY(fast_is_equal(quotient, expected, size));
}

void Fast_large_test::Given_a_1234567890_1234567890_b_1000000_When_testing_fast_division_modulo_Then_remainder_is_293330()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    uint64_t quotient[size];
    uint64_t remainder[size];
    uint64_t expected[size];
    Storage storage;
    new_storage(storage, size);
    a[1] = 1234567890;
    a[0] = 1234567890;
    b[1] = 0;
    b[0] = 1000000;
    expected[1] = 0;
    expected[0] = 293330;
    fast_division_modulo(a, b, quotient, remainder, size, size, storage);
    delete_storage(storage);
    QVERIFY(fast_is_equal(remainder, expected, size));
}

void Fast_large_test::Given_a_1_1_b_1_1_n_1000000_When_testing_fast_multiplication_modulo_Then_result_is_486209()
{
    uint16_t size = 2;
    uint64_t a[size];
    uint64_t b[size];
    uint64_t n[size];
    uint64_t result[size];
    uint64_t expected[size];
    Storage storage;
    new_storage(storage, size);
    a[1] = 1;
    a[0] = 1;
    b[1] = 1;
    b[0] = 1;
    n[1] = 0;
    n[0] = 1000000;
    expected[1] = 0;
    expected[0] = 486209;
    fast_multiplication_modulo(a, b, n, result, size, storage);
    delete_storage(storage);
    QVERIFY(fast_is_equal(result, expected, size));
}

void Fast_large_test::Given_base_1_1_exponent_1_1_modulus_1000000_When_testing_fast_exponentiation_modulo_Then_result_is_259137()
{
//    uint16_t size = 2;
//    uint16_t size_exponent = 3;
//    uint64_t base[size];
//    uint64_t exponent[size];
//    uint64_t modulus[size];
//    uint64_t result[size];
//    uint64_t expected[size];
//    Storage storage;
//    new_storage(storage, size);
//    base[1] = 1234567890;
//    base[0] = 1234567890;
//    exponent[2] = 0;
//    exponent[1] = 0;
//    exponent[0] = 1000000;
//    modulus[1] = 1;
//    modulus[0] = 1;
//    expected[1] = 0;
//    expected[0] = 293330;
//    fast_exponentiation_modulo(base, exponent, modulus, result, size, size_exponent, storage);
//    delete_storage(storage);
//    QVERIFY(fast_is_equal(result, expected, size));
}

static Fast_large_test FAST_LARGE_TEST;
