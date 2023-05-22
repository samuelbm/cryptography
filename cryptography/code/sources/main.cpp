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
    Large x(5);
    x[0] = true;
    x[1] = true;
    x[2] = true;
    x[3] = true;
    x[4] = true;
    Large a(4);
    a[0] = true;
    a[1] = true;
    Large n(4);
    n[0] = true;
    n[1] = true;
    n[2] = true;
    Large result(4);

    qDebug() << a.toHex() << x.toHex() << n.toHex();
    exponentiation_modulo(a, x, n, result, count);
    return 0;
}










