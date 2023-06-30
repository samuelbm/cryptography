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
};

#endif // FAST_LARGE_TEST_H
