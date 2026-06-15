#include "Investimento.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

Investimento::Investimento(QString cpf, QString t, QString n, double p, int q)
    : cpfDono(cpf), tipo(t), nome(n), preco(p), quantidade(q) {}

bool Investimento::salvarNoArquivo() const {
    QFile arquivoLeitura("ativos.txt");
    QStringList linhasRestantes;
    bool ativoEncontrado = false;

    if (arquivoLeitura.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream entrada(&arquivoLeitura);
        while (!entrada.atEnd()) {
            QString linha = entrada.readLine();
            QStringList dados = linha.split(",");

            // Verifica se é do usuário logado, do mesmo tipo e mesmo nome
            if (dados.size() == 5 && dados[0] == cpfDono && dados[1] == tipo && dados[2].toUpper() == nome.toUpper()) {

                double precoAntigo = dados[3].toDouble();
                int quantidadeAntiga = dados[4].toInt();

                // soma a quantidade de ativos do mesmo tipo
                int quantidadeFinal = quantidadeAntiga + quantidade;

                // calculo do preço medio
                double precoMedio = ((precoAntigo * quantidadeAntiga) + (preco * quantidade)) / quantidadeFinal;

                QString novaLinha = cpfDono + "," + tipo + "," + nome.toUpper() + "," + QString::number(precoMedio, 'f', 2) + "," + QString::number(quantidadeFinal);
                linhasRestantes.append(novaLinha);

                ativoEncontrado = true; // Se achou, soma
            } else {
                linhasRestantes.append(linha); // senão achar, mantem tudo como era antes
            }
        }
        arquivoLeitura.close();
    }

    // Se leu o arquivo todo e não encontrou (é um ativo inédito), adiciona-o ao final
    if (!ativoEncontrado) {
        QString novaLinha = cpfDono + "," + tipo + "," + nome.toUpper() + "," + QString::number(preco, 'f', 2) + "," + QString::number(quantidade);
        linhasRestantes.append(novaLinha);
    }

    // 2. REESCREVE O ARQUIVO COM OS DADOS ATUALIZADOS
    QFile arquivoEscrita("ativos.txt");
    if (arquivoEscrita.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream saida(&arquivoEscrita);
        for (int i = 0; i < linhasRestantes.size(); ++i) {
            saida << linhasRestantes[i] << "\n";
        }
        arquivoEscrita.close();
        return true;
    }

    return false;
}

bool Investimento::venderAtivo(QString cpfDono, QString nomeAtivo, int qtdVenda) {
    QFile arquivoLeitura("ativos.txt");
    QStringList linhasRestantes;
    bool sucesso = false;

    if (arquivoLeitura.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream entrada(&arquivoLeitura);
        while (!entrada.atEnd()) {
            QString linha = entrada.readLine();
            QStringList dados = linha.split(",");

            // Localiza o ativo do usuário pelo CPF e nome (convertido para maiúsculas para comparar)
            if (dados.size() == 5 && dados[0] == cpfDono && dados[2].toUpper() == nomeAtivo.toUpper()) {
                int qtdAtual = dados[4].toInt();

                if (qtdAtual > qtdVenda) {
                    // Venda parcial: mantém o ativo com quantidade reduzida
                    int novaQtd = qtdAtual - qtdVenda;
                    QString novaLinha = dados[0] + "," + dados[1] + "," + dados[2] + "," + dados[3] + "," + QString::number(novaQtd);
                    linhasRestantes.append(novaLinha);
                    sucesso = true;
                } else if (qtdAtual == qtdVenda) {
                    // Venda total: não adiciona a linha de volta (remove do arquivo)
                    sucesso = true;
                } else {
                    // Tentou vender mais do que tem: mantém como estava (erro)
                    linhasRestantes.append(linha);
                }
            } else {
                linhasRestantes.append(linha);
            }
        }
        arquivoLeitura.close();
    }

    if (sucesso) {
        QFile arquivoEscrita("ativos.txt");
        if (arquivoEscrita.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream saida(&arquivoEscrita);
            for (const QString &l : linhasRestantes) saida << l << "\n";
            arquivoEscrita.close();
        }
    }
    return sucesso;
}