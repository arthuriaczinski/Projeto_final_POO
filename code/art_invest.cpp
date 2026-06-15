#include "art_invest.h"

art_invest::art_invest(QWidget *parent)
    : QMainWindow(parent) // Chama o construtor da classe mãe (qmainwindow)
{

    this->setWindowTitle("arT Invest - Desktop Edition"); // Título da janela na barra superior

    this->setMinimumSize(800, 600); // Define apenas um tamanho mínimo para o layout nunca quebrar

    this->setStyleSheet("background-color: #121212; color: #FFFFFF;"); // cor do background

    gerenciadorDeTelas = new QStackedWidget(this);
    this->setCentralWidget(gerenciadorDeTelas);

    telaLogin = new QWidget(); // tela de login

    QHBoxLayout *layoutHorizontalGeral = new QHBoxLayout(telaLogin);

    QWidget *caixaLogin = new QWidget(telaLogin);
    caixaLogin->setFixedSize(450, 600); // tamanho da tela de login
    caixaLogin->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QVBoxLayout *layoutLogin = new QVBoxLayout(caixaLogin);
    layoutLogin->setContentsMargins(40, 50, 40, 50); // margens do layout da tela de login
    layoutLogin->setSpacing(20); // Espaço entre os itens dentro da tela de login

    QLabel *labelLogo = new QLabel("arT Invest", caixaLogin); // Cria o título da tela de login
    labelLogo->setAlignment(Qt::AlignCenter); // Centraliza

    labelLogo->setStyleSheet("font-size: 42px; font-weight: bold; color: #FFC107; background-color: transparent;");

    QString estiloInput = "QLineEdit { background-color: #1A1A1A; border: 1px solid #555555; border-radius: 10px; padding: 15px; font-size: 16px; } "
                          "QLineEdit:focus { border: 1px solid #FFC107; }";

    inputCpf = new QLineEdit(caixaLogin);
    inputCpf->setPlaceholderText("Digite seu CPF");
    inputCpf->setStyleSheet(estiloInput);

    connect(inputCpf, &QLineEdit::textEdited, this, &art_invest::formatarCpf); //

    inputSenha = new QLineEdit(caixaLogin);
    inputSenha->setPlaceholderText("Digite sua Senha");
    inputSenha->setEchoMode(QLineEdit::Password);
    inputSenha->setStyleSheet(estiloInput);

    labelErro = new QLabel("", caixaLogin);
    labelErro->setAlignment(Qt::AlignCenter);
    labelErro->setStyleSheet("color: #FF4C4C; font-size: 14px; font-weight: bold; background-color: transparent;");

    botaoEntrar = new QPushButton("Entrar", caixaLogin);
    botaoEntrar->setCursor(Qt::PointingHandCursor); // Faz o mouse virar uma "mãozinha" de clique
    botaoEntrar->setStyleSheet("QPushButton { background-color: #FFC107; color: #000000; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } "
                               "QPushButton:hover { background-color: #E0A800; }");

    botaoIrCadastro = new QPushButton("Criar Conta", caixaLogin);
    botaoIrCadastro->setCursor(Qt::PointingHandCursor);
    botaoIrCadastro->setStyleSheet("QPushButton { background-color: transparent; color: #FFC107; border: 2px solid #FFC107; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } "
                                   "QPushButton:hover { background-color: #1A1A1A; }");

    layoutLogin->addStretch();
    layoutLogin->addWidget(labelLogo);
    layoutLogin->addSpacing(50);
    layoutLogin->addWidget(inputCpf);
    layoutLogin->addWidget(inputSenha);
    layoutLogin->addWidget(labelErro);
    layoutLogin->addSpacing(20);
    layoutLogin->addWidget(botaoEntrar);
    layoutLogin->addWidget(botaoIrCadastro);
    layoutLogin->addStretch();

    layoutHorizontalGeral->addStretch();
    layoutHorizontalGeral->addWidget(caixaLogin);
    layoutHorizontalGeral->addStretch();

    telaCadastro = new QWidget();
    QHBoxLayout *layoutHorizCad = new QHBoxLayout(telaCadastro); // Molas para centralizar

    QWidget *caixaCad = new QWidget(telaCadastro);
    caixaCad->setFixedSize(450, 680);
    caixaCad->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QVBoxLayout *layoutCad = new QVBoxLayout(caixaCad);
    layoutCad->setContentsMargins(40, 50, 40, 50);
    layoutCad->setSpacing(15);

    QLabel *labelTituloCad = new QLabel("Novo Investidor", caixaCad);
    labelTituloCad->setAlignment(Qt::AlignCenter);
    labelTituloCad->setStyleSheet("font-size: 32px; font-weight: bold; color: #FFC107; background-color: transparent;");

    inputNomeCad = new QLineEdit(caixaCad);
    inputNomeCad->setPlaceholderText("Nome Completo");
    inputNomeCad->setStyleSheet(estiloInput);
    inputEmailCad = new QLineEdit(caixaCad);
    inputEmailCad->setPlaceholderText("E-mail");
    inputEmailCad->setStyleSheet(estiloInput);
    inputCpfCad = new QLineEdit(caixaCad);
    inputCpfCad->setPlaceholderText("CPF");
    inputCpfCad->setStyleSheet(estiloInput);
    // Liga a formatação em tempo real também no campo do CPF do cadastro
    connect(inputCpfCad, &QLineEdit::textEdited, this, &art_invest::formatarCpfCadastro);
    inputSenhaCad = new QLineEdit(caixaCad);
    inputSenhaCad->setPlaceholderText("Crie uma Senha");
    inputSenhaCad->setEchoMode(QLineEdit::Password);
    inputSenhaCad->setStyleSheet(estiloInput);
    botaoRegistrar = new QPushButton("Registrar", caixaCad);
    botaoRegistrar->setCursor(Qt::PointingHandCursor);
    botaoRegistrar->setStyleSheet(botaoEntrar->styleSheet()); // Copia o estilo do botão entrar
    botaoVoltarLogin = new QPushButton("Voltar", caixaCad);
    botaoVoltarLogin->setCursor(Qt::PointingHandCursor);
    botaoVoltarLogin->setStyleSheet(botaoIrCadastro->styleSheet()); // Copia o estilo do botão secundário

    layoutCad->addStretch();
    layoutCad->addWidget(labelTituloCad);
    layoutCad->addSpacing(30);
    layoutCad->addWidget(inputNomeCad);
    layoutCad->addWidget(inputEmailCad);
    layoutCad->addWidget(inputCpfCad);
    layoutCad->addWidget(inputSenhaCad);
    layoutCad->addSpacing(30);
    layoutCad->addWidget(botaoRegistrar);
    layoutCad->addWidget(botaoVoltarLogin);
    layoutCad->addStretch();
    layoutHorizCad->addStretch();
    layoutHorizCad->addWidget(caixaCad);
    layoutHorizCad->addStretch();

    telaCarteira = new QWidget();
    QHBoxLayout *layoutHorizCarteira = new QHBoxLayout(telaCarteira);

    QWidget *caixaCarteira = new QWidget(telaCarteira);
    caixaCarteira->setFixedSize(500, 600);
    caixaCarteira->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");
    QVBoxLayout *layoutCarteira = new QVBoxLayout(caixaCarteira);
    layoutCarteira->setContentsMargins(40, 50, 40, 50);
    layoutCarteira->setSpacing(20);
    labelTituloCarteira = new QLabel("Área do Investidor", caixaCarteira);
    labelTituloCarteira->setAlignment(Qt::AlignCenter);
    labelTituloCarteira->setStyleSheet("font-size: 36px; font-weight: bold; color: #FFC107; background-color: transparent;");

    botaoAcessarCarteira = new QPushButton("Acessar Carteira", caixaCarteira);
    botaoAcessarCarteira->setCursor(Qt::PointingHandCursor);
    botaoAcessarCarteira->setStyleSheet(botaoEntrar->styleSheet());

    botaoAdicionarAtivo = new QPushButton("Adicionar Ativo", caixaCarteira);
    botaoAdicionarAtivo->setCursor(Qt::PointingHandCursor);
    botaoAdicionarAtivo->setStyleSheet(botaoEntrar->styleSheet());

    botaoVenderAtivo = new QPushButton("Vender Ativo", caixaCarteira);
    botaoVenderAtivo->setCursor(Qt::PointingHandCursor);
    botaoVenderAtivo->setStyleSheet(botaoEntrar->styleSheet());

    botaoSair = new QPushButton("Sair da Conta", caixaCarteira);
    botaoSair->setCursor(Qt::PointingHandCursor);
    botaoSair->setStyleSheet(botaoIrCadastro->styleSheet());

    layoutCarteira->addStretch();
    layoutCarteira->addWidget(labelTituloCarteira);
    layoutCarteira->addSpacing(40);
    layoutCarteira->addWidget(botaoAcessarCarteira);
    layoutCarteira->addWidget(botaoAdicionarAtivo);
    layoutCarteira->addWidget(botaoVenderAtivo);
    layoutCarteira->addSpacing(30);
    layoutCarteira->addWidget(botaoSair);
    layoutCarteira->addStretch();

    layoutHorizCarteira->addStretch();
    layoutHorizCarteira->addWidget(caixaCarteira);
    layoutHorizCarteira->addStretch();

    telaAdicionarAtivo = new QWidget();
    QHBoxLayout *layoutHorizAdd = new QHBoxLayout(telaAdicionarAtivo);

    QWidget *caixaAdd = new QWidget(telaAdicionarAtivo);
    caixaAdd->setFixedSize(450, 680);
    caixaAdd->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QVBoxLayout *layoutAdd = new QVBoxLayout(caixaAdd);
    layoutAdd->setContentsMargins(40, 50, 40, 50);
    layoutAdd->setSpacing(15);

    QLabel *labelTituloAdd = new QLabel("Novo Ativo", caixaAdd);
    labelTituloAdd->setAlignment(Qt::AlignCenter);
    labelTituloAdd->setStyleSheet("font-size: 32px; font-weight: bold; color: #FFC107; background-color: transparent;");

    QString estiloCombo = "QComboBox { background-color: #1A1A1A; border: 1px solid #555555; border-radius: 10px; padding: 15px; font-size: 16px; color: #FFFFFF; } "
                          "QComboBox::drop-down { border: 0px; }";

    comboTipoAtivo = new QComboBox(caixaAdd);
    comboTipoAtivo->addItems({"FII", "Ações brasileiras", "Ações americanas", "Poupança"});
    comboTipoAtivo->setStyleSheet(estiloCombo);

    inputNomeAtivo = new QLineEdit(caixaAdd);
    inputNomeAtivo->setPlaceholderText("Nome (ex: MXRF11)");
    inputNomeAtivo->setStyleSheet(estiloInput);

    inputPrecoAtivo = new QLineEdit(caixaAdd);
    inputPrecoAtivo->setPlaceholderText("Preço Unitário (ex: 10.50)");
    inputPrecoAtivo->setStyleSheet(estiloInput);

    inputQuantidadeAtivo = new QLineEdit(caixaAdd);
    inputQuantidadeAtivo->setPlaceholderText("Quantidade");
    inputQuantidadeAtivo->setStyleSheet(estiloInput);

    botaoSalvarAtivo = new QPushButton("Salvar Ativo", caixaAdd);
    botaoSalvarAtivo->setCursor(Qt::PointingHandCursor);
    botaoSalvarAtivo->setStyleSheet(botaoEntrar->styleSheet()); // Copia o estilo primário

    botaoCancelarAtivo = new QPushButton("Cancelar", caixaAdd);
    botaoCancelarAtivo->setCursor(Qt::PointingHandCursor);
    botaoCancelarAtivo->setStyleSheet(botaoIrCadastro->styleSheet()); // Copia o estilo secundário

    layoutAdd->addStretch();
    layoutAdd->addWidget(labelTituloAdd);
    layoutAdd->addSpacing(30);
    layoutAdd->addWidget(comboTipoAtivo);
    layoutAdd->addWidget(inputNomeAtivo);
    layoutAdd->addWidget(inputPrecoAtivo);
    layoutAdd->addWidget(inputQuantidadeAtivo);
    layoutAdd->addSpacing(30);
    layoutAdd->addWidget(botaoSalvarAtivo);
    layoutAdd->addWidget(botaoCancelarAtivo);
    layoutAdd->addStretch();

    layoutHorizAdd->addStretch();
    layoutHorizAdd->addWidget(caixaAdd);
    layoutHorizAdd->addStretch();

    telaVisualizarCarteira = new QWidget();
    QHBoxLayout *layoutHorizVis = new QHBoxLayout(telaVisualizarCarteira);

    QWidget *caixaVis = new QWidget(telaVisualizarCarteira);
    caixaVis->setFixedSize(600, 700);
    caixaVis->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QVBoxLayout *layoutVis = new QVBoxLayout(caixaVis);
    layoutVis->setContentsMargins(40, 40, 40, 40);

    QLabel *labelTituloVis = new QLabel("Minha Carteira", caixaVis);
    labelTituloVis->setAlignment(Qt::AlignCenter);
    labelTituloVis->setStyleSheet("font-size: 32px; font-weight: bold; color: #FFC107; background-color: transparent; margin-bottom: 20px;");

    textoCarteira = new QTextEdit(caixaVis);
    textoCarteira->setReadOnly(true); // O usuário não pode digitar aqui, é só para visualização
    textoCarteira->setStyleSheet("QTextEdit { background-color: #1A1A1A; color: #FFFFFF; border: 1px solid #555555; border-radius: 10px; padding: 15px; font-size: 16px; }");

    botaoVoltarVisCarteira = new QPushButton("Voltar ao Menu", caixaVis);
    botaoVoltarVisCarteira->setCursor(Qt::PointingHandCursor);
    botaoVoltarVisCarteira->setStyleSheet(botaoIrCadastro->styleSheet()); // Copia o estilo secundário (borda amarela)

    layoutVis->addWidget(labelTituloVis);
    layoutVis->addWidget(textoCarteira);
    layoutVis->addSpacing(20);
    layoutVis->addWidget(botaoVoltarVisCarteira);

    layoutHorizVis->addStretch();
    layoutHorizVis->addWidget(caixaVis);
    layoutHorizVis->addStretch();
    telaVenderAtivo = new QWidget();
    QHBoxLayout *layoutHorizVenda = new QHBoxLayout(telaVenderAtivo);

    QWidget *caixaVenda = new QWidget(telaVenderAtivo);
    caixaVenda->setFixedSize(450, 680);
    caixaVenda->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QVBoxLayout *layoutVenda = new QVBoxLayout(caixaVenda);
    layoutVenda->setContentsMargins(40, 40, 40, 40);
    layoutVenda->setSpacing(15);

    QLabel *labelTituloVenda = new QLabel("Vender Ativo", caixaVenda);
    labelTituloVenda->setAlignment(Qt::AlignCenter);
    labelTituloVenda->setStyleSheet("font-size: 32px; font-weight: bold; color: #FF4C4C; background-color: transparent;");

    QLabel *labelSubVenda = new QLabel("Selecione o ativo que deseja remover:", caixaVenda);
    labelSubVenda->setStyleSheet("color: #AAAAAA; font-size: 14px; background-color: transparent;");

    listaAtivosVenda = new QListWidget(caixaVenda);
    listaAtivosVenda->setStyleSheet("QListWidget { background-color: #1A1A1A; color: #FFFFFF; border: 1px solid #555555; border-radius: 10px; padding: 10px; font-size: 16px; outline: 0px; } "
                                    "QListWidget::item:selected { background-color: #FF4C4C; color: white; border-radius: 5px; }");
    inputQtdVenda = new QLineEdit(caixaVenda);
    inputQtdVenda->setPlaceholderText("Quantidade a vender (ex: 12)");
    inputQtdVenda->setStyleSheet(estiloInput);
    labelErroVenda = new QLabel("", caixaVenda); // mensagem de erro
    labelErroVenda->setAlignment(Qt::AlignCenter);
    labelErroVenda->setStyleSheet("color: #FF4C4C; font-size: 14px; font-weight: bold; background-color: transparent;");
    botaoConfirmarVenda = new QPushButton("Confirmar Venda", caixaVenda);
    botaoConfirmarVenda->setCursor(Qt::PointingHandCursor);
    botaoConfirmarVenda->setStyleSheet("QPushButton { background-color: #FF4C4C; color: #FFFFFF; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } "
                                       "QPushButton:hover { background-color: #CC0000; }");

    botaoCancelarVenda = new QPushButton("Cancelar", caixaVenda);
    botaoCancelarVenda->setCursor(Qt::PointingHandCursor);
    botaoCancelarVenda->setStyleSheet(botaoIrCadastro->styleSheet());

    layoutVenda->addWidget(labelTituloVenda);
    layoutVenda->addWidget(labelSubVenda);
    layoutVenda->addWidget(listaAtivosVenda);
    layoutVenda->addWidget(inputQtdVenda);
    layoutVenda->addWidget(labelErroVenda);
    layoutVenda->addSpacing(10);
    layoutVenda->addWidget(botaoConfirmarVenda);
    layoutVenda->addWidget(botaoCancelarVenda);
    layoutHorizVenda->addStretch();
    layoutHorizVenda->addWidget(caixaVenda);
    layoutHorizVenda->addStretch();
    gerenciadorDeTelas->addWidget(telaLogin);             // Index 0
    gerenciadorDeTelas->addWidget(telaCadastro);          // Index 1
    gerenciadorDeTelas->addWidget(telaCarteira);          // Index 2
    gerenciadorDeTelas->addWidget(telaAdicionarAtivo);    // Index 3
    gerenciadorDeTelas->addWidget(telaVisualizarCarteira);// Index 4
    gerenciadorDeTelas->addWidget(telaVenderAtivo);       // Index 5

    connect(botaoIrCadastro, &QPushButton::clicked, this, &art_invest::irParaCadastro);
    connect(botaoVoltarLogin, &QPushButton::clicked, this, &art_invest::voltarParaLogin);

    connect(botaoRegistrar, &QPushButton::clicked, this, &art_invest::confirmarCadastro);
    connect(botaoEntrar, &QPushButton::clicked, this, &art_invest::realizarLogin);

    connect(botaoSair, &QPushButton::clicked, this, &art_invest::realizarLogout);

    connect(botaoAdicionarAtivo, &QPushButton::clicked, this, &art_invest::irParaAdicionarAtivo);
    connect(botaoCancelarAtivo, &QPushButton::clicked, this, &art_invest::voltarParaCarteira);
    connect(botaoSalvarAtivo, &QPushButton::clicked, this, &art_invest::salvarAtivo);

    connect(botaoAcessarCarteira, &QPushButton::clicked, this, &art_invest::irParaVisualizarCarteira);
    connect(botaoVoltarVisCarteira, &QPushButton::clicked, this, &art_invest::voltarDoVisualizarCarteira);
    connect(botaoVenderAtivo, &QPushButton::clicked, this, &art_invest::irParaVenderAtivo);
    connect(botaoCancelarVenda, &QPushButton::clicked, this, &art_invest::voltarParaCarteira);
    connect(botaoConfirmarVenda, &QPushButton::clicked, this, &art_invest::venderAtivoSelecionado);
}

