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
    void Given_a_equal_b_When_testing_is_less_than_Than_operation_count_is_16();

    void Given_a_equal_b_When_testing_is_not_equal_Than_return_false();
    void Given_a_lesser_than_b_When_testing_is_not_equal_Than_return_true();
    void Given_a_greater_than_b_When_testing_is_not_equal_Than_return_true();
    void Given_a_equal_b_When_testing_is_not_equal_Than_operation_count_is_16();

    void Given_a_equal_b_When_testing_is_greater_than_Than_return_false();
    void Given_a_greater_than_b_When_testing_is_greater_than_Than_return_true();
    void Given_a_lesser_than_b_When_testing_is_greater_than_Than_return_false();
    void Given_a_equal_b_When_testing_is_greater_than_Than_operation_count_is_16();

    void Given_a_greater_than_b_When_testing_is_less_or_equal_Than_return_false();
    void Given_a_equal_b_When_testing_is_less_or_equal_Than_return_true();
    void Given_a_lesser_than_b_When_testing_is_less_or_equal_Than_return_true();
    void Given_a_equal_b_When_testing_is_less_or_equal_Than_operation_count_is_16();

    void Given_a_lesser_than_b_When_testing_is_greater_or_equal_Than_return_false();
    void Given_a_equal_b_When_testing_is_greater_or_equal_Than_return_true();
    void Given_a_grater_than_b_When_testing_is_graeter_or_equal_Than_return_true();
    void Given_a_equal_b_When_testing_is_greater_or_equal_Than_operation_count_is_16();
};

#endif // PRIME_ARITHMETIC_TEST_H
