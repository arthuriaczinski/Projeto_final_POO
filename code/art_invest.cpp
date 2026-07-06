#include "art_invest.h"
#include <QApplication>

art_invest::art_invest(QWidget *parent) : QMainWindow(parent)
{
    QFont fonte("Roboto", 10); //Fonte da letra
    QApplication::setFont(fonte);

    this->setWindowTitle("arT Invest - Desktop Edition"); // Título da janela na barra superior
    this->setMinimumSize(800, 600); // Define apenas um tamanho mínimo de tela
    this->setStyleSheet("background-color: #121212; color: #FFFFFF;"); // cor do background

    gerenciadorDeTelas = new QStackedWidget(this); // faz pilha de telas e não abrir separadas
    this->setCentralWidget(gerenciadorDeTelas);

    telaLogin = new TelaLogin(this);
    telaCadastro = new TelaCadastro(this);
    telaCarteira = new TelaCarteira(this);
    telaAdicionarAtivo = new TelaAdicionarAtivo(this);
    telaVisualizarCarteira = new TelaVisualizarCarteira(this);
    telaVenderAtivo = new TelaVenderAtivo(this);

    gerenciadorDeTelas->addWidget(telaLogin);             // Index 0
    gerenciadorDeTelas->addWidget(telaCadastro);          // Index 1
    gerenciadorDeTelas->addWidget(telaCarteira);          // Index 2
    gerenciadorDeTelas->addWidget(telaAdicionarAtivo);    // Index 3
    gerenciadorDeTelas->addWidget(telaVisualizarCarteira);// Index 4
    gerenciadorDeTelas->addWidget(telaVenderAtivo);       // Index 5


    // Login
    connect(telaLogin, &TelaLogin::tentarLogin, this, &art_invest::processarLogin);
    connect(telaLogin, &TelaLogin::irParaCadastro, this, &art_invest::irParaCadastro);

    // Cadastro
    connect(telaCadastro, &TelaCadastro::tentarCadastro, this, &art_invest::processarCadastro);
    connect(telaCadastro, &TelaCadastro::voltarLogin, this, &art_invest::voltarParaLogin);

    // Menu Carteira
    connect(telaCarteira, &TelaCarteira::acessarCarteira, this, &art_invest::irParaVisualizarCarteira);
    connect(telaCarteira, &TelaCarteira::adicionarAtivo, this, &art_invest::irParaAdicionarAtivo);
    connect(telaCarteira, &TelaCarteira::venderAtivo, this, &art_invest::irParaVenderAtivo);
    connect(telaCarteira, &TelaCarteira::sairConta, this, &art_invest::realizarLogout);

    // Adicionar Ativo
    connect(telaAdicionarAtivo, &TelaAdicionarAtivo::salvarAtivo, this, &art_invest::salvarNovoAtivo);
    connect(telaAdicionarAtivo, &TelaAdicionarAtivo::cancelar, this, &art_invest::irParaMenuPrincipal);

    // Visualizar Carteira
    connect(telaVisualizarCarteira, &TelaVisualizarCarteira::voltarMenu, this, &art_invest::irParaMenuPrincipal);

    // Vender Ativo
    connect(telaVenderAtivo, &TelaVenderAtivo::confirmarVenda, this, &art_invest::processarVenda);
    connect(telaVenderAtivo, &TelaVenderAtivo::cancelar, this, &art_invest::irParaMenuPrincipal);
}

art_invest::~art_invest() {}

void art_invest::irParaCadastro() {
    telaLogin->limparCampos();
    gerenciadorDeTelas->setCurrentIndex(1); // mostra tela de registro
}

void art_invest::voltarParaLogin() {
    gerenciadorDeTelas->setCurrentIndex(0); // mostra tela de login
}

void art_invest::irParaMenuPrincipal() {
    gerenciadorDeTelas->setCurrentIndex(2); // Volta para o menu da carteira
}

void art_invest::processarCadastro(QString nome, QString email, QString cpf, QString senha) {
    Investidor novoInvestidor(nome, email, cpf, senha); // objeto do tipo investidor
    novoInvestidor.salvarNoArquivo();
    telaCadastro->limparCampos();
    gerenciadorDeTelas->setCurrentIndex(0); // após cadastro, manda usuário pra tela de login
}

void art_invest::processarLogin(QString cpf, QString senha) {
    if (Investidor::validarLogin(cpf, senha)) { // procura CPF e senha no arquivo .TXT
        cpfLogadoAtual = cpf; // se achar, avança pro menu do usuário logado
        telaLogin->limparCampos();
        gerenciadorDeTelas->setCurrentIndex(2);
    } else {
        telaLogin->exibirErro("CPF ou Senha incorretos."); // Interface gráfica exibe o erro
    }
}

void art_invest::realizarLogout() {
    cpfLogadoAtual.clear();
    gerenciadorDeTelas->setCurrentIndex(0); // Volta para a tela de login
}

void art_invest::irParaAdicionarAtivo() {
    telaAdicionarAtivo->limparCampos();
    gerenciadorDeTelas->setCurrentIndex(3); // Mostra a tela de Adicionar Ativo
}

void art_invest::salvarNovoAtivo(QString tipo, QString nome, double preco, int quantidade) {
    Investimento novoAtivo(cpfLogadoAtual, tipo, nome, preco, quantidade); // objeto novoativo
    novoAtivo.salvarNoArquivo(); // faz escrever os ativos de acordo com o usuário
    gerenciadorDeTelas->setCurrentIndex(2); // Volta para a carteira após salvar
}

void art_invest::irParaVisualizarCarteira() {
    // A Tela não lê dados. O Controlador pede ao Model(Investimento) e envia para a Tela!
    QString relatorioFinal = Investimento::gerarRelatorioCarteira(cpfLogadoAtual);
    telaVisualizarCarteira->exibirRelatorio(relatorioFinal);
    gerenciadorDeTelas->setCurrentIndex(4);
}

void art_invest::irParaVenderAtivo() {
    // A tela carrega visualmente os dados, o controller apenas avança o index
    telaVenderAtivo->carregarAtivos(cpfLogadoAtual);
    gerenciadorDeTelas->setCurrentIndex(5); // Vai para a tela de Venda
}

void art_invest::processarVenda(QString tipoAtivo, QString nomeAtivo, QString linhaOriginal, double qtdVenda) {
    // Instanciamos o objeto REAL que representa o ativo que o usuário quer vender.
    Investimento ativoParaVender(cpfLogadoAtual, tipoAtivo, nomeAtivo, 0, 0);

    if (ativoParaVender.vender(qtdVenda)) { // acessa o metodo do objeto
        telaVenderAtivo->limparCampos();
        gerenciadorDeTelas->setCurrentIndex(2); // se for possível vender. Apaga e volta pra tela inicial
    } else { // senão for possível vender retorna um erro
        telaVenderAtivo->exibirErro("Erro: Você não possui essa quantidade!");
    }
}