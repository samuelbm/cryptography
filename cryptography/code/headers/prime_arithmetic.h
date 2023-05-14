#ifndef PRIME_ARITHMETIC_H
#define PRIME_ARITHMETIC_H

#include "large.h"

typedef struct Count
{
    uint64_t operation;
    uint64_t clock;
} Count;

void count_initialization(Count& count);

bool is_equal(Large const& a, Large const& b, Count& count);
bool is_less_than(Large const& a, Large const& b, Count& count);
bool is_not_equal(Large const& a, Large const& b, Count& count);
bool is_greater_than(Large const& a, Large const& b, Count& count);
bool is_less_or_equal(Large const& a, Large const& b, Count& count);
bool is_greater_or_equal(Large const& a, Large const& b, Count& count);

void addition(Large const& addend1, Large const& addend2, Large& sum, Count& count);
void substraction(Large const& minuend, Large const& substrahend, Large& difference, Count& count);
void multiplication(Large const& multiplicand, Large const& multiplicator, Large& product, Count& count);
void division_modulo(Large const& dividend, Large const& modulus, Large const& quotient, Large const& remainder, Count& count);
void squaring(Large const& multiplicator, Large const& modulus, Count& count);
void modular_exponentiation(Large const& base, Large const& exponent, Large const& modulus, Count& count);


/*
void compute_phi_n();
void inverse();
void compute_greater_common_divisor();
void compute_naive_factorisation();
bool is_prime_with_miller_rabin();
void find prime random ???
bool is prime+1 divisible by 4
bool is y2 quadratic residue
bool what is y
*/

#endif // PRIME_ARITHMETIC_H
