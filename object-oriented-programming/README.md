<!--## Getting Started

Welcome to the VS Code Java world. Here is a guideline to help you get started to write Java code in Visual Studio Code.

## Folder Structure

The workspace contains two folders by default, where:

- `src`: the folder to maintain sources
- `lib`: the folder to maintain dependencies

Meanwhile, the compiled output files will be generated in the `bin` folder by default.

> If you want to customize the folder structure, open `.vscode/settings.json` and update the related settings there.

## Dependency Management

The `JAVA PROJECTS` view allows you to manage your dependencies. More details can be found vscode-java-dependency#manage-dependencies -->

# oriented-object-programming

Uma linguagem orientada a objetos surge da ideia de aproximar o mundo real a programação para o funcionamento ou manutenção de um programa, basicamente tudo no mundo real vira um objeto com atributos, comportamentos e ações etc.

## Classes

Possuem as propriedas do nosso objeto, vista como a unidade mínima e básica da implementação de um paradigma orientado a objetos, é como a planta de uma casa. É uma estrutura que abstrai um conjunto de objetos com características similares. Uma classe define o comportamento de seus objetos através de métodos e os estados possíveis destes objetos através de atributos. Em outros termos, uma classe descreve os serviços providos por seus objetos e quais informações eles podem armazenar.

### Atributo

É o elemento de uma classe responsável por definir sua estrutura de dados. O conjunto destes será responsável por representar suas características e fará parte dos objetos criados a partir da classe.

#### Atributo X Variável

Atributo é o que é próprio e peculiar a alguém ou a alguma coisa. Criamos dentro de Classes.

Variável é sujeita a variações ou mudanças. Realizar operações. Criamos dentro dos Métodos.

## Objetos

São os elementos manipuláveis através das definições feitas nas Classes. É a representação de um conceito/ entidade do mundo real, que pode ser física (bola, carro, árvore etc) ou conceitual (viagem, estoque, compra etc) e possui um significado bem definido para um determinado software. Para esse conceito/entidade, deve ser definida inicialmente uma Classe a partir da qual posteriormente serão instanciados objetos distintos.

Ex de criação:

    Carro carro = new Carro();

### Mensagem

É o processo de ativação de um método de um objeto. Isto ocorre quando uma chamada ao método é realizada, assim disparando a execução de seu comportamento descrito por sua classe. Pode também ser direcionada diretamente à classe, caso a requisição seja a um método estático.

Ex de Mensagem:

    carro.<método>;

## Métodos

Método é uma porção de código (sub-rotina) que é disponibilizada pela classe. Este é executado quando é feita uma requisição a ele. Um método serve para identificar quais serviços ou ações que a classe oferece. Eles são responsáveis por definir e realizar um determinado comportamento. Os métodos em Java são
definidos como: 


    tipo_dado nome_método(tipo_dado varx, tipo_dado vary){}


Para fazer a chamada do método em um outro método, basta digitar o nome do método. Para retornar um dado no método, basta digitar "return variavel;" em alguma linha daquele método.

### Métodos Especiais

- Construtor. Cria o objeto, é basicamente quem inicializa o objeto daquela classe. Java o inicializa como padrão quando não é definido pelo programador. É uma boa prática o definir na classe.

- Destrutor. Auxilia na destruição do objeto, libera esse recurso da memória para o coletor de lixo, que apaga da memória. É uma boa prática para quando você precisar liberar alguns recursos.

### Sobrecarga 

É possível mudar a assinatura de acordo com a necessidade. Ajuda a manter a abstração, ou seja, não precisamos criar vários métodos para cada necessidade.

- Assinatura: nome + parâmetros

        m1()
        m1(int i)
        m1(float f)
        m1(String s, long l)
        m1(long l, String s)

## Herança

É o relacionamento entre Classes em que uma Classe chamada de subclasse (Classe filha, Classe derivada) é uma extensão, um subtipo de outra classe chamada de superclasse (Classe mãe, Classe base). Devido a isto, a subclasse consegue reaproveitar os atributos e métodos dela. Além dos que venham a ser herdados, a subclasse pode definir seus próprios membros (atributos e métodos).

