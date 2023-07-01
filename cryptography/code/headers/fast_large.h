#ifndef FAST_LARGE_H
#define FAST_LARGE_H

#include <stdint.h>
#include "large.h"
#include <QRandomGenerator>

typedef struct Storage
{
    uint64_t* difference_s1;
    uint64_t* difference_s2;
    uint64_t* product_2s;
    uint64_t* quotient_s;
    uint64_t* dummy_quotient_2s;
    uint64_t* squared_s;
    uint64_t* phi_n_s;
    uint64_t* one_s;
    uint64_t* base_s;
    uint64_t* result_s;
    uint64_t primes[100] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
              73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
              179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
              283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
              419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
} Storage;

void new_storage(Storage& storage, uint16_t size);
void delete_storage(Storage& storage);

//
Large fast_large2Large(uint64_t fast_large[], uint16_t nb_bits);

//size_source = size_destination
void fast_copy(uint64_t source[], uint64_t destination[], uint16_t size);

//
void fast_clear(uint64_t x[], uint16_t size);

//
void fast_init_with_small_number(uint64_t init_number, uint64_t array_number[], uint16_t size);

//a_size = b_size
bool fast_is_equal(uint64_t a[], uint64_t b[], uint16_t size);

//a_ize = b_size
bool fast_is_less_than(uint64_t a[], uint64_t b[], uint16_t size);

//a_size = b_size
bool fast_is_less_or_equal_than(uint64_t a[], uint64_t b[], uint16_t size);

//a_size = b_size
//sum_size = a_size + 1
//void fast_addition(uint64_t a[], uint64_t b[], uint64_t sum[], uint16_t size_a); //same size as b, sum must be larger

//a_size = difference_size = b_size
void fast_substraction(uint64_t a[], uint64_t b[], uint64_t difference[], uint16_t size, Storage& storage);

//
void fast_addition_mono( uint64_t b, uint64_t sum[], uint16_t size);

//product_size = a_size + b_size
void fast_multiplication(uint64_t  a[], uint64_t b[], uint64_t product[], uint16_t size_a, uint16_t size_b, Storage& storage);

//
bool fast_shift_left(uint64_t number[], uint16_t size, bool carry);

//quotient_size = a_size
//remainder_size = b_size
//difference_size = b_size+1
void fast_division_modulo(uint64_t  a[], uint64_t b[], uint64_t quotient[], uint64_t remainder[], uint16_t size_a, uint16_t size_b, Storage& storage);

//a_size = b_size = n_size = result_size = size
//storage_size = dummy_quotient_size = 2*size
//difference_size = size + 1
void fast_multiplication_modulo(uint64_t a[], uint64_t b[], uint64_t n[], uint64_t result[], uint16_t size, Storage& storage);

//base_size = modulus_size = result_size = square_size = result_storage_size = size
//storage_size = dummy_quotient_size = 2*size
//difference_size = size + 1
//exponent_size
void fast_exponentiation_modulo(uint64_t base[], uint64_t exponent[], uint64_t modulus[], uint64_t result[], uint16_t size, uint16_t size_exponent, Storage& storage);

//maybe_prime should be > 1000
bool fast_is_prime_with_fermat_little_theorem(uint64_t maybe_prime[], uint16_t size, uint16_t nb_round, Storage& storage);

//return the number of try
uint16_t fast_find_prime_equiv_3_mod_4(uint64_t prime[], uint16_t size, QRandomGenerator& prng, Storage& storage, uint16_t nb_round, uint16_t nb_bits);

#endif // FAST_LARGE_H
