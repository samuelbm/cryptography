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
    Large a(8);
    Large b(8);
    Large r(8);
    Large q(8);
    a[0] = true;
    //a[1] = true;
    a[4] = true;
    b[1] = true;
    b[0] = true;
    division_modulo(a, b, q, r, count);
    qDebug() << a.toHex() << b.toHex() << q.toHex() << r.toHex();

    return 0;
}










