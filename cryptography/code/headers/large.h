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
    void initialize_array_to_false();

private:
    void allocate_memory();
    void copy_array(Large const& large);

private:
    bool* bits;
    uint16_t bits_size;
};

#endif // LARGE_H