art_invest::~art_invest()
{
}

void art_invest::formatarCpf(const QString &texto) {
    QString numeros = "";

    for (QChar c : texto) { // deixa digitar somente letras
        if (c.isDigit()) {
            numeros += c;
        }
    }

    if (numeros.length() > 11) {
        numeros = numeros.left(11);
    }

    QString formatado = "";
    for (int i = 0; i < numeros.length(); ++i) {
        if (i == 3 || i == 6) {
            formatado += ".";
        } else if (i == 9) {
            formatado += "-";
        }
        formatado += numeros[i];
    }

    inputCpf->setText(formatado);
}

void art_invest::formatarCpfCadastro(const QString &texto) {
    QString numeros = "";
    for (QChar c : texto) {
        if (c.isDigit()) { numeros += c; }
    }
    if (numeros.length() > 11) { numeros = numeros.left(11); }

    QString formatado = "";
    for (int i = 0; i < numeros.length(); ++i) {
        if (i == 3 || i == 6) { formatado += "."; }
        else if (i == 9) { formatado += "-"; }
        formatado += numeros[i];
    }
    inputCpfCad->setText(formatado);
}

void art_invest::irParaCadastro() {
    labelErro->clear();
    gerenciadorDeTelas->setCurrentIndex(1); // mostra tela de registro
}

