#ifndef SERVICO_CARTAO_H
#define SERVICO_CARTAO_H

#include "iservico_cartao.h"

class CartaoAtividade;

/**
 * @brief Classe concreta da Camada de Servico para a entidade Cartao.
 *
 * Implementa as regras de negocio definidas na interface IServicoCartao,
 * incluindo movimentacao, metricas (WIP, tempos) e gestão de tarefas.
 */
class ServicoCartao : public IServicoCartao {
    public:
        /** @brief Implementacao da criacao de cartao. */
        bool criar(const Email& solicitante, const Identificador& quadro, const Email& desenvolvedor, const CartaoAtividade& cartao) override;

        /** @brief Implementacao da leitura de cartao. */
        bool ler(const Email& solicitante, CartaoAtividade* cartao) override;

        /** @brief Implementacao da atualizacao de cartao. */
        bool atualizar(const Email& solicitante, const CartaoAtividade& cartao) override;

        /** @brief Implementacao da exclusao de cartao. */
        bool excluir(const Email& solicitante, const Identificador& cartao) override;

        /** @brief Implementacao da listagem de cartoes de um quadro. */
        bool listar(const Email& solicitante, const Identificador& quadro, std::list<Identificador>* cartoes) override;

        /** @brief Implementacao da movimentacao do cartao. */
        bool mover(const Email& solicitante, const Identificador& cartao) override;

        /** @brief Implementacao do calculo de Tempo de Ciclo. */
        bool lerTempoCiclo(const Email& solicitante, const Identificador& cartao, long* minutos) override;

        /** @brief Implementacao do calculo Medio de Tempo de Ciclo. */
        bool lerTempoCicloMedio(const Email& solicitante, const Identificador& quadro, double* minutos) override;

        /** @brief Implementacao do calculo de Lead Time. */
        bool lerLeadTime(const Email& solicitante, const Identificador& cartao, long* minutos) override;

        /** @brief Implementacao do calculo Medio de Lead Time. */
        bool lerLeadTimeMedio(const Email& solicitante, const Identificador& quadro, double* minutos) override;

        /** @brief Implementacao do calculo de WIP. */
        bool lerWIP(const Email& solicitante, const Identificador& quadro, int* wip) override;
};

#endif // SERVICO_CARTAO_H
