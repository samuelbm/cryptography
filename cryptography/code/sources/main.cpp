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
#include <QElapsedTimer>

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


//    Count count;
//    Large e(17);
//    Large d(50);
//    Large p(50);
//    Large q(50);
//    Large n(100);
//    Large m(100);
//    Large C(100);
//    p.init_with_small_number(11);
//    q.init_with_small_number(17);
//    n.init_with_small_number(187);
//    e.init_with_small_number(7);
//    d.init_with_small_number(23);
//    m.init_with_small_number(3);

//    count_initialization(count);
//    rsa_encryption(m, e, n, C, count);
//    count_initialization(count);
//    rsa_decryption(C, d, n, m, count);

    QElapsedTimer timer;
    uint16_t nb_bits = 15360/2;
    uint16_t size = nb_bits/32;
    qDebug() << size;

    Storage storage;
    new_storage(storage, size);
    uint64_t x[size];
    uint64_t y[size];
    uint64_t p[2*size];
    fast_clear(x, size);
    fast_clear(y, size);
    fast_clear(p, 2*size);
    x[0] = 8;
    y[0] = 8;

    timer.start();
    fast_multiplication(x, y, p, size, size, storage);
    qDebug() << timer.elapsed();

    Count count;
    Large a(nb_bits);
    Large b(nb_bits);
    Large n(2*nb_bits);
    a.init_with_small_number(8);
    b.init_with_small_number(8);
    timer.start();
    multiplication(a, b, n, count);
    qDebug() << timer.elapsed();
    delete_storage(storage);

   return 0;
}

