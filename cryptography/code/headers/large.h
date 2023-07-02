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
    Large(uint64_t number_of_bits);
    Large(Large const& large);
    ~Large();
    Large& operator=(Large const& large);
    bool operator[](uint64_t index) const;
    bool& operator[](uint64_t index);
    uint64_t get_number_of_bits() const;
    void clear(uint64_t start_index, uint64_t length);
    bool is_null() const;
    QString toBin() const;
    QString toHex() const;
    void split(Large& subpart, uint64_t start_index) const;
    void insert(Large const& subpart, uint64_t start_index=0);
    void REG(bool enable, Large const& D, uint64_t start_index, Count& count);
    bool SHIFT_LEFT(bool enable, bool insert, Count& count);
    bool SHIFT_RIGHT(bool enable, bool insert, Count& count);
    void init_with_small_number(uint64_t number);
private:    
    void allocate_memory();
    void copy(Large const& large);
private:
    bool* bits;
    uint64_t bits_size;
};

void count_initialization(Count& count);
Large& create_and_initialize_large(uint64_t init_value, uint64_t n_bits);

#endif // LARGE_H
