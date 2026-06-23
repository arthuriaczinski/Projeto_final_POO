#include "Investidor.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

Investidor::Investidor(QString n, QString e, QString c, QString s) // construtor classe investidor
    : Usuario(n, e, c, s) {}

bool Investidor::salvarNoArquivo() const { // salva em um arquivo .txt os dados feitos no registro
    QFile arquivo("investidores.txt");
    if (arquivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream saida(&arquivo); // escreve os dados no arquivo
        saida << nome << "," << email << "," << cpf << "," << senha << "\n"; // escreve nesta ordem
        arquivo.close();
        return true;
    }
    return false;
}

bool Investidor::validarLogin(QString cpfDigitado, QString senhaDigitada) { // validar login
    QFile arquivo("investidores.txt");
    if (arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) { // pega os dados do arquivo e detecta , para saber o nome, email etc...
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