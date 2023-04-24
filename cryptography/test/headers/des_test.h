#ifndef DES_TEST_H
#define DES_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class DES_test: public TestSuite
{
    Q_OBJECT

private slots:
    void Given_When_Then1();
};

#endif // DES_TEST_H
