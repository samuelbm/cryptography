#include "prime_arithmetic.h"
#include <QDebug>
#include <QTest>

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
    uint16_t size = difference.get_number_of_bits();
    Large difference_intermediate(size);
    count.clock++;
    SUB_n_bits(minuend, substrahend, difference_intermediate, count);
    difference.insert(difference_intermediate, 0);
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
    uint16_t multiplicand_length = multiplicand.get_number_of_bits();
    uint16_t multiplicator_length = multiplicator.get_number_of_bits();
    Large subproduct(multiplicand);
    Large sum(multiplicand_length+1);
    Large product_intermediate(product.get_number_of_bits());
    for(uint16_t i=0; i<multiplicator_length; i++)
    {
        product_intermediate.split(subproduct, i);
        addition(multiplicand, subproduct, sum, count);
        product_intermediate.REG(multiplicator[i], sum, i, count);
    }
    product.insert(product_intermediate, 0);
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
    uint16_t quotient_size = quotient.get_number_of_bits();
    uint16_t remainder_size = remainder.get_number_of_bits();
    uint16_t full_size = quotient_size + remainder_size;
    quotient.clear(0, quotient_size);
    Large dividend_intermediate(full_size);
    Large minuend_intermediate(remainder_size);
    Large difference_intermediate(remainder_size);
    Large quotient_intermediate(quotient_size);
    dividend_intermediate.insert(dividend, 0);
    bool enable, less_or_equal, carry_out;
    for(uint16_t i=0; i<quotient_size; i++)
    {
        dividend_intermediate.split(minuend_intermediate, quotient_size - 1 - i);
        substraction(minuend_intermediate, modulus, difference_intermediate, count);
        less_or_equal = is_less_or_equal(modulus, minuend_intermediate, count);
        carry_out = dividend_intermediate[full_size - 1 - i];
        enable = OR(less_or_equal, carry_out, count);
        quotient_intermediate.SHIFT_LEFT(true, enable, count);
        dividend_intermediate.REG(enable, difference_intermediate, quotient_size - 1 - i, count);
    }
    remainder.insert(MUX2_Large(enable, minuend_intermediate, difference_intermediate, count), 0);
    quotient.insert(quotient_intermediate, 0);
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
    uint16_t size = result.get_number_of_bits();
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
    uint16_t n_bits = result.get_number_of_bits();
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
    uint16_t size = result.get_number_of_bits();
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
    uint16_t exponent_size = exponent.get_number_of_bits();
    uint16_t result_size = result.get_number_of_bits();
    Large squared(result_size);
    Large result_intermediate(result_size);
    result[0] = true; //init to 1
    squared.insert(base, 0);
    uint64_t freeze_clock_count; // operations in parallel
    for(uint16_t i=0; i<exponent_size-1; i++)
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

