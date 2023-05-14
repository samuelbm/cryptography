#include "prime_arithmetic.h"
#include <QDebug>

void count_initialization(Count& count)
{
    count.operation = 0;
    count.clock = 0;
}

bool is_equal(Large const& a, Large const& b, Count& count)
{
    uint16_t n_bits = a.get_number_of_bits();
    for(uint16_t i=0; i<n_bits; i++)
    {
        count.operation++;
        if(a[i] != b[i])
            return false;
    }
    return true;
}

bool is_less_than(Large const& a, Large const& b, Count& count)
{
    uint16_t n_bits = a.get_number_of_bits();
    uint16_t index = n_bits;
    for(uint16_t i=0; i<n_bits; i++)
    {
        count.operation++;
        index--;
        if(a[index] & !b[index])
        {
            return false;
        }
        else if(!a[index] & b[index])
        {
            return true;
        }
    }
    return false;
}

bool is_not_equal(Large const& a, Large const& b, Count& count)
{
    return !is_equal(a, b, count);
}

bool is_greater_than(Large const& a, Large const& b, Count& count)
{
    return is_less_than(b, a, count);
}

bool is_less_or_equal(Large const& a, Large const& b, Count& count)
{
    return !is_less_than(b, a, count);
}

bool is_greater_or_equal(Large const& a, Large const& b, Count& count)
{
    return !is_less_than(a, b, count);
}

void addition(Large const& addend1, Large const& addend2, Large& sum, Count& count)
{
    count.clock++;
    uint16_t n_bits = addend1.get_number_of_bits();
    bool carry = false;
    bool next_carry;
    for(uint16_t i=0; i<n_bits; i++)
    {
        count.operation++;
        next_carry = (addend1[i] & addend2[i]) | (addend1[i] & carry) | (addend2[i] & carry);
        sum[i] = addend1[i] ^ addend2[i] ^ carry;
        carry = next_carry;
    }
    count.operation++;
    sum[n_bits] = carry;
}

void substraction(Large const& minuend, Large const& substrahend, Large& difference, Count& count)
{
    count.clock++;
    uint16_t n_bits = minuend.get_number_of_bits();
    bool carry = true;
    for(uint16_t i=0; i<n_bits; i++)
    {
        count.operation++;
        difference[i] = minuend[i] ^ !substrahend[i] ^ carry;
        carry = (minuend[i] & !substrahend[i]) | (minuend[i] & carry) | (!substrahend[i] & carry);
    }
    count.operation++;
    difference[n_bits] = carry;
}

void multiplication(Large const& multiplicand, Large const& multiplicator, Large& product, Count& count)
{
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

void division_modulo(Large const& dividend, Large const& modulus, Large const& quotient, Large const& remainder, Count& count)
{

}

void squaring(Large const& multiplicator, Large const& modulus, Count& count)
{

}

void modular_exponentiation(Large const& base, Large const& exponent, Large const& modulus, Count& count)
{

}

