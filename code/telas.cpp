#include "telas.h"
#include <QFile>
#include <QTextStream>

QString estiloInput = "QLineEdit { background-color: #1A1A1A; border: 1px solid #555555; border-radius: 10px; padding: 15px; font-size: 16px; } "
                      "QLineEdit:focus { border: 1px solid #FFC107; }"; // fica amarelo quando clica pra digitar

TelaLogin::TelaLogin(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layoutHorizontalGeral = new QHBoxLayout(this); // alinhamento automático de acordo com a tela

    QWidget *caixaLogin = new QWidget(this);
    caixaLogin->setFixedSize(450, 600); // tamanho da tela de login
    caixaLogin->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;"); // Bordas arredondadas

    // --- EFEITO DE SOMBRA ---
    QGraphicsDropShadowEffect *sombraLogin = new QGraphicsDropShadowEffect(this);
    sombraLogin->setBlurRadius(20);
    sombraLogin->setColor(QColor(0, 0, 0, 150));
    sombraLogin->setOffset(0, 5);
    caixaLogin->setGraphicsEffect(sombraLogin);

    QVBoxLayout *layoutLogin = new QVBoxLayout(caixaLogin);
    layoutLogin->setContentsMargins(40, 50, 40, 50); // margens do layout da tela de login para os botões ficarem longe dos cantos
    layoutLogin->setSpacing(20); // Espaço entre os itens dentro da tela de login

    QLabel *labelLogo = new QLabel("arT Invest", caixaLogin); // Cria o título da tela de login
    labelLogo->setAlignment(Qt::AlignCenter); // Centraliza
    labelLogo->setStyleSheet("font-size: 42px; font-weight: bold; color: #FFC107; background-color: transparent;");

    inputCpf = new QLineEdit(caixaLogin);
    inputCpf->setPlaceholderText("Digite seu CPF"); // texto some quando digita
    inputCpf->setStyleSheet(estiloInput);
    connect(inputCpf, &QLineEdit::textEdited, this, &TelaLogin::formatarCpf); // chama a função pra formatar o cpf no padrão

    inputSenha = new QLineEdit(caixaLogin);
    inputSenha->setPlaceholderText("Digite sua Senha"); // durante a digitação, some o texto
    inputSenha->setEchoMode(QLineEdit::Password); // faz a senha ficar oculta
    inputSenha->setStyleSheet(estiloInput);

    labelErro = new QLabel("", caixaLogin); // começa vazio, se a senha for errada mostrará texto
    labelErro->setAlignment(Qt::AlignCenter);
    labelErro->setStyleSheet("color: #FF4C4C; font-size: 14px; font-weight: bold; background-color: transparent;");

    QPushButton *botaoEntrar = new QPushButton("Entrar", caixaLogin); // cria um botão clicavel
    botaoEntrar->setCursor(Qt::PointingHandCursor); // Faz o mouse virar uma "mãozinha" de clique
    botaoEntrar->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FFC107, stop:1 #FFD54F); color: #000000; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } "
                               "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #E0A800, stop:1 #FFC107); } "
                               "QPushButton:pressed { background-color: #D39E00; padding-top: 17px; padding-bottom: 13px; }");

    // Conecta o pressionar da tecla Enter nos campos de texto ao clique do botão Entrar
    connect(inputCpf, &QLineEdit::returnPressed, botaoEntrar, &QPushButton::click);
    connect(inputSenha, &QLineEdit::returnPressed, botaoEntrar, &QPushButton::click);

    QPushButton *botaoIrCadastro = new QPushButton("Criar Conta", caixaLogin);  // cria um botão clicavel
    botaoIrCadastro->setCursor(Qt::PointingHandCursor);
    botaoIrCadastro->setStyleSheet("QPushButton { background-color: transparent; color: #FFC107; border: 2px solid #FFC107; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } "
                                   "QPushButton:hover { background-color: #1A1A1A; } "
                                   "QPushButton:pressed { background-color: #2A2A2A; padding-top: 17px; padding-bottom: 13px; }");

    layoutLogin->addStretch();
    layoutLogin->addWidget(labelLogo);
    layoutLogin->addSpacing(50); // 50 pixel para separar logo das caixas de texto
    layoutLogin->addWidget(inputCpf);
    layoutLogin->addWidget(inputSenha);
    layoutLogin->addWidget(labelErro);
    layoutLogin->addSpacing(20);
    layoutLogin->addWidget(botaoEntrar);
    layoutLogin->addWidget(botaoIrCadastro);
    layoutLogin->addStretch();

    layoutHorizontalGeral->addStretch();
    layoutHorizontalGeral->addWidget(caixaLogin); // centraliza na tela
    layoutHorizontalGeral->addStretch();

    connect(botaoEntrar, &QPushButton::clicked, this, &TelaLogin::dispararLogin);
    connect(botaoIrCadastro, &QPushButton::clicked, this, &TelaLogin::irParaCadastro);
}

