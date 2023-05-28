import numpy as np


def from_hex_symbol_to_4_bits_list(hex_symbol: str) -> np.array:
    hex_symbols_list = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
    index = hex_symbols_list.index(hex_symbol)
    vector_4bits_list = np.array([(index >> (3 - i)) & 1 for i in range(4)])
    return vector_4bits_list


def from_4_bits_list_to_hex_symbol(vector_4bits_list: np.array) -> str:
    hex_symbols_list = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
    index = np.sum([vector_4bits_list[i] << (3 - i) for i in range(4)])
    hex_symbol = hex_symbols_list[index]
    return hex_symbol


def from_hex16string_to_bits64vector(hex16string: str) -> np.array:
    vector_64bits = []
    for index in range(16):
        vector_64bits.extend(from_hex_symbol_to_4_bits_list(hex16string[index]))
    return np.array(vector_64bits)


def from_bits64vector_to_hex16string(bits64vector: np.array) -> str:
    hex16string = ""
    for index in range(16):
        hex16string += from_4_bits_list_to_hex_symbol(bits64vector[4 * index:4 * index + 4])
    return hex16string


def initial_permutation(vector_in64: np.array) -> np.array:
    transformation_vector = np.array([58, 50, 42, 34, 26, 18, 10, 2,
                                      60, 52, 44, 36, 28, 20, 12, 4,
                                      62, 54, 46, 38, 30, 22, 14, 6,
                                      64, 56, 48, 40, 32, 24, 16, 8,
                                      57, 49, 41, 33, 25, 17, 9, 1,
                                      59, 51, 43, 35, 27, 19, 11, 3,
                                      61, 53, 45, 37, 29, 21, 13, 5,
                                      63, 55, 47, 39, 31, 23, 15, 7]) - 1
    vector_out64 = vector_in64[transformation_vector]
    return vector_out64


def final_permutation(vector_in64: np.array) -> np.array:
    transformation_vector = np.array([40, 8, 48, 16, 56, 24, 64, 32,
                                      39, 7, 47, 15, 55, 23, 63, 31,
                                      38, 6, 46, 14, 54, 22, 62, 30,
                                      37, 5, 45, 13, 53, 21, 61, 29,
                                      36, 4, 44, 12, 52, 20, 60, 28,
                                      35, 3, 43, 11, 51, 19, 59, 27,
                                      34, 2, 42, 10, 50, 18, 58, 26,
                                      33, 1, 41, 9, 49, 17, 57, 25]) - 1
    vector_out64 = vector_in64[transformation_vector]
    return vector_out64


def expansion_permutation_e(R32: np.array) -> np.array:
    transformation_vector = np.array([32, 1, 2, 3, 4, 5,
                                      4, 5, 6, 7, 8, 9,
                                      8, 9, 10, 11, 12, 13,
                                      12, 13, 14, 15, 16, 17,
                                      16, 17, 18, 19, 20, 21,
                                      20, 21, 22, 23, 24, 25,
                                      24, 25, 26, 27, 28, 29,
                                      28, 29, 30, 31, 32, 1]) - 1
    vector_out48 = R32[transformation_vector]
    return vector_out48


def permutation_p(sbox32: np.array) -> np.array:
    transformation_vector = np.array([16, 7, 20, 21,
                                      29, 12, 28, 17,
                                      1, 15, 23, 26,
                                      5, 18, 31, 10,
                                      2, 8, 24, 14,
                                      32, 27, 3, 9,
                                      19, 13, 30, 6,
                                      22, 11, 4, 25]) - 1
    vector_out32 = sbox32[transformation_vector]
    return vector_out32


