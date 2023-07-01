from prime_utils import*
from elliptic_curve import*
from math import comb
from graphs import*
import numpy as np

path = "./images/figure_time_keygen.png"
x_label = "Sécurité [bits]"
y_label = "Temps [cycle d'horloge]"
markersize = 10
linewidth = 3
securities = np.logspace(5, 16, 100, True, 2)

data_rsa_32 = [1,2,3]
data_rsa_56 = [1,2,3]
data_rsa_80 = [1,2,3]
data_rsa_112 = [1,2,3]
data_rsa_128 = [1,2,3]
data_rsa_192 = [1,2,3]
data_rsa_256 = [1,2,3]
data_rsa = [data_rsa_32, data_rsa_56, data_rsa_80, data_rsa_112, data_rsa_128, data_rsa_192, data_rsa_256]
security_rsa = [32, 56, 80, 112, 128, 192, 256]
labels_rsa = ["RSA tendance", "RSA data", "RSA moyenne"]
color_shapes_rsa = ['r-', 'ro', 'rs']

def f_rsa(nb_try):
    return nb_try**2

data_ecc_p_32 = [1,2,3]
data_ecc_p_56 = [1,2,3]
data_ecc_p_80 = [1,2,3]
data_ecc_p_112 = [1,2,3]
data_ecc_p_128 = [1,2,3]
data_ecc_p_192 = [1,2,3]
data_ecc_p_256 = [1,2,3]
data_ecc_p = [data_ecc_p_32, data_ecc_p_56, data_ecc_p_80, data_ecc_p_112, data_ecc_p_128, data_ecc_p_192, data_ecc_p_256]
security_ecc_p = [32, 56, 80, 112, 128, 192, 256]
labels_ecc_p = [r"ECC $GF(p)$ tendance", "ECC $GF(p)$ data", "ECC $GF(p)$ moyenne"]
color_shapes_ecc_p = ['g-', 'go', 'gs']

def f_ecc_p(nb_try):
    return 2*nb_try

data_ecc_2m_32 = [1,2,3]
data_ecc_2m_56 = [1,2,3]
data_ecc_2m_80 = [1,2,3]
data_ecc_2m_112 = [1,2,3]
data_ecc_2m_128 = [1,2,3]
data_ecc_2m_192 = [1,2,3]
data_ecc_2m_256 = [1,2,3]
data_ecc_2m = [data_ecc_2m_32, data_ecc_2m_56, data_ecc_2m_80, data_ecc_2m_112, data_ecc_2m_128, data_ecc_2m_192, data_ecc_2m_256]
security_ecc_2m = [32, 56, 80, 112, 128, 192, 256]
labels_ecc_2m = [r"ECC $GF(2^m)$ tendance", "ECC $GF(2^m)$ data", "ECC $GF(2^m)$ moyenne"]
color_shapes_ecc_2m = ['b-', 'bo', 'bs']

def f_ecc_2m(nb_try):
    return np.sqrt(nb_try)

def get_RSA(n):
    log_n = n*np.log(2)
    f1 = (64/9)**(1/3)
    f2 = (log_n)**(1/3)
    f3 = (np.log(log_n))**(2/3)
    f4 = f1*f2*f3
    return f4*np.log2(np.exp(1))

def plot_data(ax, security, data, label, color_shape, markersize):
    x = np.array([security for _ in data])
    ax.plot(np.log2(x), np.log2(data), color_shape,  markersize=markersize, label=label)

def plot_mean(ax, security, data, label, color_shape, markersize):
    ax.plot(np.log2(security), np.mean(np.log2(data)), color_shape,  markersize=markersize, label=label)

def plot_trend(ax, f, securities, label, linewidth, color_shape):
    ax.plot(np.log2(securities), np.log2(f(securities)), color_shape,  linewidth=linewidth, label=label)

def plot_crypto(ax, f, security, securities, data_vector, labels, color_shapes, markersize, linewidth):
    plot_trend(ax, f, securities, labels[0], linewidth, color_shapes[0])
    for i in range(len(data_vector)):
        if i == 0:
            plot_data(ax, security[i], data_vector[i], labels[1], color_shapes[1], markersize)
            plot_mean(ax, security[i], np.mean(data_vector[i]), labels[2], color_shapes[2], markersize)
        else:
            pass
            plot_data(ax, security[i], data_vector[i], "", color_shapes[1], markersize)
            plot_mean(ax, security[i], np.mean(data_vector[i]), "", color_shapes[2], markersize)

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
    x_start = 5
    x_end = 16
    y_start = 1
    y_end = 10
    base = 2
    fontsize=20
    fig = plt.figure(figsize=(10, 8), dpi=100)
    ax = fig.add_subplot(111)

    plot_crypto(ax, f_rsa, security_rsa, securities, data_rsa, labels_rsa, color_shapes_rsa, markersize, linewidth)
    plot_crypto(ax, f_ecc_p, security_ecc_p, securities, data_ecc_p, labels_ecc_p, color_shapes_ecc_p, markersize, linewidth)
    plot_crypto(ax, f_ecc_2m, security_ecc_2m, securities, data_ecc_2m, labels_ecc_2m, color_shapes_ecc_2m, markersize, linewidth)
    ax.plot([np.log2(get_RSA(2048)), np.log2(get_RSA(2048))], [y_start, y_end], 'k--', linewidth=2, label='Sécurité minimale')

    ax.legend(fontsize=fontsize*0.75)
    #ax.set_title(str(curve), fontsize=fontsize)

    ax.set_xlabel(x_label, fontsize=fontsize)
    ax.set_xlim([x_start, x_end])
    ax.set_xticks([i for i in range(x_start, x_end+1)])
    ax.set_xticklabels(get_axe(base, x_start, x_end), fontsize=fontsize)

    ax.set_ylabel(y_label, fontsize=fontsize)
    ax.set_ylim([y_start, y_end])
    ax.set_yticks([i for i in range(y_start, y_end+1)])
    ax.set_yticklabels(get_axe(base, y_start, y_end), fontsize=fontsize)

    ax.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.1)
    plt.savefig(path)
    plt.show()