void TelaLogin::formatarCpf(const QString &texto) {
    QString numeros = "";
    for (QChar c : texto) { // deixa digitar somente letras
        if (c.isDigit()) numeros += c; // verifica se é um numero e adiciona
    }
    if (numeros.length() > 11) numeros = numeros.left(11); // mantem apenas os 11 primeiros numeros

    QString formatado = "";
    for (int i = 0; i < numeros.length(); ++i) {
        if (i == 3 || i == 6) formatado += "."; // adiciona ponto na posição 3 ou 6
        else if (i == 9) formatado += "-"; // adiciona o - na posição 9
        formatado += numeros[i]; // adiciona o numero atual no texto formatado
    }
    inputCpf->setText(formatado);
}

void TelaLogin::dispararLogin() {
    emit tentarLogin(inputCpf->text(), inputSenha->text());
}

void TelaLogin::exibirErro(const QString &msg) {
    labelErro->setText(msg);
}

void TelaLogin::limparCampos() {
    inputCpf->clear();
    inputSenha->clear();
    labelErro->clear();
}

TelaCadastro::TelaCadastro(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layoutHorizCad = new QHBoxLayout(this);

    QWidget *caixaCad = new QWidget(this);
    caixaCad->setFixedSize(450, 680);
    caixaCad->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QGraphicsDropShadowEffect *sombraCad = new QGraphicsDropShadowEffect(this);
    sombraCad->setBlurRadius(20);
    sombraCad->setColor(QColor(0, 0, 0, 150));
    sombraCad->setOffset(0, 5);
    caixaCad->setGraphicsEffect(sombraCad);

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
    connect(inputCpfCad, &QLineEdit::textEdited, this, &TelaCadastro::formatarCpfCadastro); // formatação automática do campo cpf

    inputSenhaCad = new QLineEdit(caixaCad);
    inputSenhaCad->setPlaceholderText("Crie uma Senha");
    inputSenhaCad->setEchoMode(QLineEdit::Password);
    inputSenhaCad->setStyleSheet(estiloInput);

    QPushButton *botaoRegistrar = new QPushButton("Registrar", caixaCad);
    botaoRegistrar->setCursor(Qt::PointingHandCursor);
    botaoRegistrar->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FFC107, stop:1 #FFD54F); color: #000000; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #E0A800, stop:1 #FFC107); } QPushButton:pressed { background-color: #D39E00; padding-top: 17px; padding-bottom: 13px; }");

    QPushButton *botaoVoltarLogin = new QPushButton("Voltar", caixaCad);
    botaoVoltarLogin->setCursor(Qt::PointingHandCursor);
    botaoVoltarLogin->setStyleSheet("QPushButton { background-color: transparent; color: #FFC107; border: 2px solid #FFC107; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } QPushButton:hover { background-color: #1A1A1A; } QPushButton:pressed { background-color: #2A2A2A; padding-top: 17px; padding-bottom: 13px; }");

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

    connect(botaoRegistrar, &QPushButton::clicked, this, &TelaCadastro::dispararCadastro);
    connect(botaoVoltarLogin, &QPushButton::clicked, this, &TelaCadastro::voltarLogin);
}

void TelaCadastro::formatarCpfCadastro(const QString &texto) {
    QString numeros = "";
    for (QChar c : texto) { if (c.isDigit()) numeros += c; }
    if (numeros.length() > 11) numeros = numeros.left(11);
    QString formatado = "";
    for (int i = 0; i < numeros.length(); ++i) {
        if (i == 3 || i == 6) formatado += ".";
        else if (i == 9) formatado += "-";
        formatado += numeros[i];
    }
    inputCpfCad->setText(formatado);
}

void TelaCadastro::dispararCadastro() {
    emit tentarCadastro(inputNomeCad->text(), inputEmailCad->text(), inputCpfCad->text(), inputSenhaCad->text());
}

void TelaCadastro::limparCampos() {
    // limpa pra evitar bug de ficar preso na tela de cadastro
    inputNomeCad->clear();
    inputEmailCad->clear();
    inputCpfCad->clear();
    inputSenhaCad->clear();
}

