#ifndef GALOIS_TEST_H
#define GALOIS_TEST_H

#include "testsuite.hpp"
#include <QtTest/QtTest>

class Galois_test: public TestSuite
{
    Q_OBJECT

private slots:
    void Given_When_Then3();
};

#endif // GALOIS_TEST_H
