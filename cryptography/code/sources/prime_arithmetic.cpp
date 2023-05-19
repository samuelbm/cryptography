#include "prime_arithmetic.h"
#include <QDebug>
#include <QTest>

void count_initialization(Count& count)
{
    count.operation = 0;
    count.clock = 0;
}

/*
a (size)                        : n
b (size)                        : n
Latency (clocks)                : 0
Operations (per bit)            : n
*/
bool is_equal(Large const& a, Large const& b, Count& count)
{
    assert(a.get_number_of_bits() == b.get_number_of_bits());
    uint16_t n_bits = a.get_number_of_bits();
    bool answer = true;
    for(uint16_t i=0; i<n_bits; i++)
    {
        count.operation++;
        if(a[i] != b[i])
            answer &= false;
    }
    return answer;
}

/*
a (size)                        : n
b (size)                        : n
Latency (clocks)                : 0
Operations (per bit)            : n
*/
bool is_less_than(Large const& a, Large const& b, Count& count)
{
    assert(a.get_number_of_bits() == b.get_number_of_bits());
    uint16_t n_bits = a.get_number_of_bits();
    uint16_t index = n_bits;
    bool answer = false;
    bool found = false;
    for(uint16_t i=0; i<n_bits; i++)
    {
        count.operation++;
        index--;
        if(a[index] ^ b[index])
        {
            answer = (found)?answer:b[index];
            found = true;
        }
    }
    return answer;
}

/*
a (size)                        : n
b (size)                        : n
Latency (clocks)                : 0
Operations (per bit)            : n
*/
bool is_not_equal(Large const& a, Large const& b, Count& count)
{
    return !is_equal(a, b, count);
}

/*
a (size)                        : n
b (size)                        : n
Latency (clocks)                : 0
Operations (per bit)            : n
*/
bool is_greater_than(Large const& a, Large const& b, Count& count)
{
    return is_less_than(b, a, count);
}

/*
a (size)                        : n
b (size)                        : n
Latency (clocks)                : 0
Operations (per bit)            : n
*/
bool is_less_or_equal(Large const& a, Large const& b, Count& count)
{
    return !is_less_than(b, a, count);
}

/*
a (size)                        : n
b (size)                        : n
Latency (clocks)                : 0
Operations (per bit)            : n
*/
bool is_greater_or_equal(Large const& a, Large const& b, Count& count)
{
    return !is_less_than(a, b, count);
}

/*
addend1 (size)                  : n
addend2 (size)                  : m (n <= m)
sum (size)                      : >= n + 1
Latency (clocks)                : 1
Operations (per bit)            : n
*/
void addition(Large const& addend1, Large const& addend2, Large& sum, Count& count)
{
    assert(addend1.get_number_of_bits() <= addend2.get_number_of_bits());
    assert(addend1.get_number_of_bits() < sum.get_number_of_bits());
    uint16_t n_bits = addend1.get_number_of_bits();
    bool carry = false;
    bool next_carry;
    count.clock++;
    for(uint16_t i=0; i<n_bits; i++)
    {
        count.operation++;
        next_carry = (addend1[i] & addend2[i]) | (addend1[i] & carry) | (addend2[i] & carry);
        sum[i] = addend1[i] ^ addend2[i] ^ carry;
        carry = next_carry;
    }
    sum[n_bits] = carry;
}

/*
minuend (size)                  : n
substrahend (size)              : n
difference (size)               : n
Latency (clocks)                : 1
Operations (per bit)            : n
*/
void substraction(Large const& minuend, Large const& substrahend, Large& difference, Count& count)
{
    assert(minuend.get_number_of_bits() == substrahend.get_number_of_bits());
    assert(minuend.get_number_of_bits() == difference.get_number_of_bits());
    uint16_t n_bits = minuend.get_number_of_bits();
    bool carry = true;
    count.clock++;
    for(uint16_t i=0; i<n_bits; i++)
    {
        count.operation++;
        difference[i] = minuend[i] ^ !substrahend[i] ^ carry;
        carry = (minuend[i] & !substrahend[i]) | (minuend[i] & carry) | (!substrahend[i] & carry);
    }
    difference[n_bits] = carry;
}

/*
multiplicand (size)             : n
multiplicator (size)            : m
product (size)                  : >= n+m
Latency (clocks)                : m
Operations (per bit)            : n*m
*/
void multiplication(Large const& multiplicand, Large const& multiplicator, Large& product, Count& count)
{
    assert(multiplicand.get_number_of_bits() + multiplicator.get_number_of_bits() <= product.get_number_of_bits());
    product.fill_with_false(0, product.get_number_of_bits());
    uint16_t multiplicand_length = multiplicand.get_number_of_bits();
    uint16_t multiplicator_length = multiplicator.get_number_of_bits();
    Large* sum = new Large(multiplicand_length+1);
    for(uint16_t i=0; i<multiplicator_length; i++)
    {
        (*sum).insert(product.sub_large(i, multiplicand_length));
        (*sum)[multiplicand_length] = false;
        addition(multiplicand, *sum, *sum, count);
        if(multiplicator[i])
        {
            product.insert(*sum, i);
        }
    }
    delete sum;
}