TelaCarteira::TelaCarteira(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layoutHorizCarteira = new QHBoxLayout(this);

    QWidget *caixaCarteira = new QWidget(this);
    caixaCarteira->setFixedSize(500, 600);
    caixaCarteira->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QGraphicsDropShadowEffect *sombraCarteira = new QGraphicsDropShadowEffect(this);
    sombraCarteira->setBlurRadius(20);
    sombraCarteira->setColor(QColor(0, 0, 0, 150));
    sombraCarteira->setOffset(0, 5);
    caixaCarteira->setGraphicsEffect(sombraCarteira);

    QVBoxLayout *layoutCarteira = new QVBoxLayout(caixaCarteira);
    layoutCarteira->setContentsMargins(40, 50, 40, 50);
    layoutCarteira->setSpacing(20);

    QLabel *labelTituloCarteira = new QLabel("Área do Investidor", caixaCarteira);
    labelTituloCarteira->setAlignment(Qt::AlignCenter);
    labelTituloCarteira->setStyleSheet("font-size: 36px; font-weight: bold; color: #FFC107; background-color: transparent;");

    QString estiloPrimario = "QPushButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FFC107, stop:1 #FFD54F); color: #000000; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #E0A800, stop:1 #FFC107); } QPushButton:pressed { background-color: #D39E00; padding-top: 17px; padding-bottom: 13px; }";
    QString estiloSecundario = "QPushButton { background-color: transparent; color: #FFC107; border: 2px solid #FFC107; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } QPushButton:hover { background-color: #1A1A1A; } QPushButton:pressed { background-color: #2A2A2A; padding-top: 17px; padding-bottom: 13px; }";

    QPushButton *botaoAcessarCarteira = new QPushButton("Acessar Carteira", caixaCarteira);
    botaoAcessarCarteira->setCursor(Qt::PointingHandCursor);
    botaoAcessarCarteira->setStyleSheet(estiloPrimario);

    QPushButton *botaoAdicionarAtivo = new QPushButton("Adicionar Ativo", caixaCarteira);
    botaoAdicionarAtivo->setCursor(Qt::PointingHandCursor);
    botaoAdicionarAtivo->setStyleSheet(estiloPrimario);

    QPushButton *botaoVenderAtivo = new QPushButton("Vender Ativo", caixaCarteira);
    botaoVenderAtivo->setCursor(Qt::PointingHandCursor);
    botaoVenderAtivo->setStyleSheet(estiloPrimario);

    QPushButton *botaoSair = new QPushButton("Sair da Conta", caixaCarteira);
    botaoSair->setCursor(Qt::PointingHandCursor);
    botaoSair->setStyleSheet(estiloSecundario);

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

    connect(botaoAcessarCarteira, &QPushButton::clicked, this, &TelaCarteira::acessarCarteira);
    connect(botaoAdicionarAtivo, &QPushButton::clicked, this, &TelaCarteira::adicionarAtivo);
    connect(botaoVenderAtivo, &QPushButton::clicked, this, &TelaCarteira::venderAtivo);
    connect(botaoSair, &QPushButton::clicked, this, &TelaCarteira::sairConta);
}

