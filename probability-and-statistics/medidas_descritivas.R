# Lendo dados de um arquivo teste 
# header=T A primeira linha contém os nomes das colunas da tabela
# em read.csv2() o default é:
# separar de colunas= ;" e separador de casas decimais=";"

dados <- read.csv2("./dados.csv",header=T)
dados

# Informação resumida
summary(dados)

# Mostra o cabeçalho
names(dados)

#---------------------------------------------------------------
# Distribuição de frequências - variável Qualitativa
dados$est_civil
dados$idade_ano

# Frequência absoluta
fa<-table(dados$est_civil)
fa

# Frequência relativa
fr<-prop.table(fa)
fr

# Frequência acumulada
fac<-cumsum(fr)
fac

#Montando a tabela (cbind organiza por colunas e rbind por linhas)
tabela<-cbind(fa,fr,fac,porcent=100*fr)
tabela

#---------------------------------------------------------------
# Distribuição de frequências - Variável quantitativa contínua (CLASSES)
ds<-dados$salario.
range(ds)
nclass.Sturges(ds)
#cut: divide a variável nos intervalos especificados
#l=7 fornece 6 intervalos
fa<-table(cut(ds,seq(4,23.30,l=7)))

fa<-table(cut(ds,seq(3.9,23.30,l=7))) # 3.9 para corrigir o erro do mínimo
                                      # valor do rstudio, que normalmente
                                      # começa a incluir um valor maior do
                                      # que o inserido como mínimo

# Frequência relativa
fr<-prop.table(fa)

# Frequência acumulada
fac<-cumsum(fr)
fac

#Montando a tabela(cbind organiza por colunas e rbind por linhas)
tabela<-cbind(fa,fr)
tabela

#---------------------------------------------------------------
# Distribuição de frequências - Variável quantitativa discreta
# Frequência absoluta
fa<-table(dados$filhos)
fa

# Frequência relativa
fr<-prop.table(table(dados$filhos))
fr

# Frequência acumulada
fac<-cumsum(prop.table(table(dados$filhos)))
fac

#Montando a tabela (cbind organiza por colunas e rbind por linhas)
tabela<-cbind(fa,fr,fac,porcent=100*fr)
tabela

#---------------------------------------------------------------
# Gráfico em barras (lembrando que table é fabs)
par(mfrow=c(1,2)) # janela de plot multipainel (1 linha e 2 colunas)
df<-dados$filhos
barplot(table(df),main="Numero de filhos")
barplot(table(df),main="Número de filhos",col="red") # muda cor das colunas

# Gráfico - composição em setores(pizza)
par(mfrow=c(1,1)) # janela de plot multipainel (1 linha e 2 colunas)
pie(table(dados$instrucao),main="Pizza")  

# Histograma
par(mfrow=c(1,3)) # janela de plot multipainel (1 linha e 2 colunas)
hist(ds)
hist(ds,nclass=5)
hist(ds,nclass=5,col="blue",main="Salário",freq=F)
#freq=F faz cim que se plote a densidade

#Gráfico de quantis
par(mfrow=c(1,1)) # janela de plot multipainel (1 linha e 2 colunas)
boxplot(ds)