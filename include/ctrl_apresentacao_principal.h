#ifndef CTRL_APRESENTACAO_PRINCIPAL_H
#define CTRL_APRESENTACAO_PRINCIPAL_H

#include "iservico_projeto.h"
#include "iservico_quadro.h"

/**
 * @file ctrl_apresentacao_principal.h
 * @brief Declaração da controladora de apresentação do menu principal.
 */

/**
 * @brief Controladora de apresentação do menu principal.
 *
 * Exibida após o login, dá acesso às telas de projetos, quadros e cartões
 * por meio das interfaces da camada de serviço.
 */
class CtrlApresentacaoPrincipal {
    private:
        IServicoProjeto* servicoProjeto;    ///< Serviço de projetos.
        IServicoQuadro* servicoQuadro;      ///< Serviço de quadros.

    public:
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

        /** @brief Executa o menu principal até o usuário sair. */
        void executarMenu();
};

#endif // CTRL_APRESENTACAO_PRINCIPAL_H
