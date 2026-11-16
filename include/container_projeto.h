#ifndef CONTAINER_PROJETO_H
#define CONTAINER_PROJETO_H

#include <list>
#include "email.h"
#include "identificador.h"
#include "projeto.h"

/**
 * @file container_projeto.h
 * @brief Declaração do contêiner de projetos.
 */

/**
 * @brief Contêiner que armazena em memória os projetos e o gestor de cada um.
 *
 * A entidade Projeto guarda apenas atributos de domínio; o relacionamento
 * "projeto tem um gestor" é guardado por este contêiner, que associa a cada
 * projeto o e-mail da pessoa gestora.
 *
 * O contêiner garante apenas que não existam dois projetos com o mesmo
 * identificador. Verificar se o gestor existe ou se o projeto pode ser
 * excluído é responsabilidade da controladora de serviço.
 *
 * Todos os métodos devolvem @c bool: @c true indica que a operação foi
 * realizada e @c false indica que não foi, sem alterar o conteúdo.
 */
class ContainerProjeto {
    private:
        /** @brief Projeto armazenado junto com o seu gestor. */
        struct Registro {
            Projeto projeto; ///< Dados do projeto.
            Email gestor;    ///< E-mail da pessoa gestora do projeto.
        };
        std::list<Registro> container; ///< Projetos armazenados.

    public:
        /**
         * @brief Inclui um projeto com o seu gestor.
         * @param gestor E-mail da pessoa gestora do projeto.
         * @param projeto Projeto a incluir.
         * @return @c false se já existe projeto com o mesmo identificador.
         */
        bool incluir(const Email& gestor, const Projeto& projeto);

        /**
         * @brief Pesquisa um projeto pelo identificador.
         * @param projeto Entrada: objeto com o identificador definido.
         *                Saída: objeto preenchido com os dados armazenados.
         * @return @c false se não existe projeto com esse identificador.
         */
        bool pesquisar(Projeto* projeto) const;

        /**
         * @brief Pesquisa o gestor de um projeto.
         * @param projeto Identificador do projeto.
         * @param gestor Saída: e-mail do gestor do projeto.
         * @return @c false se não existe projeto com esse identificador.
         */
        bool pesquisarGestor(const Identificador& projeto, Email* gestor) const;

        /**
         * @brief Atualiza os dados de um projeto já armazenado.
         *
         * O projeto é localizado pelo identificador, que não é alterado, e o
         * gestor também permanece o mesmo.
         * @param projeto Projeto com os novos dados.
         * @return @c false se não existe projeto com esse identificador.
         */
        bool atualizar(const Projeto& projeto);

        /**
         * @brief Remove um projeto.
         * @param projeto Identificador do projeto a remover.
         * @return @c false se não existe projeto com esse identificador.
         */
        bool remover(const Identificador& projeto);

        /**
         * @brief Informa se uma pessoa é gestora de algum projeto.
         * @param gestor E-mail da pessoa.
         * @return @c true se existe ao menos um projeto com esse gestor.
         */
        bool possuiGestor(const Email& gestor) const;

        /**
         * @brief Lista todos os projetos armazenados.
         * @return Cópia da lista de projetos, na ordem de inclusão.
         */
        std::list<Projeto> listar() const;
};

#endif // CONTAINER_PROJETO_H
