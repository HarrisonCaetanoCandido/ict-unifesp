import math
import numpy as np
import matplotlib.pyplot as plt

def f(x):
  return math.pow(x, 3) + x - 4

def bisseccao(intervalo, erro, it_max):
    ak = intervalo[0]
    bk = intervalo[1]
    xk = (ak + bk)/2
    sk = bk - ak  
    it = 0
    # lista das k linhas
    line_data = []
    # colunas necessarias para plotar
    column_labels = ['k', 'xk', 'f(xk)', 'stepk']
    
    while(np.abs(bk - ak) > erro and it < it_max):
      xk = (ak + bk) / 2
      sk = np.abs(bk - ak) # como nao tem do-while em python vai ter que fazer a diferença e mandar pra sk duas vezes
      it += 1

      # se chegou aqui eh pq o teorema de bolzano nao pode provar que existe ao menos um zero no intervalo. para esse caso o programa será encerrado
      if (f(ak) > 0 and f(bk) > 0 and f(xk) > 0) or (f(ak) < 0 and f(bk) < 0 and f(xk) < 0):
        print("Pelo Teorema de Bolzano, temos que f(a)f(b) >= 0, logo nao podemos afirmar a existência de ao menos um zero no intervalo (%f,%f)"  % (ak, bk))
        return

      # saida: x*, f(x*), num iteracoes. vamos fazendo isso inserindo cada tupla de linha na lista line_data
      line_data.append([it, xk, f(xk), sk])

      # f(ak) < 0 and f(bk) > 0 and f(xk) > 0, then we gonna use ak as ak and bk as xk
      if(f(ak) < 0 and f(bk) > 0 and f(xk) > 0):
        bk = xk
        continue
            
      # f(ak) > 0 and f(bk) < 0 and f(xk) > 0, then we gonna use ak as xk and bk as bk
      if(f(ak) > 0 and f(bk) < 0 and f(xk) > 0):
        ak = xk
        continue
            
      # f(ak) > 0 and f(bk) > 0 and f(xk) < 0 and f(ak) > f(bk), then we gonna use ak as bk and bk as xk
      if(f(ak) > 0 and f(bk) > 0 and f(xk) < 0 and f(ak) > f(bk)):
        ak = bk
        bk = xk
        continue
            
      # f(ak) > 0 and f(bk) > 0 and f(xk) < 0 and f(ak) < f(bk), then we gonna use ak as ak and bk as xk
      if(f(ak) > 0 and f(bk) > 0 and f(xk) < 0 and f(ak) < f(bk)):
        bk = xk
        continue
            
      # f(ak) < 0 and f(bk) < 0 and f(xk) > 0 and f(ak) > f(bk), then we gonna use ak as ak and bk as xk  
      if(f(ak) < 0 and f(bk) < 0 and f(xk) > 0 and f(ak) > f(bk)):
        bk = xk
        continue
            
      # f(ak) < 0 and f(bk) < 0 and f(xk) > 0 and f(ak) < f(bk), then we gonna use ak as xk and bk as bk
      if(f(ak) < 0 and f(bk) < 0 and f(xk) > 0 and f(ak) < f(bk)):
        ak = xk
        continue

      # f(ak) > 0 and f(bk) < 0 and f(xk) < 0, then we gonna use ak as ak and bk as xk
      if(f(ak) > 0 and f(bk) < 0 and f(xk) < 0):
        bk = xk
        continue

      # f(ak) < 0 and f(bk) > 0 and f(xk) < 0, then we gonna use ak as xk and bk as bk
      if(f(ak) < 0 and f(bk) > 0 and f(xk) < 0):
        ak = xk
        continue

    # configura a quantidade de graficos
    fig, ax = plt.subplots(figsize=(8,6))
    ax.set_axis_off()
    table = ax.table(cellText=line_data, 
                     cellLoc='center', 
                     colLabels=column_labels,
                     loc='center')
    plt.savefig('Tabela_Bisseccao.pdf', dpi=200)
    plt.show()

    
erro = 10**-10
it_max = 200
intervalo = (1, 4)

bisseccao(intervalo, erro, it_max)