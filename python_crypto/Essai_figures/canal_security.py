import numpy as np
import matplotlib.pyplot as plt

def equi_distribution(n):
    return np.array([[1/n + 1e-6 for i in range(n)]]).transpose()

def symetric_matrix_2x2(p):
    pe = p + 1e-6
    return np.array([[1-pe, pe], [pe, 1-pe]])

def H_X(px):
    return -np.sum(px * np.log2(px))

def H_XY(p_transition):
    return -np.sum(np.sum(p_transition * np.log2(p_transition)))

def H_XkY(p_transition, px):
    return -np.sum(np.sum((p_transition * px) * np.log2(p_transition)))

def I_XY(p_transition, px):
    return max(1e-6, H_X(px) - H_XkY(p_transition, px))

def C_S(p_transition_bob, p_transition_eve, px):
    return max(1e-6, I_XY(p_transition_bob, px)-I_XY(p_transition_eve, px))

def f(x, y):
    n = 2
    px = equi_distribution(n)
    X, Y = np.meshgrid(x, y)
    Z = X+Y
    for i in range(len(x)):
        for j in range(len(y)):
            p = x[i]
            e = y[j]
            bob = symetric_matrix_2x2(p)
            eve = symetric_matrix_2x2(e)
            c = C_S(bob, eve, px)
            Z[j, i] = c
    return X, Y, Z

def f2(p, e):
    z = np.zeros(np.shape(p))
    px = equi_distribution(2)
    for i in range(np.size(p)):
        bob = symetric_matrix_2x2(p[i])
        eve = symetric_matrix_2x2(e[i])
        c = C_S(bob, eve, px)
        z[i] = c
    return z

def python_bug_1_digit(x_prob):
    if x_prob == 1:
        return "1.0"
    else:
        return "0." + str(int(10*x_prob))

def draw_plot(ax, x, y, title, x_label, y_label, label=None):
    x_start = 0
    x_end = 0.5
    x_interval = 6
    y_start = 0
    y_end = 1
    y_interval = 11
    fontsize = 15
    ax.plot(x, y, linewidth=3, label=label)
    ax.set_title(title, fontsize=fontsize)
    ax.set_xlabel(x_label, fontsize=fontsize)
    ax.set_xlim([x_start, x_end])
    ax.set_xticks(np.linspace(x_start, x_end, x_interval, True))
    ax.set_xticklabels([python_bug_1_digit(i) for i in np.linspace(x_start, x_end, x_interval, True)], fontsize=fontsize)
    ax.set_ylabel(y_label, fontsize=fontsize)
    ax.set_ylim([y_start, y_end])
    ax.set_yticks(np.linspace(y_start, y_end, y_interval, True))
    ax.set_yticklabels([python_bug_1_digit(i) for i in np.linspace(y_start, y_end, y_interval, True)], fontsize=fontsize)
    ax.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.1)



path = "./images/canal_security.png"
fontsize = 20
fig = plt.figure(figsize = (16,12), dpi=80)

interval = 100
x = np.linspace(0, 0.5, interval, True)
y = np.linspace(0, 0.5, interval, True)
X, Y, Z = f(x, y)
ax1 = fig.add_subplot(2,2,1, projection='3d')
surf = ax1.plot_surface(X, Y, Z, cmap = plt.cm.viridis)
ax1.set_title("a)")
ax1.set_xlabel("BER pour le canal légitime", labelpad=20)
ax1.set_ylabel("BER pour le canal espion", labelpad=20)
ax1.set_zlabel('Capacité secrète [sh]', labelpad=20)
fig.colorbar(surf, shrink=0.5, aspect=8)
ax1.view_init(elev=30., azim=45)

interval = 100
p = np.linspace(0, 0.5, interval, True)
e = np.linspace(0.5, 0.5, interval, True)
z = f2(p, e)
ax2 = fig.add_subplot(2,2,2)
#def draw_plot(ax, x, y, title, x_label, y_label):
draw_plot(ax2, p, z, "b)", "BER pour le canal légitime", "Capacité secrète [sh]")

interval = 100
p = np.linspace(0, 0, interval, True)
e = np.linspace(0, 0.5, interval, True)
z = f2(p, e)
ax3 = fig.add_subplot(2,2,3)
draw_plot(ax3, e, z, "c)", "BER pour le canal espion", "Capacité secrète [sh]")

interval = 100
p = np.linspace(0, 0, interval, True)
e = np.linspace(0, 0.5, interval, True)
z = f2(p, e)
ax4 = fig.add_subplot(2,2,4)

interval = 100
for i in range(5):
    delta = i/10
    p = np.linspace(0, 0.5-delta, 100, True)
    e = p + delta
    z = f2(p, e)
    label = r"$\Delta$BER = " + python_bug_1_digit(delta)
    if i == 0:
        draw_plot(ax4, p, z, "d)", "BER pour le canal légitime", "Capacité secrète [sh]", label)
    else:
        ax4.plot(p, z, linewidth=3, label=label)

ax4.legend(fontsize=fontsize*0.75)


#plt.tight_layout()
#plt.savefig(path)
#plt.show()

#print(I_XY(symetric_matrix_2x2(0.0), [0.5, 0.5]))
print(I_XY(symetric_matrix_2x2(0.0), [0.5, 0.5]))
#print(I_XY(symetric_matrix_2x2(0.5), [0.5, 0.5]))
#print(I_XY(symetric_matrix_2x2(0.5), [0.1, 0.9]))