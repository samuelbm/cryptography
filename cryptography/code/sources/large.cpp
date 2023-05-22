#include "large.h"
#include <QDebug>

Large::Large(uint16_t number_of_bits): bits_size(number_of_bits)
{
    this->allocate_memory();
    this->clear(0, this->bits_size);
}

Large::Large(Large const& large)
{

    this->bits_size = large.bits_size;
    this->allocate_memory();
    this->copy(large);
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
        this->copy(large);
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

void Large::clear(uint16_t start_index, uint16_t length)
{
    for(uint16_t i=start_index; i<start_index + length; i++)
    {
        this->bits[i] = false;
    }
}

bool Large::is_null() const
{
    for(uint16_t i=0; i<this->bits_size; i++)
    {
        if((*this)[i])
        {
            return false;
        }
    }
    return true;
}

void Large::allocate_memory()
{
    bits = new bool[this->bits_size];
}

void Large::copy(Large const& large)
{
    for(uint16_t i=0; i<this->bits_size; i++)
    {
        (*this)[i] = large[i];
    }
}

QString Large::toBin() const
{
    QString str = QString::number(this->bits_size);
    str += "Bin";
    if(this->bits_size==0)
    {
        str += "0";
    }
    else
    {
        for(uint16_t i=0; i<this->bits_size; i++)
        {
            str += ((*this)[this->bits_size - i - 1])?"1":"0";
        }
    }
    return str;
}

QString Large::toHex() const
{
    QString symbols = "0123456789ABCDEF";
    QString str = QString::number(this->bits_size);
    str += "Hex";
    if(this->bits_size==0)
    {
        str += "0";
    }
    else
    {
        uint16_t digits = ((this->bits_size-1)/4)+1;
        for(uint16_t i=0; i<digits; i++)
        {
            uint16_t minimum = (i==0)?this->bits_size - 4*((int)(this->bits_size/4)):4;
            minimum = (minimum == 0)?4:minimum;
            uint16_t digit = 0;
            for(uint16_t j=0; j<minimum; j++)
            {
                digit += (*this)[4*(digits - i - 1) + j]?1<<j:0;
            }
            str += symbols[digit];
        }
    }
    return str;
}

void Large::split(Large& subpart, uint16_t start_index)
{
    assert(this->bits_size >= subpart.bits_size + start_index);
    uint16_t size = subpart.get_number_of_bits();
    for(uint16_t i=0; i<size; i++)
    {
        subpart[i] = (*this)[i + start_index];
    }
}

void Large::insert(Large const& subpart, uint16_t start_index)
{
    assert(this->bits_size >= subpart.bits_size + start_index);
    uint16_t size = subpart.get_number_of_bits();
    for(uint16_t i=0; i<size; i++)
    {
        (*this)[i + start_index] = subpart[i];
    }
}

void Large::REG(bool enable, Large const& D, uint16_t start_index, Count& count)
{
    assert(this->bits_size + start_index >= D.bits_size);
    for(uint16_t i=0; i<D.bits_size; i++)
    {
        count.regs++;
        (*this)[i] = (enable)?D[i]:(*this)[i];
    }
}

bool Large::SHIFT_LEFT(bool enable, bool insert, Count& count)
{
    bool cout = (*this)[this->bits_size-1];
    uint16_t index = this->bits_size;
    for(uint16_t i=1; i<this->bits_size; i++)
    {
        count.regs++;
        index--;
        (*this)[index] = (enable)?(*this)[index - 1]:(*this)[index];
    }
    (*this)[0] = insert;
    return cout;
}

bool Large::SHIFT_RIGHT(bool enable, bool insert, Count& count)
{
    bool cout = (*this)[0];
    uint16_t index = 0;
    for(uint16_t i=1; i<this->bits_size; i++)
    {
        count.regs++;
        index++;
        (*this)[index - 1] = (enable)?(*this)[index]:(*this)[index-1];
    }
    (*this)[this->bits_size-1] = insert;
    return cout;
}

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

Large& create_and_initialize_large(uint16_t init_value, uint16_t n_bits)
{
    Large* large = new Large(n_bits);
    for(uint16_t i=0; i<n_bits; i++)
    {
        (*large)[i] = (init_value >> i) & 1;
    }
    return *large;
};