void art_invest::voltarParaLogin() {
    gerenciadorDeTelas->setCurrentIndex(0); // mostra tela de login
}

void art_invest::confirmarCadastro() {
    QString nome = inputNomeCad->text();
    QString email = inputEmailCad->text();
    QString cpf = inputCpfCad->text();
    QString senha = inputSenhaCad->text();

    Investidor novoInvestidor(nome, email, cpf, senha);
    novoInvestidor.salvarNoArquivo();

    inputNomeCad->clear();
    inputEmailCad->clear();
    inputCpfCad->clear();
    inputSenhaCad->clear();

    gerenciadorDeTelas->setCurrentIndex(0);
}

void art_invest::realizarLogin() {
    QString cpfDigitado = inputCpf->text();
    QString senhaDigitada = inputSenha->text();

    if (Investidor::validarLogin(cpfDigitado, senhaDigitada)) {
        cpfLogadoAtual = cpfDigitado;

        labelErro->clear();
        inputCpf->clear();
        inputSenha->clear();

        gerenciadorDeTelas->setCurrentIndex(2);
    } else {
        labelErro->setStyleSheet("color: #FF4C4C; font-size: 14px; font-weight: bold; background-color: transparent;");
        labelErro->setText("CPF ou Senha incorretos.");
    }
}

