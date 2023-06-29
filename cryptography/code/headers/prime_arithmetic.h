#ifndef PRIME_ARITHMETIC_H
#define PRIME_ARITHMETIC_H

#include <QRandomGenerator>
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

bool is_prime_with_fermat_little_theorem(Large const& maybe_prime, Count& count, uint16_t nb_round=100);
Large find_prime_equiv_3_mod_4(uint16_t size, QRandomGenerator& prng, Count& count);
//bool is_prime_equiv_3_mod_4(Large const& prime, Count& count);
//bool is_y_squared_a_quadratic_residue(Large const& y_squared, Count& count);
//Large determine_y_knowing_y_squared_is_a_quadratic_residue(Large const& y_squared, Count& count);

Large string2Large(QString number_string, uint16_t size);
QString Large2String(Large const& number);
Large string2Hex(QString number_string, uint16_t size);
QString count2string(Count const& count);

#endif // PRIME_ARITHMETIC_H
