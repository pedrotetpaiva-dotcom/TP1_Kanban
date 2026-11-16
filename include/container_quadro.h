#ifndef CONTAINER_QUADRO_H
#define CONTAINER_QUADRO_H

#include <list>
#include "identificador.h"
#include "quadro.h"

/**
 * @file container_quadro.h
 * @brief Declaração do contêiner de quadros.
 */

/**
 * @brief Contêiner que armazena em memória os quadros e o projeto de cada um.
 *
 * A entidade Quadro guarda apenas atributos de domínio; o relacionamento
 * "quadro pertence a um projeto" é guardado por este contêiner, que associa a
 * cada quadro o identificador do seu projeto.
 *
 * O contêiner garante apenas que não existam dois quadros com o mesmo
 * identificador, em todo o sistema. Verificar se o projeto existe ou se o
 * quadro pode ser excluído é responsabilidade da controladora de serviço.
 *
 * Todos os métodos devolvem @c bool: @c true indica que a operação foi
 * realizada e @c false indica que não foi, sem alterar o conteúdo.
 */
class ContainerQuadro {
    private:
        /** @brief Quadro armazenado junto com o seu projeto. */
        struct Registro {
            Quadro quadro;         ///< Dados do quadro.
            Identificador projeto; ///< Identificador do projeto do quadro.
        };
        std::list<Registro> container; ///< Quadros armazenados.

    public:
        /**
         * @brief Inclui um quadro em um projeto.
         * @param projeto Identificador do projeto que contém o quadro.
         * @param quadro Quadro a incluir.
         * @return @c false se já existe quadro com o mesmo identificador.
         */
        bool incluir(const Identificador& projeto, const Quadro& quadro);

        /**
         * @brief Pesquisa um quadro pelo identificador.
         * @param quadro Entrada: objeto com o identificador definido.
         *               Saída: objeto preenchido com os dados armazenados.
         * @return @c false se não existe quadro com esse identificador.
         */
        bool pesquisar(Quadro* quadro) const;

        /**
         * @brief Pesquisa o projeto de um quadro.
         * @param quadro Identificador do quadro.
         * @param projeto Saída: identificador do projeto do quadro.
         * @return @c false se não existe quadro com esse identificador.
         */
        bool pesquisarProjeto(const Identificador& quadro, Identificador* projeto) const;

        /**
         * @brief Atualiza os dados de um quadro já armazenado.
         *
         * O quadro é localizado pelo identificador, que não é alterado, e o
         * projeto também permanece o mesmo.
         * @param quadro Quadro com os novos dados.
         * @return @c false se não existe quadro com esse identificador.
         */
        bool atualizar(const Quadro& quadro);

        /**
         * @brief Remove um quadro.
         * @param quadro Identificador do quadro a remover.
         * @return @c false se não existe quadro com esse identificador.
         */
        bool remover(const Identificador& quadro);

        /**
         * @brief Informa se um projeto possui quadros.
         * @param projeto Identificador do projeto.
         * @return @c true se existe ao menos um quadro nesse projeto.
         */
        bool possuiQuadros(const Identificador& projeto) const;

        /**
         * @brief Lista os quadros de um projeto.
         * @param projeto Identificador do projeto.
         * @return Cópia da lista de quadros do projeto, na ordem de inclusão.
         *         A lista é vazia se o projeto não tem quadros.
         */
        std::list<Quadro> listarPorProjeto(const Identificador& projeto) const;
};

#endif // CONTAINER_QUADRO_H
