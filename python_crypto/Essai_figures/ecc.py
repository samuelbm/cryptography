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
    dummy_quotient, y2, count1 = division_modulo(x ** 3 + a * x + b, p)  # 3 multiplication, 2 addition, 1 division modulo
    return y2, count


def ecc_is_point_on_curve(curve, point):
    count = Count()
    a, b, p, G = curve
    x, y = point.px, point.py
    left_side, count1 = multiplication_modulo(y, y, p)
    right_side, count2 = ecc_compute_y2(curve, x)
    count.add_count(count1)
    count.add_count(count2)
    return left_side == right_side, count


def ecc_is_same_point(point1, point2):
    count = Count()
    same_x, count1 = is_equal(point1.px, point2.px)
    same_y, count2 = is_equal(point1.py, point2.py)
    same_point = (point1.is_inf and point2.is_inf) or (same_x and same_y and not point1.is_inf and not point2.is_inf)
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

    neg_point2, countA = ecc_negate_point(curve, point2)
    is_points_vertical, countB = ecc_is_same_point(point1, neg_point2)
    count.add_count(countA)
    count.add_count(countB)
    if point1.is_inf:
        point_sum = point2
    elif point2.is_inf:
        point_sum = point1
    elif is_points_vertical:
        point_sum = ecc_point(0, 0, True)
    else:
        m, count3 = get_slope_m(curve, point1, point2)
        x3, count4 = multiplication(m, m)
        x3_1, count5 = substraction(p, point1.px)
        x3_2, count6 = substraction(p, point2.px)
        x3_12, count7 = addition(x3_1, x3_2)
        x3, count8 = addition_modulo(x3, x3_12, p)
        count.add_count(count3)
        count.add_count(count4)
        count.add_count(count5)
        count.add_count(count6)
        count.add_count(count7)
        count.add_count(count8)
        y3, count9 = substraction(p, x3)
        y3, count10 = addition(y3, point1.px)
        y3, count11 = multiplication(m, y3)
        y3_1, count12 = substraction(p, point1.py)
        y3, count13 = addition_modulo(y3, y3_1, p)
        count.time(count9.clock)
        count.power(count9.gates)
        count.time(count10.clock)
        count.power(count10.gates)
        count.time(count11.clock)
        count.power(count11.gates)
        count.time(count12.clock)
        count.power(count12.gates)
        count.time(count13.clock)
        count.power(count13.gates)
        point_sum = ecc_point(x3, y3, False)
    return point_sum, count


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


# makes the hypothesis that points are neither infinite nor vertical
# they can either be the same or different
def get_slope_m(curve, point1, point2):
    count = Count()
    a, b, p, G = curve

    is_same_point, count1 = ecc_is_same_point(point1, point2)
    count.add_count(count1)

    if is_same_point:
        num, count2 = multiplication(point1.px, point1.px)
        num, count3 = multiplication(num, 3)
        num, count4 = addition(num, a)
        denum = point1.py << 1
        count.add_count(count2)
        count.add_count(count3)
        count.add_count(count4)
    else:
        num, count5 = substraction(point1.py, point2.py)
        denum, count6 = substraction(point1.px, point2.px)
        count.add_count(count5)
        count.add_count(count6)

        if denum < 0:
            denum = -denum
            num = -num

        num, count7 = addition(num, p)
        count.add_count(count7)

    denum_inverse, count10 = inverse_prime_modulo(denum, p)
    #count.add_count(count10)

    num_add, count11 = addition(p, num)
    m, count12 = multiplication_modulo(num_add, denum_inverse, p)
    count.add_count(count11)
    count.add_count(count12)
    return m, count


if __name__ == "__main__":
    pass