Ex:

    class B extends A {
        ... 
    }

- Simples: Possui apenas uma Classe mãe
- Múltipla: Possui mais de uma Classe mãe => Não existe em Java

### Upcast e Downcast

Upcast consiste em subir uma hierarquia de Classes, já para Downcast é o inverso.
Ex de Upcast:

    A a new B(); <= Aqui considerando que "A" é a Superclasse

    B a = (B)new A(); <= É preciso explicitar para quem deseja transformar. Não é considerado muito seguro.

### Polimorfismo

"A mesma ação, se comportando diferente". Por exemplo, supondo uma hierarquia de pagamento, temos que a entidade Pagamento pode ser Processada de diferentes formas, seja por Boleto, Crédito ou PIX. A ação de processar, aqui representada por um método se comporta de maneira diferente de acordo com a instância ou objeto em questão:

                            | Pagamento |
                            |Processar()|
                           /       |      \
                |   Boleto  ||  Crédito  ||    PIX    |
                |Processar()||Processar()||Processar()|

### Sobrescrita

"A mesma ação, podendo se comportar diferente". Aqui existe a POSSIBILIDADE da ação se comportar diferente. No exemplo abaixo temos uma Conta com um atributo de saldo e um método ExibirSaldo(), perceba que a conta Corrente não sobrescreveu o método ExibirSaldo, basicamente só precisamos mostrar o saldo pelo atributo Saldo, enquanto que para Poupança e Cheque Especial temos a questão de rendimento, taxa e outros fatores para o cálculo do Saldo:

                           |     Conta     |
                           | double saldo  |
                           | ExibirSaldo() |
                           /       |        \
                | Corrente ||   Poupança  ||  C.Especial |
                |    ""    ||ExibirSaldo()||ExibirSaldo()|  

## Encapsulamento

É a possibilidade de proteger alguns dados ou funcionalidades da classe, não permitindo que seus consumidores possam acessá-la sem um tratamento.

## Associação

Possibilita um relacionamento entre Classes/Objetos, no qual estes possam pedir ajuda a outras Classes/Objetos e representar de forma completa o conceito ao qual se destinam. Neste tipo de relacionamento, as classes e os objetos interagem entre si para atingir seus objetivos.

- Estrutural, se manifestando na estrutura, métodos:
    - Composição: "Com Parte Todo"
      Ex: Pessoa e Endereço, o Endereço(Parte) só pode existir com a existência da Pessoa(Todo)

            |  Pessoa  | => | Endereço |
            | Endereço |    |    ...   |

      No código isso seria como:

      Pessoa endereco;

    - Agregação: "Sem Parte Todo"
      Ex: Disciplina e Aluno, não necessariamente a inexistência da Disciplina faz com que o aluno deixe de existir, logo aqui o Aluno é independente da Disciplina, sem relacionamento forte.

            |  Disciplina  | => |   Aluno  |
            | Aluno aluno  |    |    ...   |

- Comportamental, se manifestando nos métodos:
    - Dependência: "Depende de"
      Ex: Compra e Cupom, aqui existe um método na Classe compra que utiliza do Cupom, o método irá avaliar a entidade Cupom e validar seu uso, ou seja, depende de alguns fatores para o aproveitamento do mesmo

            |           Compra            |    |   Cupom  |
            |       Cliente cliente       | => |    ...   |
            | finalizar(Cupom cupom, ...) |

## Interface

Define um contrato que deve ser seguido pela Classe que a implementa. Quando uma Classe implementa uma interface, ela se compromete a realizar todos os comportamentos que a Interface disponibiliza.
Ex:

        interface A { // define uma interface
             ...
        }

        class B implements A { // implementa a interface A definida em B 
             ...
        }

## Pacotes

São uma organização física ou lógica para separar Classes com responsabilidades distintas. Com isso, espera-se que a aplicação fique mais organizada e seja possível separar Classes de finalidades e representatividades diferentes.
Ex:

