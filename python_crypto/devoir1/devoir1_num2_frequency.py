import numpy as np
from devoir1_num2_utils import *
from prime_utils import *


def compute_ciphertext_relative_frequencies(ciphtertext, ciphertext_alphabet):
    frequencies = []
    ciphertext_size = len(ciphtertext)
    ciphtertext_alphabet_size = len(ciphertext_alphabet)
    for index in range(ciphtertext_alphabet_size):
        letter_relative_frequency = ciphtertext.count(ciphertext_alphabet[index]) / ciphertext_size
        frequencies.append(letter_relative_frequency)
    return np.array(frequencies)


def swap(list, index_a, index_b):
    storage = list[index_a]
    list[index_a] = list[index_b]
    list[index_b] = storage


def order_from_most_frequent_to_least_frequent(alphabet, probabilities):
    for index_a in range(len(alphabet)):
        max_probability = probabilities[index_a]
        max_probability_index = index_a
        for index_b in range(index_a + 1, len(alphabet)):
            if probabilities[index_b] > max_probability:
                max_probability = probabilities[index_b]
                max_probability_index = index_b
        swap(probabilities, index_a, max_probability_index)
        swap(alphabet, index_a, max_probability_index)


def reorder_most_likely(ciphertext, ciphertext_alphabet: str, alphabet: str) -> list:
    decrypted = []
    for index in range(len(ciphertext)):
        ciphertext_letter = ciphertext[index]
        ciphertext_alphabet_index = ciphertext_alphabet.index(ciphertext_letter)
        alphabet_letter = alphabet[ciphertext_alphabet_index]
        decrypted.append(alphabet_letter)
    return decrypted


def print_comparaison(alphabet, alphabet_frequencies, ciphertext_alphabet, ciphertext_frequencies):
    print("Alphabet mapping")
    for i in range(len(alphabet)):
        if ciphertext_frequencies[i] > 0:
            letter = alphabet[i]
            cipher_letter = ciphertext_alphabet[i]
            letter_frequency = alphabet_frequencies[i]
            cipher_frequency = ciphertext_frequencies[i]
            formatted = "Letter : '{}', Cipher : '{}', letter frequency : {}, Cipher frequency : {}"
            print(formatted.format(letter, cipher_letter, letter_frequency, cipher_frequency))


def print_known_letters(known, decrypted):
    known_ciphertext = ""
    for letter_index in range(len(decrypted)):
        letter = decrypted[letter_index]
        if known.count(letter) > 0:
            known_ciphertext += letter
        else:
            known_ciphertext += "?"
    print("\nAttempt at Decrypting Ciphertext")
    print(list_to_string(decrypted))
    print(known_ciphertext)
    print()


def swap_ciphertext_letters(correct_letter, bad_letter, ciphertext_alphabet, ciphertext_frequencies, known, alphabet):
    known.append(correct_letter)
    correct_index = alphabet.index(correct_letter)
    bad_index = alphabet.index(bad_letter)
    swap(ciphertext_alphabet, correct_index, bad_index)
    swap(ciphertext_frequencies, correct_index, bad_index)
    print("We confirm '{}'->'{}'".format(bad_letter, correct_letter))

def second_round(known, alphabet, ciphertext_alphabet, alphabet_frequencies, ciphertext_frequencies):
    new_alphabet = []
    new_ciphertext_alphabet = []
    new_alphabet_frequencies = []
    new_ciphertext_frequencies = []
    for index in range(len(alphabet)):
        alphabet_letter = alphabet[index]
        if known.count(alphabet_letter) == 0:
            new_alphabet.append(alphabet[index])
            new_alphabet_frequencies.append(alphabet_frequencies[index])
            new_ciphertext_alphabet.append(ciphertext_alphabet[index])
            new_ciphertext_frequencies.append(ciphertext_frequencies[index])
    reorder_most_likely(new_ciphertext_alphabet, new_ciphertext_alphabet, new_alphabet)

    for index in range(len(new_alphabet)):
        alphabet_letter = new_alphabet[index]
        alphabet_index = alphabet.index(alphabet_letter)
        ciphertext_alphabet[alphabet_index] = new_ciphertext_alphabet[index]
        ciphertext_frequencies[alphabet_index] = new_ciphertext_frequencies[index]

    for i in range(len(alphabet)):
        if ciphertext_frequencies[i] > 0:
            letter = alphabet[i]
            cipher_letter = ciphertext_alphabet[i]
            letter_frequency = alphabet_frequencies[i]
            cipher_frequency = ciphertext_frequencies[i]
            formatted = "Letter : '{}', Cipher : '{}', letter frequency : {}, Cipher frequency : {}"
            print(formatted.format(letter, cipher_letter, letter_frequency, cipher_frequency))






if __name__ == "__main__":
    #ground_truth = string_to_list("WIDEBAND SIGNALS TRANSMITTED THROUGH FREQUENCY SELECTIVE FADING CHANNELS HAVE BEEN SHOWN TO PROVIDE A CERTAIN DEGREE OF INHERENT MULTIPATH DIVERSITY SINCE MANY REPLICAS OF THE SAME TRANSMITTEDSI GNAL ARRIVE AT THE RECEIVER")
    n = 27
    known = []
    alphabet = string_to_list(get_alphabet(n))
    ciphertext_alphabet = string_to_list(get_alphabet(n))
    alphabet_frequencies = get_frequencies(n)
    ciphertext = string_to_list(get_ciphertext(n))
    ciphertext_frequencies = compute_ciphertext_relative_frequencies(ciphertext, ciphertext_alphabet)
    print_known_letters(known, ciphertext)

    order_from_most_frequent_to_least_frequent(alphabet, alphabet_frequencies)
    order_from_most_frequent_to_least_frequent(ciphertext_alphabet, ciphertext_frequencies)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_comparaison(alphabet, alphabet_frequencies, ciphertext_alphabet, ciphertext_frequencies)
    swap_ciphertext_letters(' ', ' ', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('E', 'E', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('T', 'T', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('A', 'O', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('O', 'C', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('H', 'R', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('F', 'W', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('B', 'B', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('V', 'U', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('N', 'I', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('S', 'S', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('M', 'M', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('Y', 'P', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('I', 'C', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('D', 'R', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('R', 'C', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('G', 'W', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('L', 'C', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('C', 'C', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('W', 'U', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('U', 'U', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    swap_ciphertext_letters('P', 'P', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)
    swap_ciphertext_letters('Q', 'K', ciphertext_alphabet, ciphertext_frequencies, known, alphabet)
    decrypted = reorder_most_likely(ciphertext, ciphertext_alphabet, alphabet)
    print_known_letters(known, decrypted)

    second_round(known, alphabet, ciphertext_alphabet, alphabet_frequencies, ciphertext_frequencies)
