from prime_utils import*
from elliptic_curve import*
from math import comb
from graphs import*
import numpy as np

def get_symmetric(n):
    m = n
    return int(m)

def get_RSA(n):
    m = np.sqrt(n)
    return int(m)

def get_ECC(n):
    m = n/2
    return int(m)

def get_axe(base, minimum, maximum):
    skip = max(1, int(np.ceil((maximum-minimum+1)/10)))

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

if __name__ == "__main__":
    path = "./images/bit_strength.png"
    base = 2
    x_start = 4
    x_end = 20
    y_start = 1

    key_length = [2**i for i in range(x_start, x_end)]
    symmetric_security = [get_symmetric(n) for n in key_length]
    RSA_security = [get_RSA(n) for n in key_length]
    ECC_security = [get_ECC(n) for n in key_length]
    y_end = int(np.ceil(np.log2(max(RSA_security))))



    fontsize=20
    fig = plt.figure(figsize=(10, 8), dpi=100)
    ax = fig.add_subplot(111)
    ax.plot(np.log2(key_length), np.log2(symmetric_security), linewidth=3, label='Symétrique')
    ax.plot(np.log2(key_length), np.log2(RSA_security), linewidth=3, label='RSA')
    ax.plot(np.log2(key_length), np.log2(ECC_security), linewidth=3, label='ECC')
    ax.plot(np.log2(56), np.log2(56), 'ro', label="DES", markersize=10)
    ax.plot(np.log2(128), np.log2(128), 'rs', label="AES-128", markersize=10)
    ax.plot(np.log2(192), np.log2(192), 'gs', label="AES-192", markersize=10)
    ax.plot(np.log2(256), np.log2(256), 'bs', label="AES-256", markersize=10)
    ax.legend(fontsize=fontsize)
    #ax.set_title(str(curve), fontsize=fontsize)

    ax.set_xlabel("Nombre de bits de la clé", fontsize=fontsize)
    ax.set_xlim([x_start, x_end])
    ax.set_xticks([i for i in range(x_start, x_end+1)])
    ax.set_xticklabels(get_axe(base, x_start, x_end), fontsize=fontsize)

    ax.set_ylabel("Nombre de bits de sécurité", fontsize=fontsize)
    ax.set_ylim([y_start, y_end])
    ax.set_yticks([i for i in range(y_start, y_end+1)])
    ax.set_yticklabels(get_axe(base, y_start, y_end), fontsize=fontsize)

    ax.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.1)
    #plt.savefig(path)
    plt.show()
