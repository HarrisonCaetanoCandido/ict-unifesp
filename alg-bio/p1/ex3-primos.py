"""
Nome: Harrison Caetano Candido
RA: 156264
Turma:  IB
"""

for i in range(1, 100):
    divisivel = 0
    for j in range(1, 100):
        # ou seja, para cada inteiro que o resto da divisao de i por j for zero
        # o resultado sera a contagem como um divisivel
        if(i % j == 0):
            divisivel += 1

    # a logica é que se passar de dois divisiveis entao o numero é composto 
    if(divisivel == 2):
        print(i)