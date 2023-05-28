from utils import*
import numpy as np

def chinese_remainder(xi, di):
    n = np.prod(di)
    d_ni = np.array([int(n/di[i]) for i in range(len(di))])
    y = np.array([compute_inverse(d_ni[i], di[i]) for i in range(len(di))])
    x = np.mod(np.sum([d_ni[i]*xi[i]*y[i] for i in range(len(di))]), n)
    return x, n

print("Numéro 4 méthode 1")
x1 = np.array([0, 1, 5, 6])
d1 = np.array([2, 3, 5, 7])
ans1, n1 = chinese_remainder(x1, d1)
print("Avec d1={}, d2={}, d3={}, d4={}".format(d1[0], d1[1], d1[2], d1[3]))
print("x = {}k + {}".format(n1, ans1))
print([i*n1 + ans1 for i in range(4)])
print()

x2 = np.array([2, 1, 5, 6])
d2 = np.array([4, 3, 5, 7])
ans2, n2 = chinese_remainder(x2, d2)
print("Avec d1={}, d2={}, d3={}, d4={}".format(d2[0], d2[1], d2[2], d2[3]))
print("x = {}k + {}".format(n2, ans2))
print([i*n2 + ans2 for i in range(4)])
print()

x3 = np.array([4, 5, 6])
d3 = np.array([6, 5, 7])
ans3, n3 = chinese_remainder(x3, d3)
print("Avec d1={}, d2={}, d3={}".format(d3[0], d3[1], d3[2]))
print("x = {}k + {}".format(n3, ans3))
print([i*n3 + ans3 for i in range(4)])
print()
print("Le premier x identique dans les trois catégories est 370")

print()
print()

print("Numéro 4 méthode 2")
x4 = np.array([1, 2, 0, 6])
d4 = np.array([3, 4, 5, 7])
ans4, n4 = chinese_remainder(x4, d4)
print("Avec d1={}, d2={}, d3={}, d4={}".format(d4[0], d4[1], d4[2], d4[3]))
print("x = {}".format(ans4))
print()
