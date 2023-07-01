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

    qDebug() << "-----------------------------";
    qDebug() << "start";
    QRandomGenerator prng(1234);
    uint16_t size = 32;
    Storage storage;
    new_storage(storage, size);
    uint16_t nb_bits = 1024;
    uint16_t nb_round = 100;
    uint64_t prime[size];
    uint16_t tries;
    for(int i = 0; i<10; i++)
    {
        tries = fast_find_prime_equiv_3_mod_4(prime, size, prng, storage, nb_round, nb_bits);
        Large lprime = fast_large2Large(prime, nb_bits);
        qDebug() << i << tries << Large2String(lprime);
    }

    delete_storage(storage);
    qDebug() << "done";


//    rsa_dummy1();
//    return 0;
}
//816983375325856467272146355509
//816983375325856467272146355509
//1010 = 10
//01001111110100001100111100010000 = 1339084560
//10100100010001011110110111110111 = 2756046327
//10010011010111000000010100110101 = 2472281397
//816983375325856467272146355509
