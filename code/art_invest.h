#ifndef ART_INVEST_H
#define ART_INVEST_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QComboBox>
#include <QTextEdit>
#include <QListWidget>
#include <QFile>
#include <QTextStream>
#include <QStringList>


#include "investidor.h";
#include "investimento.h";

class art_invest : public QMainWindow
{
    Q_OBJECT

public:
    art_invest(QWidget *parent = nullptr);
    ~art_invest();

private slots:
    void formatarCpf(const QString &texto);
    void irParaCadastro();
    void voltarParaLogin();
    void formatarCpfCadastro(const QString &texto);

    void confirmarCadastro();
    void realizarLogin();
    void realizarLogout();

    void irParaAdicionarAtivo();
    void voltarParaCarteira();
    void salvarAtivo();

    void irParaVisualizarCarteira();
    void voltarDoVisualizarCarteira();

    void irParaVenderAtivo();
    void venderAtivoSelecionado();

private:
    QStackedWidget *gerenciadorDeTelas;
    QString cpfLogadoAtual;

    QWidget *telaLogin;
    QLineEdit *inputCpf;
    QLineEdit *inputSenha;
    QPushButton *botaoEntrar;
    QPushButton *botaoIrCadastro;
    QLabel *labelErro;

    QWidget *telaCadastro;
    QLineEdit *inputNomeCad;
    QLineEdit *inputEmailCad;
    QLineEdit *inputCpfCad;
    QLineEdit *inputSenhaCad;
    QPushButton *botaoRegistrar;
    QPushButton *botaoVoltarLogin;

    QWidget *telaCarteira;
    QLabel *labelTituloCarteira;
    QPushButton *botaoAcessarCarteira;
    QPushButton *botaoAdicionarAtivo;
    QPushButton *botaoVenderAtivo;
    QPushButton *botaoSair;

    QWidget *telaAdicionarAtivo;
    QComboBox *comboTipoAtivo;
    QLineEdit *inputNomeAtivo;
    QLineEdit *inputPrecoAtivo;
    QLineEdit *inputQuantidadeAtivo;
    QPushButton *botaoSalvarAtivo;
    QPushButton *botaoCancelarAtivo;

    QWidget *telaVisualizarCarteira;
    QTextEdit *textoCarteira;
    QPushButton *botaoVoltarVisCarteira;

    QWidget *telaVenderAtivo;
    QListWidget *listaAtivosVenda;
    QPushButton *botaoConfirmarVenda;
    QPushButton *botaoCancelarVenda;
};

#endif