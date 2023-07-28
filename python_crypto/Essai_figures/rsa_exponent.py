from prime_utils import *
from elliptic_curve import *
from math import comb
from graphs import *
import numpy as np

def get_symmetric(n):
    return n


def get_RSA(n):
    log_n = n * np.log(2)
    f1 = (64 / 9) ** (1 / 3)
    f2 = (log_n) ** (1 / 3)
    f3 = (np.log(log_n)) ** (2 / 3)
    f4 = f1 * f2 * f3
    return int(f4 * np.log2(np.exp(1)))


def get_ECC(n):
    return int(n / 2)


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


if __name__ == "__main__":
    x = []
    y = [128, 400, 1024, 2044, 3072, 7680, 15360]
    x_ln = []
    y_ln = []

    path = "./images/rsa_exponent.png"
    base = 2
    x_start = 4
    x_end = 9
    y_start = 5
    y_end = 16

    key_length = [2 ** i for i in range(x_start, x_end + 1)]
    symmetric_security = [get_symmetric(n) for n in key_length]
    RSA_security = [get_RSA(n) for n in key_length]
    ECC_security = [get_ECC(n) for n in key_length]


    for i in range(len(y)):
        x.append(get_RSA(y[i]))
        x_ln.append(np.log2(x[i]))
        y_ln.append(np.log2(y[i]))

    x_ln = np.matrix(x_ln).transpose()
    y_ln = np.matrix(y_ln).transpose()
    m_ones = np.ones(x_ln.shape)
    A = np.concatenate((x_ln, m_ones), 1)
    B = y_ln

    x_v = np.linalg.inv(A.transpose() * A) * A.transpose() * B
    a = np.max(x_v[0])
    b = np.max(x_v[1])

    e = (A*x_v - B).transpose() * (A*x_v - B)
    e = int(1000*np.max(e))/1000
    print('e', e)


    t = np.linspace(np.min(x_ln), np.max(x_ln), 100, True)
    z = a*t + b



    fontsize = 20
    fig = plt.figure(figsize=(10, 8), dpi=100)
    ax = fig.add_subplot(111)

    ax.scatter(np.squeeze(np.asarray(x_ln)), np.squeeze(np.asarray(y_ln)))
    ax.plot(np.squeeze(np.asarray(t)), np.squeeze(np.asarray(z)))
    sa = int(1000*a)/1000
    sb = int(10000*np.exp(b))/10000
    ax.text(5.5, 14, r"$y = bx^a = {}x".format(sb) + r"^{" +r"{}".format(sa) + r"}$", fontsize=fontsize)
    ax.text(5.5, 13, r"$R^2$ = {}".format(1 - e), fontsize=fontsize)

    ax.set_xlabel("Sécurité [bits]", fontsize=fontsize)
    ax.set_xlim([x_start, x_end])
    ax.set_xticks([i for i in range(x_start, x_end + 1)])
    ax.set_xticklabels(get_axe(base, x_start, x_end), fontsize=fontsize)

    ax.set_ylabel("Taille de la clé publique [bits]", fontsize=fontsize)
    ax.set_ylim([y_start, y_end])
    ax.set_yticks([i for i in range(y_start, y_end + 1)])
    ax.set_yticklabels(get_axe(base, y_start, y_end), fontsize=fontsize)

    ax.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.1)

    plt.savefig(path)
    plt.show()

    print(a, b)
    print(get_RSA(1024))
    print(get_RSA(2044))