void art_invest::realizarLogout() {
    cpfLogadoAtual.clear();
    gerenciadorDeTelas->setCurrentIndex(0); // Volta para a tela de login
}

void art_invest::irParaAdicionarAtivo() {
    inputNomeAtivo->clear();
    inputPrecoAtivo->clear();
    inputQuantidadeAtivo->clear();
    comboTipoAtivo->setCurrentIndex(0);

    gerenciadorDeTelas->setCurrentIndex(3); // Mostra a tela de Adicionar Ativo
}

void art_invest::voltarParaCarteira() {
    gerenciadorDeTelas->setCurrentIndex(2); // Volta para o menu
}

void art_invest::salvarAtivo() {
    QString tipo = comboTipoAtivo->currentText();
    QString nome = inputNomeAtivo->text();

    QString precoTexto = inputPrecoAtivo->text();
    precoTexto.replace(",", "."); // Transforma "10,50" em "10.50"
    double preco = precoTexto.toDouble();

    int quantidade = inputQuantidadeAtivo->text().toInt();

    Investimento novoAtivo(cpfLogadoAtual, tipo, nome, preco, quantidade);
    novoAtivo.salvarNoArquivo();

    gerenciadorDeTelas->setCurrentIndex(2); // Volta para a carteira após salvar
}

