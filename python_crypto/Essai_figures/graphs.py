import matplotlib.pyplot as plt
import numpy as np
from elliptic_curve import*

def plot_elliptic(curve: elliptic_curve, path):
    points = curve.compute_all_points()
    x_list = [point.x for point in points]
    y_list = [point.y for point in points]
    fontsize=20
    fig = plt.figure(figsize=(10, 8), dpi=100)
    ax = fig.add_subplot(111)
    ax.scatter(x_list, y_list, linewidth=3)
    ax.set_title(str(curve), fontsize=fontsize)
    ax.set_xlabel("Coordonnée en X", fontsize=fontsize)
    ax.set_ylabel("Coordonnée en Y", fontsize=fontsize)
    ax.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.2)
    maximum, nb_interval = best_neighbor(np.max(x_list))
    ax.set_xlim([-1, maximum+1])
    x_coords = [int(maximum*i/nb_interval) for i in range(nb_interval+1)]
    ax.set_xticks(x_coords)
    ax.set_xticklabels(x_coords, fontsize=fontsize)
    maximum, nb_interval = best_neighbor(np.max(x_list))
    ax.set_xlim([-1, maximum+1])
    y_coords = [int(maximum*i/nb_interval) for i in range(nb_interval+1)]
    ax.set_ylim([-1, maximum+1])
    ax.set_yticks(y_coords)
    ax.set_yticklabels(y_coords, fontsize=fontsize)
    plt.savefig(path)
    plt.show()

def divisors(x):
    divisor_list = []
    for i in range(1, x+1):
        if np.mod(x, i) == 0:
            divisor_list.append(i)
    return divisor_list

def best_divisor(divisor_list):
    best_choices = [10, 8, 9, 12]
    for choice in best_choices:
        if choice in divisor_list:
            return choice
    return -1

def best_neighbor(x):
    i = 0
    while True:
        divisor_list = divisors(x+i)
        best = best_divisor(divisor_list)
        if best > 0:
            return (x+i, best)
        i = i + 1


if __name__ == "__main__":
    a = 2
    b = -1
    p = 5
    curve = elliptic_curve(a, b, p)
    curve.compute_all_points()
    print(curve.points_to_string())