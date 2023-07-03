import numpy as np


class count:
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


def number_of_bits_max(x, y):
    return max(number_of_bits(x), number_of_bits(y))


def is_equal(x, y):
    return x == y, 0, 0, number_of_bits_max(x, y)


def is_less_than(x, y):
    return x < y, 0, 0, number_of_bits_max(x, y)


def is_less_or_equal(x, y):
    return x < y, 0, 0, number_of_bits_max(x, y)


def addition(x, y):
    n = number_of_bits_max(x, y)
    return x + y, 1, 3*n, n


def substraction(x, y):
    n = number_of_bits_max(x, y)
    return x - y, 1, 3*n, n


def multiplication(x, y):
    n = number_of_bits_max(x, y)
    return x * y, n, 4*n, n*n


def division_modulo(x, y):
    n = number_of_bits_max(x, y)
    r = x
    tampon = y
    while tampon <= r:
        tampon = tampon << 1

    q = 0
    while y != tampon:
        tampon = tampon >> 1
        q = q << 1
        if tampon <= r:
            r = r - tampon
            q = q + 1
    return q, r, n, 6*n, n*n


def addition_modulo(a, b, n):
    sum, c1, c2, c3 = addition(a, b)
    q, r, c4, c5, c6 = division_modulo(sum, n)
    return q, c1 + c4, c2 + c5, c3 + c6


def substraction_modulo(a, b, n):
    difference, c1, c2, c3 = substraction(a, b)
    q, r, c4, c5, c6 = division_modulo(difference, n)
    return q, c1 + c4, c2 + c5, c3 + c6


def multiplication_modulo(a, b, n):
    product, c1, c2, c3 = multiplication(a, b)
    q, r, c4, c5, c6 = division_modulo(product, n)
    return r, c1 + c4, c2 + c5, c3 + c6


def exponentiation_modulo(base, exponent, modulus):
    square = base
    total = 1
    expo = exponent
    a = 0
    b = 0
    c = 0
    while(expo != 0):
        e = expo & 1
        expo = expo >> 1
        if e == 1:
            total, c1, c2, c3 = multiplication_modulo(total, square, modulus)
            a += c1
            b += c2
            c += c3
        square, c1, c2, c3 = multiplication_modulo(square, square, modulus)
        a += c1
        b += c2
        c += c3
    return total, a, b, c


def greatest_common_divisor(a, b):
    if b > a:
        a, b = b, a
    r = [a, b]
    k = []
    clock = 0
    regs = 0
    gates = 0
    while r[-1] != 0:
        quotient, remainder, c1, c2, c3 = division_modulo(r[-2], r[-1])
        k.append(quotient)
        clock += c1
        regs += c2
        gates += c3
        product, c1, c2, c3 = multiplication(k[-1], r[-1])
        clock += c1
        regs += c2
        gates += c3
        difference, c1, c2, c3 = substraction(r[-2], product)
        r.append(difference)
        clock += c1
        regs += c2
        gates += c3
    return r[-2], clock, regs, gates


def is_prime_rabin_miller(n):
    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
              71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
              179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
              283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
              419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541]
    clock = 0
    regs = 3200
    gates = 0

    if n == 2:
        return True, clock, regs, gates

    for prime in primes:
        if prime < n:
            number, c1, c2, c3 = exponentiation_modulo(prime, n-1, n)
            clock += c1
            regs += c2
            gates += c3
            if number != 1 and n > prime:
                return False, clock, regs, gates  # for sure
    return True, clock, regs, gates  # probably


def pollard_rho_factorisation(n, start):
    factors = []
    clock = 0
    regs = 0
    gates = 0
    is_prime, c1, c2, c3 = is_prime_rabin_miller(n)
    clock += c1
    regs += c2
    gates += c3
    if is_prime:
        factors.append(n)
    else:
        x = 2
        y = 2
        d = 1
        while d == 1:
            x, c1, c2, c3 = g(x, n, start)
            clock += c1
            regs += c2
            gates += c3
            y, c1, c2, c3 = g(y, n, start)
            clock += c1
            regs += c2
            gates += c3
            y, c1, c2, c3 = g(y, n, start)
            clock += c1
            regs += c2
            gates += c3
            if x > y:
                delta = x - y
            else:
                delta = y - x
            d, c1, c2, c3 = greatest_common_divisor(delta, n)
            clock += c1
            regs += c2
            gates += c3
        if d == n:
            factorsx, c1, c2, c3 = pollard_rho_factorisation(n, start + 1)
            clock += c1
            regs += c2
            gates += c3
            factors.extend(factorsx)
        else:
            f1 = d
            f2, remainder, c1, c2, c3 = division_modulo(n, f1)
            clock += c1
            regs += c2
            gates += c3
            factors1, c1, c2, c3 = pollard_rho_factorisation(f1, start)
            clock += c1
            regs += c2
            gates += c3
            factors2, c1, c2, c3 = pollard_rho_factorisation(f2, start)
            clock += c1
            regs += c2
            gates += c3
            factors.extend(factors1)
            factors.extend(factors2)
    return factors, clock, regs, gates

