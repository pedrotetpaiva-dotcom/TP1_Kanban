#ifndef SERVICO_QUADRO_H
#define SERVICO_QUADRO_H

#include "iservico_quadro.h"

class Quadro;

/**
 * @brief Classe concreta da Camada de Servico para a entidade Quadro.
 *
 * Implementa as regras de negocio definidas na interface IServicoQuadro,
 * garantindo a integridade dos dados antes da persistencia.
 */
class ServicoQuadro : public IServicoQuadro {
    public:
        /** @brief Implementacao da criacao de quadro. */
        bool criar(const Email& solicitante, const Identificador& projeto, const Quadro& quadro) override;

        /** @brief Implementacao da leitura de quadro. */
        bool ler(const Email& solicitante, Quadro* quadro) override;

        /** @brief Implementacao da atualizacao de quadro. */
        bool atualizar(const Email& solicitante, const Quadro& quadro) override;

        /** @brief Implementacao da exclusao de quadro. */
        bool excluir(const Email& solicitante, const Identificador& quadro) override;

        /** @brief Implementacao da listagem de quadros de um projeto. */
        bool listar(const Email& solicitante, const Identificador& projeto, std::list<Identificador>* quadros) override;
};

#endif // SERVICO_QUADRO_H
