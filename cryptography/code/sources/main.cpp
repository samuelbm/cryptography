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
#include "utils.h"

#include "miller-rabin-gmp.h"
#include "rsa.h"
#include "fast_large.h"

int main(int argc, char *argv[])
{

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

    //int NB_ROUNDS = 40;
    //mpz_class my_mpz();
    //bool is_prime = prob_prime(my_mpz, NB_ROUNDS) >= 0.5;

uint64_t a[4];
uint64_t b[2];
uint64_t quotient[4];
uint64_t remainder[2];
uint64_t difference[3];
uint16_t size_a = 4;
uint16_t size_b = 2;
a[3] = 0;
a[2] = 0;
a[1] = 1234567890;
a[0] = 13;
b[1] = 1;
b[0] = 1;
fast_division_modulo(a, b, quotient, remainder, size_a, size_b, difference);
Large la = fast_large2Large(a, 4*32);
Large lb = fast_large2Large(b, 2*32);
Large lq = fast_large2Large(quotient, 4*32);
Large lr = fast_large2Large(remainder, 2*32);
qDebug() << Large2String(lq) << Large2String(lr);

//uint64_t d[3];
//d[2] = 1;
//d[1] = 4294967295;
//d[0] = 4294967290;
//fast_addition_mono(6, d, 3);
//Large test2 = fast_large2Large(d, 70);
//qDebug() << test2.toHex();


//    qDebug() << "start";
//    Count count;
//    count_initialization(count);
//    QRandomGenerator prng(1234);

//    for(uint16_t i=0; i<10; i++)
//    {
//        Large x = find_prime_equiv_3_mod_4(100, prng, count);
//        qDebug() << i << Large2String(x);
//    }

    rsa_dummy1();
    qDebug() << "finished";
    return 0;
}