def g(x, n, start):
    clock = 0
    regs = 0
    gates = 0
    product, c1, c2, c3 = multiplication(x, x)
    clock += c1
    regs += c2
    gates += c3
    sum, c1, c2, c3 = addition(product, start)
    clock += c1
    regs += c2
    gates += c3
    q, r, c1, c2, c3 = division_modulo(sum, n)
    clock += c1
    regs += c2
    gates += c3
    return r, clock, regs, gates

def phi(prime_list):
    prime_list.sort()
    pi = []
    ei = []
    for prime in prime_list:
        if prime in pi:
            ei[-1] += 1
        else:
            pi.append(prime)
            ei.append(1)

    clock = 0
    regs = 0
    gates = 0
    phi_n = 1
    for index in range(len(pi)):
        p = pi[index]
        e = ei[index]
        phi_n *= p ** (e - 1) * (p - 1)
    return phi_n, clock, regs, gates


def inverse_prime_modulo(a, p):
    inverse, clock, regs, gates = exponentiation_modulo(a, p-2, p)
    return inverse, clock, regs, gates

def inverse_modulo(a, phi_n, n):
    inverse, clock, regs, gates = exponentiation_modulo(a, phi_n - 1, n)
    return inverse, clock, regs, gates


def is_quadratiqc_residue(a, p):
    clock = 0
    regs = 0
    gates = 0
    exponent = (p+1) >> 2
    y1, c1, c2, c3 = exponentiation_modulo(a, exponent, p)
    clock += c1
    regs += c2
    gates += c3
    b, c1, c2, c3 = multiplication_modulo(y1, y1, p)
    clock += c1
    regs += c2
    gates += c3
    return a == b, y1, clock, regs, gates

def find_prime_3_equiv_4():
    pass



if __name__ == "__main__":
    pass
    x = 1090748135619415929462984244733782862448264161996232692431832786189721331849119295216264234525201987223957291796157025273109870820177184063610979765077554799078906298842192989538609825228048205159696851613591638196771886542609324560121290553901886301017900252535799917200010079600026535836800905297805880952350501630195475653911005312364560014847426035293551245843928918752768696279344088055617515694349945406677825140814900616105920256438504578013326493565836047242407382442812245131517757519164899226365743722432277368075027627883045206501792761700945699168497257879683851737049996900961120515655050115561271491492515342105748966629547032786321505730828430221664970324396138635251626409516168005427623435996308921691446181187406395310665404885739434832877428167407495370993511868756359970390117021823616749458620969857006263612082706715408157066575137281027022310927564910276759160520878304632411049364568754920967322982459184763427383790272448438018526977764941072715611580434690827459339991961414242741410599117426060556483763756314527611362658628383368621157993638020878537675545336789915694234433955666315070087213535470255670312004130725495834508357439653828936077080978550578912967907352780054935621561090795845172954115972927479877527738560008204118558930004777748727761853813510493840581861598652211605960308356405941821189714037868726219481498727603653616298856174822413033485438785324024751419417183012281078209729303537372804574372095228703622776363945290869806258422355148507571039619387449629866808188769662815778153079393179093143648340761738581819563002994422790754955061288818308430079648693232179158765918035565216157115402992120276155607873107937477466841528362987708699450152031231862594203085693838944657061346236704234026821102958954951197087076546186622796294536451620756509351018906023773821539532776208676978589731966330308893304665169436185078350641568336944530051437491311298834367265238595404904273455928723949525227184617404367854754610474377019768025576605881038077270707717942221977090385438585844095492116099852538903974655703943973086090930596963360767529964938414598185705963754561497355827813623833288906309004288017321424808663962671333528009232758350873059614118723781422101460198615747386855096896089189180441339558524822867541113212638793675567650340362970031930023397828465318547238244232028015189689660418822976000815437610652254270163595650875433851147123214227266605403581781469090806576468950587661997186505665475715792896
    y = 23456789987656789876412789437242813592431832786189721331849119295216264234525201987229243183278618972133184911929521626423452520198722
    n = 7681241287479187489148134325423523472398472398

    print("number of bits", number_of_bits(x))
    print("number of bits max", number_of_bits_max(x, y))
    print("is equal", is_equal(x, y))
    print("is less than", is_less_than(x, y))
    print("is less or equal", is_less_or_equal(x, y))
    print("addition", addition(x, y))
    print("substraction", substraction(x, y))
    print("multiplication", multiplication(x, y))
    print("division modulo", division_modulo(x, y))
    print("addition modulo", addition_modulo(x, y, n))
    print("substraction modulo", substraction_modulo(x, y, n))
    print("multiplication modulo", multiplication_modulo(x, y, n))
    print("exponentiation modulo", exponentiation_modulo(x, y, n))
    print("greatest common divisor", greatest_common_divisor(x, y))
    print("is prime rabin miller", is_prime_rabin_miller(x))
    z = 1234567890
    print("pollard rho factorisation", pollard_rho_factorisation(z, 1))
    f, c1, c2, c3 = pollard_rho_factorisation(z, 1)
    f.sort()
    print("phi", phi(f))
    print("inverse prime modulo", inverse_prime_modulo(5, 7))
    print("inverse modulo", inverse_modulo(5, 2, 6))
    print("quadratic residue", is_quadratiqc_residue(4, 7))
    print("quadratic residue", is_quadratiqc_residue(3, 7))

# def find_prime_3_equiv_4():
