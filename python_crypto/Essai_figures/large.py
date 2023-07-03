import numpy as np
import random
import time


class Count:
    def __init__(self):
        self.clock = 0
        self.regs = 0
        self.gates = 0

    def time(self, clock):
        self.clock += clock

    def space(self, regs):
        self.regs += regs

    def power(self, gates):
        self.gates += gates


def number_of_bits(x):
    return len(str(bin(x))[2:])


# n xor
# n-1 or
def is_equal_gates(n):
    return 2 * n - 1


# clock = 0
# regs  = 0
def is_equal(x, y):
    count = Count()
    n_bits = number_of_bits(max(x, y))
    count.power(is_equal_gates(n_bits))
    return x == y, count


# 1, 5, 9, 13, 17...
def is_less_than_gates(n):
    return 4 * n - 3


# clock = 0
# regs  = 0
def is_less_than(x, y):
    count = Count()
    n_bits = number_of_bits(max(x, y))
    count.power(is_less_than_gates(n_bits))
    return x < y, count


# 0, 2, 4, 6
def is_less_or_equal_gates(n):
    return 2 * n - 2


# clock = 0
# regs  = 0
def is_less_or_equal(x, y):
    count = Count()
    n_bits = number_of_bits(max(x, y))
    count.power(is_less_or_equal_gates(n_bits))
    return x < y, count


# n or
# 2n and
# 2n xor
def addition_gates(n):
    return 5 * n


# clock = 0
def addition(x, y):
    count = Count()
    n_bits = number_of_bits(max(x, y))
    count.space(n_bits + 1)  # sum is n+1 regs
    count.power(addition_gates(n_bits))
    return x + y, count


# n or
# 2n and
# 2n xor
def substraction_gates(n):
    return 5 * n


# clock = 0
def substraction(x, y):
    count = Count()
    n_bits = number_of_bits(max(x, y))
    count.space(n_bits + 1)  # difference is n+1 regs
    count.power(substraction_gates(n_bits))
    return x - y, count


# n additions
def multiplication_gates(n):
    return n * addition_gates(n)


def multiplication(x, y):
    count = Count()
    n_bits = number_of_bits(max(x, y))
    count.time(n_bits)  # n cycles
    count.space(2 * n_bits)  # product is 2n
    count.power(multiplication_gates(n_bits))
    return x * y, count


# n times substraction and is_less_or_equal
def division_modulo_gates(n):
    return n * substraction_gates(n) + n * is_less_or_equal_gates(n)


def division_modulo(x, y):
    count = Count()
    n_bits = number_of_bits(max(x, y))
    count.time(n_bits)  # n cycles
    count.space(3 * n_bits)  # 2n for quotient, n for remainder
    count.power(division_modulo_gates(n_bits))

    r = x
    tampon = y
    while tampon <= r:
        tampon = tampon << 1  # less or equal

    q = 0
    while y != tampon:
        tampon = tampon >> 1
        q = q << 1
        if tampon <= r:
            r = r - tampon
            q = q + 1
    return q, r, count


# 1 addition and 1 division modulo
def addition_modulo_gates(n):
    return addition_gates(n) + division_modulo_gates(n)


def addition_modulo(a, b, n):
    count = Count()
    n_bits = number_of_bits(max(a, b, n))
    count.time(n_bits + 1)  # 1 cycle for addition and n cycles for division
    count.space(4 * n_bits + 4)  # n + 1 for addition, 3*n for division with n+1 word
    count.power(addition_modulo_gates(n_bits))
    somme, count1 = addition(a, b)
    q, r, count2 = division_modulo(somme, n)
    return r, count


def substraction_modulo_gates(n):
    return substraction_gates(n) + division_modulo_gates(n)


def substraction_modulo(a, b, n):
    count = Count()
    n_bits = number_of_bits(max(a, b, n))
    count.time(n_bits + 1)  # 1 cycle for substraction and n cycles for division
    count.space(4 * n_bits + 4)  # n + 1 for substraction, 3*n for division with n+1 word
    count.power(substraction_modulo_gates(n_bits))
    difference, count1 = substraction(a, b)
    q, r, count2 = division_modulo(difference, n)
    return r, count


