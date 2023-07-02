#include "prime_arithmetic.h"
#include <QDebug>
#include <QTest>
#include "fast_large.h"

/*
addend1 (size)                  : n
addend2 (size)                  : n
sum (size)                      : n + 1
Latency                         : 1
Operations                      : n
regs                            : 0
NOT_gates                       : 0
AND_gates                       : 2*n
NAND_gates                      : 0
OR_gates                        : n
NOR_gates                       : 0
XOR_gates                       : 2*n
XNOR_gates                      : 0
*/
void addition(Large const& addend1, Large const& addend2, Large& sum, Count& count)
{
    assert(addend1.get_number_of_bits() == addend2.get_number_of_bits());
    assert(addend1.get_number_of_bits() + 1 == sum.get_number_of_bits());
    count.clock++;
    ADDER_n_bits(addend1, addend2, sum, count);
}

/*
minuend (size)                  : n
substrahend (size)              : n
difference (size)               : n
Latency                         : 1
Operations                      : n
regs                            : 0
NOT_gates                       : n
AND_gates                       : 2*n
NAND_gates                      : 0
OR_gates                        : n
NOR_gates                       : 0
XOR_gates                       : 2*n
XNOR_gates                      : 0
*/
void substraction(Large const& minuend, Large const& substrahend, Large& difference, Count& count)
{
    assert(minuend.get_number_of_bits() == substrahend.get_number_of_bits());
    assert(minuend.get_number_of_bits() == difference.get_number_of_bits());
    uint64_t size = difference.get_number_of_bits();
    Large difference_intermediate(size);
    count.clock++;
    SUB_n_bits(minuend, substrahend, difference_intermediate, count);
    difference.insert(difference_intermediate);
}

/*
multiplicand (size)             : n                                 : n
multiplicator (size)            : m                                 : n
product (size)                  : n + m                             : 2*n
Latency                         : m                                 : n
Operations                      : n*m                               : n*n
regs                            : n*m + m                           : n*n + n
NOT_gates                       : 0                                 : 0
AND_gates                       : 2*n*m                             : 2*n*n
NAND_gates                      : 0                                 : 0
OR_gates                        : n*m                               : n*n
NOR_gates                       : 0                                 : 0
XOR_gates                       : 2*n*m                             :
XNOR_gates                      : 0                                 : 0
*/
void multiplication(Large const& multiplicand, Large const& multiplicator, Large& product, Count& count)
{
    assert(multiplicand.get_number_of_bits() + multiplicator.get_number_of_bits() == product.get_number_of_bits());
    uint64_t multiplicand_length = multiplicand.get_number_of_bits();
    uint64_t multiplicator_length = multiplicator.get_number_of_bits();
    Large subproduct(multiplicand);
    Large sum(multiplicand_length+1);
    Large product_intermediate(product.get_number_of_bits());
    for(uint64_t i=0; i<multiplicator_length; i++)
    {
        product_intermediate.split(subproduct, i);
        addition(multiplicand, subproduct, sum, count);
        product_intermediate.REG(multiplicator[i], sum, i, count);
    }
    product.insert(product_intermediate);
}

