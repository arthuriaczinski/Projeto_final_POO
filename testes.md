# Testes

O processo de validação da aplicação foi dividido nas seguintes etapas;

## Validação da aplicação

Simulação com dados de login incorretos;

Simulação de diferentes sessões com diferentes usuário realizando compra e venda de ações;

Tentativa de venda de ativo com uma quantidade maior do que a que tem em carteira;

Compra do mesmo ativo que já estava em carteira anteriormente;

Para poupança durante a venda para saldos como 50,000001, é feito uma verificação se a diferença total em que o usuário deseja vender x a quantia que ele realmente tem é menor que 0.01, a venda é a autorizada da mesma forma. Desta maneira evitando que o usuário não fique sem entender o por que não foi possível vender o ativo;

Teste na adição de valores de ativos com virgula;

Verificação do cálculo de valor médio após compra do mesmo ativo, porém com valor diferente.

<div align="center">

[Retroceder](implementacao.md) | [Início](README.md)

</div>