def sbox(vector_in48bits: np.array) -> np.array:
    sboxes = np.matrix(
        [[14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3,
          8, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6,
          13],
         [15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11,
          5, 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14,
          9],
         [10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15,
          1, 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2,
          12],
         [7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14,
          9, 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2,
          14],
         [2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8,
          6, 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5,
          3],
         [12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3,
          8, 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8,
          13],
         [4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8,
          6, 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3,
          12],
         [13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9,
          2, 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6,
          11]])

    vector_out32bits = []
    for index in range(8):
        vector6bits = vector_in48bits[6 * index:6 * index + 6]
        weight = [32, 8, 4, 2, 1, 16]
        address = np.sum([vector6bits[i] * weight[i] for i in range(6)])
        value = sboxes[index, address]
        vector4bits = [(value >> (3 - i)) & 1 for i in range(4)]
        vector_out32bits.extend(vector4bits)
    return np.array(vector_out32bits)


def permute_PC1(key64: np.array) -> np.array:
    PC1 = np.array([57, 49, 41, 33, 25, 17, 9,
                    1, 58, 50, 42, 34, 26, 18,
                    10, 2, 59, 51, 43, 35, 27,
                    19, 11, 3, 60, 52, 44, 36,
                    63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 38, 30, 22,
                    14, 6, 61, 53, 45, 37, 29,
                    21, 13, 5, 28, 20, 12, 4]) - 1
    key56 = key64[PC1]
    return key56


def permute_PC2(key56: np.array) -> np.array:
    PC2 = np.array([14, 17, 11, 24, 1, 5,
                    3, 28, 15, 6, 21, 10,
                    23, 19, 12, 4, 26, 8,
                    16, 7, 27, 20, 13, 2,
                    41, 52, 31, 37, 47, 55,
                    30, 40, 51, 45, 33, 48,
                    44, 49, 39, 56, 34, 53,
                    46, 42, 50, 36, 29, 32]) - 1
    key48 = key56[PC2]
    return key48


def perform_shift(cd28: np.array, key_index) -> np.array:
    left_shift = np.array([1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1])
    shift_cumsum = np.cumsum(left_shift)
    shifting = shift_cumsum[key_index - 1]
    shifting_index = [np.mod(i + shifting, 28) for i in range(28)]
    cd28_shifted = cd28[shifting_index]
    return np.array(cd28_shifted)


def f(R32: np.array, key48: np.array) -> np.array:
    extender48 = expansion_permutation_e(R32)
    sbox_in48 = extender48 ^ key48
    sbox_out32 = sbox(sbox_in48)
    p_out32 = permutation_p(sbox_out32)
    return np.array(p_out32)


def compute_next_key(key64: np.array, key_index: np.array) -> np.array:
    key56 = permute_PC1(key64)
    c28, d28 = key56[0:28], key56[28:56]
    c28 = perform_shift(c28, key_index)
    d28 = perform_shift(d28, key_index)
    key56 = np.concatenate((c28, d28))
    key48 = permute_PC2(key56)
    return key48, c28, d28


def DES_ECB_ENCRYPT(block_hexa16: str, key_hexa16: str) -> str:
    block_64bits = from_hex16string_to_bits64vector(block_hexa16)
    key_64bits = from_hex16string_to_bits64vector(key_hexa16)
    block64 = initial_permutation(block_64bits)
    L32, R32 = block64[0:32], block64[32:64]
    for index in range(16):
        key48, c28, d28 = compute_next_key(key_64bits, index + 1)
        L32, R32 = R32, L32 ^ f(R32, key48)
        print_line(index, L32, R32, key48, c28, d28)
    block64 = np.concatenate((R32, L32))
    block64 = final_permutation(block64)
    return from_bits64vector_to_hex16string(block64)


def DES_ECB_DECRYPT(block_hexa16: str, key_hexa16: str) -> str:
    block_64bits = from_hex16string_to_bits64vector(block_hexa16)
    key_64bits = from_hex16string_to_bits64vector(key_hexa16)
    block64 = initial_permutation(block_64bits)
    L32, R32 = block64[0:32], block64[32:64]
    for index in range(16):
        key48, c28, d28 = compute_next_key(key_64bits, 16 - index)
        L32, R32 = R32, L32 ^ f(R32, key48)
        print_line(index, L32, R32, key48, c28, d28)
    block64 = np.concatenate((R32, L32))
    block64 = final_permutation(block64)
    return from_bits64vector_to_hex16string(block64)