TelaAdicionarAtivo::TelaAdicionarAtivo(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layoutHorizAdd = new QHBoxLayout(this);

    QWidget *caixaAdd = new QWidget(this);
    caixaAdd->setFixedSize(450, 680);
    caixaAdd->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QGraphicsDropShadowEffect *sombraAdd = new QGraphicsDropShadowEffect(this);
    sombraAdd->setBlurRadius(20);
    sombraAdd->setColor(QColor(0, 0, 0, 150));
    sombraAdd->setOffset(0, 5);
    caixaAdd->setGraphicsEffect(sombraAdd);

    QVBoxLayout *layoutAdd = new QVBoxLayout(caixaAdd);
    layoutAdd->setContentsMargins(40, 50, 40, 50);
    layoutAdd->setSpacing(15);

    QLabel *labelTituloAdd = new QLabel("Novo Ativo", caixaAdd);
    labelTituloAdd->setAlignment(Qt::AlignCenter);
    labelTituloAdd->setStyleSheet("font-size: 32px; font-weight: bold; color: #FFC107; background-color: transparent;");

    QString estiloCombo = "QComboBox { background-color: #1A1A1A; border: 1px solid #555555; border-radius: 10px; padding: 15px; font-size: 16px; color: #FFFFFF; } "
                          "QComboBox::drop-down { border: 0px; }";

    comboTipoAtivo = new QComboBox(caixaAdd); // cria uma lista clicavel
    comboTipoAtivo->addItems({"FII", "Ações brasileiras", "Ações americanas", "Poupança"}); // preenche a lista clicavel com esses nomes
    comboTipoAtivo->setStyleSheet(estiloCombo);
    connect(comboTipoAtivo, &QComboBox::currentTextChanged, this, &TelaAdicionarAtivo::alterarFormularioAtivo); // faz com que ao selecionar poupança, esconda os dados requiridos

    inputNomeAtivo = new QLineEdit(caixaAdd);
    inputNomeAtivo->setPlaceholderText("Nome (ex: MXRF11)");
    inputNomeAtivo->setStyleSheet(estiloInput);

    inputPrecoAtivo = new QLineEdit(caixaAdd);
    inputPrecoAtivo->setPlaceholderText("Preço Unitário (ex: 10.50)");
    inputPrecoAtivo->setStyleSheet(estiloInput);

    inputQuantidadeAtivo = new QLineEdit(caixaAdd);
    inputQuantidadeAtivo->setPlaceholderText("Quantidade");
    inputQuantidadeAtivo->setStyleSheet(estiloInput);

    QString estiloPrimario = "QPushButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FFC107, stop:1 #FFD54F); color: #000000; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #E0A800, stop:1 #FFC107); } QPushButton:pressed { background-color: #D39E00; padding-top: 17px; padding-bottom: 13px; }";
    QString estiloSecundario = "QPushButton { background-color: transparent; color: #FFC107; border: 2px solid #FFC107; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } QPushButton:hover { background-color: #1A1A1A; } QPushButton:pressed { background-color: #2A2A2A; padding-top: 17px; padding-bottom: 13px; }";

    QPushButton *botaoSalvarAtivo = new QPushButton("Salvar Ativo", caixaAdd);
    botaoSalvarAtivo->setCursor(Qt::PointingHandCursor);
    botaoSalvarAtivo->setStyleSheet(estiloPrimario);

    QPushButton *botaoCancelarAtivo = new QPushButton("Cancelar", caixaAdd);
    botaoCancelarAtivo->setCursor(Qt::PointingHandCursor);
    botaoCancelarAtivo->setStyleSheet(estiloSecundario);

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

    connect(botaoSalvarAtivo, &QPushButton::clicked, this, &TelaAdicionarAtivo::dispararSalvar);
    connect(botaoCancelarAtivo, &QPushButton::clicked, this, &TelaAdicionarAtivo::cancelar);
}

void TelaAdicionarAtivo::alterarFormularioAtivo(const QString &tipo) {
    if (tipo == "Poupança") {
        inputNomeAtivo->hide(); // esconde a caixa de digitar o nome do ativo
        inputQuantidadeAtivo->hide(); // esconde a quantidade do ativo
        inputPrecoAtivo->setPlaceholderText("Valor a guardar (ex: 500.00)");
    } else { // senão, deixa padrão aparecendo tudo
        inputNomeAtivo->show();
        inputQuantidadeAtivo->show();
        inputPrecoAtivo->setPlaceholderText("Preço Unitário (ex: 10.50)");
    }
}

void TelaAdicionarAtivo::dispararSalvar() {
    QString tipo = comboTipoAtivo->currentText(); // após selecionar o tipo de ativo, guarda na variavel tipo
    QString nome;
    double preco;
    int quantidade;

    if (tipo == "Poupança") {
        nome = "CONTA POUPANÇA";
        QString precoTexto = inputPrecoAtivo->text(); // pega o valor digitado e guarda em uma string
        precoTexto.replace(",", "."); // altera a , em uma eventual digitação por .
        preco = precoTexto.toDouble(); // Vira um double e guarda na variavel
        quantidade = 1; // por padrão é 1
    } else { //senão faz o padrão para um ativo, exceto poupança
        nome = inputNomeAtivo->text();
        QString precoTexto = inputPrecoAtivo->text();
        precoTexto.replace(",", ".");// altera , por .
        preco = precoTexto.toDouble();
        quantidade = inputQuantidadeAtivo->text().toInt();
    }
    emit salvarAtivo(tipo, nome, preco, quantidade);
}

void TelaAdicionarAtivo::limparCampos() {
    inputNomeAtivo->clear();
    inputPrecoAtivo->clear();
    inputQuantidadeAtivo->clear(); // limpa pra evitar eventuais erros
    comboTipoAtivo->setCurrentIndex(0); // deixa as opções pre selecionada na primeira
    alterarFormularioAtivo("FII"); // faz voltar pro layout padrão senão for poupança
}

