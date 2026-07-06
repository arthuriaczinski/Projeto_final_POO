# Implementação

A solução proposta pela aplicação arT invest, é a de realizar o controle de ativos financeiros (FIIs, ações nacionais, ações internacionais e poupança) de uma pessoa.

A implementação utilizou a linguagem de programação C++, baseada no paradigma de Programação orientada a objetos, garantindo encapsulamento, herança e reutilização de código, quando aplicável. Para criação da interface gráfica, utilizou-se o QT Creator, sendo a parte gráfica, totalmente implementada por linha de códigos, não foi utilizado a parte de UI do QT.

## Principais bibliotecas utilizadas e suas utilidades:

QMainWindow: Cria a janela nativa padrão do sistema operacional, servindo como base da aplicação;

QWidget: Utilizada para criar os contêineres e as telas individuais do sistema;

QStackedWidget: Gerencia uma pilha de telas (widgets), permitindo navegar entre os menus sem a necessidade de abrir novas janelas separadas;

QVBoxLayout: Gerencia e alinha a posição dos itens da interface na vertical;

QHBoxLayout: Gerencia e alinha a posição dos itens da interface na horizontal;

QGraphicsDropShadowEffect: Aplica efeitos visuais de sombreamento (sombras 3D) aos contêineres, proporcionando o aspecto moderno de Card Design à interface;

QLabel: Exibe títulos, textos fixos e mensagens de feedback/erro dinâmicas (ex: "CPF ou Senha incorretos");

QLineEdit: Cria caixas de entrada de texto em linha única para a captura de dados do usuário (ex: Nome, CPF, Senha);

QPushButton: Criação dos botões interativos do sistema (ex: "Entrar", "Registrar", "Salvar");

QComboBox: Permite a criação de um menu suspenso (lista de opções) para a escolha do tipo de ativo (ex: "FII", "Ações brasileiras", "Poupança");

QTextEdit: Caixa de texto avançada com suporte a múltiplas linhas e scrollbar automático, utilizada para exibir o relatório financeiro da carteira no formato de leitura estrita (read-only);

QListWidget: Cria uma lista interativa de itens selecionáveis (com scrollbar automático), utilizada na tela de venda para listar os ativos disponíveis;

QListWidgetItem: Representa cada dado individual de texto inserido dentro do QListWidget;

QString: Classe fundamental do Qt para manipulação de textos. Utilizada extensivamente para formatação (ex: .replace(",", ".")) e conversão de tipos (ex: .toDouble());

QStringList: Utilizado para armazenar arrays de Strings, sendo essencial para separar e organizar os dados extraídos do arquivo .txt ao encontrar um delimitador (vírgula);

QChar: Utilizado para inspecionar e tratar caracteres individuais dentro de uma String, verificando se são letras ou números (aplicado na lógica de formatação automática do CPF);

QIODevice: Classe base que fornece a interface para realizar a leitura e escrita (aquisição de dados) em dispositivos de entrada/saída;

QFile: Permite instanciar, abrir e manipular o arquivo de banco de dados local (.txt);

QTextStream: Fornece uma interface conveniente para ler e escrever dados de texto linha por linha dentro do arquivo aberto pelo QFile;

QApplication: Gerencia o fluxo de controle e as configurações principais do programa, sendo utilizado para alterar a fonte global tipográfica da aplicação.

<div align="center">

[Retroceder](projeto.md) | [Avançar](testes.md)

</div>