def multiplication_modulo_gates(n):
    return multiplication_gates(n) + division_modulo_gates(n)


def multiplication_modulo(a, b, n):
    count = Count()
    n_bits = number_of_bits(max(a, b, n))
    count.time(2 * n_bits)  # n cycles for multiplication, n cycles for division
    count.space(8 * n_bits)  # 2n for multiplication, 3n for division with 2n word
    count.power(multiplication_modulo_gates(n_bits))
    product, count1 = multiplication(a, b)
    q, r, count2 = division_modulo(product, n)
    return r, count


# 2n multiplication modulo and 2n is equal
def exponentiation_modulo_gates(n):
    return 2 * n * multiplication_modulo_gates(n) + 2 * n * is_equal_gates(n)


def exponentiation_modulo(base, exponent, modulus):
    count = Count()
    n_bits = number_of_bits(max(base, exponent, modulus))
    count.time(n_bits * n_bits)  # n times multiplicaiton modulo (because they can run in parallel)
    count.space(16 * n_bits)  # twice multiplication modulo
    count.power(exponentiation_modulo_gates(n_bits))

    square = base
    total = 1
    while exponent != 0:
        e = exponent & 1
        exponent = exponent >> 1
        if e == 1:
            total, count1 = multiplication_modulo(total, square, modulus)

        square, count2 = multiplication_modulo(square, square, modulus)
    return total, count


# cannot obtain precise stat
# 1 division, 1 multiplication and 1 substraction by iteration
def greatest_common_divisor_gates(n):
    return division_modulo_gates(n) + multiplication_modulo_gates(n) + substraction_gates(2 * n)


def greatest_common_divisor(a, b):
    count = Count()
    n_bits = number_of_bits(max(a, b))
    count.space(12 * n_bits)  # 3n for division, 2n for multiplication, n for substraction with word 2n, 3n of r, n of k

    if b > a:
        a, b = b, a
    r = [a, b]
    k = []
    while r[-1] != 0:
        count.time(2 * n_bits + 1)  # n cycles for multiplication, n cycles for division, 1 cycle for difference
        count.power(greatest_common_divisor_gates(n_bits))
        quotient, remainder, count1 = division_modulo(r[-2], r[-1])
        k.append(quotient)
        product, count2 = multiplication(k[-1], r[-1])
        difference, count3 = substraction(r[-2], product)
        r.append(difference)
    return r[-2], count


def is_prime_rabin_miller_gates(n):
    return exponentiation_modulo_gates(n)


def is_prime_rabin_miller(n):
    count = Count()
    n_bits = number_of_bits(n)
    count.space(32 * 100 + 16 * n_bits)  # 3200 bits of memory for primes and exponentation modulo

    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
              71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
              179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
              283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
              419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541]

    if n == 2:
        return True, count

    for prime in primes:
        count.time(n_bits * n_bits)  # only one exponentiation modulo to perform
        count.power(is_prime_rabin_miller_gates(n_bits))
        if prime < n:
            number, count1 = exponentiation_modulo(prime, n - 1, n)
            if number != 1 and n > prime:
                return False, count  # for sure
    return True, count  # probably


def pollard_rho_factorisation_gates(n):
    return 3 * (multiplication_gates(n) + addition_gates(2 * n) + division_modulo_gates(2 * n))


