"""
Nome: Harrison Caetano Candido
RA: 156264
Turma:  IB
"""

def fatorial(n):
    if(n < 1):
        return 1
    # 4! = 4 * (4 - 1) * (3 - 1) * (2 - 1) * (1 - 1)
    f = n * fatorial(n - 1)
    print(f)
    return f

n = int(input("Digite um número: "))

fatorial(n)