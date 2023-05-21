#ifndef BOOL_ALGEABRA_H
#define BOOL_ALGEABRA_H

#include "large.h"

typedef struct Count
{
    uint64_t operation;
    uint64_t clock;
    uint64_t regs;
    uint64_t NOT_gates;
    uint64_t AND_gates;
    uint64_t NAND_gates;
    uint64_t OR_gates;
    uint64_t NOR_gates;
    uint64_t XOR_gates;
    uint64_t XNOR_gates;
} Count;

void count_initialization(Count& count);

bool NOT(bool a, Count& count);
bool AND(bool a, bool b, Count& count);
bool NAND(bool a, bool b, Count& count);
bool OR(bool a, bool b, Count& count);
bool NOR(bool a, bool b, Count& count);
bool XOR(bool a, bool b, Count& count);
bool XNOR(bool a, bool b, Count& count);
bool MUX2_bits(bool select, bool a, bool b, Count& count);
Large MUX2_Large(bool select, Large const& a, Large const& b, Count& count);
void HALF_ADDER(bool a, bool b, bool& sum, bool& cout, Count& count);
void ADDER_1_bit(bool a, bool b, bool cin, bool& sum, bool& cout, Count& count);
void ADDER_n_bits(Large const& a, Large const& b, Large& sum, bool is_substraction, Count& count);

void REG(bool enable, bool D, bool& Q, Count& count);
void REGS(bool enable, Large const& D, Large& Q, uint16_t D_start, uint16_t Q_start, uint16_t size, Count& count);
void SHIFT_REGS(bool enable, Large const& D, Large& Q, uint16_t D_start, uint16_t Q_start, uint16_t size, bool insert, Count& count);
void COPY(Large const& D, Large& Q, uint16_t D_start, uint16_t Q_start, uint16_t size, Count& count);

#endif // BOOL_ALGEABRA_H
