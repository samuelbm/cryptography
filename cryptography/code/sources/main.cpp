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
    Large e(17);
    Large d(50);
    Large p(50);
    Large q(50);
    Large n(100);
    Large m(100);
    Large C(100);
    p.init_with_small_number(11);
    q.init_with_small_number(17);
    n.init_with_small_number(187);
    e.init_with_small_number(7);
    d.init_with_small_number(23);
    m.init_with_small_number(3);

    count_initialization(count);
    rsa_encryption(m, e, n, C, count);
    count_initialization(count);
    rsa_decryption(C, d, n, m, count);
    return 0;
}

