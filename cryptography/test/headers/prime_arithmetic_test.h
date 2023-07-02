#ifndef PRIME_ARITHMETIC_TEST_H
#define PRIME_ARITHMETIC_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class prime_arithmetic_test: public TestSuite
{
    Q_OBJECT

private slots:
    void Given_5_and_4_on_8_bits_When_testing_addition_Then_return_9();
    void Given_5_and_4_on_8_bits_When_testing_addition_Then_verify_count();

    void Given_9_and_4_on_8_bits_When_testing_substraction_Then_return_5();
    void Given_9_and_4_on_8_bits_When_testing_substraction_Then_verify_count();

    void Given_5_and_6_on_8_bits_When_testing_multiplication_Then_return_30();
    void Given_5_and_6_on_8_bits_When_testing_multiplication_Then_verify_count();

    void Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_quotient_is_5();
    void Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_remainder_is_2();
    void Given_17_and_3_on_8_bits_When_testing_division_modulo_Then_verify_count();

    void Given_17_and_3_on_8_bits_When_testing_modulo_Then_remainder_is_2();
    void Given_17_and_3_on_8_bits_When_testing_modulo_Then_verify_count();

    void Given_18_19_and_5_on_5_bits_When_testing_addition_modulo_Then_result_is_2();
    void Given_18_19_and_5_on_5_bits_When_testing_addition_modulo_Then_verify_count();

    void Given_18_19_and_5_on_5_bits_When_testing_substraction_modulo_Then_result_is_4();
    void Given_18_19_and_5_on_5_bits_When_testing_substraction_modulo_Then_verify_count();

    void Given_15_8_and_7_on_4_bits_When_testing_multiplication_modulo_Then_result_is_1();
    void Given_15_8_and_7_on_4_bits_When_testing_multiplication_modulo_Then_verify_count();

    void Given_15_8_and_7_on_4_bits_When_testing_squaring_modulo_Then_result_is_1();
    void Given_15_8_and_7_on_4_bits_When_testing_squaring_modulo_Then_verify_count();

    void Given_3_5_and_7_on_3_bits_When_testing_exponentiation_modulo_Then_result_is_5();
    void Given_3_5_and_7_on_3_bits_When_testing_exponentiation_modulo_Then_verify_count();

    void Given_6600_and_630_on_16_bits_When_testing_greatest_common_divisor_Then_result_is_30();

    void Given_5_4_On_10_bits_When_testing_inverse_Then_result_is_1();
    void Given_5_4_On_10_bits_When_testing_inverse_Then_result_verify_count();
    void Given_5_7_on_10_bits_When_testing_inverse_with_prime_Then_result_is_3();
    void Given_5_7_on_10_bits_When_testing_inverse_with_prime_Then_verify_count();

    void Given_non_prime_25140187_on_32_bits_When_testing_is_prime_with_fermat_little_theorem_Then_return_false();
    void Given_prime_115249_on_32_bits_When_testing_is_prime_with_fermat_little_theorem_Then_return_true();
    void Given_prime_115249_on_32_bits_When_testing_is_prime_with_fermat_little_theorem_Then_verify_count();

    void Given_p_13_q_29_When_testing_find_phi_phi_n_Then_phi_phi_n_is_96();

};

#endif // PRIME_ARITHMETIC_TEST_H
