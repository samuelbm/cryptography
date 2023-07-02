#include "rsa.h"
#include <QDebug>
#include "prime_arithmetic.h"

void rsa_key_genekey_generationration(uint16_t size, uint16_t pq_bits, Large const& e, Large& p, Large& q, Large& n, Large& d, Count& count, QRandomGenerator& prng, Storage& storage)
{
    uint16_t nb_round = 20;
    uint16_t tries = 0;
    p = find_prime_equiv_3_mod_4(size, prng, pq_bits, nb_round, tries, storage, count);
    q = find_prime_equiv_3_mod_4(size, prng, pq_bits, nb_round, tries, storage, count);
    multiplication(p, q, n, count);
    //Large phi_n = find_phi_n(p, q, count);
    //Large phi_phi_n = find_phi_phi_n(phi_n, count);
    //Large one(phi_phi_n.get_number_of_bits());
    //Large phi_phi_n_minus_one(phi_phi_n.get_number_of_bits());
    //one.init_with_small_number(1);
    //substraction(phi_phi_n, one, phi_phi_n_minus_one, count);
    //exponentiation_modulo(e, phi_phi_n_minus_one, phi_n, d, count);
    qDebug() << "RSA keygen: " << pq_bits << "bits, " << "p: " << Large2String(p) << ", q: " << Large2String(q)  << ", n: " << Large2String(n) << ", e: " << Large2String(e)  << ", d:" << Large2String(d) << count2string(count);
}

void rsa_encryption(Large const& m, Large const& e, Large const& n, Large& C, Count& count)
{
    exponentiation_modulo(m, e, n, C, count);
    qDebug() << "RSA encryption, " << "m: " << Large2String(m) << "C: " << Large2String(C) << count2string(count);
}

void rsa_decryption(Large const& C, Large const& d, Large const& n, Large& m, Count& count)
{
    exponentiation_modulo(C, d, n, m, count);
    qDebug() << "RSA decryption, " << "C: " << Large2String(C) << "m: " << Large2String(m) << count2string(count);
}

void rsa_keygen_128(uint16_t nb_tries)
{
    uint16_t pq_bits = 64;
    QRandomGenerator prng(1234);
    Count count;
    Storage storage;
    uint16_t size = 4;
    new_storage(storage, size);
    Large p(pq_bits);
    Large q(pq_bits);
    Large n(2*pq_bits);
    Large e(17);
    Large d(pq_bits);
    e.init_with_small_number(65537);
    Large m(pq_bits);
    Large C(pq_bits);
    qDebug() << "RSA 128 bits";
    for(uint16_t i = 0; i<nb_tries; i++)
    {
        count_initialization(count);
        rsa_key_genekey_generationration(size, pq_bits, e, p, q, n, d, count, prng, storage);
        //count_initialization(count);
        //rsa_encryption(m, e, n, C, count);
        //count_initialization(count);
        //rsa_decryption(C, d, n, m, count);
    }
    delete_storage(storage);
}

void rsa_keygen_400(uint16_t nb_tries)
{

}

void rsa_keygen_1024(uint16_t nb_tries)
{

}

void rsa_keygen_2044(uint16_t nb_tries)
{

}

void rsa_keygen_3072(uint16_t nb_tries)
{

}

void rsa_keygen_7680(uint16_t nb_tries)
{

}

//void rsa_keygen_15360(uint16_t nb_tries)
//{
//
//}

void rsa_encryption_128(uint16_t nb_tries)
{

}

void rsa_encryption_400(uint16_t nb_tries)
{

}

void rsa_encryption_1024(uint16_t nb_tries)
{

}

void rsa_encryption_2044(uint16_t nb_tries)
{

}

void rsa_encryption_3072(uint16_t nb_tries)
{

}

void rsa_encryption_7680(uint16_t nb_tries)
{

}

//void rsa_encryption_15360(uint16_t nb_tries)
//{
//
//}

void rsa_decryption_128(uint16_t nb_tries)
{

}

void rsa_decryption_400(uint16_t nb_tries)
{

}

void rsa_decryption_1024(uint16_t nb_tries)
{

}

void rsa_decryption_2044(uint16_t nb_tries)
{

}

void rsa_decryption_3072(uint16_t nb_tries)
{

}

void rsa_decryption_7680(uint16_t nb_tries)
{

}

//void rsa_decryption_15360(uint16_t nb_tries)
//{
//
//}
