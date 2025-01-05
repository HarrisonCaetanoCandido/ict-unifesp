"""
Nome: Harrison Caetano Candido
RA: 156264
Turma:  IB
"""

# implemento um insertion sort
def growing(l):
    i = 1
    while i < len(l):
        key = l[i]
        j = i - 1

        while j > -1 and key < l[j]:
            l[j + 1] = l[j]
            j -= 1

        l[j + 1] = key
        i += 1

l = [10, 9, 8, 7, 6 ,5 ,4]

growing(l)
print(l)
