#ifndef RSA_TEST_H
#define RSA_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class RSA_test: public TestSuite
{
    Q_OBJECT

private slots:
    void Given_When_Then6();
};

#endif // RSA_TEST_H
