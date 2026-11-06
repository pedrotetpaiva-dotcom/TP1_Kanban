#ifndef QUADRO_H
#define QUADRO_H

#include "identificador.h"
#include "nome.h"
#include "limite.h"

/**
 * @file quadro.h
 * @brief Declaração da entidade Quadro.
 */

/**
 * @brief Entidade que representa um quadro Kanban.
 *
 * Um quadro tem identificador, nome e limite de WIP (work in progress). O
 * quadro é composto pelas colunas A FAZER, FAZENDO e FEITO, e o limite
 * define o número máximo de cartões que podem estar ao mesmo tempo na coluna
 * FAZENDO. O identificador identifica o quadro (chave primária) e não pode
 * ser alterado depois que o quadro é criado no sistema.
 *
 * Cada atributo é uma instância de classe domínio e já chega validado: o
 * formato é verificado pelo método @c setValor da própria classe domínio.
 * Por isso os métodos set desta classe não lançam exceção.
 *
 * Os atributos devem ser definidos pelos métodos set antes de serem lidos
 * pelos métodos get.
 *
 * Relacionamentos (mantidos pela camada de serviço): todo quadro pertence a
 * exatamente um projeto e possui zero ou mais cartões de atividade.
 */
class Quadro {
    private:
        Identificador identificador; ///< Identificador do quadro (chave primária).
        Nome nome;                   ///< Nome do quadro.
        Limite limite;               ///< Limite de WIP da coluna FAZENDO.

    public:
        /**
         * @brief Define o identificador do quadro.
         * @param identificador Identificador já validado pelo domínio Identificador.
         */
        void setIdentificador(const Identificador& identificador);

        /**
         * @brief Devolve o identificador do quadro.
         * @return Identificador do quadro.
         */
        Identificador getIdentificador() const;

        /**
         * @brief Define o nome do quadro.
         * @param nome Nome já validado pelo domínio Nome.
         */
        void setNome(const Nome& nome);

        /**
         * @brief Devolve o nome do quadro.
         * @return Nome do quadro.
         */
        Nome getNome() const;

        /**
         * @brief Define o limite de WIP do quadro.
         * @param limite Limite já validado pelo domínio Limite (1 a 25).
         */
        void setLimite(const Limite& limite);

        /**
         * @brief Devolve o limite de WIP do quadro.
         * @return Limite de cartões simultâneos na coluna FAZENDO.
         */
        Limite getLimite() const;
};

#endif // QUADRO_H
