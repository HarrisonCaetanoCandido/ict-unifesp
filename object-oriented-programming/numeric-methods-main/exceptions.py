# All of this customized classes have to be derived from the built-in Exception class
    
class ZerosAreNotGuaranteed(Exception):
    """Pelo Teorema de Bolzano, temos que f(a)f(b) > 0, logo nao podemos afirmar a existência de ao menos um zero no intervalo"""
    pass

class FunctionDerivativeIsVeryCloseToZero(Exception):
    """
    Como definido pelo Método de Newton, a derivada de f ser aproximadamente zero implica numa interseção da reta tangênte com o 
    eixo das abscissas num ponto Xk muito distante de X*, pois a interseção da reta tangênte com a função f é feita em um ponto de inflexão, 
    logo é recomendado que X0 seja escolhido novamente
    """
    pass

class SecantMethodIsDivergent(Exception):
    """Note que o Método da Secante diverge quando f(xk) e f(xk-1) são aproximadamente iguais, é recomendado escolher X0 novamente"""
    pass