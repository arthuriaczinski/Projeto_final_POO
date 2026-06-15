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
    bool venderAtivo(QString cpfDono, QString nomeAtivo, int qtdVenda);
    bool salvarNoArquivo() const;
};
#endif