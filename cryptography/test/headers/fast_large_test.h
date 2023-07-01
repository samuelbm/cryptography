#ifndef FAST_LARGE_TEST_H
#define FAST_LARGE_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class Fast_large_test: public TestSuite
{
    Q_OBJECT

private slots:
    void Given_a_greater_than_b_When_testing_fast_is_equal_Then_return_false();
    void Given_a_equals_b_When_testing_fast_is_equal_Then_return_true();
    void Given_a_is_less_than_b_When_testing_fast_is_equal_Then_return_false();

    void Given_a_greater_than_b_When_testing_fast_is_less_than_Then_return_false();
    void Given_a_equals_b_When_testing_fast_is_less_than_Then_return_false();
    void Given_a_is_less_than_b_When_testing_fast_is_less_than_Then_return_true();

    void Given_a_greater_than_b_When_testing_fast_is_less_or_equal_than_Then_return_false();
    void Given_a_equals_b_When_testing_fast_is_less_or_equal_than_Then_return_true();
    void Given_a_is_less_than_b_When_testing_fast_is_less_or_equal_than_Then_return_true();

    void Given_a_2_2_and_b_1_1_When_testing_fast_substraction_Then_difference_is_1_1();
    void Given_b_1_FFFFFFFF_and_sum_1_When_testing_fast_addition_mono_Then_sum_is_2_00000000();
    void Given_a_1_1_b_1_1_When_testing_fast_multiplication_Then_product_is_0_1_2_1();
    void Given_number_number_1_1_carry_0_When_fast_shift_left_Then_number_is_2_2();
    void Given_number_number_1_1_carry_1_When_fast_shift_left_Then_number_is_2_3();
    void Given_a_1234567890_1234567890_b_1000000_When_testing_fast_division_modulo_Then_quotient_is_5302428713476();
    void Given_a_1234567890_1234567890_b_1000000_When_testing_fast_division_modulo_Then_remainder_is_293330();
    void Given_a_1_1_b_1_1_n_1000000_When_testing_fast_multiplication_modulo_Then_result_is_486209();
    void Given_base_1_1_exponent_1_1_modulus_1000000_When_testing_fast_exponentiation_modulo_Then_result_is_259137();
    void Given_non_prime_25140187_on_32_bits_When_testing_fast_is_prime_with_fermat_little_theorem_Then_return_false();
    void Given_prime_115249_on_32_bits_When_testing_fast_is_prime_with_fermat_little_theorem_Then_return_true();
};

#endif // FAST_LARGE_TEST_H
