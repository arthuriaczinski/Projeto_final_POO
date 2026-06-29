# Implementação

>[!NOTE] 
A solução proposta pela aplicação arT invest, é a de realizar o controle de ativos financeiros (FIIs, ações nacionais, ações internacionais e poupança) de uma pessoa.

A implementação utilizou a linguagem de programação C++, baseada no paradigma de Programação orientada a objetos, garantindo encapsulamento, herança e reutilização de código, quando aplicável. Para criação da interface gráfica, utilizou-se o QT Creator, sendo a parte gráfica, totalmente implementada por linha de códigos, não foi utilizado a parte de UI do QT.

Principais bibliotecas utilizadas e suas utilidades:

QApplication: Programa fica em execução esperando interações do usuário;

QMainWindow: Cria janela nativa padrão do sistema;

QWidget: Utilizada para criar as telas do sistema;

QStackedWidget: Permite entrar dentro de outros menus, sem abrir uma janela separada;

QVBoxLayout: Gerencia a posição dos itens na vertical;

QHBoxLayout: Gerencia a posição dos itens na horizontal;

QLabel: Exibir títulos, textos fixos e mensagens de erro ("CPF ou Senha incorretos");

QLineEdit: Cria caixas de texto para a entrada de dados ("Nome, CPF, Senha");

QPushButton: Criação de botões interativos do sistema ("Entrar, Registrar, Salvar");

QComboBox: Permite a criação de um menu suspenso para a escolha de ativo ("FII, Ações, Poupança");

QTextEdit: Caixa de texto com suporte a scrollbar, utilizado no relatório da carteira no formato somente de leitura;

QListWidget: Cria a caixa sem os dados, adiciona a scrollbar se necessário.

QListWidgetItem: Adiciona o texto no QListWidget;

QString: Classe de textos do QT (.toDouble(),.replace(",", ".");

QStringList: Utilizado para separar o texto no .TXT quado encontra uma virgula (CPF, FII);

QChar: Utilizado para verificar os dados de uma String, se o caracter é uma letra ou um número (utilizado na verificação do CPF);

QIODevice: Permite realizar a aquisição de dados do .TXT;

QFile: Abre o arquivo .TXT

QTextStream: Faz a aquisição dos dados no arquivo .TXT


<div align="center">

[Retroceder](projeto.md) | [Avançar](testes.md)

</div>
