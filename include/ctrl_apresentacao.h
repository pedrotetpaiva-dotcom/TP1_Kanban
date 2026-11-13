#ifndef CTRL_APRESENTACAO_H
#define CTRL_APRESENTACAO_H

#include "email.h"
#include "senha.h"
#include "iservico_autenticacao.h"
#include "iservico_pessoa.h"

/**
 * @file ctrl_apresentacao.h
 * @brief Declaração da controladora de apresentação de contas (acesso e pessoas).
 */

/**
 * @brief Controladora de apresentação do módulo de autenticação e de pessoas.
 *
 * Mostra o menu de acesso (login e cadastro de conta), guarda o e-mail do
 * usuário autenticado e oferece as telas dos serviços de pessoa (ler,
 * atualizar, excluir e listar). Lê e valida os dados digitados com os domínios
 * e chama os serviços por meio das interfaces, sem conhecer a implementação da
 * camada de serviço.
 */
class CtrlApresentacaoAutenticacao {
    private:
        IServicoAutenticacao* servicoAutenticacao;  ///< Serviço de autenticação.
        IServicoPessoa* servicoPessoa;              ///< Serviço de pessoa.
        Email usuarioLogado;                        ///< E-mail do usuário autenticado.

        void cadastrar();
        void telaLer();
        void telaAtualizar();
        void telaExcluir();
        void telaListar();

    public:
        /** @brief Cria a controladora sem serviços ligados. */
        CtrlApresentacaoAutenticacao();

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
         *
         * Em caso de login bem-sucedido, guarda o e-mail do usuário, que pode
         * ser obtido com getUsuarioLogado().
         * @return @c true se o usuário se autenticou; @c false se saiu sem entrar.
         */
        bool executarLogin();

        /**
         * @brief Devolve o e-mail do usuário autenticado.
         * @return E-mail informado no último login bem-sucedido (vazio se não houve).
         */
        Email getUsuarioLogado() const;

        /**
         * @brief Executa o menu de gestão de pessoas.
         *
         * Oferece ler, atualizar, excluir e listar pessoas, até o usuário voltar.
         */
        void executarMenuPessoas();
};

#endif // CTRL_APRESENTACAO_H
