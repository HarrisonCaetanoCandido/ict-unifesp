"""
Nome: Harrison Caetano Candido
RA: 156264
Turma:  IB
"""

def situacao_aluno():
    name = input("Digite o nome: ")
    ra = input("Digite o RA: ")
    mF = float(input("Digite a média final: "))

    if(mF >= 6):
        sF = "Aprovado"
    else:
        sF = "Reprovado"
    
    d = {}
    d['Nome'] = name
    d['RA'] = ra
    d['Média Final'] = mF
    d['Situação Final'] = sF

    return d

d = situacao_aluno()
print(d)