package ...; <= Endereça os arquivos nos pacotes

import ...; <= Importa as propriedaes de um arquivo Java, uma Classe por exemplo

## Visibilidades 

Um modificador de acesso tem como finalidade determinar até que ponto uma Classe, atributo ou método pode ser usado. A utilização de modificadores de acesso é fundamental para o uso efetivo da Orientação a Objetos. Algumas boas práticas e conceitos só são atingidos com o uso correto deles.

### Tipos de Visibilidades

- Private: Só dentro da Classe
  
  Ex: 

        private

        private int i;

        private void do();
  
- Protected => Dentro da Classe, mesmo pacote e subclasses

  Ex:

        protected

        protected int i;
        
        protected void do();

- Public: Em qualquer lugar
  
  Ex:

        public 

        public int i;

        public void do();

## Variáveis de Instância e de Classe

Uma variável de Instância funciona de maneira que duas variáveis de mesma classe possuem endereços diferentes na memória.

Para uma variável de Classe temos o conceito de uma variável dividida por dois objetos, para isso:

static int y = 0; // a mesma definição pode ser feita diretamente no arquivo da classe

    Exemplo ex1 = new Exemplo();
    System.out.println(ex1.x); // variavel diferente
    System.out.println(ex1.y); // variavel igual

    Exemplo ex2 = new Exemplo();
    System.out.println(ex2.x); // variavel diferente
    System.out.println(ex2.y); // variavel igual

## Básico

### Tipos Primitivos/Variáveis

#### Inteiras:
Ex:
    
    int x;
    x = 20;
    System.out.println(x); // printa o valor int da variavel

#### Strings:
Ex:

    System.out.println("x"); // printa o caractere "x"

Obs: Para printar o valor da variável, é necessário chamar ela no comando system.out.println

#### Inteiros + strings:
Ex:

    int x;
    x = 20;
    System.out.println("abcde" + x);

#### Byte, Short ou Long:
Tipos de dados para valores inteiros

#### Float ou Double:
Tipos de dados para valores contínuos

#### Boolean:
Tipos de dados para true ou false

#### Char:
Tipos de dados para caractere

#### Constantes:
O "prefixo" "final" transforma a variável daquele tipo em Constante.
Ex:
final int x = 20;

### Vetores

    tipo_dado[] nome_variavel = new tipo_dado[n];

#### Propriedades de Vetores em Java

Variáveis de uma classe ou membros de um vetor já são inicializados, se por exemplo for um vetor com posições não especificadas
o seu valor padrão será:

- 0 para short, int, long, double, float, byte;

- /0 para char;

- false para boolean;

- NULL para objetos.

Obs: Para variáveis locais, o valor deverá ser inicializado pelo programador.

Para inicializar posições de um vetor com valores diferentes do padrão, o método abaixo poderá ser usado:

    java.util.Arrays.fill(x, 2, 5, 3); // variavel, intervalo_inicial, intervalo_final, valor_inserido


Ou então usar:

    int x[] = {1,2,3,4,5,21,13};


Para comprimento de um vetor basta fazer a chamada:

nome_vet.length = numero de membros

### Leitura do Teclado

Declarar uma variável do tipo Scanner:
Scanner input = new Scanner(System.in);

E então:

    Tipo_Dado X;

    System.out.println("Digite um valor: ");

Para números:

    X = input.nextTipo_Dado();

Para strings até encontrar um espaço:

    X = input.next(); 

Para strings até encontrar um \n:

    X = input.nextLine();

### Operadores Matemáticos

    Adição: +
    Subtração: -
    Divisão: /
    Multiplicação: *
    Resto: %

### Atalhos Matemáticos

    Adição: +=
    Subtração: -=
    Divisão: /=
    Multiplicação: *=

### Comentários:
    "// abcd"
ou

    "/*
    *a
    *b
    *c
    *d
    */
ou como ultimo caso, que é para comentar no Java doc, que faz um resumo das classes, dos métodos e das variáveis do código:

    "/**
    *a
    *b
    *c
    *d
    */
