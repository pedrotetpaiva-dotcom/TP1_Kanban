#ifndef CTRL_SERVICO_AUTENTICACAO_H
#define CTRL_SERVICO_AUTENTICACAO_H

#include "iservico_autenticacao.h"
#include "container_pessoa.h"

/**
 * @file ctrl_servico_autenticacao.h
 * @brief Declaração da controladora de serviço de autenticação.
 */

/**
 * @brief Controladora do módulo de serviço de autenticação.
 *
 * Realiza a interface IServicoAutenticacao. Uma pessoa é autenticada quando
 * existe uma conta com o e-mail informado e a senha informada é igual à senha
 * da conta.
 */
class CtrlServicoAutenticacao : public IServicoAutenticacao {
    private:
        ContainerPessoa* containerPessoa; ///< Contêiner onde estão as contas.

    public:
        /**
         * @brief Cria a controladora ligada ao contêiner de pessoas.
         * @param containerPessoa Contêiner onde estão as contas das pessoas.
         *        Deve existir durante toda a vida da controladora.
         */
        explicit CtrlServicoAutenticacao(ContainerPessoa* containerPessoa);

        /**
         * @brief Autentica uma pessoa.
         * @param email E-mail informado pela pessoa.
         * @param senha Senha informada pela pessoa.
         * @return @c true se existe conta com esse e-mail e a senha confere;
         *         @c false caso contrário (conta inexistente ou senha errada).
         */
        bool autenticar(const Email& email, const Senha& senha) override;
};

#endif // CTRL_SERVICO_AUTENTICACAO_H
