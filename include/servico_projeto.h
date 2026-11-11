#ifndef SERVICO_PROJETO_H
#define SERVICO_PROJETO_H

#include "iservico_projeto.h"

class Projeto;

/**
 * @brief Classe concreta da Camada de Servico para a entidade Projeto.
 *
 * Implementa as regras de negocio definidas na interface IServicoProjeto,
 * conectando a interface grafica ao armazenamento de dados.
 */
class ServicoProjeto : public IServicoProjeto {
    public:
        /** @brief Implementacao da criacao de projeto. */
        bool criar(const Email& solicitante, const Projeto& projeto) override;

        /** @brief Implementacao da leitura de projeto. */
        bool ler(const Email& solicitante, Projeto* projeto) override;

        /** @brief Implementacao da atualizacao de projeto. */
        bool atualizar(const Email& solicitante, const Projeto& projeto) override;

        /** @brief Implementacao da exclusao de projeto. */
        bool excluir(const Email& solicitante, const Identificador& projeto) override;

        /** @brief Implementacao da listagem de projetos. */
        bool listar(const Email& solicitante, std::list<Identificador>* projetos) override;
};

#endif // SERVICO_PROJETO_H
