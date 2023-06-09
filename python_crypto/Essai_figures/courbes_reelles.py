from utils import *
from utils_performance import *
import numpy as np

import numpy as np
import matplotlib.pyplot as plt

def draw_arrow(ax, x, y, dx, dy, span):
    head_length = span/40
    head_width = 0.75/2
    nominal_head_length = head_length if np.abs(dy) > 2*head_length else 0
    nominal_head_width = head_width if np.abs(dy) > 2*head_length else 0
    ax.arrow(x=x, y=y, dx=dx, dy=np.sign(dy) * (np.abs(dy) - nominal_head_length), head_width=nominal_head_width, head_length=nominal_head_length, fc='b', ec='b', linewidth=2)

t_period = np.linspace(0, 1, 1001, True)
y_period = np.sin(2*np.pi*t_period)

fontsize=20
fig = plt.figure(figsize=(18,15), dpi=80)

ax1 = fig.add_subplot(221)
ax1.plot(t_period, y_period, linewidth=3)
ax1.set_title(u"a)", fontsize=fontsize)
ax1.set_xlabel(u"Temps [s]", fontsize=fontsize)
ax1.set_ylabel(u"Amplitude [V]", fontsize=fontsize)
ax1.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.2)
ax1.set_xlim([0, 1])
ax1.set_xticks(np.linspace(0, 1, 5, True))
ax1.set_xticklabels([r"$0$", r"$\frac{1}{4}T$", r"$\frac{1}{2}T$", r"$\frac{3}{4}T$", r"$T$"], fontsize=fontsize)
ax1.set_ylim([-0.5, 0.5])
ax1.set_yticks(np.linspace(-1, 1, 5, True))
ax1.set_yticklabels([r"$-A$", r"$-\frac{1}{2}A$", r"$0$", r"$\frac{1}{2}A$", r"$A$"], fontsize=fontsize)
ax1.axhline(0, color='k', linewidth=2)
ax1.axvline(0, color='k', linewidth=2)

ax2 = fig.add_subplot(222)
draw_arrow(ax2, 1, 0, 0, -0.5, 1)
draw_arrow(ax2, -1, 0, 0, 0.5, 1)
ax2.set_title(u"b)", fontsize=fontsize)
ax2.set_xlabel(u"Fréquence [Hz]", fontsize=fontsize)
ax2.set_ylabel(u"$S(f)$ [Axe imaginaire]  [V]", fontsize=fontsize)
ax2.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.2)
ax2.set_xlim([-8, 8])
ax2.set_xticks(np.linspace(-8, 8, 17, True))
ax2.set_xticklabels([r"$\frac{-8}{T}$", r"$\frac{-7}{T}$", r"$\frac{-6}{T}$", r"$\frac{-5}{T}$", r"$\frac{-4}{T}$", r"$\frac{-3}{T}$" , r"$\frac{-2}{T}$", r"$\frac{-1}{T}$", r"$0$", r"$\frac{1}{T}$", r"$\frac{2}{T}$", r"$\frac{3}{T}$", r"$\frac{4}{T}$", r"$\frac{5}{T}$", r"$\frac{6}{T}$", r"$\frac{7}{T}$", r"$\frac{8}{T}$"], fontsize=fontsize)
ax2.set_ylim([-0.5, 0.5])
ax2.set_yticks(np.linspace(-0.5, 0.5, 5, True))
ax2.set_yticklabels([r"$-\frac{1}{2}A$", r"$-\frac{1}{4}A$", r"$0$", r"$\frac{1}{4}A$", r"$\frac{1}{2}A$"], fontsize=fontsize)
ax2.axhline(0, color='k', linewidth=2)
ax2.axvline(0, color='k', linewidth=2)

ax3 = fig.add_subplot(223)
draw_arrow(ax3, 1, 0, 0, 0.25, 0.25)
draw_arrow(ax3, -1, 0, 0, 0.25, 0.25)
ax3.set_title(u"c)", fontsize=fontsize)
ax3.set_xlabel(u"Fréquence [Hz]", fontsize=fontsize)
ax3.set_ylabel(r"$|S(f)|^2$  $\left[\frac{W}{Hz}\right]$", fontsize=fontsize)
ax3.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.2)
ax3.set_xlim([-8, 8])
ax3.set_xticks(np.linspace(-8, 8, 17, True))
ax3.set_xticklabels([r"$\frac{-8}{T}$", r"$\frac{-7}{T}$", r"$\frac{-6}{T}$", r"$\frac{-5}{T}$", r"$\frac{-4}{T}$", r"$\frac{-3}{T}$" , r"$\frac{-2}{T}$", r"$\frac{-1}{T}$", r"$0$", r"$\frac{1}{T}$", r"$\frac{2}{T}$", r"$\frac{3}{T}$", r"$\frac{4}{T}$", r"$\frac{5}{T}$", r"$\frac{6}{T}$", r"$\frac{7}{T}$", r"$\frac{8}{T}$"], fontsize=fontsize)
ax3.set_ylim([0, 0.25])
ax3.set_yticks(np.linspace(0, 0.25, 3, True))
ax3.set_yticklabels([r"$0$", r"$\frac{1}{8}A^2$", r"$\frac{1}{4}A^2$"], fontsize=fontsize)
ax3.axhline(0, color='k', linewidth=2)
ax3.axvline(0, color='k', linewidth=2)

ax4 = fig.add_subplot(224)
draw_arrow(ax4, 1, 0, 0, 10*np.log10(0.25/1e-3), 60)
draw_arrow(ax4, -1, 0, 0, 10*np.log10(0.25/1e-3), 60)
ax4.set_title(u"d)", fontsize=fontsize)
ax4.set_xlabel(u"Fréquence [Hz]", fontsize=fontsize)
ax4.set_ylabel(r"$|S(f)|^2$ par rapport à $10\log_{10}\left(A^2\right)$  $\left[\frac{dBm}{Hz}\right]$", fontsize=fontsize)
ax4.grid(visible=True, which='major', axis='both', color='k', linestyle='-', linewidth=0.2)
ax4.set_xlim([-5, 5])
ax4.set_xticks(np.linspace(-8, 8, 17, True))
ax4.set_xticklabels([r"$\frac{-8}{T}$", r"$\frac{-7}{T}$", r"$\frac{-6}{T}$", r"$\frac{-5}{T}$", r"$\frac{-4}{T}$", r"$\frac{-3}{T}$" , r"$\frac{-2}{T}$", r"$\frac{-1}{T}$", r"$0$", r"$\frac{1}{T}$", r"$\frac{2}{T}$", r"$\frac{3}{T}$", r"$\frac{4}{T}$", r"$\frac{5}{T}$", r"$\frac{6}{T}$", r"$\frac{7}{T}$", r"$\frac{8}{T}$"], fontsize=fontsize)
ax4.set_ylim([-30, 30])
ax4.set_yticks(np.linspace(-30, 30, 7, True))
ax4.set_yticklabels([r"$-30$", r"$-20$", r"$-10$", r"$0$", r"$10$", r"$20$", r"$30$"], fontsize=fontsize)
ax4.axhline(0, color='k', linewidth=2)
ax4.axvline(0, color='k', linewidth=2)

plt.tight_layout()
#plt.savefig('../images/prelab1_num1and2a.png')

if __name__ == "__main__":
    pass
    plt.show()