/*
dividend (size)                 : n                                 : n
modulus (size)                  : m                                 : n
quotient (size)                 : n                                 : n
remainder (size)                : m                                 : n
Latency                         : n                                 : n
Operations                      : 3*n*m + m                         : 3*n*n + n
regs                            : n*n + n*m                         : 2*n*n
NOT_gates                       : 3*n*m + n + m                     : 3*n*n + 2*n
AND_gates                       : 5*n*m + 2*m                       : 5*n*n + 2*n
NAND_gates                      : 0                                 : 0
OR_gates                        : 3*m*n + m + n                     : 3*n*n + 2*n
NOR_gates                       : 0                                 : 0
XOR_gates                       : 3*m*n                             : 3*n*n
XNOR_gates                      : 0                                 : 0
*/
void division_modulo(Large const& dividend, Large const& modulus, Large& quotient, Large& remainder, Count& count)
{
    assert(!modulus.is_null());
    assert(dividend.get_number_of_bits() == quotient.get_number_of_bits());
    assert(modulus.get_number_of_bits() == remainder.get_number_of_bits());
    assert(quotient.get_number_of_bits() >= remainder.get_number_of_bits());
    uint64_t quotient_size = quotient.get_number_of_bits();
    uint64_t remainder_size = remainder.get_number_of_bits();
    uint64_t full_size = quotient_size + remainder_size;
    quotient.clear(0, quotient_size);
    Large dividend_intermediate(full_size);
    Large minuend_intermediate(remainder_size);
    Large difference_intermediate(remainder_size);
    Large quotient_intermediate(quotient_size);
    dividend_intermediate.insert(dividend);
    bool enable, less_or_equal, carry_out;
    for(uint64_t i=0; i<quotient_size; i++)
    {
        dividend_intermediate.split(minuend_intermediate, quotient_size - 1 - i);
        substraction(minuend_intermediate, modulus, difference_intermediate, count);
        less_or_equal = is_less_or_equal(modulus, minuend_intermediate, count);
        carry_out = dividend_intermediate[full_size - 1 - i];
        enable = OR(less_or_equal, carry_out, count);
        quotient_intermediate.SHIFT_LEFT(true, enable, count);
        dividend_intermediate.REG(enable, difference_intermediate, quotient_size - 1 - i, count);
    }
    remainder.insert(MUX2_Large(enable, minuend_intermediate, difference_intermediate, count));
    quotient.insert(quotient_intermediate);
}

/*
dividend (size)                 : n                                 : n
modulus (size)                  : m                                 : n
quotient (size)                 : n                                 : n
remainder (size)                : m                                 : n
Latency                         : n                                 : n
Operations                      : 3*n*m + m                         : 3*n*n + n
regs                            : n*n + n*m                         : 2*n*n
NOT_gates                       : 3*n*m + n + m                     : 3*n*n + 2*n
AND_gates                       : 5*n*m + 2*m                       : 5*n*n + 2*n
NAND_gates                      : 0                                 : 0
OR_gates                        : 3*n*m + n + m                     : 3*n*n + 2*n
NOR_gates                       : 0                                 : 0
XOR_gates                       : 3*n*m                             : 3*n*n
XNOR_gates                      : 0                                 : 0
*/
void modulo(Large const& dividend, Large const& modulus, Large& remainder, Count& count)
{
    assert(!modulus.is_null());
    assert(modulus.get_number_of_bits() == remainder.get_number_of_bits());
    assert(dividend.get_number_of_bits() >= remainder.get_number_of_bits());
    Large dummy_quotient(dividend.get_number_of_bits());
    division_modulo(dividend, modulus, dummy_quotient, remainder, count);
}

/*
addend1 (size)                  : n
addend2 (size)                  : n
modulus (size)                  : n
result (size)                   : n
Latency                         : n + 2
Operations                      : 3*n*n + 5*n
regs                            : 2*n*n + 3*n + 1
NOT_gates                       : 3*n*n + 5*n + 1
AND_gates                       : 5*n*n + 9*n
NAND_gates                      : 0
OR_gates                        : 3*n*n + 6*n + 1
NOR_gates                       : 0
XOR_gates                       : 3*n*n + 5*n
XNOR_gates                      : 0
*/
void addition_modulo(Large const& addend1, Large const& addend2, Large const& modulus, Large& result, Count& count)
{
    assert(addend1.get_number_of_bits() == addend2.get_number_of_bits());
    assert(addend1.get_number_of_bits() == modulus.get_number_of_bits());
    assert(addend1.get_number_of_bits() == result.get_number_of_bits());
    uint64_t size = result.get_number_of_bits();
    Large sum(size + 1);
    addition(addend1, addend2, sum, count);
    modulo(sum, modulus, result, count);
}

