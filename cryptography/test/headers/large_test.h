#ifndef LARGE_TEST_H
#define LARGE_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class Large_test: public TestSuite
{
    Q_OBJECT

private slots:
    void Given_When_Then4();

};

#endif // LARGE_TEST_H
