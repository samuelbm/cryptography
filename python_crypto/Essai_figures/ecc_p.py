from large import *
import time
from ecc import *
from system_file import *


def ecc_p_keygen(curve, size):
    a, b, p, G = curve
    kb, count = find_random_number(size)
    Pb, count2 = ecc_multiplication(curve, G, kb)
    count.add_count(count2)
    string = "ecc keygen {}, kb: {}, Pbx: {}, Pby: {}, clock: {}, regs: {}, gates: {}"
    string = string.format(size, kb, Pb.px, Pb.py, count.clock, count.regs, count.gates)
    print(string)
    return kb, Pb, count, string


def ecc_p_encryption(curve, m, Pb, size):
    count = Count()
    a, b, p, G = curve
    find_Pm = False
    x = m << 20
    is_first_pass = True
    while not find_Pm:
        y2, count1 = ecc_compute_y2(curve, x)
        find_Pm, y, count2 = is_quadratiqc_residue(y2, p)
        x, count3 = addition(x, 1)
        if is_first_pass:
            is_first_pass = False
            count.add_count(count1)
            count.add_count(count2)
            count.add_count(count3)
        else:
            count.time(count1.clock)
            count.power(count1.gates)
            count.time(count2.clock)
            count.power(count2.gates)
            count.time(count3.clock)
            count.power(count3.gates)
    Pm = ecc_point(x, y, False)

    k, count4 = find_random_number(size)
    kG, count5 = ecc_multiplication(curve, G, k)
    kPb, count6 = ecc_multiplication(curve, Pb, k)
    PmkPb, count7 = ecc_addition(curve, Pm, kPb)
    count.add_count(count4)
    count.add_count(count5)
    count.add_count(count6)
    count.add_count(count7)
    string = "ecc encryption {}, m: {}, Pmx: {}, Pmy: {}, kGx: {}, kGy: {}, PmkPbx: {}, PmkPby: {}, clock: {}, regs: {}, gates: {}"
    string = string.format(size, m, Pm.px, Pm.py, kG.px, kG.py, PmkPb.px, PmkPb.py, count.clock, count.regs,
                           count.gates)
    print(string)
    return [kG, PmkPb], count, string


def ecc_p_decryption(curve, C, kb):
    count = Count()
    kG, PmkPb = C
    kGkb, count1 = ecc_multiplication(curve, kG, kb)
    Pm, count2 = ecc_substraction(curve, PmkPb, kGkb)
    count.add_count(count1)
    count.add_count(count2)
    m = Pm.px >> 20
    string = "decryption, m: {}, kGx: {}, kGy: {}, PmkPbx: {}, PmkPby: {}, clock: {}, regs: {}, gates: {}"
    string = string.format(m, kG.px, kG.py, PmkPb.px, PmkPb.py, count.clock, count.regs, count.gates)
    print(string)
    return Pm, count, string


def ecc_p_192(tries):
    p = 6277101735386680763835789423207666416083908700390324961279
    a = p - 3
    b = 2455155546008943817740293915197451784769108058161191238065
    Gx = 602046282375688656758213480587526111916698976636884684818
    Gy = 174050332293622031404857552280219410364023488927386650641
    curve = ecc_create_curve(a, b, p, Gx, Gy)
    path = "./data/ecc_p_192.txt"
    random.seed(1234)
    m = 123
    size = 192
    for i in range(tries):
        kb, Pb, count, string_keygen = ecc_p_keygen(curve, size)
        C, count, string_encryption = ecc_p_encryption(curve, m, Pb, size)
        Pm, count, string_decryption = ecc_p_decryption(curve, C, kb)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)

# def ecc_p_224(tries):
#     p = 26959946667150639794667015087019630673557916260026308143510066298881
#     a = 26959946667150639794667015087019630673557916260026308143510066298878
#     b = 18958286285566608000408668544493926415504680968679321075787234672564
#     Gx = 19277929113566293071110308034699488026831934219452440156649784352033
#     Gy = 19926808758034470970197974370888749184205991990603949537637343198772


def ecc_p_256(tries):
    p = 115792089210356248762697446949407573530086143415290314195533631308867097853951
    a = 115792089210356248762697446949407573530086143415290314195533631308867097853948
    b = 41058363725152142129326129780047268409114441015993725554835256314039467401291
    Gx = 48439561293906451759052585252797914202762949526041747995844080717082404635286
    Gy = 36134250956749795798585127919587881956611106672985015071877198253568414405109
    curve = ecc_create_curve(a, b, p, Gx, Gy)
    path = "./data/ecc_p_256.txt"
    random.seed(1234)
    m = 123
    size = 256
    for i in range(tries):
        kb, Pb, count, string_keygen = ecc_p_keygen(curve, size)
        C, count, string_encryption = ecc_p_encryption(curve, m, Pb, size)
        Pm, count, string_decryption = ecc_p_decryption(curve, C, kb)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


def ecc_p_384(tries):
    p = 39402006196394479212279040100143613805079739270465446667948293404245721771496870329047266088258938001861606973112319
    a = 39402006196394479212279040100143613805079739270465446667948293404245721771496870329047266088258938001861606973112316
    b = 27580193559959705877849011840389048093056905856361568521428707301988689241309860865136260764883745107765439761230575
    Gx = 26247035095799689268623156744566981891852923491109213387815615900925518854738050089022388053975719786650872476732087
    Gy = 8325710961489029985546751289520108179287853048861315594709205902480503199884419224438643760392947333078086511627871
    curve = ecc_create_curve(a, b, p, Gx, Gy)
    path = "./data/ecc_p_384.txt"
    random.seed(1234)
    m = 123
    size = 384
    for i in range(tries):
        kb, Pb, count, string_keygen = ecc_p_keygen(curve, size)
        C, count, string_encryption = ecc_p_encryption(curve, m, Pb, size)
        Pm, count, string_decryption = ecc_p_decryption(curve, C, kb)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


def ecc_p_521(tries):
    p = 6864797660130609714981900799081393217269435300143305409394463459185543183397656052122559640661454554977296311391480858037121987999716643812574028291115057151
    a = 6864797660130609714981900799081393217269435300143305409394463459185543183397656052122559640661454554977296311391480858037121987999716643812574028291115057148
    b = 1093849038073734274511112390766805569936207598951683748994586394495953116150735016013708737573759623248592132296706313309438452531591012912142327488478985984
    Gx = 2661740802050217063228768716723360960729859168756973147706671368418802944996427808491545080627771902352094241225065558662157113545570916814161637315895999846
    Gy = 37571800257700204635455072244911836035944551347697624866945223956010636355557333899035866342650378575221277268886182704643828850020061383251826928984446519
    curve = ecc_create_curve(a, b, p, Gx, Gy)
    path = "./data/ecc_p_521.txt"
    random.seed(1234)
    m = 123
    size = 521
    for i in range(tries):
        kb, Pb, count, string_keygen = ecc_p_keygen(curve, size)
        C, count, string_encryption = ecc_p_encryption(curve, m, Pb, size)
        Pm, count, string_decryption = ecc_p_decryption(curve, C, kb)
        append_file(path, string_keygen)
        append_file(path, string_encryption)
        append_file(path, string_decryption)


if __name__ == "__main__":
    pass
    # ecc_p_192(10)
    # ## ecc_p_224(10)
    # ecc_p_256(10)
    # ecc_p_384(10)
    # ecc_p_521(10)

    # curve = ecc_create_curve(1, 6, 11, 2, 7)
    # a, b, p, G = curve


