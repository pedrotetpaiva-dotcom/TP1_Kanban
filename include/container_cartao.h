#ifndef CONTAINER_CARTAO_H
#define CONTAINER_CARTAO_H

#include <list>
#include "email.h"
#include "identificador.h"
#include "cartao_atividade.h"

/**
 * @file container_cartao.h
 * @brief Declaração do contêiner de cartões de atividade.
 */

/**
 * @brief Contêiner que armazena em memória os cartões de atividade, o quadro
 *        e o desenvolvedor de cada um.
 *
 * A entidade CartaoAtividade guarda apenas atributos de domínio; os
 * relacionamentos "cartão pertence a um quadro" e "cartão tem um
 * desenvolvedor" são guardados por este contêiner, que associa a cada cartão
 * o identificador do quadro e o e-mail da pessoa desenvolvedora.
 *
 * O contêiner garante apenas que não existam dois cartões com o mesmo
 * identificador, em todo o sistema. Verificar se o quadro e o desenvolvedor
 * existem, controlar o WIP e calcular tempo de ciclo e lead time é
 * responsabilidade da controladora de serviço.
 *
 * Todos os métodos devolvem @c bool: @c true indica que a operação foi
 * realizada e @c false indica que não foi, sem alterar o conteúdo.
 */
class ContainerCartao {
    private:
        /** @brief Cartão armazenado junto com o seu quadro e o seu desenvolvedor. */
        struct Registro {
            CartaoAtividade cartao;  ///< Dados do cartão.
            Identificador quadro;    ///< Identificador do quadro do cartão.
            Email desenvolvedor;     ///< E-mail da pessoa desenvolvedora do cartão.
        };
        std::list<Registro> container; ///< Cartões armazenados.

    public:
        /**
         * @brief Inclui um cartão em um quadro, com o seu desenvolvedor.
         * @param quadro Identificador do quadro que contém o cartão.
         * @param desenvolvedor E-mail da pessoa responsável pelo cartão.
         * @param cartao Cartão a incluir.
         * @return @c false se já existe cartão com o mesmo identificador.
         */
        bool incluir(const Identificador& quadro, const Email& desenvolvedor,
                     const CartaoAtividade& cartao);

        /**
         * @brief Pesquisa um cartão pelo identificador.
         * @param cartao Entrada: objeto com o identificador definido.
         *               Saída: objeto preenchido com os dados armazenados.
         * @return @c false se não existe cartão com esse identificador.
         */
        bool pesquisar(CartaoAtividade* cartao) const;

        /**
         * @brief Pesquisa o quadro de um cartão.
         * @param cartao Identificador do cartão.
         * @param quadro Saída: identificador do quadro do cartão.
         * @return @c false se não existe cartão com esse identificador.
         */
        bool pesquisarQuadro(const Identificador& cartao, Identificador* quadro) const;

        /**
         * @brief Pesquisa o desenvolvedor de um cartão.
         * @param cartao Identificador do cartão.
         * @param desenvolvedor Saída: e-mail da pessoa desenvolvedora.
         * @return @c false se não existe cartão com esse identificador.
         */
        bool pesquisarDesenvolvedor(const Identificador& cartao, Email* desenvolvedor) const;

        /**
         * @brief Atualiza os dados de um cartão já armazenado.
         *
         * O cartão é localizado pelo identificador, que não é alterado. O
         * quadro e o desenvolvedor permanecem os mesmos. Este método também
         * grava a mudança de coluna e os instantes registrados ao mover o
         * cartão.
         * @param cartao Cartão com os novos dados.
         * @return @c false se não existe cartão com esse identificador.
         */
        bool atualizar(const CartaoAtividade& cartao);

        /**
         * @brief Remove um cartão.
         * @param cartao Identificador do cartão a remover.
         * @return @c false se não existe cartão com esse identificador.
         */
        bool remover(const Identificador& cartao);

        /**
         * @brief Informa se um quadro possui cartões.
         * @param quadro Identificador do quadro.
         * @return @c true se existe ao menos um cartão nesse quadro.
         */
        bool possuiCartoes(const Identificador& quadro) const;

        /**
         * @brief Informa se uma pessoa é desenvolvedora de algum cartão.
         * @param desenvolvedor E-mail da pessoa.
         * @return @c true se existe ao menos um cartão com esse desenvolvedor.
         */
        bool possuiCartoesDoDesenvolvedor(const Email& desenvolvedor) const;

        /**
         * @brief Lista os cartões de um quadro.
         * @param quadro Identificador do quadro.
         * @return Cópia da lista de cartões do quadro, na ordem de inclusão.
         *         A lista é vazia se o quadro não tem cartões. Os dados
         *         completos permitem calcular WIP, tempo de ciclo e lead time.
         */
        std::list<CartaoAtividade> listarPorQuadro(const Identificador& quadro) const;
};

#endif // CONTAINER_CARTAO_H