/*
minuend (size)                  : n
substrahend (size)              : n
modulus (size)                  : n
result (size)                   : n
Latency                         : 2*n + 3
Operations                      : 9*n*n + 8*n
regs                            : 6*n*n+ 3*n + 1
NOT_gates                       : 9*n*n + 10*n + 1
AND_gates                       : 15*n*n + 15*n
NAND_gates                      : 0
OR_gates                        : 9*n*n + 11*n + 1
NOR_gates                       : 0
XOR_gates                       : 9*n*n + 7*n
XNOR_gates                      : 0
*/
void substraction_modulo(Large const& minuend, Large const& substrahend, Large const& modulus, Large& result, Count& count)
{
    assert(minuend.get_number_of_bits() == substrahend.get_number_of_bits());
    assert(minuend.get_number_of_bits() == modulus.get_number_of_bits());
    assert(minuend.get_number_of_bits() == result.get_number_of_bits());
    uint64_t n_bits = result.get_number_of_bits();
    Large minuend_modulo(n_bits);
    Large substraend_modulo(n_bits);
    modulo(minuend, modulus, minuend_modulo, count);
    uint64_t freeze_clock_count = count.clock;// division_modulo in parallel
    modulo(substrahend, modulus, substraend_modulo, count);
    count.clock = freeze_clock_count;
    substraction(modulus, substraend_modulo, result, count);
    addition_modulo(minuend_modulo, result, modulus, result, count);
}

/*
multiplicand (size)             : n
multiplicator (size)            : n
modulus (size)                  : n
result (size)                   : n
Latency                         : 3*n
Operations                      : 7*n*n + n
regs                            : 7*n*n + n
NOT_gates                       : 6*n*n + 3*n
AND_gates                       : 12*n*n + 2*n
NAND_gates                      : 0
OR_gates                        : 7*n*n + 3*n
NOR_gates                       : 0
XOR_gates                       : 8*n*n
XNOR_gates                      : 0
*/
void multiplication_modulo(Large const& multiplicand, Large const& multiplicator, Large const& modulus, Large& result, Count& count)
{
    assert(multiplicand.get_number_of_bits() == multiplicator.get_number_of_bits());
    assert(multiplicand.get_number_of_bits() == multiplicator.get_number_of_bits());
    assert(multiplicand.get_number_of_bits() == result.get_number_of_bits());
    uint64_t size = result.get_number_of_bits();
    Large product(2*size);
    multiplication(multiplicand, multiplicator, product, count);
    modulo(product, modulus, result, count);
}

/*
multiplicator (size)            : n
modulus (size)                  : n
result (size)                   : n
Latency                         : 3*n
Operations                      : 7*n*n + n
regs                            : 7*n*n + n
NOT_gates                       : 6*n*n + 3*n
AND_gates                       : 12*n*n + 2*n
NAND_gates                      : 0
OR_gates                        : 7*n*n + 3*n
NOR_gates                       : 0
XOR_gates                       : 8*n*n
XNOR_gates                      : 0
*/
void squaring_modulo(Large const& multiplicator, Large const& modulus, Large& result, Count& count)
{
    assert(multiplicator.get_number_of_bits() == modulus.get_number_of_bits());
    assert(multiplicator.get_number_of_bits() == result.get_number_of_bits());
    multiplication_modulo(multiplicator, multiplicator, modulus, result, count);
}

