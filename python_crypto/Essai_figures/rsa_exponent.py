from prime_utils import *
from elliptic_curve import *
from math import comb
from graphs import *
import numpy as np

def get_RSA(n):
    log_n = n * np.log(2)
    f1 = (64 / 9) ** (1 / 3)
    f2 = (log_n) ** (1 / 3)
    f3 = (np.log(log_n)) ** (2 / 3)
    f4 = f1 * f2 * f3
    return int(f4 * np.log2(np.exp(1)))

if __name__ == "__main__":
    x = []
    y = [128, 400, 1024, 2044, 3072, 7680, 15360]
    x_ln = []
    y_ln = []
    xx_ln = []
    xy_ln = []

    for i in range(len(y)):
        x.append(get_RSA(y[i]))
        x_ln.append(np.log(x[i]))
        y_ln.append(np.log(y[i]))
        #xx_ln.append(x_ln[i]*x_ln[i])
        #xy_ln.append(x_ln[i]*y_ln[i])

x_ln = np.matrix(x_ln).transpose()
y_ln = np.matrix(y_ln).transpose()
m_ones = np.ones(x_ln.shape)
A = np.concatenate((x_ln, m_ones), 1)
B = y_ln

x = np.linalg.inv(A.transpose() * A) * A.transpose() * B
a = x[0]
b = x[1]

t = np.linspace(x_ln[0,0], x_ln[len(x_ln)-1,0], 100, True)
z = a*t + b

fontsize = 20
fig = plt.figure(figsize=(10, 8), dpi=100)
ax = fig.add_subplot(111)
ax.scatter(np.squeeze(np.asarray(x_ln)), np.squeeze(np.asarray(y_ln)))
ax.plot(np.squeeze(np.asarray(t)), np.squeeze(np.asarray(z)))
plt.show()

print(a)
print(b)

print(get_RSA(1024))
print(get_RSA(2044))