#ifndef CONTAINER_PESSOA_H
#define CONTAINER_PESSOA_H

#include <list>
#include "email.h"
#include "pessoa.h"

/**
 * @file container_pessoa.h
 * @brief Declaração do contêiner de pessoas.
 */

/**
 * @brief Contêiner que armazena em memória os objetos da entidade Pessoa.
 *
 * Os contêineres fazem parte da camada de serviço e guardam os dados; a
 * lógica de negócio (permissões, regras de exclusão) fica nas controladoras
 * de serviço. Este contêiner garante apenas que não existam duas pessoas com
 * o mesmo e-mail, que é a chave primária.
 *
 * Todos os métodos devolvem @c bool: @c true indica que a operação foi
 * realizada e @c false indica que não foi, sem alterar o conteúdo.
 */
class ContainerPessoa {
    private:
        std::list<Pessoa> container; ///< Pessoas armazenadas.

    public:
        /**
         * @brief Inclui uma pessoa.
         * @param pessoa Pessoa a incluir.
         * @return @c false se já existe pessoa com o mesmo e-mail.
         */
        bool incluir(const Pessoa& pessoa);

        /**
         * @brief Pesquisa uma pessoa pelo e-mail.
         * @param pessoa Entrada: objeto com o e-mail definido.
         *               Saída: objeto preenchido com os dados armazenados.
         * @return @c false se não existe pessoa com esse e-mail.
         */
        bool pesquisar(Pessoa* pessoa) const;

        /**
         * @brief Atualiza os dados de uma pessoa já armazenada.
         *
         * A pessoa é localizada pelo e-mail, que não é alterado.
         * @param pessoa Pessoa com os novos dados.
         * @return @c false se não existe pessoa com esse e-mail.
         */
        bool atualizar(const Pessoa& pessoa);

        /**
         * @brief Remove uma pessoa.
         * @param email E-mail da pessoa a remover.
         * @return @c false se não existe pessoa com esse e-mail.
         */
        bool remover(const Email& email);

        /**
         * @brief Lista todas as pessoas armazenadas.
         * @return Cópia da lista de pessoas, na ordem de inclusão.
         */
        std::list<Pessoa> listar() const;
};

#endif // CONTAINER_PESSOA_H
