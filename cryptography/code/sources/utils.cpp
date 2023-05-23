#include "utils.h"
#include <QString>
#include <QDebug>

void find_primes(bool tab[], int size)
{
    for(int i=0; i<size; i++)
    {
        tab[i] = true;
    }
    tab[0] = false;
    tab[1] = false;
    for(int i = 0; i<size; i++)
    {
        if(tab[i])
        {
            for(int j=2*i; j<size; j+=i)
            {
                tab[j] = false;
            }
        }
    }
}

void display_primes(bool tab[], int number_of_primes_to_display)
{
    QString result = "{2";
    int index = 3;
    int primes_found = 1;
    do
    {
        if(tab[index])
        {
            result += ", " + QString::number(index);
            primes_found++;
        }
        index++;
    }
    while(primes_found < number_of_primes_to_display);
    result += "}";
    qDebug()  << result;
}

