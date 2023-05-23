#ifndef PRIME_ARITHMETIC_H
#define PRIME_ARITHMETIC_H

#include "bool_algeabra.h"

void addition(Large const& addend1, Large const& addend2, Large& sum, Count& count);
void substraction(Large const& minuend, Large const& substrahend, Large& difference, Count& count);
void multiplication(Large const& multiplicand, Large const& multiplicator, Large& product, Count& count);

void division_modulo(Large const& dividend, Large const& modulus, Large& quotient, Large& remainder, Count& count);
void modulo(Large const& dividend, Large const& modulus, Large& remainder, Count& count);
void addition_modulo(Large const& addend1, Large const& addend2, Large const& modulus, Large& result, Count& count);
void substraction_modulo(Large const& minuend, Large const& substrahend, Large const& modulus, Large& result, Count& count);
void multiplication_modulo(Large const& multiplicand, Large const& multiplicator, Large const& modulus, Large& result, Count& count);
void squaring_modulo(Large const& multiplicator, Large const& modulus, Large& result, Count& count);
void exponentiation_modulo(Large const& base, Large const& exponent, Large const& modulus, Large& result, Count& count);

void greatest_common_divisor(Large const& greatest_number, Large const& smallest_number, Large& gcd_number, Count& count);
void inverse(Large const& a, Large const& n, Large const& phi_n, Large& result, Count& count); //assume gcd(a, n) = 1
void inverse_with_prime(Large const& a, Large const& p, Large& result, Count& count); //assume gcd(a, n) = 1

bool is_prime_with_fermat_little_theorem(Large const& maybe_prime, Count& count);
/*
void find prime random ???
bool is prime+1 divisible by 4
bool is y2 quadratic residue
bool what is y
*/

#endif // PRIME_ARITHMETIC_H
