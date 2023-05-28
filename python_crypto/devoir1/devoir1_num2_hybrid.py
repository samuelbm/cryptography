import numpy as np
from devoir1_num2_utils import *
from prime_utils import *

ciphertext = get_ciphertext(27)
e_index = from_letter_to_index('E')
t_index = from_letter_to_index('T')
p_index = from_letter_to_index('P')
q_index = from_letter_to_index('Q')
n = 26

y = np.mod(p_index - q_index + n, n)
y_inverse = compute_inverse(y, n)
x = y_inverse * np.mod(e_index - t_index + n, n)
a = compute_inverse(x, n)
b = np.mod(p_index - e_index * a + 1000*n, n)

decrypted = decrypt_using_affine_transformation(ciphertext, a, b, n)

print("a: {}, b: {}".format(a, b))
print(decrypted)