/*
dividend (size)                 : n
modulus (size)                  : m
quotient (size)                 : n
remainder (size)                : m
Latency (clocks)                : n
Operations (per bit)            : 2*n*m
*/
void division_modulo(Large const& dividend, Large const& modulus, Large& quotient, Large& remainder, Count& count)
{
    Count dummy_count;
    Large zeros(modulus.get_number_of_bits());
    assert(is_not_equal(modulus, zeros, dummy_count));
    assert(dividend.get_number_of_bits() == quotient.get_number_of_bits());
    assert(modulus.get_number_of_bits() == remainder.get_number_of_bits());
    assert(quotient.get_number_of_bits() >= remainder.get_number_of_bits());
    uint16_t quotient_size = quotient.get_number_of_bits();
    uint16_t remainder_size = remainder.get_number_of_bits();
    quotient.fill_with_false(0, quotient_size);
    Large remainder_intermediate(quotient_size + remainder_size);
    Large chunk(remainder_size);
    remainder_intermediate.insert(dividend);
    for(uint16_t i=0; i<quotient_size; i++)
    {
        chunk.insert(remainder_intermediate.sub_large(quotient_size-1-i, remainder_size));
        substraction(chunk, modulus, remainder, count);
        quotient.shift_left();
        if(is_less_or_equal(modulus, chunk, count) || remainder_intermediate[quotient_size + remainder_size - 1 - i])
        {
            quotient[0] = true;
            remainder_intermediate.insert(remainder, quotient_size-1-i);
        }
        else
        {
            remainder.insert(chunk);
        }
    }
}

/*
addend1 (size)                  : n
addend2 (size)                  : n
modulus (size)                  : n
result (size)                   : n
Latency (clocks)                : n + 2
Operations (per bit)            : n(2*n + 3)
*/
void addition_modulo(Large const& addend1, Large const& addend2, Large& modulus, Large& result, Count& count)
{
    assert(addend1.get_number_of_bits() == addend2.get_number_of_bits());
    assert(addend1.get_number_of_bits() == modulus.get_number_of_bits());
    assert(addend1.get_number_of_bits() == result.get_number_of_bits());
    uint16_t n_bits = result.get_number_of_bits();
    Large sum(n_bits + 1);
    Large dummy_quotient(n_bits + 1);
    addition(addend1, addend2, sum, count);
    division_modulo(sum, modulus, dummy_quotient, result, count);
}

/*
minuend (size)                  : n
substrahend (size)              : n
modulus (size)                  : n
result (size)                   : n
Latency (clocks)                : 2*n + 3
Operations (per bit)            : 2*n*(3*n + 2)
*/
void substraction_modulo(Large const& minuend, Large const& substrahend, Large& modulus, Large& result, Count& count)
{
    assert(minuend.get_number_of_bits() == substrahend.get_number_of_bits());
    assert(minuend.get_number_of_bits() == modulus.get_number_of_bits());
    assert(minuend.get_number_of_bits() == result.get_number_of_bits());
    uint16_t n_bits = result.get_number_of_bits();
    Large minuend_modulo(n_bits);
    Large substraend_modulo(n_bits);
    Large dummy_quotient(n_bits);
    division_modulo(minuend, modulus, dummy_quotient, minuend_modulo, count);
    uint16_t freeze_clock_count = count.clock;// division_modulo in parallel
    division_modulo(substrahend, modulus, dummy_quotient, substraend_modulo, count);
    count.clock = freeze_clock_count;
    substraction(modulus, substraend_modulo, result, count);
    addition_modulo(minuend_modulo, result, modulus, result, count);
}

/*
minuend (size)                  : n
substrahend (size)              : n
modulus (size)                  : n
result (size)                   : n
Latency (clocks)                : 2*(n + 1)
Operations (per bit)            : 2*n*(3*n + 2)
*/
void multiplication_modulo(Large const& multiplicand, Large const& multiplicator, Large& modulus, Large& result, Count& count)
{

}

/*
multiplicator (size)            :
modulus (size)                  :
result (size)                   :
Latency (clocks)                :
Operations (per bit)            :
*/
void squaring_modulo(Large const& multiplicator, Large const& modulus, Large& result, Count& count)
{
    /*
    assert(multiplicator.get_number_of_bits() == modulus.get_number_of_bits());
    assert(multiplicator.get_number_of_bits() == result.get_number_of_bits());
    uint16_t n_bits = multiplicator.get_number_of_bits();
    Large product(2*n_bits);
    Large quotient(2*n_bits);
    multiplication(multiplicator, multiplicator, product, count);
    division_modulo(product, modulus, quotient, result, count);
    */
}

/*
base (size)                     :
exponent (size)                 :
modulus (size)                  :
result (size)                   :
Latency (clocks)                :
Operations (per bit)            :
*/
void modular_exponentiation(Large const& base, Large const& exponent, Large const& modulus, Large& result, Count& count)
{
    /*
    assert(base.get_number_of_bits() == modulus.get_number_of_bits());
    assert(base.get_number_of_bits() == result.get_number_of_bits());
    uint16_t exponent_size = exponent.get_number_of_bits();
    for(uint16_t i=0; i<=exponent_size; i++)
    {
        if(i<exponent_size)
        {

        }
        if(i>0)
        {

        }
    }
    */
}