/*
base (size)                     : n                                 : n
exponent (size)                 : m                                 : n
modulus (size)                  : n                                 : n
result (size)                   : n                                 : n
Latency                         : (m)*(3*n)                         : 3*n*n
Operations                      : (2*m - 1)*(7*n*n + n)             : 14*n*n*n - 5*n*n - n
regs                            : (2*m - 1)*(7*n*n + n) + (m)*(n)   : 14*n*n*n - 4*n*n - n
NOT_gates                       : (2*m - 1)*(6*n*n + 3*n)           : 12*n*n*n - 3*n
AND_gates                       : (2*m - 1)*(12*n*n + 2*n)          : 24*n*n*n - 8*n*n - 2*n
NAND_gates                      : 0                                 : 0
OR_gates                        : (2*m - 1)*(7*n*n + 3*n)           : 14*n*n*n - n*n -3*n
NOR_gates                       : 0                                 : 0
XOR_gates                       : (2*m - 1)*(8*n*n)                 : 16*n*n*n - 8*n*n
XNOR_gates                      : 0                                 : 0
*/
void exponentiation_modulo(Large const& base, Large const& exponent, Large const& modulus, Large& result, Count& count)
{
    assert(base.get_number_of_bits() == modulus.get_number_of_bits());
    assert(base.get_number_of_bits() == result.get_number_of_bits());
    uint64_t exponent_size = exponent.get_number_of_bits();
    uint64_t result_size = result.get_number_of_bits();
    Large squared(result_size);
    Large result_intermediate(result_size);
    result.clear(0, result.get_number_of_bits());
    result[0] = true; //init to 1
    squared.insert(base);
    uint64_t freeze_clock_count; // operations in parallel
    for(uint64_t i=0; i<exponent_size-1; i++)
    {
        multiplication_modulo(squared, result, modulus, result_intermediate, count);
        freeze_clock_count = count.clock;
        squaring_modulo(squared, modulus, squared, count);
        count.clock = freeze_clock_count;
        result.REG(exponent[i], result_intermediate, 0, count);
    }
    multiplication_modulo(squared, result, modulus, result_intermediate, count);
    result.REG(exponent[exponent_size - 1], result_intermediate, 0, count);
}

// statistics cannot be precisely determined, depends on the number of loops the algorithm takes.
void greatest_common_divisor(Large const& greatest_number, Large const& smallest_number, Large& gcd_number, Count& count)
{
    Count dummy_count;
    count_initialization(dummy_count);
    assert(greatest_number.get_number_of_bits() == smallest_number.get_number_of_bits());
    assert(greatest_number.get_number_of_bits() == gcd_number.get_number_of_bits());
    uint64_t size = gcd_number.get_number_of_bits();
    Large r1(size), r2(size), r3(size), zero(size);
    bool less_than = is_less_than(smallest_number, greatest_number, dummy_count);
    r1.insert((less_than)?greatest_number:smallest_number);
    r2.insert((less_than)?smallest_number:greatest_number);
    do
    {
        modulo(r1, r2, r3, count);
        r1.REG(true, r2, 0, count);
        r2.REG(true, r3, 0, count);
    }while(is_not_equal(r2, zero, count));
    gcd_number.insert(r1, 0);
}

/*
base (size)                     : n
exponent (size)                 : n
modulus (size)                  : n
result (size)                   : n
Latency                         : 3*n*n + 1
Operations                      : 14*n*n*n - 5*n*n
regs                            : 14*n*n*n - 4*n*n - n
NOT_gates                       : 12*n*n*n - 2*n
AND_gates                       : 24*n*n*n - 8*n*n
NAND_gates                      : 0
OR_gates                        : 14*n*n*n - n*n - 2*n
NOR_gates                       : 0
XOR_gates                       : 16*n*n*n - 8*n*n + 2*n
XNOR_gates                      : 0
*/
void inverse(Large const& a, Large const& n, Large const& phi_n, Large& result, Count& count)
{
    Count dummy_count;
    count_initialization(dummy_count);
    assert(a.get_number_of_bits() == n.get_number_of_bits());
    assert(a.get_number_of_bits() == phi_n.get_number_of_bits());
    assert(a.get_number_of_bits() == result.get_number_of_bits());
    uint64_t size = result.get_number_of_bits();
    Large one(size), gcd_number(size), exponent(size);
    one.init_with_small_number(1);
    greatest_common_divisor(a, n, gcd_number, dummy_count);
    assert(is_greater_than(n, one, dummy_count));
    assert(is_equal(gcd_number, one, dummy_count));
    substraction(phi_n, one, exponent, count);
    exponentiation_modulo(a, exponent, n, result, count);
}

