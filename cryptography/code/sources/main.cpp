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


    //a_size = b_size = n_size = result_size = size
    //storage_size = dummy_quotient_size = 2*size
    //difference_size = size + 1

uint16_t size = 2;
uint64_t a[size];
uint64_t b[size];
uint64_t n[size];
uint64_t result[size];
uint64_t storage[2*size];
uint64_t dummy_quotient[2*size];
uint64_t difference[size + 1];
a[1] = 1;
a[0] = 1;
b[1] = 1;
b[0] = 1;
n[1] = 0;
n[0] = 1000001;
fast_multiplication_modulo(a, b, n, result, size, storage, dummy_quotient, difference);
Large test = fast_large2Large(result, 32*size);
qDebug() << Large2String(test);

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
