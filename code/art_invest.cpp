#include "art_invest.h"

art_invest::art_invest(QWidget *parent)
    : QMainWindow(parent) // Chama o construtor da classe mãe qmainwindow, gera uma janela pique windows/mac
{

    QFont fonte("Roboto", 10); //Fonte da letra
    QApplication::setFont(fonte);

    this->setWindowTitle("arT Invest - Desktop Edition"); // Título da janela na barra superior

    this->setMinimumSize(800, 600); // Define apenas um tamanho mínimo de tela

    this->setStyleSheet("background-color: #121212; color: #FFFFFF;"); // cor do background

    gerenciadorDeTelas = new QStackedWidget(this); // faz pilha de telas e não abrir separadas
    this->setCentralWidget(gerenciadorDeTelas);

    telaLogin = new QWidget(); // tela de login

    QHBoxLayout *layoutHorizontalGeral = new QHBoxLayout(telaLogin); // alinhamento automático de acordo com atlea

    QWidget *caixaLogin = new QWidget(telaLogin);
    caixaLogin->setFixedSize(450, 600); // tamanho da tela de login
    caixaLogin->setStyleSheet("background-color: #2E2E2E; border-radius: 20px;"); // Bordas arredondadas

    QVBoxLayout *layoutLogin = new QVBoxLayout(caixaLogin);
    layoutLogin->setContentsMargins(40, 50, 40, 50); // margens do layout da tela de login para os botões ficarem longe dos cantos
    layoutLogin->setSpacing(20); // Espaço entre os itens dentro da tela de login

    QLabel *labelLogo = new QLabel("arT Invest", caixaLogin); // Cria o título da tela de login
    labelLogo->setAlignment(Qt::AlignCenter); // Centraliza

    labelLogo->setStyleSheet("font-size: 42px; font-weight: bold; color: #FFC107; background-color: transparent;");

    QString estiloInput = "QLineEdit { background-color: #1A1A1A; border: 1px solid #555555; border-radius: 10px; padding: 15px; font-size: 16px; } "
                          "QLineEdit:focus { border: 1px solid #FFC107; }"; // fica amarelo quando clica pra digitar

    inputCpf = new QLineEdit(caixaLogin);
    inputCpf->setPlaceholderText("Digite seu CPF"); // texto some quando digita
    inputCpf->setStyleSheet(estiloInput);

    connect(inputCpf, &QLineEdit::textEdited, this, &art_invest::formatarCpf); //chama a função pra formatar o cpf no padrão

    inputSenha = new QLineEdit(caixaLogin);
    inputSenha->setPlaceholderText("Digite sua Senha"); // durante a digitação, some o texto
    inputSenha->setEchoMode(QLineEdit::Password); // faz a senha ficar oculta
    inputSenha->setStyleSheet(estiloInput);

    labelErro = new QLabel("", caixaLogin); // começa vazio, se a senha for errada mostrará texto
    labelErro->setAlignment(Qt::AlignCenter);
    labelErro->setStyleSheet("color: #FF4C4C; font-size: 14px; font-weight: bold; background-color: transparent;");

    botaoEntrar = new QPushButton("Entrar", caixaLogin); // cria um botão clicavel
    botaoEntrar->setCursor(Qt::PointingHandCursor); // Faz o mouse virar uma "mãozinha" de clique
    botaoEntrar->setStyleSheet("QPushButton { background-color: #FFC107; color: #000000; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } "
                               "QPushButton:hover { background-color: #E0A800; }");

    // Conecta o pressionar da tecla Enter nos campos de texto ao clique do botão Entrar
    connect(inputCpf, &QLineEdit::returnPressed, botaoEntrar, &QPushButton::click);
    connect(inputSenha, &QLineEdit::returnPressed, botaoEntrar, &QPushButton::click);

    botaoIrCadastro = new QPushButton("Criar Conta", caixaLogin);  // cria um botão clicavel
    botaoIrCadastro->setCursor(Qt::PointingHandCursor);
    botaoIrCadastro->setStyleSheet("QPushButton { background-color: transparent; color: #FFC107; border: 2px solid #FFC107; border-radius: 25px; font-weight: bold; padding: 15px; font-size: 18px; } "
                                   "QPushButton:hover { background-color: #1A1A1A; }");

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

    telaCadastro = new QWidget(); //tela de cadastro
    QHBoxLayout *layoutHorizCad = new QHBoxLayout(telaCadastro);

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
    connect(inputCpfCad, &QLineEdit::textEdited, this, &art_invest::formatarCpfCadastro); // formatação automática do campo cpf

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

    telaAdicionarAtivo = new QWidget();// cria tela de adicionar ativo
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

    comboTipoAtivo = new QComboBox(caixaAdd); // cria uma lista clicavel
    comboTipoAtivo->addItems({"FII", "Ações brasileiras", "Ações americanas", "Poupança"}); // preenche a lista clicavel ocm esses nomes
    comboTipoAtivo->setStyleSheet(estiloCombo);
    connect(comboTipoAtivo, &QComboBox::currentTextChanged, this, &art_invest::alterarFormularioAtivo); // faz com que ao selecionar poupança, esconda os dados requiridos de um FII
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
    caixaVis->setFixedSize(600, 500); // Mais larga para caber os textos
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

    listaAtivosVenda = new QListWidget(caixaVenda); // cria lista para selecionar o ativo
    listaAtivosVenda->setStyleSheet("QListWidget { background-color: #1A1A1A; color: #FFFFFF; border: 1px solid #555555; border-radius: 10px; padding: 10px; font-size: 16px; outline: 0px; } "
                                    "QListWidget::item:selected { background-color: #FF4C4C; color: white; border-radius: 5px; }");
    inputQtdVenda = new QLineEdit(caixaVenda);
    inputQtdVenda->setPlaceholderText("Qtd. / Valor a remover (ex: 12 ou 50.00)");
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

    connect(botaoIrCadastro, &QPushButton::clicked, this, &art_invest::irParaCadastro); // se for clicado, realiza a ação
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
        if (c.isDigit()) { // verifica se é um numero
            numeros += c; // se for numero adiciona
        }
    }

    if (numeros.length() > 11) { // verifica se tem 11 numeros por conta de um cpf real
        numeros = numeros.left(11); // mantem apenas os 11 primeiros numeros
    }

    QString formatado = "";
    for (int i = 0; i < numeros.length(); ++i) {
        if (i == 3 || i == 6) {
            formatado += "."; // adiciona ponto na posição 3 ou 6
        } else if (i == 9) {
            formatado += "-"; // adiciona o - na posição 9
        }
        formatado += numeros[i]; // adiciona o numero atual no texto formatado
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
    QString nome = inputNomeCad->text(); // guarda na variavel nome
    QString email = inputEmailCad->text(); // guarda na varial email
    QString cpf = inputCpfCad->text(); // guarda na varialvel cpf
    QString senha = inputSenhaCad->text(); // guarda na varial senha

    Investidor novoInvestidor(nome, email, cpf, senha); // objeto do tipo investidor
    novoInvestidor.salvarNoArquivo();

    // limpa pra evitar bug de ficar preso na tela de cadastro
    inputNomeCad->clear();
    inputEmailCad->clear();
    inputCpfCad->clear();
    inputSenhaCad->clear();

    gerenciadorDeTelas->setCurrentIndex(0); // após cadastor, manda usuário pra tela de login
}

