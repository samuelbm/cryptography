from prime_utils import *
from elliptic_curve import *
from math import comb
from graphs import *
import numpy as np
from system_file import *
import scipy


def get_rsa_data(rsa_paths):
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

    for rsa_path in rsa_paths:
        size, p, q, n, e, d, m, C, keygen_clock, keygen_regs, keygen_gates, encryption_clock, encryption_regs, \
        encryption_gates, decryption_clock, decryption_regs, decryption_gates = rsa_decode(rsa_path)
        size_v.extend(size)
        p_v.extend(p)
        q_v.extend(q)
        n_v.extend(n)
        e_v.extend(e)
        d_v.extend(d)
        m_v.extend(m)
        C_v.extend(C)
        keygen_clock_v.extend(keygen_clock)
        keygen_regs_v.extend(keygen_regs)
        keygen_gates_v.extend(keygen_gates)
        encryption_clock_v.extend(encryption_clock)
        encryption_regs_v.extend(encryption_regs)
        encryption_gates_v.extend(encryption_gates)
        decryption_clock_v.extend(decryption_clock)
        decryption_regs_v.extend(decryption_regs)
        decryption_gates_v.extend(decryption_gates)

    return size_v, p_v, q_v, n_v, e_v, d_v, m_v, C_v, keygen_clock_v, keygen_regs_v, keygen_gates_v, \
           encryption_clock_v, encryption_regs_v, encryption_gates_v, decryption_clock_v, decryption_regs_v, \
           decryption_gates_v


def get_ecc_p_data(ecc_p_paths):
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

    for ecc_p_path in ecc_p_paths:
        size, kb, Pb, m, Pm, C, keygen_clock, keygen_regs, keygen_gates, encryption_clock, encryption_regs, \
        encryption_gates, decryption_clock, decryption_regs, decryption_gates = ecc_p_decode(ecc_p_path)
        size_v.extend(size)
        kb_v.extend(kb)
        Pb_v.extend(Pb)
        m_v.extend(m)
        Pm_v.extend(Pm)
        C_v.extend(C)
        keygen_clock_v.extend(keygen_clock)
        keygen_regs_v.extend(keygen_regs)
        keygen_gates_v.extend(keygen_gates)
        encryption_clock_v.extend(encryption_clock)
        encryption_regs_v.extend(encryption_regs)
        encryption_gates_v.extend(encryption_gates)
        decryption_clock_v.extend(decryption_clock)
        decryption_regs_v.extend(decryption_regs)
        decryption_gates_v.extend(decryption_gates)

    return size_v, kb_v, Pb_v, m_v, Pm_v, C_v, keygen_clock_v, keygen_regs_v, keygen_gates_v, encryption_clock_v, \
           encryption_regs_v, encryption_gates_v, decryption_clock_v, decryption_regs_v, decryption_gates_v


def get_RSA(n):
    log_n = n * np.log(2)
    f1 = (64 / 9) ** (1 / 3)
    f2 = (log_n) ** (1 / 3)
    f3 = (np.log(log_n)) ** (2 / 3)
    f4 = f1 * f2 * f3
    return int(f4 * np.log2(np.exp(1)))


def get_ECC(n):
    return int(n / 2)


def rsa_security_translation(rsa_key_length, closest):
    rsa_equivalent = []
    closest = np.array(closest)
    for key_length in rsa_key_length:
        min_v = np.abs(get_RSA(key_length) - closest)
        min_value = np.min(min_v)
        index = list(min_v).index(min_value)
        rsa_equivalent.append(closest[index])
    return rsa_equivalent


def ecc_p_security_translation(ecc_p_key_length, closest):
    ecc_p_equivalent = []
    closest = np.array(closest)
    for key_length in ecc_p_key_length:
        min_v = np.abs(get_ECC(key_length) - closest)
        min_value = np.min(min_v)
        index = list(min_v).index(min_value)
        ecc_p_equivalent.append(closest[index])
    return ecc_p_equivalent


def plot_data(ax, security, data, label, color_shape, markersize):
    x = np.array([security for _ in data])
    ax.plot(np.log2(x), np.log10(data), color_shape, markersize=markersize, label=label)


def get_axe(base, minimum, maximum):
    skip = max(1, int(np.ceil((maximum - minimum + 1) / 10)))
    axe = []
    count = 0
    for i in range(minimum, maximum + 1):
        if count == 0:
            string1 = r"$" + str(base) + "^{" + str(i) + "}$"
        else:
            string1 = ""
        axe.append(string1)
        count = np.mod(count + 1, skip)
    return axe


