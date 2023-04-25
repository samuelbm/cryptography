#include "large.h"

Large::Large(uint16_t number_of_bits): bits_size(number_of_bits)
{
    this->allocate_memory();
    this->initialize_array_to_false();
}

Large::Large(Large const& large)
{

    this->bits_size = large.bits_size;
    this->allocate_memory();
    this->copy_array(large);
}

Large::~Large()
{
    delete [] this->bits;
}

Large& Large::operator=(Large const& large)
{
    if(this != &large)
    {
        this->~Large();
        this->bits_size = large.bits_size;
        this->allocate_memory();
        this->copy_array(large);
    }
    return *this;
}

bool Large::operator[](uint16_t index) const
{
    return this->bits[index];
}

bool& Large::operator[](uint16_t index)
{
    return this->bits[index];
}

uint16_t Large::get_number_of_bits() const
{
    return this->bits_size;
}

void Large::initialize_array_to_false()
{
    for(uint16_t i=0; i<this->bits_size; i++)
    {
        this->bits[i] = false;
    }
}

void Large::allocate_memory()
{
    bits = new bool[this->bits_size];
}

void Large::copy_array(Large const& large)
{
    for(uint16_t i=0; i<this->bits_size; i++)
    {
        this->bits[i] = large[i];
    }
}


