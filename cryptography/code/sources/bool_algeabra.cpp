#include "bool_algeabra.h"

void count_initialization(Count& count)
{
    count.operation = 0;
    count.clock = 0;
    count.NOT_gates = 0;
    count.AND_gates = 0;
    count.NAND_gates = 0;
    count.OR_gates = 0;
    count.NOR_gates = 0;
    count.XOR_gates = 0;
    count.XNOR_gates = 0;
}

void REG(bool enable, bool D, bool& Q, Count& count)
{

}

void REGS(bool enable, Large const& D, Large& Q, uint16_t D_start, uint16_t Q_start, uint16_t size, Count& count)
{

}

void SHIFT_REGS(bool enable, Large const& D, Large& Q, uint16_t D_start, uint16_t Q_start, uint16_t size, bool insert, Count& count)
{

}

bool NOT(bool a, Count& count)
{
    count.NOT_gates++;
    return !a;
}

bool AND(bool a, bool b, Count& count)
{
    count.AND_gates++;
    return a && b;
}

bool NAND(bool a, bool b, Count& count)
{
    count.NAND_gates++;
    return !(a && b);
}

bool OR(bool a, bool b, Count& count)
{
    count.OR_gates++;
    return a || b;
}

bool NOR(bool a, bool b, Count& count)
{
    count.NOR_gates++;
    return !(a || b);
}

bool XOR(bool a, bool b, Count& count)
{
    count.XNOR_gates++;
    return a ^ b;
}

bool XNOR(bool a, bool b, Count& count)
{
    count.XNOR_gates++;
    return !(a ^ b);
}

void HALF_ADDER(bool a, bool b, bool& sum, bool& cout, Count& count)
{
    sum = XOR(a, b, count);
    cout = AND(a, b, count);
}

void ADDER_1_bit(bool a, bool b, bool cin, bool& sum, bool& cout, Count& count)
{
    count.operation++;
    bool sum1, sum2, cout1, cout2;
    HALF_ADDER(a, b, sum1, cout1, count);
    HALF_ADDER(sum1, cin, sum2, cout2, count);
    sum = sum2;
    cout = OR(cout1, cout2, count);
}

void ADDER_n_bits(Large const& a, Large const& b, Large& sum, bool is_substraction, Count& count)
{
    uint16_t n_bits = a.get_number_of_bits();
    bool a_bit, b_bit, sum_bit, carry_bit;
    carry_bit = is_substraction;
    for(uint16_t i=0; i<n_bits; i++)
    {
        a_bit = a[i];
        b_bit = (is_substraction)? NOT(b[i], count) : b[i];
        ADDER_1_bit(a_bit, b_bit, carry_bit, sum_bit, carry_bit, count);
        sum[i] = sum_bit;
    }
    if(!is_substraction)
    {
        sum[n_bits] = carry_bit;
    }
}
