#ifndef SERVICO_PESSOA_H
#define SERVICO_PESSOA_H

#include "iservico_pessoa.h"

class Pessoa;

/**
 * @brief Classe concreta da Camada de Servico para a entidade Pessoa.
 *
 * Implementa as regras de negocio definidas na interface IServicoPessoa,
 * responsavel pelo gerenciamento de contas de usuario no sistema.
 */
class ServicoPessoa : public IServicoPessoa {
    public:
        /** @brief Implementacao da criacao de conta de usuario. */
        bool criar(const Pessoa& pessoa) override;

        /** @brief Implementacao da leitura de dados do usuario. */
        bool ler(Pessoa* pessoa) override;

        /** @brief Implementacao da atualizacao de dados do usuario. */
        bool atualizar(const Pessoa& pessoa) override;

        /** @brief Implementacao da exclusao de conta de usuario. */
        bool excluir(const Email& email) override;

        /** @brief Implementacao da listagem de contas registradas. */
        bool listar(std::list<Email>* emails) override;
};

#endif // SERVICO_PESSOA_H
