#ifndef CTRL_APRESENTACAO_PROJETO_H
#define CTRL_APRESENTACAO_PROJETO_H

#include "iservico_projeto.h"

/**
 * @file ctrl_apresentacao_projeto.h
 * @brief Declaração da controladora de apresentação de projetos.
 */

/**
 * @brief Controladora de apresentação das telas de projetos.
 *
 * Lê os dados digitados e chama o serviço de projetos por meio da interface.
 */
class CtrlApresentacaoProjeto {
    private:
        IServicoProjeto* servicoProjeto;    ///< Serviço de projetos.

    public:
        /**
         * @brief Liga a controladora ao serviço de projetos.
         * @param servico Implementação de IServicoProjeto.
         */
        void setServicoProjeto(IServicoProjeto* servico);

        /** @brief Executa o menu de projetos até o usuário voltar. */
        void executarMenu();
};

#endif // CTRL_APRESENTACAO_PROJETO_H
