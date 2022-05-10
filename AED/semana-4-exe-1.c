/*
Hoje é a inauguração de um grande supermercado em sua cidade, e todos estão muito
excitados com os baixos preços prometidos.
Este supermercado tem N funcionários que trabalham no caixa, identificados por números
de 1 a N, em que cada funcionário leva um determinado tempo vi para processar um item
de um cliente. Ou seja, se um cliente tem cj itens em sua cesta, um determinado funcionário
levará vi*cj segundos para processar todos os itens deste cliente.
Quando um cliente entra na fila para ser atendido ele espera até que um funcionário esteja
livre para o atendê-lo. Se mais de um funcionário estiver livre ao mesmo tempo, o cliente
será atendido pelo funcionário de menor número de identificação. Tal funcionário só estará
livre novamente após processar todos os itens deste cliente.
Há M clientes na fila para serem atendidos, cada um com um determinado número de itens
na sua cesta. Dadas as informações sobre os funcionários nos caixas e os clientes, o
gerente pediu sua ajuda para descobrir quanto tempo levará para que todos os clientes
sejam atendidos.
Este exercício deverá ser implementado utilizando a estrutura de dados do tipo Fila
Sequencial!!! Vocês deverão alocar a estrutura do tipo Fila e utilizar funções para a sua
manipulação, assim com uma função para calcular a saída (que deverá receber como
parâmetro as duas filas criadas). Cada cliente atendido deverá sair da fila!
*/