#ifndef CTRL_APRESENTACAO_CARTAO_H
#define CTRL_APRESENTACAO_CARTAO_H

#include "iservico_cartao.h"
#include "email.h"

/**
 * @file ctrl_apresentacao_cartao.h
 * @brief Declaração da controladora de apresentação de cartões de atividade.
 */

/**
 * @brief Controladora de apresentação das telas de cartões de atividade.
 *
 * Lê e valida com os domínios os dados digitados e chama o serviço por meio da
 * interface IServicoCartao, em nome do usuário autenticado. As telas de criar, atualizar e excluir são destinadas ao gestor do projeto; as demais, a qualquer usuário autenticado.
 */
class CtrlApresentacaoCartao {
    private:
        IServicoCartao* servico;   ///< Serviço ligado a esta controladora.
        Email usuario;      ///< E-mail do usuário autenticado (solicitante).

        void telaCriar();
        void telaLer();
        void telaAtualizar();
        void telaExcluir();
        void telaListar();
        void telaMover();
        void telaTempoCiclo();
        void telaTempoCicloMedio();
        void telaLeadTime();
        void telaLeadTimeMedio();
        void telaWIP();

    public:
        /** @brief Cria a controladora sem serviço ligado. */
        CtrlApresentacaoCartao();

        /**
         * @brief Liga a controladora ao serviço de cartões de atividade.
         * @param servico Implementação de IServicoCartao.
         */
        void setServico(IServicoCartao* servico);

        /**
         * @brief Define o usuário autenticado, enviado como solicitante em cada serviço.
         * @param usuario E-mail do usuário que fez login.
         */
        void setUsuario(const Email& usuario);

        /** @brief Executa o menu de cartões de atividade até o usuário voltar. */
        void executarMenu();
};

#endif // CTRL_APRESENTACAO_CARTAO_H
