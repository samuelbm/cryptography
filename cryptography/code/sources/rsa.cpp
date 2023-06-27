#include "rsa.h"


void rsa_key_genekey_generationration(uint16_t p_size, uint16_t q_size,  uint16_t e_size, Large const& e, Large& p, Large& q, Large& n, Large& d, Count& count)
{

}

void rsa_encryption(Large const& m, Large const& e, Large const& n, Large& C, Count& count)
{
    exponentiation_modulo(m, e, n, C, count);
}

void rsa_decryption(Large const& C, Large const& d, Large const& n, Large& m, Count& count)
{
    exponentiation_modulo(C, d, n, m, count);
}
