#ifndef CTRL_APRESENTACAO_H
#define CTRL_APRESENTACAO_H

#include "email.h"
#include "senha.h"
#include "iservico_autenticacao.h"
#include "iservico_pessoa.h"

/**
 * @file ctrl_apresentacao.h
 * @brief Declaração da controladora de apresentação de acesso (login e cadastro).
 */

/**
 * @brief Controladora de apresentação da tela de acesso.
 *
 * Mostra o menu inicial, lê e valida e-mail e senha digitados e chama os
 * serviços de autenticação e de pessoa por meio das interfaces, sem conhecer
 * a implementação da camada de serviço.
 */
class CtrlApresentacaoAutenticacao {
    private:
        IServicoAutenticacao* servicoAutenticacao;  ///< Serviço de autenticação.
        IServicoPessoa* servicoPessoa;              ///< Serviço de pessoa, usado no cadastro.

    public:
        /**
         * @brief Liga a controladora ao serviço de autenticação.
         * @param servico Implementação de IServicoAutenticacao.
         */
        void setServicoAutenticacao(IServicoAutenticacao* servico);

        /**
         * @brief Liga a controladora ao serviço de pessoa.
         * @param servico Implementação de IServicoPessoa.
         */
        void setServicoPessoa(IServicoPessoa* servico);

        /**
         * @brief Executa o menu de acesso (login e cadastro de conta).
         * @return @c true se o usuário se autenticou; @c false se saiu sem entrar.
         */
        bool executarLogin();
};

#endif // CTRL_APRESENTACAO_H
