#ifndef INVESTIMENTO_H
#define INVESTIMENTO_H
#include <QString>

class Investimento {
private:
    QString cpfDono;
    QString tipo;
    QString nome;
    double preco;
    int quantidade;

public:
    Investimento(QString cpf, QString t, QString n, double p, int q);

    bool vender(double qtdVenda) const;
    bool salvarNoArquivo() const;

    // A classe gerencia seus próprios dados
    QString getNome() const { return nome; }
    QString getTipo() const { return tipo; }
    QString getCpfDono() const { return cpfDono; }

    // A regra de negócio de somar a carteira sai da tela e vem para a classe
    static QString gerarRelatorioCarteira(QString cpfDono);
};
#endif
