#ifndef ISERVICO_AUTENTICACAO_H
#define ISERVICO_AUTENTICACAO_H

#include "email.h"
#include "senha.h"

/**
 * @file iservico_autenticacao.h
 * @brief Interface do serviço de autenticação.
 */

/**
 * @brief Interface do serviço de autenticação, usada pela camada de apresentação.
 *
 * Implementada na camada de serviço por CtrlServicoAutenticacao.
 */
class IServicoAutenticacao {
    public:
        /**
         * @brief Verifica as credenciais de uma pessoa.
         * @param email E-mail informado no login.
         * @param senha Senha informada no login.
         * @return @c true se existe uma pessoa com esse e-mail e essa senha;
         *         @c false caso contrário.
         */
        virtual bool autenticar(const Email& email, const Senha& senha) = 0;

        /** @brief Destrutor virtual, necessário em classes abstratas. */
        virtual ~IServicoAutenticacao() {}
};

#endif // ISERVICO_AUTENTICACAO_H
