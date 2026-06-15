#include "Investidor.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

Investidor::Investidor(QString n, QString e, QString c, QString s)
    : Usuario(n, e, c, s) {}

bool Investidor::salvarNoArquivo() const {
    QFile arquivo("investidores.txt");
    if (arquivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream saida(&arquivo);
        saida << nome << "," << email << "," << cpf << "," << senha << "\n";
        arquivo.close();
        return true;
    }
    return false;
}

bool Investidor::validarLogin(QString cpfDigitado, QString senhaDigitada) {
    QFile arquivo("investidores.txt");
    if (arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream entrada(&arquivo);
        while (!entrada.atEnd()) {
            QString linha = entrada.readLine();
            QStringList dados = linha.split(",");
            if (dados.size() == 4) {
                if (dados[2] == cpfDigitado && dados[3] == senhaDigitada) {
                    arquivo.close();
                    return true;
                }
            }
        }
        arquivo.close();
    }
    return false;
}