# cannot give exact stats because unknown number of iterations
def pollard_rho_factorisation(n, start):
    count = Count()
    n_bits = number_of_bits(n)
    count.space(100 * n)  # craete a small stack for recording of many factors

    factors = []
    is_prime, count1 = is_prime_rabin_miller(n)
    if is_prime:
        factors.append(n)
    else:
        x = 2
        y = 2
        d = 1
        while d == 1:
            count.time(30 * n + 6)  # 3 multiplication(2n), 3 addition(n+1) with word 2n, 3 division(3n) with word 2n
            count.power(pollard_rho_factorisation_gates(n_bits))

            product, count2 = multiplication(x, x)
            somme, count3 = addition(product, start)
            q, x, count4 = division_modulo(somme, n)
            product, count5 = multiplication(y, y)
            somme, count6 = addition(product, start)
            q, y, count7 = division_modulo(somme, n)
            product, count8 = multiplication(y, y)
            somme, count9 = addition(product, start)
            q, y, count10 = division_modulo(somme, n)

            if x > y:
                delta = x - y
            else:
                delta = y - x
            d, count11 = greatest_common_divisor(delta, n)
        if d == n:
            factorsx, count12 = pollard_rho_factorisation(n, start + 1)
            factors.extend(factorsx)
        else:
            f1 = d
            f2, remainder, count13 = division_modulo(n, f1)
            factors1, count14 = pollard_rho_factorisation(f1, start)
            factors2, count15 = pollard_rho_factorisation(f2, start)
            factors.extend(factors1)
            factors.extend(factors2)
    return factors, count


def phi_gates(n):
    return multiplication_gates(n)


def phi(prime_list):
    count = Count()
    n_bits = number_of_bits(max(prime_list))
    count.space(n_bits * (4 + len(prime_list)))  # 3 variable(a, b, p) + the number of factor in the list

    prime_list.sort()
    pi = []
    ei = []
    for prime in prime_list:
        if prime in pi:
            ei[-1] += 1
        else:
            pi.append(prime)
            ei.append(1)

    phi_n = 1
    for index in range(len(pi)):
        p = pi[index]
        e = ei[index]
        phi_n *= p ** (e - 1) * (p - 1)
        count.time(1 + n_bits * (e - 1) * (p - 1))
        count.power((e - 1) * (p - 1) * phi_gates(n_bits))
    return phi_n, count


# 1 exponentiation modulo and 1 substraction
def inverse_prime_modulo_gates(n):
    return exponentiation_modulo_gates(n) + substraction_gates(n)


def inverse_prime_modulo(a, p):
    count = Count()
    n_bits = number_of_bits(max(a, p))
    count.time(1 + n_bits * n_bits)  # 1 for substraction and n*n for exponentiation modulo
    count.space(17*n_bits + 1)  # n_bits + 1 for substraction and 16*n for exponentiation modulo
    count.power(exponentiation_modulo_gates(n_bits))

    inverse, count1 = exponentiation_modulo(a, p - 2, p)
    return inverse, count


def inverse_modulo_gates(n):
    return exponentiation_modulo_gates(n) + substraction_gates(n)


def inverse_modulo(a, phi_n, n):
    count = Count()
    n_bits = number_of_bits(max(a, n))
    count.time(1 + n_bits * n_bits)  # 1 for substraction and n*n for exponentiation modulo
    count.space(17*n_bits + 1)  # n_bits + 1 for substraction and 16*n for exponentiation modulo
    count.power(inverse_modulo_gates(n_bits))

    inverse, count1 = exponentiation_modulo(a, phi_n - 1, n)
    return inverse, count


def quadratic_residue_gates(n):
    return addition_gates(n) + exponentiation_modulo_gates(n) + multiplication_modulo_gates(n) + is_equal_gates(n)


def is_quadratiqc_residue(a, p):
    count = Count()
    n_bits = number_of_bits(max(a, p))
    count.time(3 + n_bits*n_bits + 2*n_bits)  #1 for addition, 2 for shift right, n*n for exponentiation modulo, 2n for addition
    count.space(25*n_bits + 1)  #
    count.power(quadratic_residue_gates(n_bits))

    exponent = (p+1) >> 2
    y1, count1 = exponentiation_modulo(a, exponent, p)
    b, count2 = multiplication_modulo(y1, y1, p)
    return a == b, y1, count


def find_prime_3_equiv_4_gates(n):
    return 1


def find_prime_3_equiv_4(size):
    is_prime = False
    while not is_prime:
        maybe_prime = 1
        for i in range(size-3):
            maybe_prime = (maybe_prime << 1) + random.getrandbits(1)
        maybe_prime = (maybe_prime << 2) + 3
        is_prime, count = is_prime_rabin_miller(maybe_prime)
        count.time(1)
        count.space(size)
    return maybe_prime, count


