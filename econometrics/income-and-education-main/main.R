# usado para remover todos os objetos (variáveis, funções, etc.) atualmente armazenados na memória do ambiente de trabalho
rm(list=ls())

# para estabelecer o seu diretório de trabalho
setwd("/home/harrison/econometria")
getwd()

# pacote do tidyverse. Retornam os tibbles, que são dataframes(tabelas com linha e coluna)
install.packages("tidyverse")
# pacote para trabalhar com a função views
install.packages("utils")
# pacote para ler arquivos .ods
install.packages("readODS")
# pacote para plotar grafico de correlacao de variaveis 
install.packages("corrplot")

library(tidyverse)
library(readr)
library(readxl)
library(utils)
library(corrplot)

# importando dados externos para o R
general_data <- read_excel("base_de_dados.xlsx", sheet = "MUNICÍPIO")

# tibble com 526 linhas e 24 colunas View(data_general) summary(data_general) View(data_ed) summary(data_ed)
View(general_data)
summary(general_data)

# cria a matriz de correlacao das variaveis (primeira analise de correlacao). a opcao use permite usar apenas observações completas aos pares ao calcular a matriz de correlação
correlation_matrix <- cor(general_data[, c("MatPubEf", "MatPubEm", "MatPriEf", "MatPriEm", "DistEfPri", "DistEmPri", "DistEfPub", "DistEmPub", "TaxEvaEfPri", "TaxEvaEmPri", "TaxEvaEfPub", "TaxEvaEmPub", "IdebAi", "IdebAf", "MatLinfEf", "MatLinfEm", "MatIntEf", "MatIntEm", "DocSupEfPub", "DocSupEmPub", "DocSupEfPri", "DocSupEmPri", "TaxMortInf", "RendPibPCap", "RendMedioFormal")], use = "pairwise.complete.obs")
corrplot(correlation_matrix, method = "square", type = "lower", tl.cex = 0.7, tl.srt = 45)

# segunda analise de correlacao, com as devidas correcoes
correlation_matrix <- cor(general_data[, c("MatPubEf", "MatPubEm", "MatPriEf", "MatPriEm", "DistEfPri", "DistEmPri", "DistEfPub", "DistEmPub", "TaxEvaEfPub", "IdebAi", "IdebAf", "MatLinfEf", "MatLinfEm", "MatIntEf", "DocSupEfPub", "DocSupEmPub", "DocSupEfPri", "DocSupEmPri", "RendPibPCap", "RendMedioFormal")], use = "pairwise.complete.obs")
corrplot(correlation_matrix, method = "square", type = "lower", tl.cex = 0.7, tl.srt = 45)

# regressao linear multipla
model <- lm(RendMedioFormal ~ MatPubEf + MatPubEm + MatPriEf + MatPriEm + DistEfPri + DistEmPri + DistEfPub + DistEmPub + TaxEvaEfPub + IdebAi + IdebAf + MatLinfEf + MatLinfEm + MatIntEf + DocSupEfPub + DocSupEmPub + DocSupEfPri + DocSupEmPri + RendPibPCap, data = general_data)
summary(model)