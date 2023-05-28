import numpy as np

def from_octal_to_digit(octal: int) -> str:
    octals = ['0', '1', '2', '3', '4', '5', '6', '7']
    return octals[octal]

def from_digit_to_octal(digit: str) -> int:
    octals = ['0', '1', '2', '3', '4', '5', '6', '7']
    return octals.index(digit)

def from_string_to_int(string: str) -> int:
    total = 0
    for digit in string:
        total = 8*total + from_digit_to_octal(digit)
    return total

def from_int_to_string(value: int, nb_digit: int) -> str:
    digits = ""
    for i in range(nb_digit):
        index = nb_digit - i - 1
        octal = (value >> 3*index) & 7
        digits += from_octal_to_digit(octal)
    return digits

def encrypt_ciphertext(message:str, key:str)->str:
    ciphertext = ""
    key_int = from_string_to_int(key)
    for index in range(5):
        symbol = message[2*index:2*index+2]
        symbol_int = from_string_to_int(symbol)
        ciphertext_symbol_int = np.mod(symbol_int + key_int, 64)
        ciphertext += from_int_to_string(ciphertext_symbol_int, 2)
    return ciphertext

def decrypt_ciphertext(ciphertext:str, key:str)->str:
    message = ""
    key_int = from_string_to_int(key)
    for index in range(5):
        symbol = ciphertext[2*index:2*index+2]
        symbol_int = from_string_to_int(symbol)
        ciphertext_symbol_int = np.mod(symbol_int - key_int + 64, 64)
        message += from_int_to_string(ciphertext_symbol_int, 2)
    return message


key = "52"
message = "0011223344"
ciphertext = encrypt_ciphertext(message, key)
decrypted = decrypt_ciphertext(ciphertext, key)
print("clé: {}".format(key))
print("message: {}".format(message))
print("ciphertext: {}".format(ciphertext))
print("decrypted: {}".format(decrypted))