TelaVisualizarCarteira::TelaVisualizarCarteira(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layoutHorizVis = new QHBoxLayout(this);

    QWidget *caixaVis = new QWidget(this);
    caixaVis->setFixedSize(600, 500); // Mais larga para caber os textos
    caixaVis->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QGraphicsDropShadowEffect *sombraVis = new QGraphicsDropShadowEffect(this);
    sombraVis->setBlurRadius(20);
    sombraVis->setColor(QColor(0, 0, 0, 150));
    sombraVis->setOffset(0, 5);
    caixaVis->setGraphicsEffect(sombraVis);

    QVBoxLayout *layoutVis = new QVBoxLayout(caixaVis);
    layoutVis->setContentsMargins(40, 40, 40, 40);

    QLabel *labelTituloVis = new QLabel("Minha Carteira", caixaVis);
    labelTituloVis->setAlignment(Qt::AlignCenter);
    labelTituloVis->setStyleSheet("font-size: 32px; font-weight: bold; color: #FFC107; background-color: transparent; margin-bottom: 20px;");

    textoCarteira = new QTextEdit(caixaVis);
    textoCarteira->setReadOnly(true); // O usuário não pode digitar aqui, é só para visualização
    textoCarteira->setStyleSheet("QTextEdit { background-color: #1A1A1A; color: #FFFFFF; border: 1px solid #555555; border-radius: 10px; padding: 15px; font-size: 16px; }");

    QPushButton *botaoVoltarVisCarteira = new QPushButton("Voltar ao Menu", caixaVis);
    botaoVoltarVisCarteira->setCursor(Qt::PointingHandCursor);
    botaoVoltarVisCarteira->setStyleSheet("QPushButton { background-color: transparent; color: #FFC107; border: 2px solid #FFC107; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } QPushButton:hover { background-color: #1A1A1A; } QPushButton:pressed { background-color: #2A2A2A; padding-top: 17px; padding-bottom: 13px; }");

    layoutVis->addWidget(labelTituloVis);
    layoutVis->addWidget(textoCarteira);
    layoutVis->addSpacing(20);
    layoutVis->addWidget(botaoVoltarVisCarteira);

    layoutHorizVis->addStretch();
    layoutHorizVis->addWidget(caixaVis);
    layoutHorizVis->addStretch();

    connect(botaoVoltarVisCarteira, &QPushButton::clicked, this, &TelaVisualizarCarteira::voltarMenu);
}

void TelaVisualizarCarteira::exibirRelatorio(const QString &relatorio) {
    textoCarteira->setText(relatorio);
}

TelaVenderAtivo::TelaVenderAtivo(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layoutHorizVenda = new QHBoxLayout(this);

    QWidget *caixaVenda = new QWidget(this);
    caixaVenda->setFixedSize(450, 680);
    caixaVenda->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;");

    QGraphicsDropShadowEffect *sombraVenda = new QGraphicsDropShadowEffect(this);
    sombraVenda->setBlurRadius(20);
    sombraVenda->setColor(QColor(0, 0, 0, 150));
    sombraVenda->setOffset(0, 5);
    caixaVenda->setGraphicsEffect(sombraVenda);

    QVBoxLayout *layoutVenda = new QVBoxLayout(caixaVenda);
    layoutVenda->setContentsMargins(40, 40, 40, 40);
    layoutVenda->setSpacing(15);

    QLabel *labelTituloVenda = new QLabel("Vender Ativo", caixaVenda);
    labelTituloVenda->setAlignment(Qt::AlignCenter);
    labelTituloVenda->setStyleSheet("font-size: 32px; font-weight: bold; color: #FF4C4C; background-color: transparent;");

    QLabel *labelSubVenda = new QLabel("Selecione o ativo que deseja remover:", caixaVenda);
    labelSubVenda->setStyleSheet("color: #AAAAAA; font-size: 14px; background-color: transparent;");

    listaAtivosVenda = new QListWidget(caixaVenda); // cria lista para selecionar o ativo
    listaAtivosVenda->setStyleSheet("QListWidget { background-color: #1A1A1A; color: #FFFFFF; border: 1px solid #555555; border-radius: 10px; padding: 10px; font-size: 16px; outline: 0px; } "
                                    "QListWidget::item:selected { background-color: #FF4C4C; color: white; border-radius: 5px; }");

    inputQtdVenda = new QLineEdit(caixaVenda);
    inputQtdVenda->setPlaceholderText("Qtd. / Valor a remover (ex: 12 ou 50.00)");
    inputQtdVenda->setStyleSheet(estiloInput);

    labelErroVenda = new QLabel("", caixaVenda); // mensagem de erro
    labelErroVenda->setAlignment(Qt::AlignCenter);
    labelErroVenda->setStyleSheet("color: #FF4C4C; font-size: 14px; font-weight: bold; background-color: transparent;");

    QPushButton *botaoConfirmarVenda = new QPushButton("Confirmar Venda", caixaVenda);
    botaoConfirmarVenda->setCursor(Qt::PointingHandCursor);
    botaoConfirmarVenda->setStyleSheet("QPushButton { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FF4C4C, stop:1 #FF7373); color: #FFFFFF; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } "
                                       "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #CC0000, stop:1 #FF4C4C); } "
                                       "QPushButton:pressed { background-color: #990000; padding-top: 17px; padding-bottom: 13px; }");

    QPushButton *botaoCancelarVenda = new QPushButton("Cancelar", caixaVenda);
    botaoCancelarVenda->setCursor(Qt::PointingHandCursor);
    botaoCancelarVenda->setStyleSheet("QPushButton { background-color: transparent; color: #FFC107; border: 2px solid #FFC107; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } QPushButton:hover { background-color: #1A1A1A; } QPushButton:pressed { background-color: #2A2A2A; padding-top: 17px; padding-bottom: 13px; }");

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

    connect(botaoConfirmarVenda, &QPushButton::clicked, this, &TelaVenderAtivo::dispararVenda);
    connect(botaoCancelarVenda, &QPushButton::clicked, this, &TelaVenderAtivo::cancelar);
}

