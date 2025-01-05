# 1- Crie um array unidimensional com valores aleatórios e imprima o
# valor médio e a mediana.

import numpy as np

m = np.random.randint(0,10, (np.random.randint(0,10)))
print(m)
print(np.mean(m))
print(np.median(m))