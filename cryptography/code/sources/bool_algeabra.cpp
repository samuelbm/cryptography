#include "bool_algeabra.h"

void count_initialization(Count& count)
{
    count.operation = 0;
    count.clock = 0;
    count.regs = 0;
    count.NOT_gates = 0;
    count.AND_gates = 0;
    count.NAND_gates = 0;
    count.OR_gates = 0;
    count.NOR_gates = 0;
    count.XOR_gates = 0;
    count.XNOR_gates = 0;
}


/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : 1
AND_gates                       : 0
NAND_gates                      : 0
OR_gates                        : 0
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
bool NOT(bool a, Count& count)
{
    count.NOT_gates++;
    return !a;
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : 0
AND_gates                       : 1
NAND_gates                      : 0
OR_gates                        : 0
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
bool AND(bool a, bool b, Count& count)
{
    count.AND_gates++;
    return a && b;
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : 0
AND_gates                       : 0
NAND_gates                      : 1
OR_gates                        : 0
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
bool NAND(bool a, bool b, Count& count)
{
    count.NAND_gates++;
    return !(a && b);
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : 0
AND_gates                       : 0
NAND_gates                      : 0
OR_gates                        : 1
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
bool OR(bool a, bool b, Count& count)
{
    count.OR_gates++;
    return a || b;
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : 0
AND_gates                       : 0
NAND_gates                      : 0
OR_gates                        : 0
NOR_gates                       : 1
XOR_gates                       : 0
XNOR_gates                      : 0
*/
bool NOR(bool a, bool b, Count& count)
{
    count.NOR_gates++;
    return !(a || b);
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : 0
AND_gates                       : 0
NAND_gates                      : 0
OR_gates                        : 0
NOR_gates                       : 0
XOR_gates                       : 1
XNOR_gates                      : 0
*/
bool XOR(bool a, bool b, Count& count)
{
    count.XNOR_gates++;
    return a ^ b;
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : 0
AND_gates                       : 0
NAND_gates                      : 0
OR_gates                        : 0
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 1
*/
bool XNOR(bool a, bool b, Count& count)
{
    count.XNOR_gates++;
    return !(a ^ b);
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : 1
AND_gates                       : 2
NAND_gates                      : 0
OR_gates                        : 1
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
bool MUX2_bits(bool select, bool a, bool b, Count& count)
{
    return OR(AND(NOT(a, count), select, count), AND(b, select, count), count);
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : n
AND_gates                       : 2*n
NAND_gates                      : 0
OR_gates                        : n
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
Large MUX2_Large(bool select, Large const& a, Large const& b, Count& count)
{
    assert(a.get_number_of_bits() == b.get_number_of_bits());
    uint16_t size = a.get_number_of_bits();
    Large* result = new Large(size);
    for(uint16_t i=0; i < size; i++)
    {
        (*result)[i] = MUX2_bits(select, a[i], b[i], count);
    }
    return *result;
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 0
NOT_gates                       : 0
AND_gates                       : 1
NAND_gates                      : 0
OR_gates                        : 0
NOR_gates                       : 0
XOR_gates                       : 1
XNOR_gates                      : 0
*/
void HALF_ADDER(bool a, bool b, bool& sum, bool& cout, Count& count)
{
    sum = XOR(a, b, count);
    cout = AND(a, b, count);
}

/*
Latency                         : 0
Operations                      : 1
regs                            : 0
NOT_gates                       : 0
AND_gates                       : 2
NAND_gates                      : 0
OR_gates                        : 1
NOR_gates                       : 0
XOR_gates                       : 2
XNOR_gates                      : 0
*/
void ADDER_1_bit(bool a, bool b, bool cin, bool& sum, bool& cout, Count& count)
{
    count.operation++;
    bool sum1, sum2, cout1, cout2;
    HALF_ADDER(a, b, sum1, cout1, count);
    HALF_ADDER(sum1, cin, sum2, cout2, count);
    sum = sum2;
    cout = OR(cout1, cout2, count);
}

/*
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
void ADDER_n_bits(Large const& a, Large const& b, Large& sum, bool is_substraction, Count& count)
{
    uint16_t n_bits = a.get_number_of_bits();
    bool carry_bit = is_substraction;
    bool a_bit, b_bit, sum_bit;
    for(uint16_t i=0; i<n_bits; i++)
    {
        a_bit = a[i];
        b_bit = MUX2_bits(is_substraction, b[i], NOT(b[i], count), count);
        ADDER_1_bit(a_bit, b_bit, carry_bit, sum_bit, carry_bit, count);
        sum[i] = sum_bit;
    }
    if(!is_substraction)
    {
        sum[n_bits] = carry_bit;
    }
}

/*
Latency                         : 0
Operations                      : 0
regs                            : 1
NOT_gates                       : 1
AND_gates                       : 2
NAND_gates                      : 0
OR_gates                        : 1
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
void REG(bool enable, bool D, bool& Q, Count& count)
{
    count.regs++;
    Q = MUX2_bits(enable, Q, D, count);
}

/*
Latency                         : 0
Operations                      : 0
regs                            : n
NOT_gates                       : n
AND_gates                       : 2*n
NAND_gates                      : 0
OR_gates                        : n
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
void REGS(bool enable, Large const& D, Large& Q, uint16_t D_start, uint16_t Q_start, uint16_t size, Count& count)
{
    assert(D_start + size <= D.get_number_of_bits());
    assert(Q_start + size <= Q.get_number_of_bits());
    for(uint16_t i=0; i<size; i++)
    {
        uint16_t index = size - 1 - i;
        REG(enable, D[index + D_start], Q[index + Q_start], count);
    }
}

/*
Latency                         : 0
Operations                      : 0
regs                            : n
NOT_gates                       : n
AND_gates                       : 2*n
NAND_gates                      : 0
OR_gates                        : n
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
void SHIFT_REGS(bool enable, Large const& D, Large& Q, uint16_t D_start, uint16_t Q_start, uint16_t size, bool insert, Count& count)
{
    assert(D_start + size <= D.get_number_of_bits());
    assert(Q_start + size <= Q.get_number_of_bits());
    REGS(enable, D, Q, D_start, Q_start + 1, size-1, count);
    REG(enable, insert, Q[Q_start], count);
}

/*
Latency                         : 0
Operations                      : 0
regs                            : n
NOT_gates                       : 0
AND_gates                       : 0
NAND_gates                      : 0
OR_gates                        : 0
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : 0
*/
void COPY(Large const& D, Large& Q, uint16_t D_start, uint16_t Q_start, uint16_t size, Count& count)
{
    assert(D_start + size <= D.get_number_of_bits());
    assert(Q_start + size <= Q.get_number_of_bits());
    for(uint16_t i=0; i<size; i++)
    {
        count.regs++;
        uint16_t index = size - 1 - i;
        Q[index + Q_start] = D[index + D_start];
    }
}
