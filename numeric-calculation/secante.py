import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return 31 - ((9.8*x)/13)*(1. - np.exp(-6.0*(13.0/x)))

def secante(x0, x1, erro, it_max):    
    xk1 = x0
    xk2 = x1
    it = 0      
    sk = np.abs(xk2 - xk1)
    # lista das k linhas
    line_data = []
    # colunas necessarias para plotar
    column_labels = ['k', 'xk', 'f(xk)', 'stepk']
    
    """
    xk1 = xk-1
    xk2 = xk
    x = xk+1
    """

    while(sk >= erro and abs(f(xk2)) >= erro and abs(f(xk1)) >= erro and it < it_max):
      x = xk2 - f(xk2)*(xk2 - xk1)/(f(xk2) - f(xk1))
      xk1 = xk2
      xk2 = x
      it += 1
      sk = np.abs(xk2 - xk1)
      line_data.append([it, x, f(x), sk])      
    
    # configura o tamanho do grafico
    fig, ax = plt.subplots(figsize=(6,2))
    ax.set_axis_off()
    table = ax.table(cellText=line_data, 
                     cellLoc='center', 
                     colLabels=column_labels,
                     loc='center')
    plt.savefig('Tabela_Secante.pdf', dpi=200)
    plt.show()

x0 = 52
x1 = 58
erro = 10**-6
it_max = 200

secante(x0, x1, erro, it_max)