/*
base (size)                     : n
exponent (size)                 : n
modulus (size)                  : n
result (size)                   : n
Latency                         : 3*n*n + 1
Operations                      : 14*n*n*n - 5*n*n
regs                            : 14*n*n*n - 4*n*n - n
NOT_gates                       : 12*n*n*n - 2*n
AND_gates                       : 24*n*n*n - 8*n*n
NAND_gates                      : 0
OR_gates                        : 14*n*n*n - n*n - 2*n
NOR_gates                       : 0
XOR_gates                       : 16*n*n*n - 8*n*n + 2*n
XNOR_gates                      : 0
*/
void inverse_with_prime(Large const& a, Large const& p, Large& result, Count& count)
{
    Count dummy_count;
    count_initialization(dummy_count);
    assert(a.get_number_of_bits() == p.get_number_of_bits());
    assert(a.get_number_of_bits() == result.get_number_of_bits());
    uint64_t size = result.get_number_of_bits();
    Large one(size), two(size), gcd_number(size), exponent(size);
    one.init_with_small_number(1);
    two.init_with_small_number(2);
    greatest_common_divisor(a, p, gcd_number, dummy_count);
    assert(is_greater_than(p, one, dummy_count));
    assert(is_equal(gcd_number, one, dummy_count));
    //ajouter assert sur test primality rabin miller()
    substraction(p, two, exponent, count);
    exponentiation_modulo(a, exponent, p, result, count);
}

/*
base (size)                     : 100*(n)
exponent (size)                 : 100*(n)
modulus (size)                  : 100*(n)
result (size)                   : 100*(n)
Latency                         : 100*(3*n*n) + 1
Operations                      : 100*(14*n*n*n - 5*n*n) + n
regs                            : 100*(14*n*n*n - 4*n*n - n)
NOT_gates                       : 100*(12*n*n*n - 3*n) + n
AND_gates                       : 100*(24*n*n*n - 8*n*n - n+ 1) + 2*n
NAND_gates                      : 0
OR_gates                        : 100*(14*n*n*n - n*n -3*n) + n
NOR_gates                       : 0
XOR_gates                       : 100*(16*n*n*n - 8*n*n) + 2*n
XNOR_gates                      : 100*(n)
*/
bool is_prime_with_fermat_little_theorem(Large const& maybe_prime, Count& count, uint16_t nb_round)
{
    Count dummy_count;
    count_initialization(dummy_count);
    uint64_t primes_size = nb_round;
    uint64_t size = maybe_prime.get_number_of_bits();
    Large threshold(size), base(size), exponent(size), one(size), result(size);
    one.init_with_small_number(1);
    threshold.init_with_small_number(542);
    uint64_t primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
              73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
              179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
              283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
              419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
    Large small_prime(maybe_prime.get_number_of_bits());
    if(is_less_than(maybe_prime, threshold, count))
    {
        for(uint16_t i=0; i<100 ;i++)
        {
            small_prime.init_with_small_number(primes[i]);
            if(is_equal(maybe_prime, small_prime, count))
            {
                return true;
            }
        }
        return false;
    }
    substraction(maybe_prime, one, exponent, count);
    bool is_prime = true; // probably
    for(uint64_t i=0; i<primes_size; i++)
    {
        base.init_with_small_number(primes[i]);
        exponentiation_modulo(base, exponent, maybe_prime, result, count);
        is_prime = AND(is_prime, is_equal(result, one, count), count);
    }
    return is_prime;
}