void art_invest::voltarDoVisualizarCarteira() {
    gerenciadorDeTelas->setCurrentIndex(2);
}

void art_invest::irParaVisualizarCarteira() {
    QString listaFii = "";
    QString listaAcoesBr = "";
    QString listaAcoesAm = "";
    QString listaPoupanca = "";

    double totalFii = 0, totalAcoesBr = 0, totalAcoesAm = 0, totalPoupanca = 0;

    QFile arquivo("ativos.txt");
    if (arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream entrada(&arquivo);

        while (!entrada.atEnd()) {
            QString linha = entrada.readLine();
            QStringList dados = linha.split(",");

            if (dados.size() == 5 && dados[0] == cpfLogadoAtual) {
                QString tipo = dados[1];
                QString nome = dados[2];
                double preco = dados[3].toDouble();
                int quantidade = dados[4].toInt();
                double valorTotalDesteAtivo = preco * quantidade;

                // formata até 2 casas decimais e remove virgula
                QString precoBR = QString::number(preco, 'f', 2).replace(".", ",");
                QString totalBR = QString::number(valorTotalDesteAtivo, 'f', 2).replace(".", ",");

                QString textoAtivo = QString("- %1 | Qtd: %2 | Preço: R$ %3 | Subtotal: R$ %4\n")
                                         .arg(nome)
                                         .arg(quantidade)
                                         .arg(precoBR)
                                         .arg(totalBR);

                if (tipo == "FII") {
                    listaFii += textoAtivo;
                    totalFii += valorTotalDesteAtivo;
                } else if (tipo == "Ações brasileiras") {
                    listaAcoesBr += textoAtivo;
                    totalAcoesBr += valorTotalDesteAtivo;
                } else if (tipo == "Ações americanas") {
                    listaAcoesAm += textoAtivo;
                    totalAcoesAm += valorTotalDesteAtivo;
                } else if (tipo == "Poupança") {
                    listaPoupanca += textoAtivo;
                    totalPoupanca += valorTotalDesteAtivo;
                }
            }
        }
        arquivo.close();
    }

    QString relatorioFinal = "";

    if (!listaFii.isEmpty()) {
        relatorioFinal += "=== FIIs (Total: R$ " + QString::number(totalFii, 'f', 2).replace(".", ",") + ") ===\n" + listaFii + "\n";
    }
    if (!listaAcoesBr.isEmpty()) {
        relatorioFinal += "=== Ações Brasileiras (Total: R$ " + QString::number(totalAcoesBr, 'f', 2).replace(".", ",") + ") ===\n" + listaAcoesBr + "\n";
    }
    if (!listaAcoesAm.isEmpty()) {
        relatorioFinal += "=== Ações Americanas (Total: R$ " + QString::number(totalAcoesAm, 'f', 2).replace(".", ",") + ") ===\n" + listaAcoesAm + "\n";
    }
    if (!listaPoupanca.isEmpty()) {
        relatorioFinal += "=== Poupança (Total: R$ " + QString::number(totalPoupanca, 'f', 2).replace(".", ",") + ") ===\n" + listaPoupanca + "\n";
    }

    if (relatorioFinal.isEmpty()) {
        relatorioFinal = "Sua carteira está vazia.\nVolte e adicione seus primeiros investimentos!";
    } else {
        double patrimonioTotal = totalFii + totalAcoesBr + totalAcoesAm + totalPoupanca;
        relatorioFinal += "\n-------------------------------------------------\n";
        relatorioFinal += "PATRIMÔNIO TOTAL: R$ " + QString::number(patrimonioTotal, 'f', 2).replace(".", ",");
    }

    textoCarteira->setText(relatorioFinal);

    gerenciadorDeTelas->setCurrentIndex(4);
}

