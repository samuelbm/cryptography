#include "prime_arithmetic.h"

bool is_equal(Large const& a, Large const& b, uint64_t& operation_count)
{
    uint16_t n_bits = a.get_number_of_bits();
    if(n_bits != b.get_number_of_bits())
        return false;

    for(uint16_t i=0; i<n_bits; i++)
    {
        operation_count++;
        if(a[i] != b[i])
            return false;
    }
    return true;
}

bool is_less_than(Large const& a, Large const& b, uint64_t& operation_count)
{
    uint16_t n_bits = a.get_number_of_bits();
    if(n_bits != b.get_number_of_bits())
        return false;

    uint16_t index = n_bits;
    for(uint16_t i=0; i<n_bits; i++)
    {
        operation_count++;
        index--;
        if(a[i] & ~b[i])
        {
            return false;
        }
        else if(~a[i] & b[i])
        {
            return true;
        }
    }
    return false;
}

bool is_not_equal(Large const& a, Large const& b, uint64_t& operation_count)
{
    return ~is_equal(a, b, operation_count);
}

bool is_greater_than(Large const& a, Large const& b, uint64_t& operation_count)
{
    return is_less_than(b, a, operation_count);
}

bool is_less_or_equal(Large const& a, Large const& b, uint64_t& operation_count)
{
    return ~is_less_than(b, a, operation_count);
}

bool is_greater_or_equal(Large const& a, Large const& b, uint64_t& operation_count)
{
    return ~is_less_than(a, b, operation_count);
}

void addition(Large const& a, Large const& b, Large& sum, uint16_t& a_start, uint16_t& sum_start, bool carry_in, uint64_t& operation_count)
{
    bool carry = carry_in;
    uint16_t n_bits = b.get_number_of_bits();
    for(uint16_t i=0; i<n_bits; i++)
    {
        operation_count++;
        sum[i + sum_start] = a[i + a_start] ^ b[i] ^ carry;
        carry = (a[i + a_start] & b[i]) | (a[i + a_start] & carry) | (b[i] & carry);
    }
    sum[n_bits + sum_start] = carry;
}