def hamming_distance(X: str, Y: str) -> int:
    X64 = from_hex16string_to_bits64vector(X)
    Y64 = from_hex16string_to_bits64vector(Y)
    return np.sum(X64 ^ Y64)


def list_to_bin(l: list) -> str:
    binary = ""
    for b in l:
        binary += str(b)
    return binary

def print_line(i, Li, Ri, Ki, Ci, Di):
    Li = list_to_bin(Li)
    Ri = list_to_bin(Ri)
    Ki = list_to_bin(Ki)
    Ci = list_to_bin(Ci)
    Di = list_to_bin(Di)
    i = "0" + str(i) if i<10 else str(i)
    print("L{}: {}, R{}: {}, K{}: {}, C{}: {}, D{}: {}".format(i, Li, i, Ri, i, Ki, i, Ci, i, Di))


def print_message_key_ciphertext(message_name, message, key_name, key, ciphertext_name, ciphertext, decrypt_name,
                                 decrypt):
    print("{}: {}, {}: {}, {}: {}, {}: {}".format(message_name, message, key_name, key, ciphertext_name, ciphertext,
                                                  decrypt_name, decrypt))


def print_hamming(name1, name2, distance):
    print("D({},{})={}".format(name1, name2, distance))


# message_string = "0123456789ABCDEF"
# key_string = "133457799BBCDFF1"
# ciphertext_known = "85E813540F0AB405"
# encrypted_block = DES_ECB_ENCRYPT(message_string, key_string)
# decrypted_block = DES_ECB_DECRYPT(encrypted_block, key_string)
# print("Test pour s'assurer que la fonction est valide")
# print_hex("message", message_string)
# print_hex("clé", key_string)
# print_hex("ciphertext connu", ciphertext_known)
# print_hex("message encrypté", encrypted_block)
# print_hex("message décrypté", decrypted_block)


M1 = "0000000000000000"
K1 = "08192A3B4C5D6E7F"
M2 = "85B62C9146F283DB"
K2 = "79BCC147527F5BA7"
K3 = "79BCC147727F5BA7"
M3 = "85B62C9156F283DB"


print("numéro A")
print("Encrypting C1 = DES(M1, K1)")
C1 = DES_ECB_ENCRYPT(M1, K1)
print("Decrypting D1 = DES(C1, K1)")
D1 = DES_ECB_DECRYPT(C1, K1)
print_message_key_ciphertext("M1", M1, "K1", K1, "C1", C1, "D1", D1)

print("numéro B")
print("Encrypting C2 = DES(M2, K2)")
C2 = DES_ECB_ENCRYPT(M2, K2)
print("Decrypting D2 = DES(C2, K2)")
D2 = DES_ECB_DECRYPT(C2, K2)
print_message_key_ciphertext("M2", M2, "K2", K2, "C2", C2, "D2", D2)

print("numéro C")
print("Encrypting C3 = DES(M2, K3)")
C3 = DES_ECB_ENCRYPT(M2, K3)
print("Decrypting D3 = DES(C3, K3)")
D3 = DES_ECB_DECRYPT(C3, K3)
print_message_key_ciphertext("M2", M2, "K3", K3, "C3", C3, "D3", D3)
M22_dist = hamming_distance(M2, M2)
K23_dist = hamming_distance(K2, K3)
C23_dist = hamming_distance(C2, C3)
print_hamming("M2", "M2", M22_dist)
print_hamming("K2", "K3", K23_dist)
print_hamming("C2", "C3", C23_dist)

print("numéro D")
print("Encrypting C4 = DES(M3, K2)")
C4 = DES_ECB_ENCRYPT(M3, K2)
print("Decrypting D4 = DES(C4, K2)")
D4 = DES_ECB_DECRYPT(C4, K2)
print_message_key_ciphertext("M3", M3, "K2", K2, "C4", C4, "D4", D4)
M23_dist = hamming_distance(M2, M3)
K22_dist = hamming_distance(K2, K2)
C24_dist = hamming_distance(C2, C4)
print_hamming("M2", "M3", M23_dist)
print_hamming("K2", "K2", K22_dist)
print_hamming("C2", "C4", C24_dist)
