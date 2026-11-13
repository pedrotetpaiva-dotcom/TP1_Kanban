#ifndef CTRL_APRESENTACAO_PRINCIPAL_H
#define CTRL_APRESENTACAO_PRINCIPAL_H

#include "iservico_projeto.h"
#include "iservico_quadro.h"
#include "iservico_cartao.h"
#include "ctrl_apresentacao.h"

/**
 * @file ctrl_apresentacao_principal.h
 * @brief Declaração da controladora de apresentação do menu principal.
 */

/**
 * @brief Controladora de apresentação do menu principal.
 *
 * Exibida após o login, dá acesso às telas de projetos, quadros e cartões
 * por meio das interfaces da camada de serviço. A tela de pessoas é a da
 * controladora de autenticação, que foi ligada a esta com setCtrlAutenticacao().
 */
class CtrlApresentacaoPrincipal {
    private:
        IServicoProjeto* servicoProjeto;    ///< Serviço de projetos.
        IServicoQuadro* servicoQuadro;      ///< Serviço de quadros.
        IServicoCartao* servicoCartao;      ///< Serviço de cartões.
        CtrlApresentacaoAutenticacao* ctrlAutenticacao; ///< Controladora que oferece as telas de pessoas.

    public:
        /** @brief Cria a controladora sem serviços ligados. */
        CtrlApresentacaoPrincipal();

        /**
         * @brief Liga a controladora ao serviço de cartões.
         * @param servico Implementação de IServicoCartao.
         */
        void setServicoCartao(IServicoCartao* servico);

        /**
         * @brief Liga a controladora à de autenticação, usada nas telas de pessoas.
         * @param ctrl Controladora de autenticação, já ligada ao serviço de pessoa.
         */
        void setCtrlAutenticacao(CtrlApresentacaoAutenticacao* ctrl);

        /**
         * @brief Liga a controladora ao serviço de projetos.
         * @param servico Implementação de IServicoProjeto.
         */
        void setServicoProjeto(IServicoProjeto* servico);

        /**
         * @brief Liga a controladora ao serviço de quadros.
         * @param servico Implementação de IServicoQuadro.
         */
        void setServicoQuadro(IServicoQuadro* servico);

        /**
         * @brief Executa o menu principal até o usuário sair.
         *
         * Obtém da controladora de autenticação o e-mail do usuário logado e o
         * repassa às controladoras de projetos, quadros e cartões.
         */
        void executarMenu();
};

#endif // CTRL_APRESENTACAO_PRINCIPAL_H
