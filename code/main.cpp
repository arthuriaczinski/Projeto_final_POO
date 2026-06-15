#include "art_invest.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    art_invest w;
    w.showMaximized(); // faz ficar na tela cheia em janela
    return a.exec();
}