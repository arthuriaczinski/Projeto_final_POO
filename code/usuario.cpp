#include "Usuario.h"

Usuario::Usuario(QString n, QString e, QString c, QString s)
    : nome(n), email(e), cpf(c), senha(s) {}

QString Usuario::getNome() const { return nome; }
QString Usuario::getEmail() const { return email; }
QString Usuario::getCpf() const { return cpf; }
QString Usuario::getSenha() const { return senha; }