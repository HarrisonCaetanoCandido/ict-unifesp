# importando o conjunto de dados da biblioteca scikit-learn, contendo o conjunto Iris
from sklearn import datasets
# divisão de vetores ou matrizes em subconjuntos aleatórios para treinamento
from sklearn.model_selection import train_test_split
# para pre-processar os dados de entrada
from sklearn.preprocessing import StandardScaler
# importando o classificador
from sklearn.ensemble import RandomForestClassifier
# usada para calcular metricas de desempenho do modelo
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score
# plotar a base de dados como uma tabela
import pandas as pd

# fase 1: carregar a base de dados escolhida, no caso conjunto Iris
iris = datasets.load_iris()

# fase 2: preparar a base de dados
# divisao da base de dados em base de treinamento e teste
# X possui caracteristicas como comprimento e largura da pétala e sépala
# y possui as especies das flores
# obs 1: X maiusculo é uma convencao para denotar variaveis de entrada (atributos)
# representados como dataframes [n_samples, n_features]
# obs 2: y minusculo é uma convencao para denotar variavel de saida ou alvo, um vetor [n_samples]
X, y = iris.data, iris.target

# criando um dataframe, apenas para visualização, do pandas com os dados do conjunto
df = pd.DataFrame(X, columns=iris.feature_names)
df['target'] = y
df['flower_name'] = [iris.target_names[i] for i in y]

print(df)

# pre-processamento: normalizando os dados de entrada
scaler = StandardScaler()
X = scaler.fit_transform(X)

# considerando empiricamente que a base é confiável,
# faremos 70% da base trabalhar para treinamento e 30% para teste,
# com uma aleatoriedade de geração de números aleatórios igual a 42,
# ou seja, é o quanto os dados são embaralhados
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.70, random_state=42)

# criando uma instancia do classificador com 100 arvores,
# mais uma vez a aleatoriedade de random_forest garante maior independência entre as árvores
clf = RandomForestClassifier(n_estimators=100, random_state=42)

# fase 3: treinando o modelo
clf.fit(X_train, y_train)

# fase 4: fazer previsoes com base nos dados de teste
y_pred = clf.predict(X_test)

# calcula as metricas de desempenho
precision = precision_score(y_test, y_pred, average='weighted')
recall = recall_score(y_test, y_pred, average='weighted')
f1 = f1_score(y_test, y_pred, average='weighted')

print("Acurácia: ", accuracy_score(y_test, y_pred))
print("Precisão: ", precision)
print("Recall: ", recall)
print("F1-score: ", f1)