#include "fast_large.h"
#include <QDebug>

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

void fast_addition_mono(uint64_t b, uint64_t sum[], uint16_t size_a)
{
    uint64_t mask = 1;
    mask <<= 32;
    sum[0] += b;
    for(uint16_t i=0; i<size_a; i++)
    {
        uint64_t carry = sum[i] & mask;
        sum[i] ^= carry;
        sum[i+1] += (carry)?1:0;
    }
}

void fast_multiplication(uint64_t  a[], uint64_t b[], uint64_t product[], uint16_t size_a, uint16_t size_b)
{
    uint64_t storage;
    uint64_t storage_low;
    uint64_t storage_high;
    uint64_t mask_low = 4294967295;
    uint64_t mask_high = 18446744069414584320 ;
    fast_clear(product, size_a + size_b);
    for(uint16_t i=0; i<size_b; i++)
    {
        for(uint16_t j=0; j<size_a; j++)
        {
            storage = a[j] * b[i];
            storage_low = storage & mask_low;
            storage_high = (storage & mask_high) >> 32;
            fast_addition_mono(storage_low, product+i+j, size_a + size_b -i -j);
            fast_addition_mono(storage_high, product+i+j+1, size_a + size_b -i -j-1);
        }
    }
}


void fast_shift_left(uint64_t number[], uint16_t size, bool carry)
{
    uint64_t mask = 1;
    mask <<= 32;
    for(uint16_t i=0; i<size-1; i++)
    {
        number[i] <<= 1;
        number[i] += (carry)?1:0;
        carry = number[i] & mask;
        number[i] ^= number[i] & mask;
    }
    number[size-1] <<= 1;
    number[size-1] += (carry)?1:0;
    number[size-1] ^= (number[size-1] & mask);
}

void fast_division_modulo(uint64_t  a[], uint64_t b[], uint64_t quotient[], uint64_t remainder[], uint16_t size_a, uint16_t size_b, uint64_t storage_a[])
{
    fast_clear(quotient, size_a);
    fast_clear(remainder, size_b);
    fast_clear(storage_a, size_a);
    //uint64_t storage;
    //uint64_t storage_low;
    //uint64_t storage_high;
    //uint64_t mask_low = 4294967295;
    //uint64_t mask_high = 18446744069414584320 ;

    for(uint16_t i=0; i<size_b; i++)
    {

        for(uint16_t j=0; j<64; j++)
        {
            storage = a[j] * b[i];
            storage_low = storage & mask_low;
            storage_high = (storage & mask_high) >> 32;
            fast_addition_mono(storage_low, product+i+j, size_a + size_b -i -j);
            fast_addition_mono(storage_high, product+i+j+1, size_a + size_b -i -j-1);
        }
    }
}
