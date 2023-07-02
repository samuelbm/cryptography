#include "testsuite.hpp"
#include "des_test.h"
#include "ecc_test.h"
#include "galois_test.h"
#include "large_test.h"
#include "prime_arithmetic_test.h"
#include "rsa_test.h"
#include "fast_large_test.h"

#include "large.h"
#include "prime_arithmetic.h"
#include "utils.h"

#include <QDebug>
#include "rsa.h"
#include "fast_large.h"
#include <QRandomGenerator>

int main(int argc, char *argv[])
{
    qDebug() << argc << argv[0][0];

//    // setup lambda
//    int status = 0;
//    auto runTest = [&status, argc, argv](QObject* obj) {
//        status |= QTest::qExec(obj, argc, argv);
//    };

//    // run suite
//    auto &suite = TestSuite::suite();
//    for (auto it = suite.begin(); it != suite.end(); ++it) {
//        runTest(*it);
//    }

//    if(status)
//    {
//        qDebug() << "Test Failed";// << Qt::endl;
//        return 0;
//    }
//    else
//    {
//        qDebug() << "Test Successful";// << Qt::endl;
//    }


    //regarder si ca me prend le meme temps pour encryption et decryption si oui on va le faire juste une fois.
    rsa_128(10);
    return 0;
}

