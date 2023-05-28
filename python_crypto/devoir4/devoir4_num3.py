from utils import*
from utils_performance import*
import numpy as np

print("Numéro 3")

di = np.array([7, 11, 13])
n = np.prod(di)
d_ni = np.array([int(n / di[i]) for i in range(len(di))])
y = np.array([compute_inverse(d_ni[i], di[i]) for i in range(len(di))])
xi = np.array([compute_inverse(95, di[0]), compute_inverse(95, di[1]), compute_inverse(95, di[2])])
x = np.mod(np.sum([d_ni[i] * xi[i] * y[i] for i in range(len(di))]), n)

print("d1={}, d2={}, d3={}, n=d1*d2*d3={}".format(di[0], di[1], di[2], n))
print("(n/d1)={}, (n/d2)={}, (n/d3)={}".format(d_ni[0], d_ni[1], d_ni[2]))
print("y1=(n/d1)^-1={}, y2=(n/d2)^-1={}, y3=(n/d3)^-1={}".format(y[0], y[1], y[2]))
print("x1 = 95^-1 mod d1 = {}^-1 mod d1 = {}".format(np.mod(95, di[0]), xi[0]))
print("x2 = 95^-1 mod d2 = {}^-1 mod d2 = {}".format(np.mod(95, di[1]), xi[1]))
print("x3 = 95^-1 mod d3 = {}^-1 mod d3 = {}".format(np.mod(95, di[2]), xi[2]))
print("x = (n/d1)*y1*x1 + (n/d1)*y1*x1 + (n/d1)*y1*x1 mod n = {}*{}*{} + {}*{}*{} + {}*{}*{} mod {} = {}".format(d_ni[0], y[0], xi[0], d_ni[1], y[1], xi[1], d_ni[2], y[2], xi[2], n, x))
print("Vérification: inverse de 95 mod 1001 = {}".format(compute_inverse(95, 1001)))
print()