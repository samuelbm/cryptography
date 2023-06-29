#ifndef FAST_LARGE_H
#define FAST_LARGE_H

#include <stdint.h>
#include "large.h"

Large fast_large2Large(uint64_t fast_large[], uint16_t nb_bits);
void copy(uint64_t source[], uint64_t destination[], uint16_t size_a);
void fast_clear(uint64_t x[], uint16_t size);
void fast_init_with_small_number(uint64_t init_number, uint64_t array_number[], uint16_t size);
bool fast_is_equal(uint64_t a[], uint64_t b[], uint16_t size_a);
bool fast_is_less_than(uint64_t a[], uint64_t b[], uint16_t size_a);
bool fast_is_less_or_equal_than(uint64_t a[], uint64_t b[], uint16_t size_a);
void fast_addition(uint64_t a[], uint64_t b[], uint64_t sum[], uint16_t size_a); //same size as b, sum must be larger
void fast_substraction(uint64_t a[], uint64_t b[], uint64_t difference[], uint16_t size_a); //a must be greater than b but of same size


void fast_addition_mono( uint64_t b, uint64_t sum[], uint16_t size_a);
void fast_multiplication(uint64_t  a[], uint64_t b[], uint64_t product[], uint16_t size_a, uint16_t size_b);
void fast_shift_left(uint64_t number[], uint16_t size, bool carry);
void fast_division_modulo(uint64_t  a[], uint64_t b[], uint64_t quotient[], uint64_t remainder[], uint16_t size_a, uint16_t size_b);
//void fast_addition_modulo(uint64_t a[], uint64_t b[], uint64_t n[], uint64_t result[], uint16_t size_a, uint16_);
//void fast_squaring_modulo(uint64_t const& multiplicator, uint64_t const& modulus, Large& result, Count& count);
//void fast_exponentiation_modulo(uint64_t const& base, uint64_t const& exponent, Large const& modulus, Large& result, Count& count);
//bool fast_is_prime_with_fermat_little_theorem(uint64_t const& maybe_prime, Count& count, uint16_t nb_round=100);

//uint16_t fast_find_prime_equiv_3_mod_4(uint16_t size, QRandomGenerator& prng, Count& count);

#endif // FAST_LARGE_H
