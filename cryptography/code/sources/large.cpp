#include "large.h"

Large::Large(uint16_t number_of_bits): bits_size(number_of_bits)
{
    this->allocate_memory();
    this->fill_with_false(0, this->bits_size);
}

Large::Large(Large const& large)
{

    this->bits_size = large.bits_size;
    this->allocate_memory();
    this->insert(large);
}

Large::~Large()
{
    delete [] this->bits;
}

Large& Large::operator=(Large const& large)
{
    if(this != &large)
    {
        if(this->bits_size != large.bits_size)
        {
            this->~Large();
            this->bits_size = large.bits_size;
            this->allocate_memory();
        }
        this->insert(large);
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

Large& Large::sub_large(uint16_t start_index, uint16_t length) const
{
    Large* sub = new Large(length);
    for(uint16_t i=0; i < length; i++)
    {
        sub[i] = (*this)[i + start_index];
    }
    return *sub;
}

Large& Large::insert(Large const& large, uint16_t start_index)
{
    for(uint16_t i=0; i < large.get_number_of_bits(); i++)
    {
        (*this)[i + start_index] = large[i];
    }
    return *this;
}

Large& Large::concatenate(Large const& large) const
{
    uint16_t n_bits = this->bits_size + large.bits_size;
    Large* concatenated = new Large(n_bits);
    concatenated->insert(*this);
    concatenated->insert(large, this->bits_size);
    return *concatenated;
}

Large& Large::shift_left(uint16_t shift)
{
    for(uint16_t i=this->bits_size; i>shift; i--)
    {
        (*this)[i-1] =(*this)[i-shift-1];
    }
    this->fill_with_false(0, shift);
    return *this;
}

Large& Large::shift_right(uint16_t shift)
{
    for(uint16_t i=shift; i<this->bits_size; i++)
    {
        (*this)[i-shift] =(*this)[i];
    }
    this->fill_with_false(this->bits_size - shift, shift);
    return *this;
}

void Large::fill_with_false(uint16_t start_index, uint16_t length)
{
    for(uint16_t i=start_index; i<start_index + length; i++)
    {
        this->bits[i] = false;
    }
}

void Large::allocate_memory()
{
    bits = new bool[this->bits_size];
}


