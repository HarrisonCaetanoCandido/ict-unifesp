# 6 - Crie um array unidimensional com valores aleatórios e encontre os
# valores únicos e suas contagens.

import numpy as np

m = np.random.randint(0, np.random.randint(1,10), (np.random.randint(1,10)))

print(m)

print(np.unique(m, return_counts=True))