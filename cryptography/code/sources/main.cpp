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

//    uint16_t size = 2;
//    Storage storage;
//    new_storage(storage, size);
//    uint64_t base[size];
//    uint64_t exponent[size + 1];
//    uint64_t modulus[size];
//    uint64_t result[size];
//    uint64_t squared[size];

//    base[1] = 1;
//    base[0] = 1;
//    modulus[1] = 0;
//    modulus[0] = 1000000;
//    exponent[2] = 0;
//    exponent[1] = 1;
//    exponent[0] = 1;
//    //fast_exponentiation_modulo(base, exponent, modulus, result, size, size+1, squared, storage, dummy_quotient, difference, result_storage, squared_storage);
//    Large test = fast_large2Large(result, 32*size);
//    qDebug() << Large2String(test);

//    delete_storage(storage);
//    //rsa_dummy1();
    return 0;
}
