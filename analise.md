## Descrição Geral do domínio do problema

O sistema proposto visa simular um aplicativo de um banco digital. Com uma interface simplificada e minimalista.
O foco é fornecer uma plataforma onde os usuários possam gerenciar seu dinheiro de forma autônoma, rápida e segura. As principais entidades deste domínio incluem Clientes, Contas Bancárias e Transações.

## Requisitos funcionais 
01 - Cadastro de clientes;

02 - Autenticação de clientes;

03 - Dashboard principal (saldo/fatura);

04 - Extrato;

05 - Operações básicas (Pix/TED/Home broker);

## Requisitos não funcionais
Requisitos não funcionais

01 - Código será escrito em C++;

02 - Interface minimalista e simples;

03 - Informações devem ser armazenadas em um .TXT;

04 - Código deve garantir segurança na autenticação;

## Diagrama de Casos de Uso

O Diagrama de Casos de Uso a seguir foi elaborado com o objetivo de mapear as interações essenciais entre os usuários e o sistema do banco, delimitando o escopo funcional da aplicação. A modelagem abaixo foca somente nas interações realizadas pelo usuário, abstraindo banco de dados.
Para representar adequadamente o controle de acesso e garantir a segurança do sistema , o diagrama adota a separação de papéis através de dois atores principais:

## - Visitante:
Representa o estado inicial do usuário no aplicativo, onde o visitante deve obrigatoriamente se cadastrar ou realizar o login para interagir com o APP, caso contrário, não terá qualquer permissão ou acesso no APP.

## - Cliente cadastrado: 
Representa o usuário que já passou pelo processo de autenticação, ou através de um novo registro, ou um login com uma conta já existente. Esse ator simula as tarefas reais do usuário que irá utilizar o APP.

<img width="266" height="681" alt="Caso_de_uso_POO_final drawio" src="https://github.com/user-attachments/assets/1a203053-80cc-4675-b4fa-5aff5cb951fd" />

 
## Diagrama de Domínio do problema

Elaborar um diagrama conceitual do domínio do problema.


<div align="center">

[Retroceder](README.md) | [Avançar](projeto.md)

</div>
