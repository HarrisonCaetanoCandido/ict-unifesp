# operações aritméticas simples:

1+2+3
2+3*4 # soma e multiplicação
3/2+1 # divisao e soma
4*3**3 # potência pode ser **
4*3^3 # potencia pode ser ^
sqrt(2) #raiz 
sin(pi/2) # seno
exp(2) # euler
log(3) # log natural ln
log10(3) # log base 10

#Se um objeto x tem o valor 10, ao digitarmos seu nome, o programa exibe o
#o valor do objeto

x <- 10 # atribui
x # printa
y=15
y

# Tipos de objetos
#vetores
x1<-c(1,3,6) # função 'c' de concatenar
x1
x1[2] # Seleciona a posição em colchetes
x1[2]<-10 # Troca o valor na posição em coclhetes
x1

x2<-seq(0.1,by=0.1) # Faz uma sequência de 0 a 1 de 0.1 em 0.1
x2
help(seq) #Ajuda sobre determinada função 

x3<-rep(2,5) # Repete 5 vezes o valor de 2
x3

# Matrizes
m1 <- matrix(1:9,byrow=F,nrow=3) #ou byrow=1, ordena por coluna
m1
m2 <-matrix(1:9,byrow=T,nrow=3) #ou byrow=0, ordena por linha
m2
m3 <- diag(3)
m3
a<-c(4,6,8,2,10,12,18,14,6,8,12,14)
m4<-matrix(a,nrow=4,ncol=3,byrow=F) # ou byrow=F

# Operação com matrizes
m1*m2 # Dessa maneira é multiplicado elemento a elemento, 
      # não é produto de matrizes

(m1)%*%(m2) # Multiplicacao matricial

# Verificar endereço atual de trabalho
getwd()