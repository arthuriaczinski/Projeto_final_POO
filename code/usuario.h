#ifndef USUARIO_H
#define USUARIO_H
#include <QString>

class Usuario {
protected:
    QString nome;
    QString email;
    QString cpf;
    QString senha;
public:
    Usuario(QString n, QString e, QString c, QString s);
    QString getNome() const;
    QString getEmail() const;
    QString getCpf() const;
    QString getSenha() const;
};
#endif