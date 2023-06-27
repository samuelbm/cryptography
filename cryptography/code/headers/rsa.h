#ifndef RSA_H
#define RSA_H

#include "prime_arithmetic.h"

void rsa_key_generation(uint16_t p_size, uint16_t q_size,  uint16_t e_size, Large const& e, Large& p, Large& q, Large& n, Large& d, Count& count);
void rsa_encryption(Large const& m, Large const& e, Large const& n, Large& C, Count& count);
void rsa_decryption(Large const& C, Large const& d, Large const& p, Large const& q, Large& m, Count& count);

#endif // RSA_H
