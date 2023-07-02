#include "rsa.h"
#include <QDebug>
#include "prime_arithmetic.h"

void rsa_key_genekey_generationration(uint16_t pq_bits, uint16_t e_size, Large const& e, Large& p, Large& q, Large& n, Large& d, Count& count, QRandomGenerator prng, Storage& storage)
{
    uint16_t nb_round = 20;
    uint16_t tries = 0;
    p = find_prime_equiv_3_mod_4(pq_bits, prng, pq_bits, nb_round, tries, storage, count);
    q = find_prime_equiv_3_mod_4(pq_bits, prng, pq_bits, nb_round, tries, storage, count);
    multiplication(p, q, n, count);

}

void rsa_encryption(Large const& m, Large const& e, Large const& n, Large& C, Count& count)
{
    exponentiation_modulo(m, e, n, C, count);
}

void rsa_decryption(Large const& C, Large const& d, Large const& n, Large& m, Count& count)
{
    exponentiation_modulo(C, d, n, m, count);
}

void rsa_128()
{

}

void rsa_400()
{

}

void rsa_1024()
{

}

void rsa_2044()
{

}

void rsa_3072()
{

}

void rsa_7680()
{

}

//void rsa_15360()
//{
//
//}
