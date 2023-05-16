#ifndef PRIME_ARITHMETIC_TEST_H
#define PRIME_ARITHMETIC_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class prime_arithmetic_test: public TestSuite
{
    Q_OBJECT

private slots:
    void Given_a_lesser_than_b_When_testing_is_equal_Than_return_false();
    void Given_a_greater_than_b_When_testing_is_equal_Than_return_false();
    void Given_a_equal_b_When_testing_is_equal_Than_return_true();
    void Given_a_equal_b_When_testing_is_equal_Than_operation_count_is_16();

    void Given_a_equal_b_When_testing_is_less_than_Than_return_false();
    void Given_a_lesser_than_b_When_testing_is_less_than_Than_return_true();
    void Given_a_greater_than_b_When_testing_is_less_than_Than_return_false();
    void Given_a_equal_b_When_testing_is_less_than_Than_operation_count_is_8();

    void Given_a_equal_b_When_testing_is_not_equal_Than_return_false();
    void Given_a_lesser_than_b_When_testing_is_not_equal_Than_return_true();
    void Given_a_greater_than_b_When_testing_is_not_equal_Than_return_true();
    void Given_a_equal_b_When_testing_is_not_equal_Than_operation_count_is_8();

    void Given_a_equal_b_When_testing_is_greater_than_Than_return_false();
    void Given_a_greater_than_b_When_testing_is_greater_than_Than_return_true();
    void Given_a_lesser_than_b_When_testing_is_greater_than_Than_return_false();
    void Given_a_equal_b_When_testing_is_greater_than_Than_operation_count_is_8();

    void Given_a_greater_than_b_When_testing_is_less_or_equal_Than_return_false();
    void Given_a_equal_b_When_testing_is_less_or_equal_Than_return_true();
    void Given_a_lesser_than_b_When_testing_is_less_or_equal_Than_return_true();
    void Given_a_equal_b_When_testing_is_less_or_equal_Than_operation_count_is_8();

    void Given_a_lesser_than_b_When_testing_is_greater_or_equal_Than_return_false();
    void Given_a_equal_b_When_testing_is_greater_or_equal_Than_return_true();
    void Given_a_grater_than_b_When_testing_is_graeter_or_equal_Than_return_true();
    void Given_a_equal_b_When_testing_is_greater_or_equal_Than_operation_count_is_8();

    void Given_5_and_4_on_8_bits_When_testing_addition_Then_return_9();
    void Given_5_and_4_on_8_bits_When_testing_addition_Then_operation_is_8();
    void Given_5_and_4_on_8_bits_When_testing_addition_Then_clock_is_0();

    void Given_9_and_4_on_8_bits_When_testing_substrction_Then_return_5();
    void Given_9_and_4_on_8_bits_When_testing_substrction_Then_operation_is_8();
    void Given_9_and_4_on_8_bits_When_testing_substrction_Then_clock_is_0();

    void Given_5_and_6_on_8_bits_When_testing_multiplication_Then_return_30();
    void Given_5_and_6_on_8_bits_When_testing_multiplication_Then_operation_is_64();
    void Given_5_and_6_on_8_bits_When_testing_multiplication_Then_clock_is_8();

    void Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_quotient_is_5();
    void Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_remainder_is_2();
    void Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_operation_is_128();
    void Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_clock_is_8();
};

#endif // PRIME_ARITHMETIC_TEST_H
