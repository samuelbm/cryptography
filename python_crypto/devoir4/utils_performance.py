import numpy as np


class elliptic_curve:
    def __init__(self, a, b, p):
        self.a = a
        self.b = b
        self.p = p
        self.x_list = []
        self.y2_list = []
        self.Q_p_list = []
        self.is_y2_in_Q_list = []
        self.points = []
        self.count = 0
        self.divisor = 1

    def __eq__(self, other):
        self.count += 3
        return (self.a == other.a) and (self.b == other.b) and (self.p == other.p)

    #def compute_y2(self, x: int):
        #return np.mod(x ** 3 + self.a * x + self.b, self.p)

class elliptic_point:
    def __init__(self, x: int, y: int, curve: elliptic_curve, is_inf=False):
        self.x = x
        self.y = y
        self.curve = curve
        self.is_inf = is_inf

    def __str__(self):
        if self.is_inf:
            return "(inf)"
        else:
            return "({}, {})".format(self.x, self.y)

    def __eq__(self, other):
        self.curve.count += 2
        return (self.x == other.x) and (self.y == other.y) and (self.curve == other.curve)

    def __neg__(self):
        self.curve.count += 1
        return elliptic_point(self.x, np.mod(-self.y, self.curve.p), self.curve, self.is_inf)

    def __add__(self, other):
        self.curve.count += 32
        if self.is_inf:
            return elliptic_point(other.x, other.y, other.curve, other.is_inf)
        elif other.is_inf:
            return elliptic_point(self.x, self.y, self.curve, self.is_inf)
        elif self == -other:
            return elliptic_point(self.x, self.y, self.curve, True)
        else:
            self.curve.count += 68
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
            self.curve.count += 66
            num = 3 * self.x ** 2 + self.curve.a
            denum = 2 * self.y
        else:
            self.curve.count += 2
            num = self.y - other.y
            denum = self.x - other.x

        if denum < 0:
            denum = -denum
            num = -num

        count1 = 0
        k, count1 = gcd_performance(np.abs(num), denum, count1)
        num = int(num / k)
        denum = int(denum / k)
        count1 += 64
        gcd_value, count1 = gcd_performance(denum, self.curve.p, count1)
        if gcd_value != 1:
            self.curve.divisor = gcd_value
        x, is_coprime, count1 = compute_inverse_performance(denum, self.curve.p, count1)
        m = np.mod(np.mod(num, self.curve.p) * x, self.curve.p)
        self.curve.count += 3*32 + count1
        return m


def gcd_performance(a: int, b: int, count) -> int:
    count1 = 0
    if b > a:
        a, b = b, a
    r = [a, b]
    k = []
    while r[-1] != 0:
        count1 += 63
        k.append(int(np.floor(r[-2] / r[-1])))
        r.append(r[-2] - k[-1] * r[-1])
    return r[-2], count+count1


def from_factors_to_unique_factor_and_exponent(factors):
    factor = []
    exponent = []
    for index in range(len(factors)):
        element = factors[index]
        if element in factor:
            exponent[-1] += 1
        else:
            factor.append(element)
            exponent.append(1)
    return [factor, exponent]


def factorise_performance(n, count):
    count1 = 0
    factors = []
    x = n
    i = 2
    while i <= int(np.floor(np.sqrt(x))):
        if np.mod(x, i) == 0:
            count1 += 64
            factors.append(i)
            x = int(x / i)
        else:
            i = i + 1
        count1 += 32
    factors.append(x)
    return factors, count+count1


def get_phi_n_performance(n, count):
    count1=0
    factors, count = factorise_performance(n, count)
    phi_n = 1
    factor, exponent = from_factors_to_unique_factor_and_exponent(factors)
    for index in range(len(factor)):
        count1 += 32**2 + 32 + 2
        pi = factor[index]
        ei = exponent[index]
        phi_n *= pi ** (ei - 1) * (pi - 1)
    return phi_n, count+count1


def compute_a_power_x_mod_n_performance(a, x, n, count):
    if x == 0:
        return np.mod(1, n)
    count1 = 0
    x_binary = [(x >> i) & 1 for i in range(0, 1 + int(np.floor(np.log2(x))))]
    a_power_x_mod_n = 1
    squaring = np.mod(a, n)
    count1 += 32
    for index in range(len(x_binary)):
        count1 += 128
        a_power_x_mod_n = np.mod(a_power_x_mod_n * squaring ** x_binary[index], n)
        squaring = np.mod(squaring ** 2, n)
    return a_power_x_mod_n, count+count1


def compute_inverse_performance(a, n, count):
    count1 = 0
    k, count = gcd_performance(a, n, count)
    is_coprime = k==1
    count1 += 32
    phi_n, count = get_phi_n_performance(n, count)
    x, count = compute_a_power_x_mod_n_performance(a, phi_n - 1, n, count)
    return x, is_coprime, count+count1

if __name__ == "__main__":
    pass
    #count = 10
    # k, count = gcd_performance(12, 21, count)
    # print(k, count)
    # factors, count = factorise_performance(10, count)
    # print(factors, count)
    # phi_n, count = get_phi_n_performance(10, count)
    # print(phi_n, count)
    # h, count = compute_a_power_x_mod_n_performance(2, 5, 11, count)
    # print(h, count)
    # x, is_coprime, count = compute_inverse_performance(3, 9, count)
    # print(x, is_coprime, count)


    # curve = elliptic_curve(1, -1, 11)
    # p1 = elliptic_point(1, 1, curve)
    # print(curve.count)
    # p2 = p1 + p1
    # print(curve.count, p2)
    # p3 = p1*2
    # print(curve.count, p3)
