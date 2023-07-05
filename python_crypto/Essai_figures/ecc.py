import numpy as np
from large import *

class ecc_point():
    def __init__(self, px, py, is_inf):
        self.px = px
        self.py = py
        self.is_inf = is_inf

def ecc_create_curve(a, b, p, gx, gy):
    G = ecc_point(gx, gy, False)
    curve = [a, b, p, G]
    return curve


def ecc_compute_y2(curve, x):
    a, b, p, G = curve
    count = Count()
    n_bits = number_of_bits(p)
    count.time(3 * multiplication_clock(n_bits) + 2 + division_modulo_clock(n_bits))
    count.space(3 * multiplication_regs(n_bits) + 2 * addition_regs(n_bits) + division_modulo_regs(n_bits))
    count.power(3 * multiplication_gates(n_bits) + 2 * addition_gates(n_bits) + division_modulo_gates(n_bits))
    y2, count1 = division_modulo(x ** 3 + a * x + b, p)  # 3 multiplication, 2 addition, 1 division modulo
    return y2, count

def ecc_is_point_on_curve(curve, point):
    count = Count()
    a, b, p, G = curve
    x, y = point.px, point.py
    left_side, count1 = exponentiation_modulo(y, 2, p)
    right_side, count2 = ecc_compute_y2(curve, x)
    count.add_count(count1)
    count.add_count(count2)
    return left_side == right_side, count

def ecc_is_same_point(point1, point2):
    count = Count()
    same_x, count1 = is_equal(point1.px, point2.px)
    same_y, count2 = is_equal(point1.py, point2.py)
    same_point = (not point1.is_inf and not point2.is_inf) or (same_x and same_y and point1.is_inf and point2.is_inf)
    count.add_count(count1)
    count.add_count(count2)
    return same_point, count

def ecc_negate_point(curve, point):
    count = Count()
    a, b, p, G = curve
    neg_py, count1 = substraction(p, point.py)
    neg_point = ecc_point(point.px, p - point.py, point.is_inf)
    count.add_count(count1)
    return neg_point, count


def ecc_addition(curve, point1, point2):
    count = Count()
    a, b, p, G = curve

    neg_point2, count1 = ecc_negate_point(curve, point2)
    points_are_inverse, count2 = ecc_is_same_point(point1, neg_point2)
    count.add_count(count1)
    count.add_count(count2)

    if point1.is_inf:
        return point2, count
    elif point2.is_inf:
        return point1, count
    elif points_are_inverse:
        return ecc_point(0, 0, True)
    else:
        m, count3 = get_slope_m(curve, point1, point2)
        x3, count4 = multiplication(m, m)
        x3_1, count5 = addition(p, point1.px)
        x3_2, count6 = addition(p, point2.px)
        x3, count7 =

#             m = self.get_m(other)
#             x3 = np.mod(m ** 2 - self.x - other.x, self.curve.p)
#             y3 = np.mod(m * (self.x - x3) - self.y, self.curve.p)
#             return elliptic_point(x3, y3, self.curve, self.is_inf)

def ecc_substraction(curve, point1, point2):
    count = Count()
    neg_point2, count1 = ecc_negate_point(curve, point2)
    point_sum, count2 = ecc_addition(curve, point1, neg_point2)
    count.add_count(count1)
    count.add_count(count2)
    return point_sum, count

def ecc_multiplication(curve, point1, scalar):
    count = Count()
    point_double = point1
    point_prod = ecc_point(0, 0, True)
    is_first_pass = True
    while scalar != 0:
        is_component = scalar & 1
        scalar = scalar >> 1
        point_prod_temp, count1 = ecc_addition(curve, point_prod, point_double)
        point_double, count2 = ecc_addition(curve, point_double, point_double)

        if is_component:
            point_prod = point_prod_temp

        if is_first_pass:
            is_first_pass = False
            count.add_count(count1)
            count.add_count(count2)
        else:
            count.time(count1.clock)
            count.power(count1.gates)
            count.time(count2.clock)
            count.power(count2.gates)

    return point_prod, count



#makes the hypothesis that points are neither infinite nor vertical
#they can either be the same or different
def get_slope_m(curve, point1, point2):
    pass


#     def get_m(self, other):
#         if self == other:
#             num = 3 * self.x ** 2 + self.curve.a
#             denum = 2 * self.y
#         else:
#             num = self.y - other.y
#             denum = self.x - other.x
#
#         if denum < 0:
#             denum = -denum
#             num = -num
#
#         k = gcd(np.abs(num), denum)
#         num = int(num / k)
#         denum = int(denum / k)
#         gcd_value = gcd(denum, self.curve.p)
#         if gcd_value != 1:
#             print("An inverse might not exist gcd({},{}) = {}".format(denum, self.curve.p, gcd_value))
#         m = np.mod(np.mod(num, self.curve.p) * compute_inverse(denum, self.curve.p), self.curve.p)
#         return m
#


if __name__ == "__main__":
    pass
