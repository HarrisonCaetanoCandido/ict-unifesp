import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return x**2 - 2

def df(x):
    return 2*x

# lista das k linhas
line_data = []
# colunas necessarias para plotar
column_labels = ['it', 'xk', 'f(xk)', 'df(xk)', 'stepk']

def newton(x0, erro, it_max):
    x = x0
    it = 0
    # evitar erro na primeira iteracao
    sk = erro + 1
    
    line_data.append([it, x, f(x), df(x),'-'])

    while(sk >= erro and it < it_max):
        xold = x
        x = x - f(x)/df(x)
        sk = np.abs(x - xold)
        it += 1
        
        line_data.append([it, x, f(x), df(x), sk])
    
    # configura a tabela
    fig, ax = plt.subplots(figsize=(8,6))
    ax.set_axis_off()
    table = ax.table(cellText=line_data, 
                     cellLoc='center', 
                     colLabels=column_labels,
                     loc='center')
    plt.savefig('Pt1_Ex2.1.pdf', dpi=200)
    plt.show()
  
x0 = 5
erro = 10**-12
it_max = 6

newton(x0, erro, it_max)