if __name__ == "__main__":
    pass
    n1 = 1090748135619415929462984244733782862448264161996232692431832786189721331849119295216264234525201987223957291796157025273109870820177184063610979765077554799078906298842192989538609825228048205159696851613591638196771886542609324560121290553901886301017900252535799917200010079600026535836800905297805880952350501630195475653911005312364560014847426035293551245843928918752768696279344088055617515694349945406677825140814900616105920256438504578013326493565836047242407382442812245131517757519164899226365743722432277368075027627883045206501792761700945699168497257879683851737049996900961120515655050115561271491492515342105748966629547032786321505730828430221664970324396138635251626409516168005427623435996308921691446181187406395310665404885739434832877428167407495370993511868756359970390117021823616749458620969857006263612082706715408157066575137281027022310927564910276759160520878304632411049364568754920967322982459184763427383790272448438018526977764941072715611580434690827459339991961414242741410599117426060556483763756314527611362658628383368621157993638020878537675545336789915694234433955666315070087213535470255670312004130725495834508357439653828936077080978550578912967907352780054935621561090795845172954115972927479877527738560008204118558930004777748727761853813510493840581861598652211605960308356405941821189714037868726219481498727603653616298856174822413033485438785324024751419417183012281078209729303537372804574372095228703622776363945290869806258422355148507571039619387449629866808188769662815778153079393179093143648340761738581819563002994422790754955061288818308430079648693232179158765918035565216157115402992120276155607873107937477466841528362987708699450152031231862594203085693838944657061346236704234026821102958954951197087076546186622796294536451620756509351018906023773821539532776208676978589731966330308893304665169436185078350641568336944530051437491311298834367265238595404904273455928723949525227184617404367854754610474377019768025576605881038077270707717942221977090385438585844095492116099852538903974655703943973086090930596963360767529964938414598185705963754561497355827813623833288906309004288017321424808663962671333528009232758350873059614118723781422101460198615747386855096896089189180441339558524822867541113212638793675567650340362970031930023397828465318547238244232028015189689660418822976000815437610652254270163595650875433851147123214227266605403581781469090806576468950587661997186505665475715792896
    n2 = 23456789987656789876412789437242813592431832786189721331849119295216264234525201987229243183278618972133184911929521626423452520198722
    n3 = 7681241287479187489148134325423523472398472398

    print("number of bits", number_of_bits(n1))
    print("is equal", is_equal(n1, n2))
    print("is less than", is_less_than(n1, n2))
    print("is less or equal", is_less_or_equal(n1, n2))
    print("addition", addition(n1, n2))
    print("substraction", substraction(n1, n2))
    print("multiplication", multiplication(n1, n2))
    print("division modulo", division_modulo(n1, n2))
    print("addition modulo", addition_modulo(n1, n2, n3))
    print("substraction modulo", substraction_modulo(n1, n2, n3))
    print("multiplication modulo", multiplication_modulo(n1, n2, n3))
    print("exponentiation modulo", exponentiation_modulo(n1, n2, n3))
    print("greatest common divisor", greatest_common_divisor(n1, n2))
    print("is prime rabin miller", is_prime_rabin_miller(n1))
    z = 1234567890
    print("pollard rho factorisation", pollard_rho_factorisation(z, 1))
    f, c = pollard_rho_factorisation(z, 1)
    f.sort()
    print("phi", phi(f))
    print("inverse prime modulo", inverse_prime_modulo(5, 7))
    print("inverse modulo", inverse_modulo(5, 2, 6))
    print("quadratic residue", is_quadratiqc_residue(4, 7))
    print("quadratic residue", is_quadratiqc_residue(3, 7))
    print("find prime 3 equiv 4", find_prime_3_equiv_4(100))

    # random.seed(1234)
    # x = [100, 200, 400, 800, 1600, 3200, 6400]
    # for i in x:
    #     t1 = time.time()
    #     p, c = find_prime_3_equiv_4(i)
    #     t2 = time.time()
    #     print(i, t2 - t1, p)
