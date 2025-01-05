# Crie um array unidimensional com valores aleatórios e encontre o
# índice do valor mais próximo de um valor fornecido

import numpy as np

value = int(input("Digite algum valor aleatório: "))

def random_search(value):
    m = np.random.randint(0,10, (np.random.randint(0,10)))
    print(m)
    j = 0
    for index, i in enumerate(m):
        print(i)
        if(i == value):
            print("Index de ", value, "encontrado em: ", index)
            j = 1
            
    if(j == 0):
        print("Nao encontrado")
    
random_search(value)