#include "bool_algeabra.h"
#include <QTest>

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
    count.XOR_gates++;
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
Operations                      : 1
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
    count.operation++;
    return OR(AND(NOT(select, count), a, count), AND(select, b, count), count);
}

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
Operations                      : n
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
    uint64_t size = a.get_number_of_bits();
    Large* result = new Large(size);
    for(uint64_t i=0; i < size; i++)
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
a (size)                        : n
b (size)                        : n
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
void ADDER_n_bits(Large const& a, Large const& b, Large& sum, Count& count)
{
    assert(a.get_number_of_bits() == b.get_number_of_bits());
    assert(a.get_number_of_bits() + 1 == sum.get_number_of_bits());
    uint64_t n_bits = a.get_number_of_bits();
    bool carry_bit = false;
    for(uint64_t i=0; i<n_bits; i++)
    {
        ADDER_1_bit(a[i], b[i], carry_bit, sum[i], carry_bit, count);
    }
    sum[n_bits] = carry_bit;
}

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
Operations                      : n
regs                            : 0
NOT_gates                       : n
AND_gates                       : 2*n
NAND_gates                      : 0
OR_gates                        : n
NOR_gates                       : 0
XOR_gates                       : 2*n
XNOR_gates                      : 0
*/
void SUB_n_bits(Large const& a, Large const& b, Large& sum, Count& count)
{
    assert(a.get_number_of_bits() == b.get_number_of_bits());
    assert(a.get_number_of_bits() == sum.get_number_of_bits());
    uint64_t n_bits = a.get_number_of_bits();
    bool carry_bit = true;
    for(uint64_t i=0; i<n_bits; i++)
    {
        ADDER_1_bit(a[i], NOT(b[i], count), carry_bit, sum[i], carry_bit, count);
    }
}

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
Operations                      : n
regs                            : 0
NOT_gates                       : 0
AND_gates                       : n
NAND_gates                      : 0
OR_gates                        : 0
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : n
*/
bool is_equal(Large const& a, Large const& b, Count& count)
{
    assert(a.get_number_of_bits() == b.get_number_of_bits());
    uint64_t n_bits = a.get_number_of_bits();
    bool answer = true;
    for(uint64_t i=0; i<n_bits; i++)
    {
        count.operation++;
        answer = AND(XNOR(a[i], b[i], count), answer, count);
    }
    return answer;
}

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
Operations                      : 2*n
regs                            : 0
NOT_gates                       : 2*n
AND_gates                       : 3*n
NAND_gates                      : 0
OR_gates                        : 2*n
NOR_gates                       : 0
XOR_gates                       : n
XNOR_gates                      : 0
*/
bool is_less_than(Large const& a, Large const& b, Count& count)
{
    assert(a.get_number_of_bits() == b.get_number_of_bits());
    uint64_t size = a.get_number_of_bits();
    bool answer = false;
    bool found = false;
    bool enable;
    for(uint64_t i=0; i<size; i++)
    {
        uint64_t index = size - 1 - i;
        count.operation++;
        enable = XOR(a[index], b[index], count);
        answer = MUX2_bits(AND(NOT(found, count), enable, count), answer, b[index], count);
        found = OR(enable, found, count);
    }
    return answer;
}

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
Operations                      : n
regs                            : 0
NOT_gates                       : 1
AND_gates                       : n
NAND_gates                      : 0
OR_gates                        : 0
NOR_gates                       : 0
XOR_gates                       : 0
XNOR_gates                      : n
*/
bool is_not_equal(Large const& a, Large const& b, Count& count)
{
    return NOT(is_equal(a, b, count), count);
}

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
Operations                      : 2*n
regs                            : 0
NOT_gates                       : 2*n
AND_gates                       : 3*n
NAND_gates                      : 0
OR_gates                        : 2*n
NOR_gates                       : 0
XOR_gates                       : n
XNOR_gates                      : 0
*/
bool is_greater_than(Large const& a, Large const& b, Count& count)
{
    return is_less_than(b, a, count);
}

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
Operations                      : 2*n
regs                            : 0
NOT_gates                       : 2*n + 1
AND_gates                       : 3*n
NAND_gates                      : 0
OR_gates                        : 2*n
NOR_gates                       : 0
XOR_gates                       : n
XNOR_gates                      : 0
*/
bool is_less_or_equal(Large const& a, Large const& b, Count& count)
{
    return NOT(is_less_than(b, a, count), count);
}

/*
a (size)                        : n
b (size)                        : n
Latency                         : 0
Operations                      : 2*n
regs                            : 0
NOT_gates                       : 2*n + 1
AND_gates                       : 3*n
NAND_gates                      : 0
OR_gates                        : 2*n
NOR_gates                       : 0
XOR_gates                       : n
XNOR_gates                      : 0
*/
bool is_greater_or_equal(Large const& a, Large const& b, Count& count)
{
    return NOT(is_less_than(a, b, count), count);
}
