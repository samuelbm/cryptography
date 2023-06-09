from prime_utils import*
from elliptic_curve import*
from math import comb
from graphs import*
import numpy as np

if __name__ == "__main__":
    people = [2]
    people.extend([10 ** i for i in range(1, 7)])
    people = np.array(people)
    asymetric_keys = people
    symetric_keys = np.array([comb(i, 2) for i in people])
    path = "./images/number_keys.png"

    fontsize=20
    fig = plt.figure(figsize=(10, 8), dpi=100)
    ax = fig.add_subplot(111)
    ax.plot(np.log10(people), np.log10(symetric_keys), linewidth=3, label='Cryptographie symétrique')
    ax.plot(np.log10(people), np.log10(asymetric_keys), linewidth=3, label='Cryptographie asymétrique')
    ax.legend(fontsize=fontsize)
    #ax.set_title(str(curve), fontsize=fontsize)
    ax.set_xlabel("Nombre d'usagers", fontsize=fontsize)
    ax.set_ylabel("Nombre de clés à générer", fontsize=fontsize)
    ax.set_xlim([0, 6])
    ax.set_ylim([0, 12])
    ax.set_xticks([i for i in range(7)])
    ax.set_yticks([i for i in range(13)])
    ax.set_xticklabels([r"$10^0$", r"$10^1$", r"$10^2$", r"$10^3$", r"$10^4$", r"$10^5$", r"$10^6$"], fontsize=fontsize)
    ax.set_yticklabels([r"$10^0$", "", r"$10^2$", "", r"$10^4$", "", r"$10^6$", "", r"$10^8$", "", r"$10^{10}$", "", r"$10^{12}$"], fontsize=fontsize)
    ax.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.1)
    plt.savefig(path)
    plt.show()