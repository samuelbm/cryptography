#include "prime_arithmetic.h"
#include <QDebug>
#include <QTest>

/*
addend1 (size)                  : n
addend2 (size)                  : n
sum (size)                      : n + 1
Latency                         : 0
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
    ADDER_n_bits(addend1, addend2, sum, count);
}

/*
minuend (size)                  : n
substrahend (size)              : n
difference (size)               : n
Latency                         : 0
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
    SUB_n_bits(minuend, substrahend, difference_intermediate, count);
    difference.insert(difference_intermediate, 0);
}

/*
multiplicand (size)             : n
multiplicator (size)            : m
product (size)                  : n+m
Latency                         : m
Operations                      : n*m
regs                            : (n + 1)*m
NOT_gates                       : 0
AND_gates                       : 2*n*m
NAND_gates                      : 0
OR_gates                        : n*m
NOR_gates                       : 0
XOR_gates                       : 2*n*m
XNOR_gates                      : 0
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
        count.clock++;
        product_intermediate.split(subproduct, i);
        addition(multiplicand, subproduct, sum, count);
        product_intermediate.REG(multiplicator[i], sum, i, count);
    }
    product.insert(product_intermediate, 0);
}

/*
dividend (size)                 : n
modulus (size)                  : m
quotient (size)                 : n
remainder (size)                : m
Latency                         : n
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
        count.clock++;
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
dividend (size)                 :
modulus (size)                  :
quotient (size)                 :
remainder (size)                :
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
void substraction_modulo(Large const& minuend, Large const& substrahend, Large const& modulus, Large& result, Count& count)
{
    assert(minuend.get_number_of_bits() == substrahend.get_number_of_bits());
    assert(minuend.get_number_of_bits() == modulus.get_number_of_bits());
    assert(minuend.get_number_of_bits() == result.get_number_of_bits());
    uint16_t n_bits = result.get_number_of_bits();
    Large minuend_modulo(n_bits);
    Large substraend_modulo(n_bits);
    modulo(minuend, modulus, minuend_modulo, count);
    uint16_t freeze_clock_count = count.clock;// division_modulo in parallel
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
void squaring_modulo(Large const& multiplicator, Large const& modulus, Large& result, Count& count)
{
    assert(multiplicator.get_number_of_bits() == modulus.get_number_of_bits());
    assert(multiplicator.get_number_of_bits() == result.get_number_of_bits());
    multiplication_modulo(multiplicator, multiplicator, modulus, result, count);
}

/*
base (size)                     :
exponent (size)                 :
modulus (size)                  :
result (size)                   :
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
void exponentiation_modulo(Large const& base, Large const& exponent, Large const& modulus, Large& result, Count& count)
{
    assert(base.get_number_of_bits() == modulus.get_number_of_bits());
    assert(base.get_number_of_bits() == result.get_number_of_bits());
    uint16_t exponent_size = exponent.get_number_of_bits();
    uint16_t result_size = result.get_number_of_bits();
    Large squared(result_size);
    squared.insert(base, 0);
    qDebug() << squared.toHex();
    for(uint16_t i=0; i<exponent_size-1; i++)
    {
        squaring_modulo(squared, modulus, squared, count);
        qDebug() << squared.toHex();
    }
}

