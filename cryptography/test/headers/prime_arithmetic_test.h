#ifndef PRIME_ARITHMETIC_TEST_H
#define PRIME_ARITHMETIC_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class prime_arithmetic_test: public TestSuite
{
    Q_OBJECT

private slots:
    void Given_When_Then5();
};

#endif // PRIME_ARITHMETIC_TEST_H
