#include "large.h"
#include <QDebug>

Large::Large(uint64_t number_of_bits): bits_size(number_of_bits)
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

bool Large::operator[](uint64_t index) const
{
    return this->bits[index];
}

bool& Large::operator[](uint64_t index)
{
    return this->bits[index];
}

uint64_t Large::get_number_of_bits() const
{
    return this->bits_size;
}

void Large::clear(uint64_t start_index, uint64_t length)
{
    for(uint64_t i=start_index; i<start_index + length; i++)
    {
        this->bits[i] = false;
    }
}

bool Large::is_null() const
{
    for(uint64_t i=0; i<this->bits_size; i++)
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
    for(uint64_t i=0; i<this->bits_size; i++)
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
        for(uint64_t i=0; i<this->bits_size; i++)
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
        uint64_t digits = ((this->bits_size-1)/4)+1;
        for(uint64_t i=0; i<digits; i++)
        {
            int minimum = (i==0)?this->bits_size - 4*((int)(this->bits_size/4)):4;
            minimum = (minimum == 0)?4:minimum;
            int digit = 0;
            for(int j=0; j<minimum; j++)
            {
                digit += (*this)[4*(digits - i - 1) + j]?1<<j:0;
            }
            str += symbols.at(digit);
        }
    }
    return str;
}

void Large::split(Large& subpart, uint64_t start_index) const
{
    assert(this->bits_size >= subpart.bits_size + start_index);
    uint64_t size = subpart.get_number_of_bits();
    for(uint64_t i=0; i<size; i++)
    {
        subpart[i] = (*this)[i + start_index];
    }
}

void Large::insert(Large const& subpart, uint64_t start_index)
{
    assert(this->bits_size >= subpart.bits_size + start_index);
    uint64_t size = subpart.get_number_of_bits();
    for(uint64_t i=0; i<size; i++)
    {
        (*this)[i + start_index] = subpart[i];
    }
}

void Large::REG(bool enable, Large const& D, uint64_t start_index, Count& count)
{
    assert(this->bits_size + start_index >= D.bits_size);
    for(uint64_t i=0; i<D.bits_size; i++)
    {
        count.regs++;
        (*this)[i + start_index] = (enable)?D[i]:(*this)[i + start_index];
    }
}

bool Large::SHIFT_LEFT(bool enable, bool insert, Count& count)
{
    bool cout = (*this)[this->bits_size-1];
    uint64_t index = this->bits_size;
    for(uint64_t i=1; i<this->bits_size; i++)
    {
        count.regs++;
        index--;
        (*this)[index] = (enable)?(*this)[index - 1]:(*this)[index];
    }
    count.regs++;
    (*this)[0] = (enable)?insert:(*this)[0];
    return cout;
}

bool Large::SHIFT_RIGHT(bool enable, bool insert, Count& count)
{
    bool cout = (*this)[0];
    uint64_t index = 0;
    for(uint64_t i=1; i<this->bits_size; i++)
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

void Large::init_with_small_number(uint64_t number)
{
    uint64_t target_size = 64;
    uint64_t size = (target_size<this->bits_size)?target_size:this->bits_size;
    this->clear(0, size);
    for(uint64_t i=0; i<size; i++)
    {
        (*this)[i] = (number >> i) & 1;
    }
};