void art_invest::irParaVenderAtivo() {
    listaAtivosVenda->clear(); // Limpa a lista antiga para evitar duplicados
    inputQtdVenda->clear();    // Limpa a quantidade anterior
    labelErroVenda->clear();   // Limpa qualquer mensagem de erro antiga

    QFile arquivo("ativos.txt");
    if (arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream entrada(&arquivo);

        while (!entrada.atEnd()) {
            QString linhaOriginal = entrada.readLine();
            QStringList dados = linhaOriginal.split(",");

            if (dados.size() == 5 && dados[0] == cpfLogadoAtual) {
                QString tipo = dados[1];
                QString nome = dados[2];
                QString quantidade = dados[4];
                QString textoBonito = tipo + " - " + nome + " | Qtd: " + quantidade;
                QListWidgetItem *item = new QListWidgetItem(textoBonito);
                item->setData(Qt::UserRole, linhaOriginal);
                listaAtivosVenda->addItem(item);
            }
        }
        arquivo.close();
    }

    gerenciadorDeTelas->setCurrentIndex(5); // Vai para a tela de Venda
}

void art_invest::venderAtivoSelecionado() {
    // Descobre qual item o usuário clicou
    QListWidgetItem *itemSelecionado = listaAtivosVenda->currentItem();

    // Valida se o usuário clicou em algum item da lista
    if (!itemSelecionado) {
        labelErroVenda->setText("Selecione um ativo na lista!");
        return;
    }

    // Usamos o Qt::UserRole para resgatar a linha do .txt
    QString linhaParaDeletar = itemSelecionado->data(Qt::UserRole).toString();
    QStringList dados = linhaParaDeletar.split(",");
    QString nomeAtivo = dados[2];  // O nome exato que está gravado no .txt é o índice 2
    int qtdVenda = inputQtdVenda->text().toInt();  // Captura a quantidade digitada no QLineEdit
    if (qtdVenda <= 0) {
        labelErroVenda->setText("Digite uma quantidade maior que zero!");
        return;
    }
    Investimento inv(cpfLogadoAtual, "", "", 0, 0);

    if (inv.venderAtivo(cpfLogadoAtual, nomeAtivo, qtdVenda)) {
        inputQtdVenda->clear();
        labelErroVenda->clear();
        gerenciadorDeTelas->setCurrentIndex(2);
    } else {
        // Se a função venderAtivo retornou false, a quantidade que o usuário digitou é maior do que ele tem de ativoss
        labelErroVenda->setText("Erro: Você não possui essa quantidade!");
    }
}