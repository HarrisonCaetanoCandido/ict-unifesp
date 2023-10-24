from flask import Flask, render_template, request
from numericmethods import NumericMethods
import math

"""
- export FLASK_APP=file_name.py | As atualizações só serao feitas ao reiniciar o servidor, pois o flask debugger = off
- export FLASK_ENV=development  | As atualizações serão feitas a cada salvamento dos arquivos 
  (não precisa reiniciar o servidor), pois o flask debugger = on
- export FLASK_DEBUG=1 | Parece que FLASK_ENV está obsoleto, então é recomendado usar o FLASK_DEBUG para o flask versão 2.3
"""

# instancia um objeto Flask, em que __name__ é o nome do módulo python atual
app = Flask(__name__)

# a função do route é linkar uma url em uma função
@app.route('/', methods=["GET", "POST"])
def index():
    # verificar qual metodo esta sendo usado no momento
    if request.method == "GET":
        return render_template("index.html")
    else:
        not_handle_polynomial = str(request.form.get("polynomial_func"))
        polynomial = []
        number = []
        got_apotency = 0
        
        for character in not_handle_polynomial:
            # -1 é numero ou '-', 0 é *, 1 é caractere alfabético
            if alfabetic_verification(character) == 0:
                got_apotency += 1

            # caso em que queremos ler 5x**2 + 2x, no caso ignorar o numero seguido de **
            elif alfabetic_verification(character) == -1 and got_apotency == 2:
                got_apotency = 0
                # coloco o numero lido  na primeira posicao da lista
                new_number = ''.join(number)
                polynomial.append(float(new_number))
                # limpo a lista
                number.clear()
                # pulo a potencia atual
                continue

            if alfabetic_verification(character) == -1 and got_apotency == 0:
                number.append(character)

        if request.form.get("a0") != None:
            a0 = float(request.form.get("a0"))
            b0 = float(request.form.get("b0"))
            error_string = request.form.get("error")
            it_max = int(request.form.get("it_max"))

            error = error_string_correction(error_string)

            interval = [a0, b0]
            bisection = NumericMethods(polynomial, interval, error, it_max)
            bisection.bisection_method()

            return render_template("index.html", plot_url="static/img/BisectionTable.jpg")
        elif request.form.get("xk") != None:
            xk = float(request.form.get("xk"))
            error_string = request.form.get("nerror")
            it_max = int(request.form.get("nit_max"))

            error = error_string_correction(error_string)

            newton = NumericMethods(polynomial, xk, error, it_max)
            newton.newton_method()

            return render_template("index.html", plot_url="static/img/NewtonTable.jpg")

        else:
            a0 = float(request.form.get("sa0"))
            b0 = float(request.form.get("sb0"))
            error_string = request.form.get("serror")
            it_max = int(request.form.get("sit_max"))

            error = error_string_correction(error_string)

            interval = [a0, b0]
            secant = NumericMethods(polynomial, interval, error, it_max)
            secant.secant_method()

            return render_template("index.html", plot_url="static/img/SecantTable.jpg")

def alfabetic_verification(character):
    if character == 'x' or character == 'X' or character == 'a' or character == 'b' or character == 'c' or character == 'd' or character == 'e' or character == 'f' or character == 'g' or character == 'h' or character == 'i' or character == 'j' or character == 'k' or character == 'l' or character == 'm' or character == 'n' or character == 'o' or character == 'p' or character == 'q' or character == 'r' or character == 's' or character == 't' or character == 'u' or character == 'v' or character == 'w' or character == 'y' or character == 'z' or character == 'A' or character == 'B' or character == 'C' or character == 'D' or character == 'E' or character == 'F' or character == 'G' or character == 'H' or character == 'I' or character == 'J' or character == 'K' or character == 'L' or character == 'M' or character == 'N' or character == 'O' or character == 'P' or character == 'Q' or character == 'R' or character == 'S' or character == 'T' or character == 'U' or character == 'V' or character == 'W' or character == 'Y' or character == 'Z':
        return 1
    if character == '*':
        return 0
    # aqui entra o caso de '-' também
    return -1

def error_string_correction(error_string):

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

    return error

@app.route('/sobre')
def sobre():
    return 'Olá, Mundo!'

@app.route('/<string:name>')
def error(name):
    py_variable = f'A página "{name}" não existe'
    return render_template("error.html", error_variable=py_variable)