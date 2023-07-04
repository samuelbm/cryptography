from large import *
import time

def rsa_keygen(size, e):
    t1 = time.time()
    count = Count()
    delta = size >> 6
    p_size = (size >> 1) - delta
    q_size = (size >> 1) + delta
    p, count1 = find_prime_3_equiv_4(p_size)
    q, count2 = find_prime_3_equiv_4(q_size)
    factors = []
    phi_n, count3 = multiplication(p-1, q-1)
    factors_p, count4 = pollard_rho_factorisation(p-1, 1)
    factors_q, count5 = pollard_rho_factorisation(q-1, 1)
    factors.extend(factors_p)
    factors.extend(factors_q)
    phi_phi_n, count6 = phi(factors)
    d, count7 = inverse_modulo(e, phi_phi_n, phi_n)
    n, count8 = multiplication(p, q)
    count.add_count(count1)
    count.add_count(count2)
    count.add_count(count3)
    count.add_count(count4)
    count.add_count(count5)
    count.add_count(count6)
    count.add_count(count7)
    count.add_count(count8)
    t2 = time.time()
    print("time: {}, rsa keygen {}, p: {}, q: {}, n: {}, e: {}, d: {}, clock: {}, regs: {}, gates: {}".format(t2-t1, size, p, q, n, e, d, count.clock, count.regs, count.gates))
    return p, q, n, e, d, count



def rsa_encryption(m, e, n):
    C, count = exponentiation_modulo(m, e, n)
    print("rsa encryption, m: {}, e: {}, n: {}, C: {}, clock: {}, regs: {}, gates: {}".format(m, e, n, C, count.clock, count.regs, count.gates))
    return C, count

def rsa_decryption(C, d, n):
    m, count = exponentiation_modulo(C, d, n)
    print("rsa decryption, C: {}, d: {}, n: {}, m: {}, clock: {}, regs: {}, gates: {}".format(C, d, n, m, count.clock, count.regs, count.gates))
    return m, count



def rsa_128(tries):
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen = rsa_keygen(128, 65537)
        C, count_encryption = rsa_encryption(m, e, n)
        m, count_decryption = rsa_decryption(C, d, n)

def rsa_400(tries):
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen = rsa_keygen(400, 65537)
        C, count_encryption = rsa_encryption(m, e, n)
        m, count_decryption = rsa_decryption(C, d, n)


def rsa_1024(tries):
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen = rsa_keygen(1024, 65537)
        C, count_encryption = rsa_encryption(m, e, n)
        m, count_decryption = rsa_decryption(C, d, n)


def rsa_2044(tries):
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen = rsa_keygen(2044, 65537)
        C, count_encryption = rsa_encryption(m, e, n)
        m, count_decryption = rsa_decryption(C, d, n)


def rsa_3072(tries):
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen = rsa_keygen(3072, 65537)
        C, count_encryption = rsa_encryption(m, e, n)
        m, count_decryption = rsa_decryption(C, d, n)


# too long to process
# def rsa_7680(tries):
#     pass
#

# too long to process
# def rsa_15360(tries):
#     pass


if __name__ == "__main__":
    rsa_128(10)
