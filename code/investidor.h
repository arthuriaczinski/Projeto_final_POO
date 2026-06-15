#ifndef INVESTIDOR_H
#define INVESTIDOR_H
#include "Usuario.h"

class Investidor : public Usuario {
public:
    Investidor(QString n, QString e, QString c, QString s);


    bool salvarNoArquivo() const;
    static bool validarLogin(QString cpfDigitado, QString senhaDigitada);
};
#endif