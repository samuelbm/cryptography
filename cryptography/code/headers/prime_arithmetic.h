#ifndef PRIME_ARITHMETIC_H
#define PRIME_ARITHMETIC_H

#include "large.h"

bool is_equal(Large const& a, Large const& b, uint64_t& operation_count);
bool is_less_than(Large const& a, Large const& b, uint64_t& operation_count);
bool is_not_equal(Large const& a, Large const& b, uint64_t& operation_count);
bool is_greater_than(Large const& a, Large const& b, uint64_t& operation_count);
bool is_less_or_equal(Large const& a, Large const& b, uint64_t& operation_count);
bool is_greater_or_equal(Large const& a, Large const& b, uint64_t& operation_count);

void addition(Large const& a, Large const& b, Large& sum, uint16_t& a_start, uint16_t& sum_start, bool carry_in, uint64_t& operation_count);

/*
void modular_addition(Large const& a, Large const& b, Large& sum, uint64_t& operation_count);
void modular_negation();
void modular_substraction();
void modular_multiplication();
void modular_division_and_remainder();
void modular_squaring();
void modular_exponentiation();
void modular_inverse();

void compute_greater_common_divisor();
void compute_naive_factorisation();
void compute_phi_n();
bool is_prime_with_miller_rabin();
*/

#endif // PRIME_ARITHMETIC_H
