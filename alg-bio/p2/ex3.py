# 3- Crie um array unidimensional com valores aleatórios e calcule a
# diferença entre cada elemento e o próximo elemento.

import numpy as np

m = np.random.randint(0,10, (np.random.randint(0,10)))
print(m)
j = 1
for index, i in enumerate(m):
    if(index + 1 >= m.size):
        j = 0
    print("value:", i, " difference", m[index+j] - i)