void TelaVenderAtivo::carregarAtivos(const QString& cpfLogado) {
    limparCampos(); // Limpa a lista antiga para evitar duplicados
    QString nomeArquivo = "ativos_" + cpfLogado + ".txt";
    QFile arquivo(nomeArquivo);
    if (arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream entrada(&arquivo);
        while (!entrada.atEnd()) {
            QString linhaOriginal = entrada.readLine();
            QStringList dados = linhaOriginal.split(",");
            if (dados.size() == 5 && dados[0] == cpfLogado) {
                QString tipo = dados[1];
                QString nome = dados[2];
                QString quantidade = dados[4];
                QString textoBonito;
                if (tipo == "Poupança") {
                    textoBonito = tipo + " - " + nome + " | Saldo: R$ " + dados[3].replace(".", ",");
                } else {
                    textoBonito = tipo + " - " + nome + " | Qtd: " + quantidade;
                }
                QListWidgetItem *item = new QListWidgetItem(textoBonito); // permite interação
                item->setData(Qt::UserRole, linhaOriginal); // salva em userRole
                listaAtivosVenda->addItem(item); // deixa vísivel o bloco
            }
        }
        arquivo.close();
    }
}

void TelaVenderAtivo::dispararVenda() {
    QListWidgetItem *itemSelecionado = listaAtivosVenda->currentItem(); // Descobre qual item o usuário clicou
    if (!itemSelecionado) { // Valida se o usuário clicou em algum item da lista
        exibirErro("Selecione um ativo na lista!");
        return;
    }
    QString linhaParaDeletar = itemSelecionado->data(Qt::UserRole).toString(); // Qt::UserRole para resgatar a linha do .txt
    QStringList dados = linhaParaDeletar.split(","); // corta a linha pelas ,
    QString tipoAtivo = dados[1]; // Pegamos o tipo oculto
    QString nomeAtivo = dados[2];  // Nome do ativo sempre está no indice 2

    QString entradaQtd = inputQtdVenda->text();
    entradaQtd.replace(",", "."); // pega o valor e troca a , por .
    double qtdVenda = entradaQtd.toDouble();

    if (qtdVenda <= 0) { // se tentar vender 0
        exibirErro("Digite uma quantidade maior que zero!");
        return;
    }
    // A View envia os dados puros, o Controller (art_invest) cuida do banco de dados!
    emit confirmarVenda(tipoAtivo, nomeAtivo, linhaParaDeletar, qtdVenda);
}

void TelaVenderAtivo::limparCampos() {
    listaAtivosVenda->clear();
    inputQtdVenda->clear();
    labelErroVenda->clear();
}

void TelaVenderAtivo::exibirErro(const QString &msg) {
    labelErroVenda->setText(msg);
}