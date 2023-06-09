from prime_utils import *
import numpy as np


class elliptic_curve:

    def __init__(self, a, b, p):
        self.a = a
        self.b = b
        self.p = p
        self.verify_primality_p()
        self.verify_singularity()
        self.x_list = []
        self.y2_list = []
        self.Q_p_list = []
        self.is_y2_in_Q_list = []
        self.points = []

    def __eq__(self, other):
        return (self.a == other.a) and (self.b == other.b) and (self.p == other.p)

    def verify_primality_p(self):
        a, b = factorise(self.p)
        if len(a) != 1 or b[0] != 1:
            print("Elliptic curve parameter p not prime")

    def verify_singularity(self):
        discriminant = np.mod(4 * self.a + 27 * self.b, self.p)
        if discriminant == 0:
            print("Elliptic discriminant mod p is null")

    def __str__(self):
        bracket_p = "{" + str(self.p) + "}"
        return r"$E_p(a,b) = E_{}({},{})$".format(bracket_p, self.a, self.b)

    def compute_y2(self, x: int):
        return np.mod(x ** 3 + self.a * x + self.b, self.p)

    def compute_all_points(self):
        self.x_list = [x for x in range(self.p)]
        self.y2_list = [self.compute_y2(x) for x in self.x_list]
        N = int((self.p - 1) / 2)
        self.Q_p_list = [np.mod((x + 1) ** 2, self.p) for x in range(N)]
        self.is_y2_in_Q_list = [self.y2_list[x] in self.Q_p_list for x in self.x_list]
        for x in self.x_list:
            if self.is_y2_in_Q_list[x]:
                y1 = self.Q_p_list.index(self.y2_list[x]) + 1
                y2 = self.p - y1
                p1 = elliptic_point(x, y1, self)
                p2 = elliptic_point(x, y2, self)
                self.points.append(p1)
                self.points.append(p2)
            elif self.y2_list[x] == 0:
                p = elliptic_point(x, 0, self)
                self.points.append(p)
        return self.points

    def points_to_string(self):
        array_string = ""
        for point in self.points:
            array_string += str(point) + ", "
        return array_string[:-2]

    def is_quadratic_residue(self, x):
        is_p_mod_4_equal_3 = np.mod(self.p + 1, 4) == 0
        if is_p_mod_4_equal_3:
            residu = self.compute_y2(x)
            exponent = int((self.p+1)/4)
            y1 = compute_a_power_x_mod_n(residu, exponent, self.p)
            return compute_a_power_x_mod_n(y1, 2, self.p) == residu, y1, self.p - y1
        else:
            print("Cannot determine if is residue quadratic")



class elliptic_point:
    def __init__(self, x: int, y: int, curve: elliptic_curve, is_inf=False):
        self.x = x
        self.y = y
        self.curve = curve
        self.is_on_curve = self.is_point_is_on_curve()
        self.is_inf = is_inf

    def is_point_is_on_curve(self):
        return False

    def __str__(self):
        if self.is_inf:
            #return "(inf)"
            return "$\infty$"
        else:
            return "({}, {})".format(self.x, self.y)

    def __eq__(self, other):
        return (self.x == other.x) and (self.y == other.y) and (self.curve == other.curve)

    def __neg__(self):
        if self.is_inf:
            return elliptic_point(self.x, np.mod(-self.y, self.curve.p), self.curve, self.is_inf)
        else:
            return elliptic_point(self.x, np.mod(-self.y, self.curve.p), self.curve, self.is_inf)

    def __add__(self, other):
        if self.is_inf:
            return elliptic_point(other.x, other.y, other.curve, other.is_inf)
        elif other.is_inf:
            return elliptic_point(self.x, self.y, self.curve, self.is_inf)
        elif self == -other:
            return elliptic_point(self.x, self.y, self.curve, True)
        else:
            m = self.get_m(other)
            x3 = np.mod(m ** 2 - self.x - other.x, self.curve.p)
            y3 = np.mod(m * (self.x - x3) - self.y, self.curve.p)
            return elliptic_point(x3, y3, self.curve, self.is_inf)

    def __sub__(self, other):
        return self + (-other)

    def __mul__(self, scalar):
        nb_digit = 1 + int(np.log2(scalar))
        digits = [(scalar >> i) & 1 for i in range(nb_digit)]
        multiples = []
        multiples.append(self)
        for i in range(1, nb_digit):
            multiples.append(multiples[i - 1] + multiples[i - 1])
        total = elliptic_point(0, 0, self.curve, True)
        for i in range(nb_digit):
            if digits[i]:
                total = total + multiples[i]
        return total

    def get_m(self, other):
        if self == other:
            num = 3 * self.x ** 2 + self.curve.a
            denum = 2 * self.y
        else:
            num = self.y - other.y
            denum = self.x - other.x

        if denum < 0:
            denum = -denum
            num = -num

        k = gcd(np.abs(num), denum)
        num = int(num / k)
        denum = int(denum / k)
        gcd_value = gcd(denum, self.curve.p)
        if gcd_value != 1:
            print("An inverse might not exist gcd({},{}) = {}".format(denum, self.curve.p, gcd_value))
        m = np.mod(np.mod(num, self.curve.p) * compute_inverse(denum, self.curve.p), self.curve.p)
        return m

def ECC_encrypt(k: int, G: elliptic_point, Pm: elliptic_point, PB: elliptic_point):
    return [G*k, Pm + PB*k]

def ECC_decrypt(encrypt, kb: int)->elliptic_point:
    P1 = encrypt[0]
    P2 = encrypt[1]
    Pm = P2 - P1*kb
    return Pm

def print_all_points(points):
    for point in points:
        print(point, end=', ')
    print("(inf)")
    print()
    print()

if __name__ == "__main__":
    pass

    curve = elliptic_curve(1, 1, 23)
    curve.compute_all_points()
    points = curve.points
    for point in points:
        print(point)
    print("------")
    p1 = points[8]
    for i in range(1, 100):
        print(i, p1 * i)