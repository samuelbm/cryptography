#ifndef LARGE_H
#define LARGE_H

#include <stdint.h>

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
    Large& sub_large(uint16_t start_index, uint16_t length) const;
    Large& insert(Large const& large, uint16_t start_index=0);
    Large& concatenate(Large const& large) const;
    Large& shift_left(uint16_t shift=1);
    Large& shift_right(uint16_t shift=1);


private:    
    void fill_with_false(uint16_t start_index, uint16_t length);
    void allocate_memory();

private:
    bool* bits;
    uint16_t bits_size;
};

#endif // LARGE_H
