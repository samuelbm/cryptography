#include "fast_large.h"
#include <QDebug>

void new_storage(Storage& storage, uint16_t size)
{
    storage.difference_s1 = new uint64_t[size + 1];
    storage.product_2s = new uint64_t[2*size];
    storage.quotient_s = new uint64_t[size];
    storage.dummy_quotient_2s = new uint64_t[2*size];
}

void delete_storage(Storage& storage)
{
    delete[] storage.difference_s1;
    delete[] storage.product_2s;
    delete[] storage.quotient_s;
    delete[] storage.dummy_quotient_2s;
    storage.difference_s1 = nullptr;
    storage.product_2s = nullptr;
    storage.quotient_s = nullptr;
    storage.dummy_quotient_2s = nullptr;
}

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

void fast_copy(uint64_t source[], uint64_t destination[], uint16_t size_a)
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

//void fast_addition(uint64_t a[], uint64_t b[], uint64_t sum[], uint16_t size_a)
//{
//    uint64_t mask = 1;
//    mask <<= 32;
//    sum[0] = 0;
//    for(uint16_t i=0; i<size_a; i++)
//    {
//        sum[i] += (a[i] + b[i]);
//        uint64_t carry = sum[i] & mask;
//        sum[i] ^= carry;
//        sum[i+1] = (carry)?1:0;
//    }
//}

void fast_substraction(uint64_t a[], uint64_t b[], uint64_t difference[], uint16_t size, Storage& storage)
{
    uint64_t mask_inverse = 4294967295;
    uint64_t inverse;
    uint64_t mask = 1;
    mask <<= 32;
    fast_clear(storage.difference_s1, size);
    storage.difference_s1[0] = 1;
    for(uint16_t i=0; i<size; i++)
    {
        inverse = b[i] ^ mask_inverse;
        storage.difference_s1[i] += (a[i] + inverse);
        uint64_t carry = storage.difference_s1[i] & mask;
        storage.difference_s1[i] ^= carry;
        storage.difference_s1[i+1] = (carry)?1:0;
    }
    storage.difference_s1[size] = 0;
    fast_copy(storage.difference_s1, difference, size);
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

void fast_multiplication(uint64_t  a[], uint64_t b[], uint64_t product[], uint16_t size_a, uint16_t size_b, Storage& storage)
{
//    uint64_t storage;
//    uint64_t storage_low;
//    uint64_t storage_high;
//    uint64_t mask_low = 4294967295;
//    uint64_t mask_high = 18446744069414584320 ;
//    fast_clear(product, size_a + size_b);
//    for(uint16_t i=0; i<size_b; i++)
//    {
//        for(uint16_t j=0; j<size_a; j++)
//        {
//            storage = a[j] * b[i];
//            storage_low = storage & mask_low;
//            storage_high = (storage & mask_high) >> 32;
//            fast_addition_mono(storage_low, product+i+j, size_a + size_b -i -j);
//            fast_addition_mono(storage_high, product+i+j+1, size_a + size_b -i -j-1);
//        }
//    }
}


void fast_shift_left(uint64_t number[], uint16_t size, bool carry)
{
//    uint64_t mask = 1;
//    mask <<= 32;
//    for(uint16_t i=0; i<size-1; i++)
//    {
//        number[i] <<= 1;
//        number[i] += (carry)?1:0;
//        carry = number[i] & mask;
//        number[i] ^= number[i] & mask;
//    }
//    number[size-1] <<= 1;
//    number[size-1] += (carry)?1:0;
//    number[size-1] ^= (number[size-1] & mask);
}

void fast_division_modulo(uint64_t  a[], uint64_t b[], uint64_t quotient[], uint64_t remainder[], uint16_t size_a, uint16_t size_b, Storage& storage)
{
//    fast_clear(quotient, size_a);
//    fast_clear(remainder, size_b);
//    fast_clear(difference, size_b+1);
//    uint16_t index = size_a;
//    uint16_t bit;
//    bool carry;
//    for(uint16_t i=0; i<size_a; i++)
//    {
//        index--;
//        bit = 32;
//        for(uint16_t j=0; j<32; j++)
//        {
//            bit--;
//            carry = (a[index] >> bit) & 1;
//            fast_shift_left(remainder, size_b, carry);
//            fast_shift_left(quotient, size_a, false);
//            if(fast_is_less_or_equal_than(b, remainder, size_b))
//            {
//                fast_substraction(remainder, b, difference, size_b);
//                fast_copy(difference, remainder,  size_b);
//                quotient[0] += 1;
//            }
//        }
//    }
}

void fast_multiplication_modulo(uint64_t a[], uint64_t b[], uint64_t n[], uint64_t result[], uint16_t size, Storage& storage)
{
//    fast_multiplication(a, b, storage, size, size);
//    fast_division_modulo(storage, n, dummy_quotient, result, 2*size, size, difference);
}

void fast_exponentiation_modulo(uint64_t base[], uint64_t exponent[], uint64_t modulus[], uint64_t result[], uint16_t size, uint16_t size_exponent, Storage& storage)
{
//    fast_clear(result, size);
//    result[0] += 1;
//    copy(base, squared, size);
//    for(uint16_t i=0; i<size_exponent; i++)
//    {
//        for(uint16_t j=0; j<32; j++)
//        {
//            if((exponent[i] >> j) & 1)
//            {
//                fast_multiplication_modulo(result, squared, modulus, result_storage, size, storage, dummy_quotient, difference);
//                copy(result_storage, result, size);
//            }
//            fast_multiplication_modulo(squared, squared, modulus, squared_storage, size, storage, dummy_quotient, difference);
//            copy(squared_storage, squared, size);
//        }
//    }
}

