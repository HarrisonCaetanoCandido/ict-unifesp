"""
Nome: Harrison Caetano Candido
RA: 156264
Turma:  IB
"""

def imc_f(l):
    name = input("Digite o nome: ")
    sex = input("Digite o sexo: ")
    weight = float(input("Digite o peso: "))
    height = int(input("Digite a altura: ")) # centimetros

    imc = weight/(height*height) * 10000

    imc = round(imc, 4)

    if(imc <24.9):
        status = "Peso normal"
    if(imc >=25 and imc <= 29.9):
        status = "Sobrepeso"
    if(imc > 30):
        status = "Obesidade"

    d = {}
    d['Nome'] = name
    d['Sexo'] = sex
    d['Peso'] = weight
    d['Altura'] = height
    d['IMC'] = imc
    d['Status'] = status

    l.append(d)   

# main
pacients = int(input("Digite quantos pacientes deseja analisar: "))
l = []

for i in range(pacients):
    imc_f(l)
    print(i)
    print(l[i])

