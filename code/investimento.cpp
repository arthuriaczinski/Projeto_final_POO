#include "Investimento.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

Investimento::Investimento(QString cpf, QString t, QString n, double p, int q) // construtor
    : cpfDono(cpf), tipo(t), nome(n), preco(p), quantidade(q) {}

bool Investimento::salvarNoArquivo() const { // cria o txt
    QString nomeArquivo = "ativos_" + cpfDono + ".txt";
    QFile arquivoLeitura(nomeArquivo);
    QStringList linhasRestantes;
    bool ativoEncontrado = false;

    QString nomeLimpo = nome.trimmed().toUpper(); // faz com que seja possivel detectar se foi escrito com letra minuscula ou maiscula, fazendo tudo virar maiuscula

    if (arquivoLeitura.open(QIODevice::ReadOnly | QIODevice::Text)) { // procura se ja tem o investimento que vai ser colocado
        QTextStream entrada(&arquivoLeitura);
        while (!entrada.atEnd()) {
            QString linha = entrada.readLine();
            QStringList dados = linha.split(","); // separa por virgula os dados dos atvios

            if (dados.size() == 5 && dados[0] == cpfDono && dados[1] == tipo && dados[2].trimmed().toUpper() == nomeLimpo) { // Verifica se é do usuário logado, do mesmo tipo e mesmo nome

                double precoAntigo = dados[3].toDouble(); // converte os dados do txt, preço e quantidade para numero
                int quantidadeAntiga = dados[4].toInt();

                if (tipo == "Poupança") {
                    double novoSaldo = precoAntigo + preco; // n  tem preço médio, portanto só soma o valor antigo e novo
                    QString novaLinha = cpfDono + "," + tipo + "," + nomeLimpo + "," + QString::number(novoSaldo, 'f', 2) + ",1"; //saldo com duas casas decimas e qtd como 1
                    linhasRestantes.append(novaLinha);
                } else {
                    // soma a quantidade de ativos do mesmo tipo
                    int quantidadeFinal = quantidadeAntiga + quantidade;

                    // calculo do preço medio para ações e fiis
                    double precoMedio = 0.0;
                    if (quantidadeFinal > 0) {
                        precoMedio = ((precoAntigo * quantidadeAntiga) + (preco * quantidade)) / quantidadeFinal;
                    }

                    QString novaLinha = cpfDono + "," + tipo + "," + nomeLimpo + "," + QString::number(precoMedio, 'f', 2) + "," + QString::number(quantidadeFinal);
                    linhasRestantes.append(novaLinha);
                }

                ativoEncontrado = true; // Se achou, soma
            } else {

                linhasRestantes.append(linha); // senão achar, mantem tudo como era antes
            }
        }
        arquivoLeitura.close();
    }

    // Se leu o arquivo todo e não encontrou o ativo, adiciona no final
    if (!ativoEncontrado) {
        QString novaLinha = cpfDono + "," + tipo + "," + nomeLimpo + "," + QString::number(preco, 'f', 2) + "," + QString::number(quantidade);
        linhasRestantes.append(novaLinha);
    }

    QFile arquivoEscrita(nomeArquivo); //atualiza a lista
    if (arquivoEscrita.open(QIODevice::WriteOnly | QIODevice::Text)) { // abre em write only
        QTextStream saida(&arquivoEscrita);
        for (int i = 0; i < linhasRestantes.size(); ++i) {
            saida << linhasRestantes[i] << "\n";
        }
        arquivoEscrita.close();
        return true;
    }

    return false;
}

bool Investimento::venderAtivo(QString cpfDono, QString nomeAtivo, double qtdVenda) {
    QString nomeArquivo = "ativos_" + cpfDono + ".txt";
    QFile arquivoLeitura(nomeArquivo);
    QStringList linhasRestantes;
    bool sucesso = false;

    QString nomeLimpo = nomeAtivo.trimmed().toUpper();

    if (arquivoLeitura.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream entrada(&arquivoLeitura);
        while (!entrada.atEnd()) {
            QString linha = entrada.readLine();
            QStringList dados = linha.split(",");
            if (dados.size() == 5 && dados[0] == cpfDono && dados[2].trimmed().toUpper() == nomeLimpo) { // Localiza o ativo do usuário pelo CPF e nome

                if (dados[1] == "Poupança") {
                    double saldoAtual = QString(dados[3]).replace(",", ".").toDouble();

                    if (saldoAtual > qtdVenda) {
                        double novoSaldo = saldoAtual - qtdVenda;
                        QString novaLinha = dados[0] + "," + dados[1] + "," + dados[2] + "," + QString::number(novoSaldo, 'f', 2) + ",1";
                        linhasRestantes.append(novaLinha);
                        sucesso = true;
                    } else if (abs(saldoAtual - qtdVenda) < 0.01) {
                        sucesso = true; // saque total zera a conta
                    } else {
                        linhasRestantes.append(linha);// Tentou sacar mais do que tem
                    }
                } else {
                    int qtdAtual = dados[4].toInt();
                    int qtdVendaInt = static_cast<int>(qtdVenda); // Converte de volta para int para ações

                    if (qtdAtual > qtdVendaInt) {

                        int novaQtd = qtdAtual - qtdVendaInt; // venda parcial do ativo
                        QString novaLinha = dados[0] + "," + dados[1] + "," + dados[2] + "," + dados[3] + "," + QString::number(novaQtd);
                        linhasRestantes.append(novaLinha);
                        sucesso = true;
                    } else if (qtdAtual == qtdVendaInt) {

                        sucesso = true;// venda total
                    } else {

                        linhasRestantes.append(linha);// Tentou vender mais do que tem
                    }
                }
            } else {
                linhasRestantes.append(linha);
            }
        }
        arquivoLeitura.close();
    }

    if (sucesso) {
        QFile arquivoEscrita(nomeArquivo);
        if (arquivoEscrita.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream saida(&arquivoEscrita);
            for (const QString &l : linhasRestantes) saida << l << "\n";
            arquivoEscrita.close();
        }
    }
    return sucesso;
}