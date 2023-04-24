#ifndef ECC_TEST_H
#define ECC_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class ECC_test: public TestSuite
{
    Q_OBJECT

private slots:
    void Given_When_Then2();
};

#endif // ECC_TEST_H
