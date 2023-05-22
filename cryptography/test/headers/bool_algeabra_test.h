#ifndef BOOL_ALGEABRA_TEST_H
#define BOOL_ALGEABRA_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class bool_algeabra_test: public TestSuite
{
    Q_OBJECT
private slots:
    void Given_a_lesser_than_b_When_testing_is_equal_Then_return_false();
    void Given_a_greater_than_b_When_testing_is_equal_Then_return_false();
    void Given_a_equal_b_When_testing_is_equal_Then_return_true();
    void Given_a_equal_b_When_testing_is_equal_Then_verify_count();

    void Given_a_equal_b_When_testing_is_less_than_Then_return_false();
    void Given_a_lesser_than_b_When_testing_is_less_than_Then_return_true();
    void Given_a_greater_than_b_When_testing_is_less_than_Then_return_false();
    void Given_a_equal_b_When_testing_is_less_than_Then_verify_count();

    void Given_a_equal_b_When_testing_is_not_equal_Then_return_false();
    void Given_a_lesser_than_b_When_testing_is_not_equal_Then_return_true();
    void Given_a_greater_than_b_When_testing_is_not_equal_Then_return_true();
    void Given_a_equal_b_When_testing_is_not_equal_Then_verify_count();

    void Given_a_equal_b_When_testing_is_greater_than_Then_return_false();
    void Given_a_greater_than_b_When_testing_is_greater_than_Then_return_true();
    void Given_a_lesser_than_b_When_testing_is_greater_than_Then_return_false();
    void Given_a_equal_b_When_testing_is_greater_than_Then_verify_count();

    void Given_a_greater_than_b_When_testing_is_less_or_equal_Then_return_false();
    void Given_a_equal_b_When_testing_is_less_or_equal_Then_return_true();
    void Given_a_lesser_than_b_When_testing_is_less_or_equal_Then_return_true();
    void Given_a_equal_b_When_testing_is_less_or_equal_Then_verify_count();

    void Given_a_lesser_than_b_When_testing_is_greater_or_equal_Then_return_false();
    void Given_a_equal_b_When_testing_is_greater_or_equal_Then_return_true();
    void Given_a_grater_than_b_When_testing_is_graeter_or_equal_Then_return_true();
    void Given_a_equal_b_When_testing_is_greater_or_equal_Then_verify_count();

    void Given_0_When_testing_NOT_Then_return_1();
    void Given_1_When_testing_NOT_Then_return_0();
    void Given_1_When_testing_NOT_Then_verify_count();

    void Given_0_and_0_When_testing_AND_Then_return_0();
    void Given_0_and_1_When_testing_AND_Then_return_0();
    void Given_1_and_0_When_testing_AND_Then_return_0();
    void Given_1_and_1_When_testing_AND_Then_return_1();
    void Given_1_and_1_When_testing_AND_Then_verify_count();

    void Given_0_and_0_When_testing_NAND_Then_return_1();
    void Given_0_and_1_When_testing_NAND_Then_return_1();
    void Given_1_and_0_When_testing_NAND_Then_return_1();
    void Given_1_and_1_When_testing_NAND_Then_return_0();
    void Given_1_and_1_When_testing_NAND_Then_verify_count();

    void Given_0_and_0_When_testing_OR_Then_return_0();
    void Given_0_and_1_When_testing_OR_Then_return_1();
    void Given_1_and_0_When_testing_OR_Then_return_1();
    void Given_1_and_1_When_testing_OR_Then_return_1();
    void Given_1_and_1_When_testing_OR_Then_verify_count();

    void Given_0_and_0_When_testing_NOR_Then_return_1();
    void Given_0_and_1_When_testing_NOR_Then_return_0();
    void Given_1_and_0_When_testing_NOR_Then_return_0();
    void Given_1_and_1_When_testing_NOR_Then_return_0();
    void Given_1_and_1_When_testing_NOR_Then_verify_count();

    void Given_0_and_0_When_testing_XOR_Then_return_0();
    void Given_0_and_1_When_testing_XOR_Then_return_1();
    void Given_1_and_0_When_testing_XOR_Then_return_1();
    void Given_1_and_1_When_testing_XOR_Then_return_0();
    void Given_1_and_1_When_testing_XOR_Then_verify_count();

    void Given_0_and_0_When_testing_XNOR_Then_return_1();
    void Given_0_and_1_When_testing_XNOR_Then_return_0();
    void Given_1_and_0_When_testing_XNOR_Then_return_0();
    void Given_1_and_1_When_testing_XNOR_Then_return_1();
    void Given_1_and_1_When_testing_XNOR_Then_verify_count();

    void Given_0_1_and_select_0_When_testing_MUX2_bits_Then_return_0();
    void Given_0_1_and_select_1_When_testing_MUX2_bits_Then_return_1();
    void Given_0_1_and_select_1_When_testing_MUX2_bits_Then_verify_count();

    void Given_0_1_on_3_bits_and_select_0_When_testing_MUX2_Large_Then_return_0();
    void Given_0_1_on_3_bits_and_select_1_When_testing_MUX2_Large_Then_return_1();
    void Given_0_1_on_3_bits_and_select_1_When_testing_MUX2_Large_Then_verify_count();

    void Given_0_0_When_testing_HALF_ADDER_Then_sum_is_0();
    void Given_0_0_When_testing_HALF_ADDER_Then_cout_is_0();
    void Given_1_0_When_testing_HALF_ADDER_Then_sum_is_1();
    void Given_1_0_When_testing_HALF_ADDER_Then_cout_is_0();
    void Given_0_1_When_testing_HALF_ADDER_Then_sum_is_1();
    void Given_0_1_When_testing_HALF_ADDER_Then_cout_is_0();
    void Given_1_1_When_testing_HALF_ADDER_Then_sum_is_0();
    void Given_1_1_When_testing_HALF_ADDER_Then_cout_is_1();
    void Given_1_1_When_testing_HALF_ADDER_Then_verify_count();

    void Given_1_1_1_When_testing_ADDER_1_bit_Then_sum_is_1();
    void Given_1_1_1_When_testing_ADDER_1_bit_Then_cout_is_1();
    void Given_1_1_1_When_testing_ADDER_1_bit_Then_verify_count();

    void Given_1_2_on_3_bits_When_testing_ADDER_n_bits_Then_sum_is_3();
    void Given_1_2_on_3_bits_When_testing_ADDER_n_bits_Then_verify_count();

    void Given_2_1_on_3_bits_When_testing_SUB_n_bits_Then_sum_is_1();
    void Given_2_1_on_3_bits_When_testing_SUB_n_bits_Then_verify_count();



};

#endif // BOOL_ALGEABRA_TEST_H
