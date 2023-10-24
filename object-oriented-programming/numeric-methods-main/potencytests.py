import math

def test_one():
    error_string = "10**10"

    raised_to = 0
    base = []
    potency = []
    b_flag = p_flag = 0

    for character in error_string:
        if b_flag == 0 and character != "*" and character == "-" and raised_to < 2:
            # indica que a base é negativa
            b_flag = 1

        if p_flag == 0 and character != "*" and character == "-" and raised_to == 2:
            # indica que a potencia é negativa
            p_flag = 1

        # para a base antes de elevar
        if character != "*" and character != "-" and raised_to < 2:
            base.append(character)

        # para quando acharmos os asteriscos, servirão para indicar o momento que a potencia deve ser coletada
        if character == "*" and raised_to < 2:
            raised_to += 1
                
        # começa a coletar a potencia
        if character != "*" and character != "-" and raised_to == 2:
            potency.append(character)

    new_base = ''.join(base)
    new_potency = ''.join(potency)

    f_base = float(new_base)
    f_potency = float(new_potency)

    if b_flag == 0 and p_flag == 0:
        error = math.pow(f_base, f_potency)
    if b_flag == 0 and p_flag == 1:
        error = math.pow(f_base, -1 * f_potency)
    if b_flag == 1 and p_flag == 0:
        error = -1 * math.pow(f_base, f_potency)
    if b_flag == 1 and p_flag == 1:
        error = -1 * math.pow(f_base, -1 * f_potency)

    assert error == (10**10)

def test_two():
    error_string = "10**-10"

    raised_to = 0
    base = []
    potency = []
    b_flag = p_flag = 0

    for character in error_string:
        if b_flag == 0 and character != "*" and character == "-" and raised_to < 2:
            # indica que a base é negativa
            b_flag = 1

        if p_flag == 0 and character != "*" and character == "-" and raised_to == 2:
            # indica que a potencia é negativa
            p_flag = 1

        # para a base antes de elevar
        if character != "*" and character != "-" and raised_to < 2:
            base.append(character)

        # para quando acharmos os asteriscos, servirão para indicar o momento que a potencia deve ser coletada
        if character == "*" and raised_to < 2:
            raised_to += 1
                
        # começa a coletar a potencia
        if character != "*" and character != "-" and raised_to == 2:
            potency.append(character)

    new_base = ''.join(base)
    new_potency = ''.join(potency)

    f_base = float(new_base)
    f_potency = float(new_potency)

    if b_flag == 0 and p_flag == 0:
        error = math.pow(f_base, f_potency)
    if b_flag == 0 and p_flag == 1:
        error = math.pow(f_base, -1 * f_potency)
    if b_flag == 1 and p_flag == 0:
        error = -1 * math.pow(f_base, f_potency)
    if b_flag == 1 and p_flag == 1:
        error = -1 * math.pow(f_base, -1 * f_potency)

    assert error == (10**-10)

def test_three():
    error_string = "-10**10"

    raised_to = 0
    base = []
    potency = []
    b_flag = p_flag = 0

    for character in error_string:
        if b_flag == 0 and character != "*" and character == "-" and raised_to < 2:
            # indica que a base é negativa
            b_flag = 1

        if p_flag == 0 and character != "*" and character == "-" and raised_to == 2:
            # indica que a potencia é negativa
            p_flag = 1

        # para a base antes de elevar
        if character != "*" and character != "-" and raised_to < 2:
            base.append(character)

        # para quando acharmos os asteriscos, servirão para indicar o momento que a potencia deve ser coletada
        if character == "*" and raised_to < 2:
            raised_to += 1
                
        # começa a coletar a potencia
        if character != "*" and character != "-" and raised_to == 2:
            potency.append(character)

    new_base = ''.join(base)
    new_potency = ''.join(potency)

    f_base = float(new_base)
    f_potency = float(new_potency)

    if b_flag == 0 and p_flag == 0:
        error = math.pow(f_base, f_potency)
    if b_flag == 0 and p_flag == 1:
        error = math.pow(f_base, -1 * f_potency)
    if b_flag == 1 and p_flag == 0:
        error = -1 * math.pow(f_base, f_potency)
    if b_flag == 1 and p_flag == 1:
        error = -1 * math.pow(f_base, -1 * f_potency)

    assert error == (-10**10)

def test_four():
    error_string = "-10**-10"

    raised_to = 0
    base = []
    potency = []
    b_flag = p_flag = 0

    for character in error_string:
        if b_flag == 0 and character != "*" and character == "-" and raised_to < 2:
            # indica que a base é negativa
            b_flag = 1

        if p_flag == 0 and character != "*" and character == "-" and raised_to == 2:
            # indica que a potencia é negativa
            p_flag = 1

        # para a base antes de elevar
        if character != "*" and character != "-" and raised_to < 2:
            base.append(character)

        # para quando acharmos os asteriscos, servirão para indicar o momento que a potencia deve ser coletada
        if character == "*" and raised_to < 2:
            raised_to += 1
                
        # começa a coletar a potencia
        if character != "*" and character != "-" and raised_to == 2:
            potency.append(character)

    new_base = ''.join(base)
    new_potency = ''.join(potency)

    f_base = float(new_base)
    f_potency = float(new_potency)

    if b_flag == 0 and p_flag == 0:
        error = math.pow(f_base, f_potency)
    if b_flag == 0 and p_flag == 1:
        error = math.pow(f_base, -1 * f_potency)
    if b_flag == 1 and p_flag == 0:
        error = -1 * math.pow(f_base, f_potency)
    if b_flag == 1 and p_flag == 1:
        error = -1 * math.pow(f_base, -1 * f_potency)

    assert error == (-10**-10)
