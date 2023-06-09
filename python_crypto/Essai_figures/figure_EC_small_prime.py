from prime_utils import*
from elliptic_curve import*
from graphs import*
import numpy as np

a = 1
b = 7
p = 11


curve = elliptic_curve(a, b, p)
points = curve.compute_all_points()
print_all_points(points)
nb_points = np.size(points) + 1


#---------------
first = "$\\times$"
for i in range(nb_points-1):
    first += " & " + (points[i]).__str__()
print(first+ "\\\\ \hline")
for i in range(nb_points-1):
    phrase = str(i+1)
    for j in range(nb_points-1):
        phrase += " & "
        phrase += (points[j] * (i + 1)).__str__()
    print(phrase + "\\\\ \hline")
#---------------


print("numéro 1A)")
path = "./images/EC_small_prime.png"
plot_elliptic(curve, path)

P = points[0] * 15
print(P)
print(-P)
print(P + P)
print(P + points[0])
print(points[0]*16)