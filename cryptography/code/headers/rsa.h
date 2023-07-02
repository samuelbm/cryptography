#ifndef RSA_H
#define RSA_H

#include <QRandomGenerator>
#include "prime_arithmetic.h"
#include "fast_large.h"

void rsa_key_generation(uint16_t size, uint16_t pq_bits, Large const& e, Large& p, Large& q, Large& n, Large& d, Count& count, QRandomGenerator& prng, Storage& storage);
void rsa_encryption(Large const& m, Large const& e, Large const& n, Large& C, Count& count);
void rsa_decryption(Large const& C, Large const& d, Large const& n, Large& m, Count& count);
void rsa_128(uint16_t nb_tries);
void rsa_400(uint16_t nb_tries);
void rsa_1024(uint16_t nb_tries);
void rsa_2044(uint16_t nb_tries);
void rsa_3072(uint16_t nb_tries);
void rsa_7680(uint16_t nb_tries);
//void rsa_15360(uint16_t nb_tries);

#endif // RSA_H