void art_invest::realizarLogin() { // função ao clicar entrar
    QString cpfDigitado = inputCpf->text(); // guarda o que foi digitado
    QString senhaDigitada = inputSenha->text();

    if (Investidor::validarLogin(cpfDigitado, senhaDigitada)) { // procura CPF e senha no arquivo .TXT e retorna true ou false
        cpfLogadoAtual = cpfDigitado; // se achar, avança pro menu do usuário logado

        labelErro->clear();
        inputCpf->clear();
        inputSenha->clear();

        gerenciadorDeTelas->setCurrentIndex(2);
    } else { // senão da erro
        labelErro->setStyleSheet("color: #FF4C4C; font-size: 14px; font-weight: bold; background-color: transparent;");
        labelErro->setText("CPF ou Senha incorretos.");
    }
}

void art_invest::realizarLogout() {
    cpfLogadoAtual.clear();
    gerenciadorDeTelas->setCurrentIndex(0); // Volta para a tela de login
}

void art_invest::alterarFormularioAtivo(const QString &tipo) {
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

void art_invest::irParaAdicionarAtivo() {// salva ativo após digitação
    inputNomeAtivo->clear();
    inputPrecoAtivo->clear();
    inputQuantidadeAtivo->clear(); // limpa pra evitar eventuais erros
    comboTipoAtivo->setCurrentIndex(0); // deixa as opções pre selecionada na primeira

    alterarFormularioAtivo("FII"); // faz voltar pro layout padrão senão for poupança

    gerenciadorDeTelas->setCurrentIndex(3); // Mostra a tela de Adicionar Ativo
}

void art_invest::voltarParaCarteira() {
    gerenciadorDeTelas->setCurrentIndex(2); // Volta para o menu
}

void art_invest::salvarAtivo() {
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
    } else {//senão fazo  padrão para um ativo, exceto poupança
        nome = inputNomeAtivo->text();
        QString precoTexto = inputPrecoAtivo->text();
        precoTexto.replace(",", ".");// altera , por .
        preco = precoTexto.toDouble();
        quantidade = inputQuantidadeAtivo->text().toInt();
    }

    Investimento novoAtivo(cpfLogadoAtual, tipo, nome, preco, quantidade); // objeto novoativo
    novoAtivo.salvarNoArquivo(); // faz escrever os ativos de acordo com o usuário

    gerenciadorDeTelas->setCurrentIndex(2); // Volta para a carteira após salvar
}

