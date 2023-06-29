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
