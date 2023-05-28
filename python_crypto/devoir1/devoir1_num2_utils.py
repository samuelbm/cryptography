import numpy as np

def string_to_list(string):
    list = []
    for index in range(len(string)):
        list.append(string[index])
    return list


def list_to_string(list):
    string = ""
    for char in list:
        string = string + char
    return string




def get_alphabet(number_of_letters: int) -> str:
    alphabet_string26 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    alphabet_string27 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "
    if number_of_letters == 26:
        return alphabet_string26
    elif number_of_letters == 27:
        return alphabet_string27
    else:
        print("get_alphabet not working")
        return ""


def get_frequencies(number_of_letters: int) -> np.array:
    alphabet_frequencies = np.array(
        [0.0642, 0.0127, 0.0218, 0.0317, 0.1031, 0.0208, 0.0152, 0.0467, 0.0575, 0.0008, 0.0049, 0.0321, 0.0198,
         0.0574, 0.0632, 0.0152, 0.0008, 0.0484, 0.0514, 0.0796, 0.0228, 0.0083, 0.0175, 0.0013, 0.0164, 0.0005,
         0.1859])
    if number_of_letters == 26:
        return alphabet_frequencies[0:26]/np.sum(alphabet_frequencies[0:26])
    elif number_of_letters == 27:
        return alphabet_frequencies
    else:
        print("get_frequencies not working")
        return []



def get_ciphertext(number_of_letters: int) -> str:
    ciphertext_string = "LRIPUNAI JRDANMJ QCNAJTRQQPI QKCHXDK WCPVXPABZ JPMPBQREP WNIRAD BKNAAPMJ KNEP UPPA JKHLA "\
                        "QH OCHERIP N BPCQNRA IPDCPP HW RAKPCPAQ TXMQRONQK IREPCJRQZ JRABP TNAZ CPOMRBNJ HW QKP JNTP "\
                        "QCNAJTRQQPIJR DANM NCCREP NQ QKP CPBPREPC"
    if number_of_letters == 26:
        return ciphertext_string.replace(" ", "")
    elif number_of_letters == 27:
        return ciphertext_string
    else:
        print("get_ciphertext not working")
        return ""


def get_affine_transform_alphabet(a, b, n) -> str:
    alphabet = get_alphabet(n)
    transform_alphabet = []
    for index in range(len(alphabet)):
        transform_index = np.mod(a * index + b, n)
        letter_transform = alphabet[transform_index]
        transform_alphabet.append(letter_transform)
    return transform_alphabet


def decrypt_using_affine_transformation(ciphertext, a, b, n):
    alphabet = get_alphabet(n)
    transform_alphabet = get_affine_transform_alphabet(a, b, n)
    decrypted_word = ""
    for letter in ciphertext:
        if letter == ' ':
            decrypted_letter = ' '
        else:
            index = transform_alphabet.index(letter)
            decrypted_letter = alphabet[index]
        decrypted_word += decrypted_letter
    return decrypted_word

#def from_index_to_digram(index):
#     letter1_index = int(np.floor(index/26))
#     letter2_index = int(np.mod(index, 26))
#     digram = ""
#     digram += from_index_to_letter(letter1_index)
#     digram += from_index_to_letter(letter2_index)
#     return digram
#
# def from_digram_to_index(digram):
#     letter1_index = from_letter_to_index(digram[0])
#     letter2_index = from_letter_to_index(digram[1])
#     digram_index = letter1_index*26 + letter2_index
#     return digram_index
#
# def get_digrams_list_and_frequencies():
#     digrams_list = []
#     digrams_frequencies = []
#     for i in range(26*26):
#         digram = from_index_to_digram(i)
#         digrams_list.append(digram)
#         digrams_frequencies.append(0)
#     return digrams_list, digrams_frequencies
#
# def is_character_space(character):
#     return character == " "
#
# def is_digram_space_free(digram):
#     is_character1_space = is_character_space(digram[0])
#     is_character2_space = is_character_space(digram[1])
#     return not is_character1_space and not is_character2_space
#
#
#
# def analayse_digrams_in_cyphertext(ciphertext: str):
#     digrams_list, digrams_frequencies = get_digrams_list_and_frequencies()
#     for ciphertext_index in range(len(ciphertext)-1):
#         digram = ciphertext[ciphertext_index:ciphertext_index+2]
#         if is_digram_space_free(digram):
#             digram_index = from_digram_to_index(digram)
#             digrams_frequencies[digram_index] += 1
#     return digrams_list, digrams_frequencies