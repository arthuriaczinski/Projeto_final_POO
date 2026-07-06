#ifndef TELAS_H
#define TELAS_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>

class TelaLogin : public QWidget {
    Q_OBJECT
public:
    explicit TelaLogin(QWidget *parent = nullptr);
    void exibirErro(const QString &msg);
    void limparCampos();
signals: // Sinais que a tela envia para o Controlador (art_invest)
    void tentarLogin(QString cpf, QString senha);
    void irParaCadastro();
private slots:
    void formatarCpf(const QString &texto);
    void dispararLogin();
private:
    QLineEdit *inputCpf;
    QLineEdit *inputSenha;
    QLabel *labelErro;
};

class TelaCadastro : public QWidget {
    Q_OBJECT
public:
    explicit TelaCadastro(QWidget *parent = nullptr);
    void limparCampos();
signals:
    void tentarCadastro(QString nome, QString email, QString cpf, QString senha);
    void voltarLogin();
private slots:
    void formatarCpfCadastro(const QString &texto);
    void dispararCadastro();
private:
    QLineEdit *inputNomeCad;
    QLineEdit *inputEmailCad;
    QLineEdit *inputCpfCad;
    QLineEdit *inputSenhaCad;
};

class TelaCarteira : public QWidget {
    Q_OBJECT
public:
    explicit TelaCarteira(QWidget *parent = nullptr);
signals:
    void acessarCarteira();
    void adicionarAtivo();
    void venderAtivo();
    void sairConta();
};


class TelaAdicionarAtivo : public QWidget {
    Q_OBJECT
public:
    explicit TelaAdicionarAtivo(QWidget *parent = nullptr);
    void limparCampos();
signals:
    void salvarAtivo(QString tipo, QString nome, double preco, int quantidade);
    void cancelar();
private slots:
    void alterarFormularioAtivo(const QString &tipo);
    void dispararSalvar();
private:
    QComboBox *comboTipoAtivo;
    QLineEdit *inputNomeAtivo;
    QLineEdit *inputPrecoAtivo;
    QLineEdit *inputQuantidadeAtivo;
};

class TelaVisualizarCarteira : public QWidget {
    Q_OBJECT
public:
    explicit TelaVisualizarCarteira(QWidget *parent = nullptr);
    void exibirRelatorio(const QString &relatorio);
signals:
    void voltarMenu();
private:
    QTextEdit *textoCarteira;
};

class TelaVenderAtivo : public QWidget {
    Q_OBJECT
public:
    explicit TelaVenderAtivo(QWidget *parent = nullptr);
    void carregarAtivos(const QString& cpfLogado);
    void limparCampos();
    void exibirErro(const QString &msg);
signals:
    void confirmarVenda(QString tipoAtivo, QString nomeAtivo, QString linhaOriginal, double qtdVenda);
    void cancelar();
private slots:
    void dispararVenda();
private:
    QListWidget *listaAtivosVenda;
    QLineEdit *inputQtdVenda;
    QLabel *labelErroVenda;
};

#endif // TELAS_H