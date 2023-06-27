#include "rsa.h"
#include <QDebug>

void rsa_key_genekey_generationration(uint16_t p_size, uint16_t q_size,  uint16_t e_size, Large const& e, Large& p, Large& q, Large& n, Large& d, Count& count)
{

}

void rsa_encryption(Large const& m, Large const& e, Large const& n, Large& C, Count& count)
{
    exponentiation_modulo(m, e, n, C, count);
}

void rsa_decryption(Large const& C, Large const& d, Large const& n, Large& m, Count& count)
{
    exponentiation_modulo(C, d, n, m, count);
}

void rsa_dummy1()
{
    Count count;
    count_initialization(count);
    Large p(10);
    Large q(10);
    Large n(20);
    Large e(20);
    Large d(20);
    Large m(20);
    Large C(20);
    Large phi_n(20);
    Large phi_phi_n(20);
    phi_n.init_with_small_number(160);
    phi_phi_n.init_with_small_number(64);
    p.init_with_small_number(11);
    q.init_with_small_number(17);
    multiplication(p, q, n, count);
    e.init_with_small_number(7);
    inverse(e, phi_n, phi_phi_n, d, count);
    qDebug() << "d" << Large2String(d);
    m.init_with_small_number(2);
    qDebug() << "message" << Large2String(m);
    rsa_encryption(m, e, n, C, count);
    qDebug() << "encryption C=" << Large2String(C);
    rsa_decryption(C, d, n, m, count);
    qDebug() << "decryption m=" << Large2String(m);
}
