#include "fast_large.h"

Large fast_large2Large(uint64_t fast_large[], uint16_t nb_bits)
{
    Large number(nb_bits);
    for(uint16_t i=0; i<nb_bits; i++)
    {
        uint64_t quotient = (i >> 5);
        uint64_t remainder = i - (quotient << 5);
        number[i] = (fast_large[quotient] >> remainder) & 1;
    }
    return number;
}

void copy(uint64_t source[], uint64_t destination[], uint16_t size_a)
{
    for(uint16_t i=0; i<size_a; i++)
    {
        destination[i] = source[i];
    }
}

void fast_clear(uint64_t x[], uint16_t size)
{
    for(uint16_t i=0; i<size; i++)
    {
        x[i] = 0;
    }
}

void fast_init_with_small_number(uint64_t init_number, uint64_t array_number[], uint16_t size)
{
    fast_clear(array_number, size);
    array_number[0] = init_number;
}

bool fast_is_equal(uint64_t a[], uint64_t b[], uint16_t size_a)
{
    for(uint16_t i=0; i<size_a; i++)
    {
       if(a[i] != b[i])
       {
           return false;
       }
    }
    return true;
}

bool fast_is_less_than(uint64_t a[], uint64_t b[], uint16_t size_a)
{
    uint16_t index = size_a;
    for(uint16_t i=0; i<size_a; i++)
    {
       index--;
       if(a[index] < b[index])
       {
           return true;
       }
       else if(a[index] > b[index])
       {
            return false;
       }
    }
    return false;
}

bool fast_is_less_or_equal_than(uint64_t a[], uint64_t b[], uint16_t size_a)
{
    uint16_t index = size_a;
    for(uint16_t i=0; i<size_a; i++)
    {
       index--;
       if(a[index] > b[index])
       {
           return false;
       }
    }
    return true;
}

void fast_addition(uint64_t a[], uint64_t b[], uint64_t sum[], uint16_t size_a) //same size as b, sum must be large
{
    uint64_t mask = 1;
    mask <<= 32;
    sum[0] = 0;
    for(uint16_t i=0; i<size_a; i++)
    {
        sum[i] += (a[i] + b[i]);
        uint64_t carry = sum[i] & mask;
        sum[i] ^= carry;
        sum[i+1] = (carry)?1:0;
    }
}

void fast_substraction(uint64_t a[], uint64_t b[], uint64_t difference[], uint16_t size_a) //a must be greater than b but of same size
{
    uint64_t mask_inverse = 4294967295;
    uint64_t inverse;
    uint64_t mask = 1;
    mask <<= 32;
    difference[0] = 1;
    for(uint16_t i=0; i<size_a; i++)
    {
        inverse = b[i] ^ mask_inverse;
        difference[i] += (a[i] + inverse);
        uint64_t carry = difference[i] & mask;
        difference[i] ^= carry;
        difference[i+1] = (carry)?1:0;
    }
    difference[size_a] = 0;
}
