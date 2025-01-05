import numpy as np

# criamos um array numpy
matrix = np.array([[1,2,3],[4,5,6],[7,8,9]])

# fazemos multiplicacao com matriz
t_matrix = 3 * matrix
print(t_matrix)

# ndarray é um objeto, é uma estrutura de dados como uma matriz n-dimensional.
# o ndarray é alocado em espaços contíguos na memória e os elementos devem ser 
# de mesmo tipo

# pego aqui o elemento da linha 1 e ultima coluna
print(t_matrix[1,-1])

print(t_matrix.ndim)
print(t_matrix.shape)
print(t_matrix.size)
print(t_matrix.dtype)

# crio arrays de 0 a 10 pulando de 2 em 2
print(np.arange(0, 10, 2))

# ou de 10 a 0 decrescendo em 2
print(np.arange(10,0, -2))

# crio array com todos os elementos iguais a 0
print(np.zeros((2,2)))

# crio matriz em que todos os elementos sao 1
print(np.ones((2,2)))

# crio array ones unidimensional
print(np.ones((2)))

# crio um vetor de zeros com o mesmo formato dimensional que outro array
print(np.zeros_like(t_matrix))

# crio elementos igualmente espaçados com percentual igual (1/5) no intervalo de 0 a 1  
print(np.linspace(0,1,5))

# crio um array de valores aleatorios no formato (3,3)
print(np.random.randint(0,10,(3,3)))

# posso redefinir o tipo de um array usando .astype
m = np.ones((3,3), dtype='int8')
print(m.dtype)
m = m.astype('int64')
print(m.dtype)
# quantos bites tem aquele array
print(m.itemsize)

# soma de matrizes de mesma dimensao
new = t_matrix + m 
print(new)

# divisao de matrizes de mesma dimensao
new = t_matrix // m 
print(new)

# operação com escalar é interpretada como uma operação elemento a elemento
new = 5 + m 
print(new)

new = 5 * m 
print(new)

# multiplicacao de matrizes as dimensoes iguais
print(np.dot(t_matrix, m))

# matriz inversa m⁻¹ = todos os elementos sao 1/numero
a = np.array([[2,4,6],[2,0,2],[6,8,14]])
print(np.linalg.inv(a))

