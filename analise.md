## Descrição Geral do domínio do problema

O sistema proposto visa simular um aplicativo de investimentos. Com uma interface simplificada e minimalista.
O intuito do programa é organizar e gerir os investimentos do usuário de uma maneira fácil e intuitiva. É possível adicionar novos ativos, adicionar ativos já comprados anteriormente, remover/vender ativios e acompanhar o lucro consolidado do ativo.

## Requisitos funcionais 
01 - Cadastro do investidor;

02 - Autenticação do investidor;

03 - Dashboard principal (visão consolidada da carteira);

04 - Compra de novos ativos (aportes);

05 - Venda de ativos;

06 - Logout na sessão;

## Requisitos não funcionais
Requisitos não funcionais

01 - Código será escrito em C++;

02 - Interface minimalista e simples, desenvolvida no QT;

03 - Informações devem ser armazenadas em um .TXT;

04 - Código deve garantir segurança na autenticação;

05 - Arquitetura em POO;
## Diagrama de Casos de Uso

O Diagrama de Casos de Uso a seguir foi elaborado com o objetivo de mapear as interações essenciais entre o investidor e o gerenciador de investimentos, delimitando o escopo funcional da aplicação. A modelagem abaixo foca somente nas interações realizadas pelo investidor, abstraindo banco de dados.
Para representar adequadamente o controle de acesso e garantir a segurança do sistema , o diagrama adota a separação de papéis através de dois atores principais:

## - Visitante:
Representa o estado inicial do usuário no aplicativo, onde o visitante deve obrigatoriamente se cadastrar ou realizar o login para interagir com o APP, caso contrário, não terá qualquer permissão ou acesso no APP.

## - Investidor: 
Representa o usuário que já passou pelo processo de autenticação, ou através de um novo registro, ou um login com uma conta já existente. Esse ator possui acesso completo a aplicação, simula um usário que já utiliza o programa.

<img src="img/Casos_de_uso.drawio.png" width="30%" style="padding: 10px">
 
## Diagrama de Domínio do problema

O Diagrama de Classes a seguir representa a estrutura do aplicativo do banco. Ele serve como o "esqueleto" do código C++, definindo as classes que farão o sistema funcionar, seus atributos e seus métodos.

O diagrama abaixo é dividido por atributos privados e métodos públicos.

Associação simples entre Cliente e ContaBancaria: Cliente tem uma conta bancaria;

Associação direcionada entre ContaBancaria apontando para Investimento, Transacao e CartaoCredito. Relação "TEM UM"

<img src="img/diagrama_de_classes.png" width="30%" style="padding: 10px">

<div align="center">

[Retroceder](README.md) | [Avançar](projeto.md)

</div>