/*
base (size)                     : 100*(n)
exponent (size)                 : 100*(n)
modulus (size)                  : 100*(n)
result (size)                   : 100*(n)
Latency                         : 100*(3*n*n) + 1
Operations                      : 100*(14*n*n*n - 5*n*n) + n
regs                            : 100*(14*n*n*n - 4*n*n)
NOT_gates                       : 100*(12*n*n*n - 3*n) + n
AND_gates                       : 100*(24*n*n*n - 8*n*n - n+ 1) + 2*n
NAND_gates                      : 0
OR_gates                        : 100*(14*n*n*n - n*n -3*n) + n
NOR_gates                       : 0
XOR_gates                       : 100*(16*n*n*n - 8*n*n) + 2*n
XNOR_gates                      : 100*(n)
*/
Large find_prime_equiv_3_mod_4(uint16_t size, QRandomGenerator& prng, uint16_t nb_bits, uint16_t nb_round, uint16_t& tries, Storage& storage, Count& count)
{
    uint64_t n = nb_bits;
    tries = fast_find_prime_equiv_3_mod_4(storage.prime_s, size, prng, storage, nb_round, nb_bits);
    count.clock += (3*n*n*nb_round + 1)*tries;
    count.operation += ((14*n*n*n - 5*n*n)*nb_round + n)*tries;
    count.regs += ((14*n*n*n - 4*n*n)*nb_round)*tries;
    count.NOT_gates += ((12*n*n*n - 3*n)*nb_round + n)*tries;
    count.AND_gates += ((24*n*n*n - 8*n*n - n+ 1)*nb_round + 2*n)*tries;
    count.NAND_gates += 0;
    count.OR_gates += ((14*n*n*n - n*n -3*n)*nb_round + n)*tries;
    count.NOR_gates += 0;
    count.XOR_gates += ((16*n*n*n - 8*n*n)*nb_round + 2*n)*tries;
    count.XNOR_gates += (n*nb_round)*tries;
    return fast_large2Large(storage.prime_s, nb_bits);
}
Large find_phi_n(Large const& p, Large const& q, Count& count)
{
    uint16_t p_size = p.get_number_of_bits();
    uint16_t q_size = q.get_number_of_bits();
    uint16_t n_size = p_size + q_size;
    Large one(p_size);
    Large p_minus_one(p_size);
    Large q_minus_one(q_size);
    Large phi_n(n_size);
    one.init_with_small_number(1);
    substraction(p, one, p_minus_one, count);
    substraction(q, one, q_minus_one, count);
    multiplication(p_minus_one, q_minus_one, phi_n, count);
    return phi_n;
}

Large find_phi_phi_n(Large const& phi_n, Count& count)
{
    uint16_t n_size = phi_n.get_number_of_bits();
    uint16_t p_size = (n_size + 1)/2;
    Large phi_n_copy(n_size);
    Large zero(p_size);
    Large one(p_size);
    Large two(p_size);
    Large remainder(p_size);
    Large factor(p_size);
    Large factor_minus_one(p_size);
    Large factor_sum(p_size + 1);
    Large quotient(n_size);
    Large phi_phi_n(n_size);
    Large phi_phi_n_intermediate(n_size + p_size);

    zero.init_with_small_number(0);
    one.init_with_small_number(1);
    two.init_with_small_number(2);
    factor.init_with_small_number(3);
    phi_n.split(phi_n_copy, 0);
    phi_phi_n.init_with_small_number(1);
    uint16_t exponent = 0;
    while(phi_n_copy[0] == 0)
    {
        phi_n_copy.SHIFT_RIGHT(true, false, count);
        if(exponent != 0)
        {
            phi_phi_n.SHIFT_LEFT(true, false, count);
        }
        exponent++;
    }
    exponent = 0;
    do
    {
        division_modulo(phi_n_copy, factor, quotient, remainder, count);
        if(is_equal(remainder, zero, count))
        {
            quotient.split(phi_n_copy, 0);
            if(exponent == 0)
            {
                substraction(factor, one, factor_minus_one, count);
                multiplication(phi_phi_n, factor_minus_one, phi_phi_n_intermediate, count);
                phi_phi_n_intermediate.split(phi_phi_n, 0);
            }
            else
            {
                multiplication(phi_phi_n, factor, phi_phi_n_intermediate, count);
                phi_phi_n_intermediate.split(phi_phi_n, 0);
            }
            exponent++;
        }
        else
        {
            exponent = 0;
            addition(factor, two, factor_sum, count);
            factor_sum.split(factor, 0);
        }
    }while(!is_prime_with_fermat_little_theorem(phi_n_copy, count, 20));
    phi_n_copy.split(factor, 0);
    if(exponent == 1)
    {
        substraction(factor, one, factor_minus_one, count);
        multiplication(phi_phi_n, factor_minus_one, phi_phi_n_intermediate, count);
        phi_phi_n_intermediate.split(phi_phi_n, 0);
    }
    else
    {
        multiplication(phi_phi_n, factor, phi_phi_n_intermediate, count);
        phi_phi_n_intermediate.split(phi_phi_n, 0);
    }
    return phi_phi_n;
}

