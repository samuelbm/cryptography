#ifndef RSA_H
#define RSA_H

#include <QRandomGenerator>
#include "prime_arithmetic.h"
#include "fast_large.h"

void rsa_key_generation(uint16_t pq_bits,  uint16_t e_size, Large const& e, Large& p, Large& q, Large& n, Large& d, Count& count, QRandomGenerator prng, Storage& storage);
void rsa_encryption(Large const& m, Large const& e, Large const& n, Large& C, Count& count);
void rsa_decryption(Large const& C, Large const& d, Large const& n, Large& m, Count& count);
void rsa_128();
void rsa_400();
void rsa_1024();
void rsa_2044();
void rsa_3072();
void rsa_7680();
//void rsa_15360();

#endif // RSA_H
