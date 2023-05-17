#include <QDebug>
#include "des_test.h"
#include "ecc_test.h"
#include "galois_test.h"
#include "large_test.h"
#include "prime_arithmetic_test.h"
#include "rsa_test.h"
#include "testsuite.hpp"

#include "large.h"
#include "prime_arithmetic.h"


int main(int argc, char *argv[])
{

    // setup lambda
    int status = 0;
    auto runTest = [&status, argc, argv](QObject* obj) {
        status |= QTest::qExec(obj, argc, argv);
    };

    // run suite
    auto &suite = TestSuite::suite();
    for (auto it = suite.begin(); it != suite.end(); ++it) {
        runTest(*it);
    }

    if(status)
    {
        qDebug() << "Test Failed";// << Qt::endl;
        return 0;
    }
    else
    {
        qDebug() << "Test Successful";// << Qt::endl;
    }


    Count count;
    count_initialization(count);
    Large dividend(6);
    Large divisor(3);
    Large quotient(6);
    Large remainder(3);
    dividend[0] = true;
    dividend[3] = true;
    divisor[0] = true;
    divisor[2] = true;
    division_modulo(dividend, divisor, quotient, remainder, count);
    qDebug() << dividend.toHex() << divisor.toHex() << quotient.toHex() << remainder.toHex();
    return 0;
}










