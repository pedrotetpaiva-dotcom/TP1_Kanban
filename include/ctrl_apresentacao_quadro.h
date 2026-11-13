#ifndef CTRL_APRESENTACAO_QUADRO_H
#define CTRL_APRESENTACAO_QUADRO_H

#include "iservico_quadro.h"
#include "email.h"

/**
 * @file ctrl_apresentacao_quadro.h
 * @brief Declaração da controladora de apresentação de quadros.
 */

/**
 * @brief Controladora de apresentação das telas de quadros.
 *
 * Lê e valida com os domínios os dados digitados e chama o serviço por meio da
 * interface IServicoQuadro, em nome do usuário autenticado. As telas de criar, atualizar e excluir são destinadas ao gestor do projeto; o serviço recusa os demais.
 */
class CtrlApresentacaoQuadro {
    private:
        IServicoQuadro* servico;   ///< Serviço ligado a esta controladora.
        Email usuario;      ///< E-mail do usuário autenticado (solicitante).

        void telaCriar();
        void telaLer();
        void telaAtualizar();
        void telaExcluir();
        void telaListar();

    public:
        /** @brief Cria a controladora sem serviço ligado. */
        CtrlApresentacaoQuadro();

        /**
         * @brief Liga a controladora ao serviço de quadros.
         * @param servico Implementação de IServicoQuadro.
         */
        void setServico(IServicoQuadro* servico);

        /**
         * @brief Define o usuário autenticado, enviado como solicitante em cada serviço.
         * @param usuario E-mail do usuário que fez login.
         */
        void setUsuario(const Email& usuario);

        /** @brief Executa o menu de quadros até o usuário voltar. */
        void executarMenu();
};

#endif // CTRL_APRESENTACAO_QUADRO_H
