#ifndef LARGE_H
#define LARGE_H

#include <stdint.h>
#include <QString>

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

class Large
{
public:
    Large(uint16_t number_of_bits);
    Large(Large const& large);
    ~Large();
    Large& operator=(Large const& large);
    bool operator[](uint16_t index) const;
    bool& operator[](uint16_t index);
    uint16_t get_number_of_bits() const;
    void clear(uint16_t start_index, uint16_t length);
    bool is_null() const;
    QString toBin() const;
    QString toHex() const;
    void split(Large& subpart, uint16_t start_index);
    void insert(Large const& subpart, uint16_t start_index=0);
    void REG(bool enable, Large const& D, uint16_t start_index, Count& count);
    bool SHIFT_LEFT(bool enable, bool insert, Count& count);
    bool SHIFT_RIGHT(bool enable, bool insert, Count& count);
    void init_with_small_number(uint16_t number);
private:    
    void allocate_memory();
    void copy(Large const& large);
private:
    bool* bits;
    uint16_t bits_size;
};

void count_initialization(Count& count);
Large& create_and_initialize_large(uint16_t init_value, uint16_t n_bits);

#endif // LARGE_H
