#ifndef ISERVICO_AUTENTICACAO_H
#define ISERVICO_AUTENTICACAO_H

#include "email.h"
#include "senha.h"

// O "I" na frente do nome é uma boa prática para indicar que é uma Interface
class IServicoAutenticacao {
    public:
        // Método virtual puro (o "= 0" no final é o que torna a classe abstrata em C++)
        // Ele vai receber o Email e a Senha que você validou e retornar 'true' se o login der certo
        virtual bool autenticar(const Email& email, const Senha& senha) = 0;

        // Destrutor virtual (obrigatório em classes abstratas C++)
        virtual ~IServicoAutenticacao() {}
};

#endif // ISERVICO_AUTENTICACAO_H
