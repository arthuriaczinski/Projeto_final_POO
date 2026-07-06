#ifndef ART_INVEST_H
#define ART_INVEST_H

#include <QMainWindow>
#include <QStackedWidget>

#include "investidor.h"
#include "investimento.h"
#include "telas.h" // Inclui todas as Views

class art_invest : public QMainWindow
{
    Q_OBJECT
public:
    art_invest(QWidget *parent = nullptr);
    ~art_invest();

private slots:
    void processarLogin(QString cpf, QString senha);
    void processarCadastro(QString nome, QString email, QString cpf, QString senha);
    void realizarLogout();

    void irParaCadastro();
    void voltarParaLogin();

    void irParaMenuPrincipal();
    void irParaAdicionarAtivo();
    void irParaVisualizarCarteira();
    void irParaVenderAtivo();

    void salvarNovoAtivo(QString tipo, QString nome, double preco, int quantidade);
    void processarVenda(QString tipoAtivo, QString nomeAtivo, QString linhaOriginal, double qtdVenda);

private:
    QStackedWidget *gerenciadorDeTelas;
    QString cpfLogadoAtual;

    TelaLogin *telaLogin;
    TelaCadastro *telaCadastro;
    TelaCarteira *telaCarteira;
    TelaAdicionarAtivo *telaAdicionarAtivo;
    TelaVisualizarCarteira *telaVisualizarCarteira;
    TelaVenderAtivo *telaVenderAtivo;
};

#endif // ART_INVEST_H