import numpy as np
from ecc import *


# file1 = open("myfile.txt", "w")
# L = ["This is Delhi \n", "This is Paris \n", "This is London"]
# file1.writelines(L)
# file1.close()


def append_file(path, text):
    # Append-adds at last
    file1 = open(path, "a")  # append mode
    file1.write(text + "\n")
    file1.close()


def read_file(path):
    file1 = open(path, "r")
    string = file1.read()
    file1.close()
    return string


# # Write-Overwrites
# file1 = open("myfile.txt", "w")  # write mode
# file1.write("Tomorrow \n")
# file1.close()
#
# file1 = open("myfile.txt", "r")
# print("Output of Readlines after writing")
# print(file1.read())
# print()
# file1.close()

def rsa_decode(path):
    data = read_file(path)
    data_lines = data.split("\n")
    size_v = []
    p_v = []
    q_v = []
    n_v = []
    e_v = []
    d_v = []
    m_v = []
    C_v = []
    keygen_clock_v = []
    keygen_regs_v = []
    keygen_gates_v = []
    encryption_clock_v = []
    encryption_regs_v = []
    encryption_gates_v = []
    decryption_clock_v = []
    decryption_regs_v = []
    decryption_gates_v = []
    index = 0
    for line in data_lines:
        if np.mod(index, 3) == 0:
            size, p, q, n, e, d, clock, regs, gates = rsa_decode_keygen(line)
            size_v.append(size)
            p_v.append(p)
            q_v.append(q)
            n_v.append(n)
            e_v.append(e)
            d_v.append(d)
            keygen_clock_v.append(clock)
            keygen_regs_v.append(regs)
            keygen_gates_v.append(gates)

        elif np.mod(index, 3) == 1:
            C, clock, regs, gates = rsa_decode_encryption(line)
            C_v.append(C)
            encryption_clock_v.append(clock)
            encryption_regs_v.append(regs)
            encryption_gates_v.append(gates)
        else:
            m, clock, regs, gates = rsa_decode_decryption(line)
            m_v.append(m)
            decryption_clock_v.append(clock)
            decryption_regs_v.append(regs)
            decryption_gates_v.append(gates)
        index += 1
    return size_v, p_v, q_v, n_v, e_v, d_v, m_v, C_v, keygen_clock_v, keygen_regs_v, keygen_gates_v, \
           encryption_clock_v, encryption_regs_v, encryption_gates_v, decryption_clock_v, decryption_regs_v, \
           decryption_gates_v


def rsa_decode_keygen(line):
    data_split = line.split(",")
    size = int(data_split[1].split(" ")[-1])
    p = int(data_split[2].split(" ")[-1])
    q = int(data_split[3].split(" ")[-1])
    n = int(data_split[4].split(" ")[-1])
    e = int(data_split[5].split(" ")[-1])
    d = int(data_split[6].split(" ")[-1])
    clock = int(data_split[7].split(" ")[-1])
    regs = int(data_split[8].split(" ")[-1])
    gates = int(data_split[9].split(" ")[-1])
    return size, p, q, n, e, d, clock, regs, gates


def rsa_decode_encryption(line):
    data_split = line.split(",")
    C = int(data_split[4].split(" ")[-1])
    clock = int(data_split[5].split(" ")[-1])
    regs = int(data_split[6].split(" ")[-1])
    gates = int(data_split[7].split(" ")[-1])
    return C, clock, regs, gates


def rsa_decode_decryption(line):
    data_split = line.split(",")
    m = int(data_split[4].split(" ")[-1])
    clock = int(data_split[5].split(" ")[-1])
    regs = int(data_split[6].split(" ")[-1])
    gates = int(data_split[7].split(" ")[-1])
    return m, clock, regs, gates


def ecc_p_decode(path):
    data = read_file(path)
    data_lines = data.split("\n")
    size_v = []
    kb_v = []
    Pb_v = []
    m_v = []
    Pm_v = []
    C_v = []
    keygen_clock_v = []
    keygen_regs_v = []
    keygen_gates_v = []
    encryption_clock_v = []
    encryption_regs_v = []
    encryption_gates_v = []
    decryption_clock_v = []
    decryption_regs_v = []
    decryption_gates_v = []
    index = 0
    for line in data_lines:
        if np.mod(index, 3) == 0:
            size, kb, Pb, clock, regs, gates = ecc_p_decode_keygen(line)
            size_v.append(size)
            kb_v.append(kb)
            Pb_v.append(Pb)
            keygen_clock_v.append(clock)
            keygen_regs_v.append(regs)
            keygen_gates_v.append(gates)
        elif np.mod(index, 3) == 1:
            Pm, C, clock, regs, gates = ecc_p_decode_encryption(line)
            Pm_v.append(Pm)
            C_v.append(C)
            encryption_clock_v.append(clock)
            encryption_regs_v.append(regs)
            encryption_gates_v.append(gates)
        else:
            m, clock, regs, gates = ecc_p_decode_decryption(line)
            m_v.append(m)
            decryption_clock_v.append(clock)
            decryption_regs_v.append(regs)
            decryption_gates_v.append(gates)
        index += 1
    return size_v, kb_v, Pb_v, m_v, Pm_v, C_v, keygen_clock_v, keygen_regs_v, keygen_gates_v, encryption_clock_v, \
           encryption_regs_v, encryption_gates_v, decryption_clock_v, decryption_regs_v, decryption_gates_v


def ecc_p_decode_keygen(line):
    data_split = line.split(",")
    size = int(data_split[0].split(" ")[-1])
    kb = int(data_split[1].split(" ")[-1])
    Pb = ecc_point(int(data_split[2].split(" ")[-1]), int(data_split[3].split(" ")[-1]), False)
    clock = int(data_split[4].split(" ")[-1])
    regs = int(data_split[5].split(" ")[-1])
    gates = int(data_split[6].split(" ")[-1])
    return size, kb, Pb, clock, regs, gates


def ecc_p_decode_encryption(line):
    data_split = line.split(",")
    Pm = ecc_point(int(data_split[2].split(" ")[-1]), int(data_split[3].split(" ")[-1]), False)
    kG = ecc_point(int(data_split[4].split(" ")[-1]), int(data_split[5].split(" ")[-1]), False)
    PmkPb = ecc_point(int(data_split[6].split(" ")[-1]), int(data_split[7].split(" ")[-1]), False)
    C = [kG, PmkPb]
    clock = int(data_split[8].split(" ")[-1])
    regs = int(data_split[9].split(" ")[-1])
    gates = int(data_split[10].split(" ")[-1])
    return Pm, C, clock, regs, gates


def ecc_p_decode_decryption(line):
    data_split = line.split(",")
    m = int(data_split[1].split(" ")[-1])
    clock = int(data_split[6].split(" ")[-1])
    regs = int(data_split[7].split(" ")[-1])
    gates = int(data_split[8].split(" ")[-1])
    return m, clock, regs, gates


if __name__ == "__main__":
    # path = "./data/rsa_128.txt"
    # rsa_decode(path)
    path = "./data/ecc_p_192.txt"
    ecc_p_decode(path)
