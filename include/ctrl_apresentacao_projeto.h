#ifndef CTRL_APRESENTACAO_PROJETO_H
#define CTRL_APRESENTACAO_PROJETO_H

#include "iservico_projeto.h"
#include "email.h"

/**
 * @file ctrl_apresentacao_projeto.h
 * @brief Declaração da controladora de apresentação de projetos.
 */

/**
 * @brief Controladora de apresentação das telas de projetos.
 *
 * Lê e valida com os domínios os dados digitados e chama o serviço por meio da
 * interface IServicoProjeto, em nome do usuário autenticado. As telas de criar, atualizar e excluir são destinadas ao gestor; o serviço recusa os demais.
 */
class CtrlApresentacaoProjeto {
    private:
        IServicoProjeto* servico;   ///< Serviço ligado a esta controladora.
        Email usuario;      ///< E-mail do usuário autenticado (solicitante).

        void telaCriar();
        void telaLer();
        void telaAtualizar();
        void telaExcluir();
        void telaListar();

    public:
        /** @brief Cria a controladora sem serviço ligado. */
        CtrlApresentacaoProjeto();

        /**
         * @brief Liga a controladora ao serviço de projetos.
         * @param servico Implementação de IServicoProjeto.
         */
        void setServico(IServicoProjeto* servico);

        /**
         * @brief Define o usuário autenticado, enviado como solicitante em cada serviço.
         * @param usuario E-mail do usuário que fez login.
         */
        void setUsuario(const Email& usuario);

        /** @brief Executa o menu de projetos até o usuário voltar. */
        void executarMenu();
};

#endif // CTRL_APRESENTACAO_PROJETO_H