rsa_data_paths = ["./data/rsa_128.txt", "./data/rsa_400.txt", "./data/rsa_1024.txt", "./data/rsa_2044.txt",
                  "./data/rsa_3072.txt"]
rsa_size_v, rsa_p_v, rsa_q_v, rsa_n_v, rsa_e_v, rsa_d_v, rsa_m_v, rsa_C_v, rsa_keygen_clock_v, rsa_keygen_regs_v, \
rsa_keygen_gates_v, rsa_encryption_clock_v, rsa_encryption_regs_v, rsa_encryption_gates_v, rsa_decryption_clock_v, \
rsa_decryption_regs_v, rsa_decryption_gates_v = get_rsa_data(rsa_data_paths)
rsa_strengh = [32, 56, 80, 112, 128, 192, 256]
rsa_equivalent = rsa_security_translation(rsa_size_v, rsa_strengh)

ecc_p_data_paths = ["./data/ecc_p_192.txt", "./data/ecc_p_256.txt", "./data/ecc_p_384.txt", "./data/ecc_p_521.txt"]
ecc_p_size_v, ecc_p_kb_v, ecc_p_Pb_v, ecc_p_m_v, ecc_p_Pm_v, ecc_p_C_v, ecc_p_keygen_clock_v, ecc_p_keygen_regs_v, \
ecc_p_keygen_gates_v, ecc_p_encryption_clock_v, ecc_p_encryption_regs_v, ecc_p_encryption_gates_v, \
ecc_p_decryption_clock_v, ecc_p_decryption_regs_v, ecc_p_decryption_gates_v = get_ecc_p_data(ecc_p_data_paths)
ecc_p_strengh = [96, 128, 192, 256]
ecc_p_equivalent = ecc_p_security_translation(ecc_p_size_v, ecc_p_strengh)

path = "./images/figure_power_keygen.png"
x_label = "Sécurité [bits]"
y_label = "Énergie dissipée [portes logiques]"
markersize_data = 5
markersize_mean = 10
linewidth = 3
nb_round = 10


if __name__ == "__main__":
    pass
    x_start = 4
    x_end = 10
    y_start = 1
    y_end = 22
    base = 2
    fontsize = 20
    linewidth = 2
    markersize = 20
    fig = plt.figure(figsize=(10, 8), dpi=100)
    ax = fig.add_subplot(111)

    nb_points = 1000
    x = np.linspace(x_start, x_end, nb_points, True)

    x_rsa = np.log2(rsa_equivalent)
    y_rsa = np.log10(rsa_keygen_gates_v)
    slope_rsa, intercept_rsa, r, p, se = scipy.stats.linregress(x_rsa, y_rsa)
    y_rsa_trend = slope_rsa * x + intercept_rsa
    ax.scatter(x_rsa, y_rsa, label="RSA", s=markersize, marker='o')
    ax.plot(x, y_rsa_trend, label="RSA régression", linewidth=linewidth)


    x_ecc_p = np.log2(ecc_p_equivalent)
    y_ecc_p = np.log10(ecc_p_keygen_gates_v)
    slope_ecc_p, intercept_ecc_p, r, p, se = scipy.stats.linregress(x_ecc_p, y_ecc_p)
    y_ecc_p_trend = slope_ecc_p * x + intercept_ecc_p
    ax.scatter(x_ecc_p, y_ecc_p, label=r"ECC $GF(p)$", s=markersize, marker='o')
    ax.plot(x, y_ecc_p_trend, label="ECC régression", linewidth=linewidth)

    print(slope_rsa, slope_ecc_p)

    ax.legend(fontsize=fontsize * 0.75)
    # ax.set_title(str(curve), fontsize=fontsize)

    ax.set_xlabel(x_label, fontsize=fontsize)
    ax.set_xlim([x_start, x_end])
    ax.set_xticks([i for i in range(x_start, x_end + 1)])
    ax.set_xticklabels(get_axe(base, x_start, x_end), fontsize=fontsize)

    ax.set_ylabel(y_label, fontsize=fontsize)
    ax.set_ylim([y_start, y_end])
    ax.set_yticks([i for i in range(y_start, y_end + 1)])
    ax.set_yticklabels(get_axe(10, y_start, y_end), fontsize=fontsize)

    ax.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.1)
    plt.savefig(path)
    plt.show()