void art_invest::voltarDoVisualizarCarteira() {
    gerenciadorDeTelas->setCurrentIndex(2);
}

void art_invest::irParaVisualizarCarteira() { // lista de ativos de cada tipo
    QString listaFii = "";
    QString listaAcoesBr = "";
    QString listaAcoesAm = "";
    QString listaPoupanca = "";

    double totalFii = 0, totalAcoesBr = 0, totalAcoesAm = 0, totalPoupanca = 0; // soma valor de cada tipo de ativo

    QString nomeArquivo = "ativos_" + cpfLogadoAtual + ".txt"; // monta arquivo de ativos
    QFile arquivo(nomeArquivo); // cria arquivo
    if (arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) { // deixa em modo readonly
        QTextStream entrada(&arquivo);

        while (!entrada.atEnd()) {
            QString linha = entrada.readLine(); // guarda linha de texto na variavel linha
            QStringList dados = linha.split(","); // quando acha uma , guarda em dados

            if (dados.size() == 5 && dados[0] == cpfLogadoAtual) { // verifica se foi separado em 5 pedaços
                QString tipo = dados[1]; // guarda cada pedaço de dados na variavel certa
                QString nome = dados[2];
                double preco = dados[3].toDouble(); //transforrma em double
                int quantidade = dados[4].toInt(); // tranforma em int
                double valorTotalDesteAtivo = preco * quantidade; // valor total

                // formata até 2 casas decimais e remove virgula
                QString precoBR = QString::number(preco, 'f', 2).replace(".", ","); // faz o usuário ver , ao invés de .
                QString totalBR = QString::number(valorTotalDesteAtivo, 'f', 2).replace(".", ",");

                QString textoAtivo;
                if (tipo == "Poupança") {
                    textoAtivo = QString("- %1 | Saldo: R$ %2\n") // usado %1 e %2 pra escrita e interpretação mais facil
                                     .arg(nome)
                                     .arg(precoBR);
                } else {
                    textoAtivo = QString("- %1 | Qtd: %2 | Preço Médio: R$ %3 | Subtotal: R$ %4\n")
                                     .arg(nome)
                                     .arg(quantidade)
                                     .arg(precoBR)
                                     .arg(totalBR);
                }
                //dependendo do tipo, vai jogar determinado texto pro usuario ver
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
        arquivo.close(); // quando terminar, fecha o arquivo
    }

    QString relatorioFinal = "";
    // senão estiver vazio, escreve cada tipo de ativo da forma abaixo para o usuário ver
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

    QString nomeArquivo = "ativos_" + cpfLogadoAtual + ".txt";
    QFile arquivo(nomeArquivo);
    if (arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream entrada(&arquivo);

        while (!entrada.atEnd()) {
            QString linhaOriginal = entrada.readLine();
            QStringList dados = linhaOriginal.split(",");

            if (dados.size() == 5 && dados[0] == cpfLogadoAtual) {
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

    gerenciadorDeTelas->setCurrentIndex(5); // Vai para a tela de Venda
}

void art_invest::venderAtivoSelecionado() {

    QListWidgetItem *itemSelecionado = listaAtivosVenda->currentItem(); // Descobre qual item o usuário clicou

    if (!itemSelecionado) { // Valida se o usuário clicou em algum item da lista
        labelErroVenda->setText("Selecione um ativo na lista!");
        return;
    }
    QString linhaParaDeletar = itemSelecionado->data(Qt::UserRole).toString(); // Qt::UserRole para resgatar a linha do .txt
    QStringList dados = linhaParaDeletar.split(","); // corta a linha pelas ,
    QString nomeAtivo = dados[2];  // Nome do ativo sempre está no indice 2
    QString entradaQtd = inputQtdVenda->text();
    entradaQtd.replace(",", "."); // pega o valor e troca a , por .
    double qtdVenda = entradaQtd.toDouble();

    if (qtdVenda <= 0) { // se tentar vender 0
        labelErroVenda->setText("Digite uma quantidade maior que zero!");
        return;
    }
    Investimento inv(cpfLogadoAtual, "", "", 0, 0); // permite abrir a aba de vender mesmo sem ter nada

    if (inv.venderAtivo(cpfLogadoAtual, nomeAtivo, qtdVenda)) {
        inputQtdVenda->clear();
        labelErroVenda->clear();
        gerenciadorDeTelas->setCurrentIndex(2); // se for possível vender. Apaga e volta pra tela inicial
    } else { // senão for possível vender retorna um erro
        labelErroVenda->setText("Erro: Você não possui essa quantidade!");
    }
}