/*
a (size)                        : n
n (size)                        : n
inverse (size)                  : n
Latency                         :
Operations                      :
regs                            :
NOT_gates                       :
AND_gates                       :
NAND_gates                      :
OR_gates                        :
NOR_gates                       :
XOR_gates                       :
XNOR_gates                      :
*/


//-----------------------------


Large string2Large(QString number_string, uint16_t size)
{
    Count count;
    count_initialization(count);
    Large digit(4);
    Large power(size);
    Large product(size+4);
    Large result_intermediate(size+5);
    Large sub_result_intermediate(size+4);
    Large power_intermediate(size+4);
    Large base(4);
    Large result(size);
    power.init_with_small_number(1);
    sub_result_intermediate.clear(0, sub_result_intermediate.get_number_of_bits());
    base.init_with_small_number(10);
    for(uint16_t i=0; i<number_string.length(); i++)
    {
        char chr = number_string.at(number_string.length() - i - 1).toLatin1() - '0';
        uint64_t current_digit = (uint64_t)(chr);
        digit.init_with_small_number(current_digit);
        multiplication(digit, power, product, count);
        result_intermediate.split(sub_result_intermediate, 0);
        addition(product,  sub_result_intermediate, result_intermediate, count);
        multiplication(base, power, power_intermediate, count);
        power_intermediate.split(power, 0);
   }
    result_intermediate.split(result, 0);
    return result;
}

QString Large2String(Large const& number)
{
    Count count;
    count_initialization(count);
    QString string_number = "";
    Large base(4);
    Large dummy(4);
    Large power(number.get_number_of_bits());
    Large power_intermediate(number.get_number_of_bits() + 4);
    Large quotient(number.get_number_of_bits());
    Large remainder(number.get_number_of_bits());
    uint16_t exponent = (uint16_t)(0.30103*number.get_number_of_bits());
    base.init_with_small_number(10);
    power.init_with_small_number(1);
    remainder = number;
    for(uint16_t i=0; i<exponent; i++)
    {
        multiplication(base, power, power_intermediate, count);
        power_intermediate.split(power, 0);
    }
    for(uint16_t i=0; i<exponent + 1; i++)
    {
        division_modulo(remainder, power, quotient, remainder, count );
        QString digits = "0123456789";
        int index = 8*quotient[3] + 4*quotient[2] + 2*quotient[1] + 1*quotient[0];
        assert(index < 10);
        if(index >  0 || string_number.length() != 0)
        {
            string_number += digits[index] ;
        }
        division_modulo(power, base, quotient, dummy, count);
        power = quotient;
    }
    if(string_number.length() == 0)
    {
        string_number += "0";
    }
    return string_number;
}

Large string2Hex(QString number_string, uint16_t size)
{
    Large result(size);
    result.clear(0, size);
    for(uint16_t i=0; i<size; i++)
    {
        uint16_t index = number_string.length() -1 -(int)(i/4);
        uint16_t remainder = i &  3;
        char chr = number_string.at(index).toLatin1();
        uint64_t current_digit = (uint64_t)(('0' <= chr && chr <= '9')?chr - '0':(('a' <= chr && chr <= 'f')?chr-'a' + 10:chr-'A'+ 10));
        result[i] = (current_digit >> remainder);
    }
    return result;
}

QString count2string(Count const& count)
{
    QString result="";
    //latence-regs-gates
    uint64_t latency_count = count.clock;
    uint64_t regs_count = count.regs;
    uint64_t gates_count = count.AND_gates + count.NAND_gates + count.OR_gates + count.NOR_gates + count.XNOR_gates + count.XNOR_gates;
    result += QString::number(latency_count) + ","; // latency
    result += QString::number(regs_count) + ","; // regs
    result += QString::number(gates_count) + ","; // gates
    return result;
}
