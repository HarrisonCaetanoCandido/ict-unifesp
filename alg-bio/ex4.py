"""
Nome: Harrison Caetano Candido
RA: 156264
Turma:  IB
"""

import math

def fatorial(n):
    if(n < 1):
        return 1
    
    f = n * fatorial(n - 1)
    print(f)
    return f

t = float(input("Digite o valor de t: "))
cosh = 0

for n in range(20):
    cosh += (1/fatorial(2 * n)) * t**(2*n)

sinh = - 1 + cosh**2

print("cosh^2: ", cosh**2)
print("cosh: ", cosh)
print("sinh^2: ", math.sqrt(sinh))
print("sinh: ", sinh)