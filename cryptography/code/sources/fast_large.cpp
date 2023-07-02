#include "fast_large.h"
#include <QDebug>

void new_storage(Storage& storage, uint16_t size)
{
    storage.difference_s1 = new uint64_t[size + 1];
    storage.difference_s2 = new uint64_t[size + 1];
    storage.product_2s = new uint64_t[2*size];
    storage.quotient_s = new uint64_t[size];
    storage.dummy_quotient_2s = new uint64_t[2*size];
    storage.squared_s = new uint64_t[size];
    storage.phi_n_s = new uint64_t[size];
    storage.one_s = new uint64_t[size];
    storage.base_s = new uint64_t[size];
    storage.result_s = new uint64_t[size];
    storage.prime_s = new uint64_t[size];
    fast_init_with_small_number(1, storage.one_s, size);
}

void delete_storage(Storage& storage)
{
    delete[] storage.difference_s1;
    delete[] storage.difference_s2;
    delete[] storage.product_2s;
    delete[] storage.quotient_s;
    delete[] storage.dummy_quotient_2s;
    delete[] storage.squared_s;
    delete[] storage.phi_n_s;
    delete[] storage.one_s;
    delete[] storage.base_s;
    delete[] storage.result_s;
    delete[] storage.prime_s;
    storage.difference_s1 = nullptr;
    storage.difference_s2 = nullptr;
    storage.product_2s = nullptr;
    storage.quotient_s = nullptr;
    storage.dummy_quotient_2s = nullptr;
    storage.squared_s = nullptr;
    storage.phi_n_s = nullptr;
    storage.one_s = nullptr;
    storage.base_s = nullptr;
    storage.result_s = nullptr;
    storage.result_s = nullptr;
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

void fast_copy(uint64_t source[], uint64_t destination[], uint16_t size)
{
    for(uint16_t i=0; i<size; i++)
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

bool fast_is_less_or_equal_than(uint64_t a[], uint64_t b[], uint16_t size)
{
    uint16_t index = size;
    for(uint16_t i=0; i<size; i++)
    {
       index--;
       if(a[index] > b[index])
       {
           return false;
       }
       else if(a[index] < b[index])
       {
            return true;
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
    uint64_t cross_product;
    uint64_t storage_low;
    uint64_t storage_high;
    uint64_t mask_low = 4294967295;
    uint64_t mask_high = 18446744069414584320 ;
    fast_clear(product, size_a + size_b);
    for(uint16_t i=0; i<size_b; i++)
    {
        for(uint16_t j=0; j<size_a; j++)
        {
            cross_product = a[j] * b[i];
            storage_low = cross_product & mask_low;
            storage_high = (cross_product & mask_high) >> 32;
            fast_addition_mono(storage_low, product+i+j, size_a + size_b -i -j);
            fast_addition_mono(storage_high, product+i+j+1, size_a + size_b -i -j-1);
        }
    }
}


bool fast_shift_left(uint64_t number[], uint16_t size, bool carry)
{
    bool super_carry = (number[size-1] >> 31) & 1;
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
    return super_carry;
}

void fast_division_modulo(uint64_t  a[], uint64_t b[], uint64_t quotient[], uint64_t remainder[], uint16_t size_a, uint16_t size_b, Storage& storage)
{
    Large la = fast_large2Large(a, 256);
    fast_clear(quotient, size_a);
    fast_clear(remainder, size_b);
    uint16_t index = size_a;
    uint16_t bit;
    bool carry;
    bool super_carry;
    for(uint16_t i=0; i<size_a; i++)
    {
        index--;
        bit = 32;
        for(uint16_t j=0; j<32; j++)
        {
            bit--;
            carry = (a[index] >> bit) & 1;
            super_carry = fast_shift_left(remainder, size_b, carry);
            fast_shift_left(quotient, size_a, false);
            if(super_carry || fast_is_less_or_equal_than(b, remainder, size_b))
            {
                fast_substraction(remainder, b, remainder, size_b, storage);
                quotient[0] += 1;
            }
        }
    }
}

void fast_multiplication_modulo(uint64_t a[], uint64_t b[], uint64_t n[], uint64_t result[], uint16_t size, Storage& storage)
{
    fast_multiplication(a, b, storage.product_2s, size, size, storage);
    fast_division_modulo(storage.product_2s, n, storage.dummy_quotient_2s, result, 2*size, size, storage);
}

void fast_exponentiation_modulo(uint64_t base[], uint64_t exponent[], uint64_t modulus[], uint64_t result[], uint16_t size, uint16_t size_exponent, Storage& storage)
{
    fast_clear(result, size);
    result[0] += 1;
    fast_copy(base, storage.squared_s, size);
    for(uint16_t i=0; i<size_exponent; i++)
    {
        for(uint16_t j=0; j<32; j++)
        {
            if((exponent[i] >> j) & 1)
            {
                fast_multiplication_modulo(result, storage.squared_s, modulus, result, size, storage);
            }
            fast_multiplication_modulo(storage.squared_s, storage.squared_s, modulus, storage.squared_s, size, storage);
        }
    }
}

bool fast_is_prime_with_fermat_little_theorem(uint64_t maybe_prime[], uint16_t size, uint16_t nb_round, Storage& storage)
{
    fast_substraction(maybe_prime, storage.one_s, storage.phi_n_s, size, storage);
    for(uint64_t i = 0; i < nb_round; i++)
    {
        fast_init_with_small_number(storage.primes[i], storage.base_s, size);
        fast_exponentiation_modulo(storage.base_s, storage.phi_n_s, maybe_prime, storage.result_s, size, size, storage);
        if(!fast_is_equal(storage.result_s, storage.one_s, size))
        {
            return false; //certainly;
        }
    }
    return true; //probably
}

// cette implémentation semble ne pas etre assez aléatoire.
//uint16_t fast_find_prime_equiv_3_mod_4(uint64_t prime[], uint16_t size, QRandomGenerator& prng, Storage& storage, uint16_t nb_round, uint16_t nb_bits)
//{
//    uint64_t one = 1;
//    uint64_t all_one_32 = 4294967295;
//    uint16_t tries = 0;
//    uint16_t mask = 31;
//    do
//    {
//        tries++;
//        for(uint16_t i=0; i<size; i++)
//        {
//            prime[i] = prng.generate64();
//        }
//        for(uint16_t i=0; i<32*size; i++)
//        {
//            uint64_t index_word = i >> 5;
//            uint64_t index_bit = i & mask;
//            if(i == 0 || i == 1)
//            {
//                prime[index_word] |= (one << index_bit);
//            }
//            else if(i == nb_bits - 1)
//            {
//                prime[index_word] |= (one << index_bit);
//            }
//            else if(i >= nb_bits)
//            {
//                prime[index_word] &= ((one << index_bit) ^ all_one_32);
//            }
//        }
//        Large test = fast_large2Large(prime, nb_bits);
//        qDebug() << tries << test.toHex() << Large2String(test);
//    } while(!fast_is_prime_with_fermat_little_theorem(prime, size, nb_round, storage));
//    return tries;
//}

uint16_t fast_find_prime_equiv_3_mod_4(uint64_t prime[], uint16_t size, QRandomGenerator& prng, Storage& storage, uint16_t nb_round, uint16_t nb_bits)
{
    uint64_t one = 1;
    uint64_t all_one_32 = 4294967295;
    uint16_t tries = 0;
    uint16_t mask = 31;
    uint16_t index;
    do
    {
        tries++;
        for(uint16_t i=0; i < size; i++)
        {
            for(uint16_t j=0; j < 32; j++)
            {
                index = 32*i + j;
                if(index == 0 || index == 1)
                {
                    prime[i] |= (one << j);
                }
                else if(index == nb_bits - 1)
                {
                    prime[i] |= (one << j);
                }
                else if(index >= nb_bits)
                {
                    prime[i] &= ((one << j) ^ all_one_32);
                }
                else
                {
                    prime[i] = (prng.generate64() & 1)? prime[i] | (one << j): prime[i] & ((one << j) ^ all_one_32);
                }
            }
        }
    } while(!fast_is_prime_with_fermat_little_theorem(prime, size, nb_round, storage));
    return tries;
}

