import numpy as np
from devoir1_num2_utils import *
from prime_utils import *
from PyDictionary import PyDictionary
import time

dictionary = PyDictionary()


def is_a_word(word_to_check):
    return dictionary.meaning(word_to_check, disable_errors=True) != None


def brute_force_affine_transformation(ciphertext_word: str, n: int) -> list:
    count = 0
    working_affiche_transformation = []
    for a in range(26):
        for b in range(26):
            count = count + 1
            if np.mod(count, 100) == 0:
                print("progression {}%".format(int(100 * count / 26 ** 2)))
            if gcd(a, n) == 1:
                for i in range(len(ciphertext_word)):
                    ciphertext_subword = ciphertext_word[0:i]
                    decrypted_word = decrypt_using_affine_transformation(ciphertext_subword, a, b, n)
                    if len(decrypted_word)>0 and is_a_word(decrypted_word):
                        maximum_subword_length = len(decrypted_word)
                        print("a: {}, b: {}, decrypted word: '{}', subword length: {}".
                              format(a, b, decrypted_word, maximum_subword_length))
                working_affiche_transformation.append((a, b, maximum_subword_length))
    print("progression 100%")
    return working_affiche_transformation

def get_affine_parameters_from_list(working_affiche_transformation: list):
    correct_subwords_list = [tuples[2] for tuples in working_affiche_transformation]
    maximum_index = correct_subwords_list.index(np.max(correct_subwords_list))
    a, b = working_affiche_transformation[maximum_index][0], working_affiche_transformation[maximum_index][1]
    return a, b

if __name__ == "__main__":
    #WIDEBANDSIGNALSTRANSMITTEDTHROUGHFREQUENCYSELECTIVEFADINGCHANNELSHAVEBEENSHOWNTOPROVIDEACERTAINDEGREEOFINHERENTMULTIPATHDIVERSITYSINCEMANYREPLICASOFTHESAMETRANSMITTEDSIGNALARRIVEATTHERECEIVER
    #a, b, n = (7, 13, 26)
    n = 26
    ciphertext = get_ciphertext(n)
    ciphertext_word = ciphertext[0:12]

    print("timer started")
    time_stamp_start = time.time()
    working_affiche_transformation = brute_force_affine_transformation(ciphertext_word, n)
    time_stamp_stop = time.time()
    print("Processing time: ", time_stamp_stop - time_stamp_start, "seconds")

    a, b = get_affine_parameters_from_list(working_affiche_transformation)
    decrypted_ciphertext = decrypt_using_affine_transformation(ciphertext, a, b, n)
    print(decrypted_ciphertext)






