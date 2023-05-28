import numpy as np


def compute_entropy(x_probabilities: np.array) -> float:
    x_entropy = 0
    for probability in x_probabilities:
        x_entropy = x_entropy - probability * np.log2(probability)
    return x_entropy

def compute_conditionnal_entropy(y_knowing_x_probabilities: np.matrix, x_probabilities: np.matrix) -> float:
    conditionnal_entropy = 0
    m, n = y_knowing_x_probabilities.shape
    for j in range(m):
        for i in range(n):
            x_probability = x_probabilities[i]
            y_knowing_x_probability = y_knowing_x_probabilities[j, i]
            if y_knowing_x_probability > 1e-6:
                xy_probability = x_probability * y_knowing_x_probability
                conditionnal_entropy += -xy_probability * np.log2(y_knowing_x_probability)
    return conditionnal_entropy

def compute_ciphertext_probabilities(data) -> np.array:
    message_probabilities = np.array(data[0])
    key_probabilities = np.array(data[1])
    ciphertext_matrix = np.matrix(data[2])
    ciphertext_probabilities = np.zeros(np.max(ciphertext_matrix))
    m, n = ciphertext_matrix.shape
    for j in range(m):
        for i in range(n):
            index = ciphertext_matrix[j, i] - 1
            ciphertext_probabilities[index] += message_probabilities[j] * key_probabilities[i]
    return ciphertext_probabilities

def compute_transition_matrix_message_knowing_ciphertext(data) -> np.matrix:
    message_probabilities = np.array(data[0])
    key_probabilities = np.array(data[1])
    ciphertext_matrix = np.matrix(data[2])
    ciphertext_probabilities = compute_ciphertext_probabilities(data)
    message_knowing_ciphertext = np.zeros((message_probabilities.size, ciphertext_probabilities.size))
    m, n = ciphertext_matrix.shape
    for j in range(m):
        for i in range(n):
            ciphertext_index = ciphertext_matrix[j, i] - 1
            ciphertext_probability = ciphertext_probabilities[ciphertext_index]
            message_probability = message_probabilities[j]
            key_probability = key_probabilities[i]
            message_knowing_ciphertext_probability = message_probability * key_probability/ciphertext_probability
            message_knowing_ciphertext[j, ciphertext_index] += message_knowing_ciphertext_probability
    return message_knowing_ciphertext

def compute_transition_matrix_key_knowing_ciphertext(data) -> np.matrix:
    message_probabilities = np.array(data[0])
    key_probabilities = np.array(data[1])
    ciphertext_matrix = np.matrix(data[2])
    ciphertext_probabilities = compute_ciphertext_probabilities(data)
    key_knowing_ciphertext = np.zeros((key_probabilities.size, ciphertext_probabilities.size))
    m, n = ciphertext_matrix.shape
    for j in range(m):
        for i in range(n):
            ciphertext_index = ciphertext_matrix[j, i] - 1
            ciphertext_probability = ciphertext_probabilities[ciphertext_index]
            message_probability = message_probabilities[j]
            key_probability = key_probabilities[i]
            key_knowing_ciphertext_probability = message_probability * key_probability / ciphertext_probability
            key_knowing_ciphertext[i, ciphertext_index] += key_knowing_ciphertext_probability
    return key_knowing_ciphertext



#data problem
message_probabilities   = np.array([1 / 3, 1 / 2, 1 / 6])
key_probabilities       = np.array([1 / 3, 1 / 3, 1 / 3])
ciphertext_matrix       = np.matrix([[1, 2, 3], [2, 3, 4], [3, 4, 1]])
data = [message_probabilities, key_probabilities, ciphertext_matrix]

#computing basics intermediate values
ciphertext_probabilities = compute_ciphertext_probabilities(data)
message_knowing_ciphertext              = compute_transition_matrix_message_knowing_ciphertext(data)
key_knowing_ciphertext_probabilities    = compute_transition_matrix_key_knowing_ciphertext(data)
ciphertext_probabilities                = compute_ciphertext_probabilities(data)
message_knowing_ciphertext_matrix   = compute_transition_matrix_message_knowing_ciphertext(data)
key_knowing_ciphertext_matrix       = compute_transition_matrix_key_knowing_ciphertext(data)


#computing problem answers
messages_entropy        = compute_entropy(message_probabilities)
keys_entropy            = compute_entropy(key_probabilities)
ciphertext_entropy      = compute_entropy(ciphertext_probabilities)
message_equivocation    = compute_conditionnal_entropy(message_knowing_ciphertext_matrix, ciphertext_probabilities)
key_equivocation        = compute_conditionnal_entropy(key_knowing_ciphertext_probabilities, ciphertext_probabilities)
print("H(M)=   ", messages_entropy, "[sh]")
print("H(K)=   ", keys_entropy, "[sh]")
print("H(C)=   ", ciphertext_entropy, "[sh]")
print("H(M|C)= ", message_equivocation, "[sh]")
print("H(K|C)= ", key_equivocation, "[sh]")
