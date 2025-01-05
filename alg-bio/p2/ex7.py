"""Desafio: Análise de Dados com NumPy e Matplotlib
Instruções:
    1. Crie um array unidimensional chamado dados com 1000 elementos
    inteiros aleatórios no intervalo de 1 a 100.
    2. Utilizando NumPy, calcule a média, mediana, desvio padrão e
    variância dos valores no array dados. Armazene cada resultado em
    uma variável correspondente.
    3. Crie um histograma com 20 bins utilizando a função plt.hist() para
    visualizar a distribuição dos valores no array dados.
    4. Crie um novo array chamado dados_filtrados que contenha apenas
    os valores maiores que a média calculada no passo 3.
    5. Utilizando a função plt.boxplot(), crie um boxplot para visualizar a
    distribuição dos valores no array dados_filtrados.
    6. Imprima na tela as estatísticas resumidas dos valores no array
    dados_filtrados utilizando a função np.stats.describe().
"""

import numpy as np
import Matplotlib as mp 

dados = np.ranrom.randint(1, 100, (1000))
mean = np.mean(dados)
median = np.median(dados)
std = np.std(dados)

