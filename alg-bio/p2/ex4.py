# 5 - Crie uma matriz de zeros de tamanho 10x10 e adicione uma borda de
# valor 1.

import numpy as np

m = np.zeros((10,10))
print(m)

for i in range(0, 10):
    # (0,n)
    m[0,i] = 1
    # (n, 0)
    m[i, 0] = 1
    # (10,n)
    m[9,i] = 1
    # (10,10)
    m[i,9] = 1
    
print(m)