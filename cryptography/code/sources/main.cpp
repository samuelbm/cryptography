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

    Count count;
    count_initialization(count);
    QRandomGenerator prng(1234);
    uint16_t nb_bits = 100;
    uint16_t size = 4;
    Storage storage;
    uint16_t nb_primes_to_find = 10;
    uint16_t nb_round = 20;
    uint16_t tries;
    Large prime(nb_bits);
    new_storage(storage, size);
    for(uint64_t i=0; i<nb_primes_to_find; i++)
    {
        tries = 0;
        prime = find_prime_equiv_3_mod_4(size, prng, nb_bits, nb_round, tries, storage, count);
        qDebug() << i << tries << Large2String(prime);
    }
    delete_storage(storage);

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
