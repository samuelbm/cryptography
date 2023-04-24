#include <QDebug>
#include "des_test.h"
#include "ecc_test.h"
#include "galois_test.h"
#include "large_test.h"
#include "prime_arithmetic_test.h"
#include "rsa_test.h"
#include "testsuite.hpp"


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
        qDebug() << "Test Failed" << Qt::endl;
        return 0;
    }
    else
    {
        qDebug() << "Test Successful" << Qt::endl;
    }

//

//

    return 0;
}










