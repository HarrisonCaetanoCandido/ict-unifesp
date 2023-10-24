import math
from exceptions import ZerosAreNotGuaranteed, FunctionDerivativeIsVeryCloseToZero, SecantMethodIsDivergent
import matplotlib.pyplot as plt
import numpy as np

class NumericMethods:
  def __init__(self, polynomial, interval, error, it_max):

    self.polynomial = np.poly1d(polynomial)

    if type(interval) is list:
      self.a = interval[0]
      self.b = interval[1]
    else:
      # caso em que precisamos da derivada
      self.polynomial_derivative = np.polyder(self.polynomial)
      self.a = interval

    self.error = error
    self.it_max = it_max

    # lista das k linhas
    self.line_data = []

  """"
  limitações atuais ao usar a função de leitura polinomial do numpy:
  - Não lê potências negativas
  - Não lê polinomios como 5x**2 - 3
  """

  def f(self, x) -> float:
    return self.polynomial(x)

  def df(self, x) -> float:
    return self.polynomial_derivative(x)

  def bisection_method(self):
      ak = self.a
      bk = self.b  
      it = 0
      # colunas necessarias para plotar
      column_labels = ['it', 'xk', 'f(xk)', 'stepk']
      
      while(abs(bk - ak) > self.error and it < self.it_max):
        xk = (ak + bk) / 2
        sk = abs(bk - ak) # como nao tem do-while em python vai ter que fazer a diferença e mandar pra sk duas vezes
        it += 1
        
        # se chegou aqui eh pq o teorema de bolzano nao pode provar que existe ao menos um zero no intervalo. para esse caso o programa será encerrado
        if (self.f(ak) > 0 and self.f(bk) > 0 and self.f(xk) > 0) or (self.f(ak) < 0 and self.f(bk) < 0 and self.f(xk) < 0):
          raise ZerosAreNotGuaranteed('Pelo Teorema de Bolzano, temos que f(a)f(b) > 0, logo nao podemos afirmar a existência de ao menos um zero no intervalo')

        # saida: x*, self.f(x*), num iteracoes. vamos fazendo isso inserindo cada tupla de linha na lista line_data
        self.line_data.append([it, xk, self.f(xk), sk])

        # f(ak) < 0 and f(bk) > 0 and f(xk) > 0, then we gonna use ak as ak and bk as xk
        if(self.f(ak) < 0 and self.f(bk) > 0 and self.f(xk) > 0):
          bk = xk
          continue
              
        # f(ak) > 0 and f(bk) < 0 and f(xk) > 0, then we gonna use ak as xk and bk as bk
        if(self.f(ak) > 0 and self.f(bk) < 0 and self.f(xk) > 0):
          ak = xk
          continue
              
        # f(ak) > 0 and f(bk) > 0 and f(xk) < 0 and f(ak) > f(bk), then we gonna use ak as bk and bk as xk
        if(self.f(ak) > 0 and self.f(bk) > 0 and self.f(xk) < 0 and self.f(ak) > self.f(bk)):
          ak = bk
          bk = xk
          continue
              
        # f(ak) > 0 and f(bk) > 0 and f(xk) < 0 and f(ak) < f(bk), then we gonna use ak as ak and bk as xk
        if(self.f(ak) > 0 and self.f(bk) > 0 and self.f(xk) < 0 and self.f(ak) < self.f(bk)):
          bk = xk
          continue
              
        # f(ak) < 0 and f(bk) < 0 and f(xk) > 0 and f(ak) > f(bk), then we gonna use ak as ak and bk as xk  
        if(self.f(ak) < 0 and self.f(bk) < 0 and self.f(xk) > 0 and self.f(ak) > self.f(bk)):
          bk = xk
          continue
              
        # f(ak) < 0 and f(bk) < 0 and f(xk) > 0 and f(ak) < f(bk), then we gonna use ak as xk and bk as bk
        if(self.f(ak) < 0 and self.f(bk) < 0 and self.f(xk) > 0 and self.f(ak) < self.f(bk)):
          ak = xk
          continue

        # f(ak) > 0 and f(bk) < 0 and f(xk) < 0, then we gonna use ak as ak and bk as xk
        if(self.f(ak) > 0 and self.f(bk) < 0 and self.f(xk) < 0):
          bk = xk
          continue

        # f(ak) < 0 and f(bk) > 0 and f(xk) < 0, then we gonna use ak as xk and bk as bk
        if(self.f(ak) < 0 and self.f(bk) > 0 and self.f(xk) < 0):
          ak = xk
          continue

      self.it_max = it

      # configura a quantidade de graficos
      fig, ax = plt.subplots(figsize=(8,6))
      ax.set_axis_off()
      table = ax.table(cellText=self.line_data, cellLoc='center', colLabels=column_labels, loc='center')
      plt.savefig('static/img/BisectionTable.jpg', dpi=200)

  def newton_method(self):
      xk = self.a
      # evitar erro na primeira iteracao
      sk = self.error + 1
      it = 0
      # colunas necessarias para plotar
      column_labels = ['it', 'xk', 'f(xk)', 'df(xk)', 'stepk']

      while(sk >= self.error and abs(self.f(xk)) >= self.error and it < self.it_max):
          if self.df(xk) >= 0 and self.df(xk) < 1:
            raise FunctionDerivativeIsVeryCloseToZero('Como definido pelo Método de Newton, a derivada de f ser aproximadamente zero implica numa interseção da reta tangênte com o eixo das abscissas num ponto Xk muito distante de X*, pois a interseção da reta tangênte com a função f é feita em um ponto de inflexão, logo é recomendado que X0 seja escolhido novamente')

          xold = xk
          xk = xk - self.f(xk)/self.df(xk)
          sk = abs(xk - xold)
          it += 1
          
          self.line_data.append([it, xk, self.f(xk), self.df(xk), sk])

      self.it_max = it
      
      # configura a tabela
      fig, ax = plt.subplots(figsize=(8,6))
      ax.set_axis_off()
      table = ax.table(cellText=self.line_data, cellLoc='center', colLabels=column_labels, loc='center')
      plt.savefig('static/img/NewtonTable.jpg', dpi=200)

  def secant_method(self):    
      xk1 = self.a
      xk2 = self.b  
      # evitar o pulo no laço no lancamento de excessao quando existem casos em que a0 == b0
      sk = self.error
      it = 0
      # colunas necessarias para plotar
      column_labels = ['it', 'xk+1', 'f(xk)', 'stepk']
      """
      xk1 = xk-1
      xk2 = xk
      x = xk+1
      """

      while(sk >= self.error and abs(self.f(xk2)) >= self.error and abs(self.f(xk1)) >= self.error and it < self.it_max):
        if self.f(xk2) == self.f(xk1):
          raise SecantMethodIsDivergent('Note que o Método da Secante diverge quando f(xk) e f(xk-1) são aproximadamente iguais, é recomendado escolher X0 novamente')

        x = xk2 - self.f(xk2)*(xk2 - xk1)/(self.f(xk2) - self.f(xk1))
        xk1 = xk2
        xk2 = x
        it += 1
        sk = abs(xk2 - xk1)
        self.line_data.append([it, x, self.f(x), sk])    

      self.it_max = it  
      
      # configura o tamanho do grafico
      fig, ax = plt.subplots(figsize=(8,6))
      ax.set_axis_off()
      table = ax.table(cellText=self.line_data, cellLoc='center', colLabels=column_labels, loc='center')
      plt.savefig('static/img/SecantTable.jpg', dpi=200)