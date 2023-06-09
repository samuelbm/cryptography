#ifndef BOOL_ALGEABRA_H
#define BOOL_ALGEABRA_H

#include "large.h"

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
void ADDER_n_bits(Large const& a, Large const& b, Large& sum, Count& count);
void SUB_n_bits(Large const& a, Large const& b, Large& sum, Count& count);
bool is_equal(Large const& a, Large const& b, Count& count);
bool is_less_than(Large const& a, Large const& b, Count& count);
bool is_not_equal(Large const& a, Large const& b, Count& count);
bool is_greater_than(Large const& a, Large const& b, Count& count);
bool is_less_or_equal(Large const& a, Large const& b, Count& count);
bool is_greater_or_equal(Large const& a, Large const& b, Count& count);
#endif // BOOL_ALGEABRA_H
