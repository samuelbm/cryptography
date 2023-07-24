from large import *
import time
from system_file import *


# def rsa_keygen(size, e):
#     t1 = time.time()
#     count = Count()
#     delta = size >> 6
#     p_size = (size >> 1) - delta
#     q_size = (size >> 1) + delta
#
#     count_p = Count()
#     condition_p = False
#     while not condition_p:
#         p, count1 = find_prime_3_equiv_4(p_size)
#         factors_p, count2, condition_p = pollard_rho_factorisation(p - 1)
#         if count_p.clock == 0:
#             count_p.add_count(count1)
#             count_p.add_count(count2)
#         else:
#             count_p.power(count1.gates)
#             count_p.time(count1.clock)
#             count_p.power(count2.gates)
#             count_p.time(count2.clock)
#     count.add_count(count_p)
#
#     count_q = Count()
#     condition_q = False
#     while not condition_q:
#         q, count1 = find_prime_3_equiv_4(q_size)
#         factors_q, count2, condition_q = pollard_rho_factorisation(q - 1)
#         if count_q.clock == 0:
#             count_q.add_count(count1)
#             count_q.add_count(count2)
#         else:
#             count_q.power(count1.gates)
#             count_q.time(count1.clock)
#             count_q.power(count2.gates)
#             count_q.time(count2.clock)
#     count.add_count(count_q)
#
#     factors = []
#     phi_n, count5 = multiplication(p - 1, q - 1)
#     factors.extend(factors_p)
#     factors.extend(factors_q)
#     phi_phi_n, count6 = phi(factors)
#     d, count7 = inverse_modulo(e, phi_phi_n, phi_n)
#     n, count8 = multiplication(p, q)
#     count.add_count(count5)
#     count.add_count(count6)
#     count.add_count(count7)
#     count.add_count(count8)
#     t2 = time.time()
#     string = "time: {}, rsa keygen {}, p: {}, q: {}, n: {}, e: {}, d: {}, clock: {}, regs: {}, gates: {}"
#     print(string.format(t2 - t1, size, p, q, n, e, d, count.clock, count.regs, count.gates))
#     return p, q, n, e, d, count

def rsa_keygen(size, e):
    t1 = time.time()
    count = Count()
    delta = size >> 6
    p_size = (size >> 1) - delta
    q_size = (size >> 1) + delta

    p, p_small, n_p, count_p = find_smart_prime(p_size)
    factor_p, count1, worked_p = pollard_rho_factorisation(n_p)
    factor_p.append(p_small)
    count.add_count(count_p)
    count.add_count(count1)

    q, q_small, n_q, count_q = find_smart_prime(q_size)
    factor_q, count2, worked_q = pollard_rho_factorisation(n_q)
    factor_q.append(q_small)
    count.add_count(count_q)
    count.add_count(count2)

    if worked_p and worked_q:
        factors = []
        phi_n, count5 = multiplication(p - 1, q - 1)
        factors.extend(factor_p)
        factors.extend(factor_q)
        phi_phi_n, count6 = phi(factors)
        d, count7 = inverse_modulo(e, phi_phi_n, phi_n)
        n, count8 = multiplication(p, q)
        count.add_count(count5)
        count.add_count(count6)
        count.add_count(count7)
        count.add_count(count8)
        t2 = time.time()
        string = "time: {}, rsa keygen {}, p: {}, q: {}, n: {}, e: {}, d: {}, clock: {}, regs: {}, gates: {}"
        string = string.format(t2 - t1, size, p, q, n, e, d, count.clock, count.regs, count.gates)
        print(string)
    else:
        if not worked_p:
            print("not working", p_small)
        if not worked_q:
            print("not working", q_small)

    return p, q, n, e, d, count, string


def rsa_encryption(m, e, n):
    C, count = exponentiation_modulo(m, e, n)
    string = "rsa encryption, m: {}, e: {}, n: {}, C: {}, clock: {}, regs: {}, gates: {}"
    string = string.format(m, e, n, C, count.clock, count.regs, count.gates)
    print(string)
    return C, count, string


def rsa_decryption(C, d, n):
    m, count = exponentiation_modulo(C, d, n)
    string = "rsa decryption, C: {}, d: {}, n: {}, m: {}, clock: {}, regs: {}, gates: {}"
    string = string.format(C, d, n, m, count.clock, count.regs, count.gates)
    print(string)
    return m, count, string


def rsa_128(tries):
    path = "./data/rsa_128.txt"
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen, string_keygen = rsa_keygen(128, 65537)
        C, count_encryption, string_encryption = rsa_encryption(m, e, n)
        m, count_decryption, string_decryption = rsa_decryption(C, d, n)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


def rsa_400(tries):
    path = "./data/rsa_400.txt"
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen, string_keygen = rsa_keygen(400, 65537)
        C, count_encryption, string_encryption = rsa_encryption(m, e, n)
        m, count_decryption, string_decryption = rsa_decryption(C, d, n)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


def rsa_1024(tries):
    path = "./data/rsa_1024.txt"
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen, string_keygen = rsa_keygen(1024, 65537)
        C, count_encryption, string_encryption = rsa_encryption(m, e, n)
        m, count_decryption, string_decryption = rsa_decryption(C, d, n)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


def rsa_2044(tries):
    path = "./data/rsa_2044.txt"
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen, string_keygen = rsa_keygen(2044, 65537)
        C, count_encryption, string_encryption = rsa_encryption(m, e, n)
        m, count_decryption, string_decryption = rsa_decryption(C, d, n)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


def rsa_3072(tries):
    path = "./data/rsa_3072.txt"
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen, string_keygen = rsa_keygen(3072, 65537)
        C, count_encryption, string_encryption = rsa_encryption(m, e, n)
        m, count_decryption, string_decryption = rsa_decryption(C, d, n)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


def rsa_7680(tries):
    path = "./data/rsa_7680.txt"
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen, string_keygen = rsa_keygen(7680, 65537)
        C, count_encryption, string_encryption = rsa_encryption(m, e, n)
        m, count_decryption, string_decryption = rsa_decryption(C, d, n)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


def rsa_15360(tries):
    path = "./data/rsa_15360.txt"
    random.seed(1234)
    m = 123
    for i in range(tries):
        p, q, n, e, d, count_keygen, string_keygen = rsa_keygen(15360, 65537)
        C, count_encryption, string_encryption = rsa_encryption(m, e, n)
        m, count_decryption, string_decryption = rsa_decryption(C, d, n)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


if __name__ == "__main__":
    pass
    rsa_128(10)
    rsa_400(10)
    rsa_1024(10)
    rsa_2044(10)
    rsa_3072(10)
    rsa_7680(10)
    rsa_15360(10)
