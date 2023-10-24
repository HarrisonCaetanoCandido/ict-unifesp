def test_polynomial():
    polynomial = []
    number = []
    got_apotency = 0
    not_handle_polynomial = "13x**2+91x-5"

    for character in not_handle_polynomial:
        # -1 é numero ou '-', 0 é *, 1 é caractere alfabético
        if alfabetic_verification(character) == 0:
            got_apotency += 1
            was_anumber = 0

        # caso em que queremos ler 5x**2 + 2x, no caso ignorar o numero seguido de **
        elif alfabetic_verification(character) == -1 and got_apotency == 2:
            got_apotency = 0
            # coloco o numero lido  na primeira posicao da lista
            new_number = ''.join(number)
            new_number = float(new_number)
            polynomial.append(new_number)
            # limpo a lista
            number.clear()
            # pulo a potencia atual
            continue

        if alfabetic_verification(character) == -1 or alfabetic_verification(character) == 2 and got_apotency == 0:
            number.append(character)
            # confirma que o caractere nterior a um sinal '+' ou '-' era um digito
            was_anumber = 1
        
        if alfabetic_verification(character) == 2 and was_anumber == 1:
             # coloco o numero lido  na primeira posicao da lista
            new_number = ''.join(number)
            new_number = float(new_number)
            polynomial.append(new_number)
            # limpo a lista
            number.clear()
            was_anumber = 0
            
    assert polynomial[0] == 13
    assert polynomial[1] == 91
    assert polynomial[2] == -5

def alfabetic_verification(character):
    if character == 'x' or character == 'X' or character == 'a' or character == 'b' or character == 'c' or character == 'd' or character == 'e' or character == 'f' or character == 'g' or character == 'h' or character == 'i' or character == 'j' or character == 'k' or character == 'l' or character == 'm' or character == 'n' or character == 'o' or character == 'p' or character == 'q' or character == 'r' or character == 's' or character == 't' or character == 'u' or character == 'v' or character == 'w' or character == 'y' or character == 'z' or character == 'A' or character == 'B' or character == 'C' or character == 'D' or character == 'E' or character == 'F' or character == 'G' or character == 'H' or character == 'I' or character == 'J' or character == 'K' or character == 'L' or character == 'M' or character == 'N' or character == 'O' or character == 'P' or character == 'Q' or character == 'R' or character == 'S' or character == 'T' or character == 'U' or character == 'V' or character == 'W' or character == 'Y' or character == 'Z':
        return 1
    if character == '*':
        return 0
    if character == '-' or character == '+':
        return 2
    return -1