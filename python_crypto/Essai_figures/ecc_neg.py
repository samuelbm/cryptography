import numpy as np
import matplotlib.pyplot as plt

def ecc_real(t_points, a, b):
    x_list = []
    y1_list = []
    y2_list = []
    for t in t_points:
        y2 = t**3 + a*t + b
        if(y2 >= 1e-9):
            x_list.append(t)
            y1_list.append(np.sqrt(y2))
            y2_list.append(-y1_list[-1])
    return x_list, y1_list, y2_list

def f(x, a, b):
    y2 = x**3 + a*x + b
    return np.sqrt(y2)


n = 10000
xmin = -4
xmax = 4
ymin = -10
ymax = 10
xlim = [xmin, xmax]
ylim = [ymin, ymax]
xticks = [int(i) for i in range(xmin, xmax+1, 2)]
yticks = [int(i) for i in range(ymin, ymax+1, 5)]
print(xticks)
t = np.linspace(xmin, xmax, n, True)
t1 = np.linspace(xmin, 1, n, True)
t2 = np.linspace(1, xmax, n, True)

path = "./images/EC_inverse.png"
fontsize = 20
fig = plt.figure(figsize = (10,6), dpi=80)
ax1 = fig.add_subplot(1,2,1)
a = -3
b = 3
x, y1, y2 = ecc_real(t, a, b)
#ax1.plot(x, y1, linewidth=3, label=label)
ax1.plot(x, y1, linewidth=3, c=u'#1f77b4')
ax1.plot(x, y2, linewidth=3, c=u'#1f77b4')
ax1.set_title("a)", fontsize=fontsize)
ax1.set_xlabel("x", fontsize=20)
ax1.set_xlim(xlim)
ax1.set_xticks(xticks)
ax1.set_xticklabels(xticks, fontsize=fontsize)
ax1.set_ylabel("y", fontsize=20)
ax1.set_ylim(ylim)
ax1.set_yticks(yticks)
ax1.set_yticklabels(yticks, fontsize=fontsize)
ax1.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.1)
ax1.plot([-1, -1], [-f(-1, a, b), f(-1, a, b)], c=u'#ff7f0e')
ax1.scatter([-1, -1], [-f(-1, a, b), f(-1, a, b)], c=u'#ff7f0e', zorder=2)
ax1.text(-1, 2.5, r"$P$", fontsize=fontsize)
ax1.text(-1, -3.5, r"$Q=-P$", fontsize=fontsize)

ax2 = fig.add_subplot(1,2,2)
a = -3
b = 1
x, y1, y2 = ecc_real(t1, -3, 1)
ax2.plot(x, y1, linewidth=3, c=u'#1f77b4')
ax2.plot(x, y2, linewidth=3, c=u'#1f77b4')
x, y1, y2 = ecc_real(t2, -3, 1)
ax2.plot(x, y1, linewidth=3, c=u'#1f77b4')
ax2.plot(x, y2, linewidth=3, c=u'#1f77b4')
ax2.set_title("b)", fontsize=fontsize)
ax2.set_xlabel("x", fontsize=20)
ax2.set_xlim(xlim)
ax2.set_xticks(xticks)
ax2.set_xticklabels(xticks, fontsize=fontsize)
ax2.set_ylabel("y", fontsize=20)
ax2.set_ylim(ylim)
ax2.set_yticks(yticks)
ax2.set_yticklabels(yticks, fontsize=fontsize)
ax2.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.1)
ax2.plot([-1, -1], [-f(-1, a, b), f(-1, a, b)], c=u'#ff7f0e')
ax2.scatter([-1, -1], [-f(-1, a, b), f(-1, a, b)], c=u'#ff7f0e', zorder=2)
ax2.text(-1, 2.5, r"$P$", fontsize=fontsize)
ax2.text(-1, -3.5, r"$Q=-P$", fontsize=fontsize)


plt.tight_layout()
plt.savefig(path)
plt.show()
