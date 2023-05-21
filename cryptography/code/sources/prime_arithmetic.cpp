#include "prime_arithmetic.h"
#include <QDebug>
#include <QTest>

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
Operations                      : n
regs                            : n
NOT_gates                       : n
AND_gates                       : 2*n
NAND_gates                      : 0
OR_gates                        : n
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
bool is_equal(Large const& a, Large const& b, Count& count)
{
    assert(a.get_number_of_bits() == b.get_number_of_bits());
    uint16_t n_bits = a.get_number_of_bits();
    bool answer = true;
    bool enable;
    for(uint16_t i=0; i<n_bits; i++)
    {
        count.operation++;
        enable = XOR(a[i], b[i], count);
        REG(enable, false, answer, count);
    }
    return answer;
}

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
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
bool is_less_than(Large const& a, Large const& b, Count& count)
{
    assert(a.get_number_of_bits() == b.get_number_of_bits());
    uint16_t size = a.get_number_of_bits();
    bool answer = false;
    bool found = false;
    bool enable, new_answer;
    for(uint16_t i=0; i<size; i++)
    {
        uint16_t index = size - 1 - i;
        count.operation++;
        enable = XOR(a[index], b[index], count);
        new_answer = MUX2_bits(found, b[index], answer, count);
        REG(enable, new_answer, answer, count);
        REG(enable, true, found, count);
    }
    return answer;
}

/*
a (size)                        : n
b (size)                        : n
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
bool is_not_equal(Large const& a, Large const& b, Count& count)
{
    return !is_equal(a, b, count);
}

/*
a (size)                        : n
b (size)                        : n
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
bool is_greater_than(Large const& a, Large const& b, Count& count)
{
    return is_less_than(b, a, count);
}

/*
a (size)                        : n
b (size)                        : n
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
bool is_less_or_equal(Large const& a, Large const& b, Count& count)
{
    return !is_less_than(b, a, count);
}

/*
a (size)                        : n
b (size)                        : n
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
bool is_greater_or_equal(Large const& a, Large const& b, Count& count)
{
    return !is_less_than(a, b, count);
}

/*
addend1 (size)                  : n
addend2 (size)                  : m (n <= m)
sum (size)                      : >= n + 1
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
void addition(Large const& addend1, Large const& addend2, Large& sum, Count& count)
{
    assert(addend1.get_number_of_bits() <= addend2.get_number_of_bits());
    assert(addend1.get_number_of_bits() < sum.get_number_of_bits());
    ADDER_n_bits(addend1, addend2, sum, false, count);
}

/*
minuend (size)                  : n
substrahend (size)              : n
difference (size)               : n
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
void substraction(Large const& minuend, Large const& substrahend, Large& difference, Count& count)
{
    assert(minuend.get_number_of_bits() == substrahend.get_number_of_bits());
    assert(minuend.get_number_of_bits() == difference.get_number_of_bits());
    ADDER_n_bits(minuend, substrahend, difference, true, count);
}

/*
multiplicand (size)             : n
multiplicator (size)            : m
product (size)                  : >= n+m
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
void multiplication(Large const& multiplicand, Large const& multiplicator, Large& product, Count& count)
{
    assert(multiplicand.get_number_of_bits() + multiplicator.get_number_of_bits() <= product.get_number_of_bits());
    product.clear(0, product.get_number_of_bits());
    uint16_t multiplicand_length = multiplicand.get_number_of_bits();
    uint16_t multiplicator_length = multiplicator.get_number_of_bits();
    Large sum = Large(multiplicand_length+1);
    for(uint16_t i=0; i<multiplicator_length; i++)
    {
        COPY(product, sum, i, 0, multiplicand_length + 1, count);
        addition(multiplicand, sum, sum, count);
        REGS(multiplicator[i], sum, product, 0, i, multiplicand_length + 1, count);
    }
}

/*
dividend (size)                 : n
modulus (size)                  : m
quotient (size)                 : n
remainder (size)                : m
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
    Large dividend_part(remainder_size);
    Large remainder_intermediate(remainder_size);
    COPY(dividend, dividend_intermediate, 0, 0, quotient_size, count);
    bool enable;
    for(uint16_t i=0; i<quotient_size; i++)
    {
        COPY(dividend_intermediate, dividend_part, quotient_size-1-i, 0, remainder_size, count);
        substraction(dividend_part, modulus, remainder_intermediate, count);
        COPY(quotient, quotient, 0, 1, quotient_size, count);
        enable = OR(is_less_or_equal(modulus, dividend_part, count), remainder_intermediate[full_size - 1 - i], count);
        quotient[0] = enable;
        REGS(enable, remainder_intermediate, dividend_intermediate, 0, quotient_size-1-i, remainder_size, count);
    }
    COPY(MUX2_Large(enable, dividend_part, remainder_intermediate, count), remainder, 0, 0, remainder_size, count);
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
    squaring_modulo(base, modulus, squared, count);
    for(uint16_t i=0; i<exponent_size-1; i++)
    {
        squaring_modulo(squared, modulus, squared, count);
    }

}

