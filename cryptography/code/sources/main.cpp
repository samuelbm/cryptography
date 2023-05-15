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
    Large multiplicand(4);
    Large multiplicator(4);
    Large product(8);
    multiplicand[0] = true;
    multiplicand[1] = false;
    multiplicand[2] = true;
    multiplicand[3] = false;
    multiplicator[0] = false;
    multiplicator[1] = true;
    multiplicator[2] = true;
    multiplicator[3] = false;

    multiplication(multiplicand, multiplicator, product, count);
    qDebug() << multiplicand.toHex() << multiplicator.toHex() << product.toHex();


    return 0;
}










