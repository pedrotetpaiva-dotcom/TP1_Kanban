#ifndef PROJETO_H
#define PROJETO_H

#include "identificador.h"
#include "nome.h"
#include "texto.h"
#include "timestamp.h"

/**
 * @file projeto.h
 * @brief Declaração da entidade Projeto.
 */

/**
 * @brief Entidade que representa um projeto gerido pelo método Kanban.
 *
 * Um projeto tem identificador, nome, descrição, início e término. O
 * identificador identifica o projeto (chave primária) e não pode ser
 * alterado depois que o projeto é criado no sistema.
 *
 * Cada atributo é uma instância de classe domínio e já chega validado: o
 * formato é verificado pelo método @c setValor da própria classe domínio.
 * Por isso os métodos set desta classe não lançam exceção.
 *
 * Os atributos devem ser definidos pelos métodos set antes de serem lidos
 * pelos métodos get.
 *
 * Relacionamentos (mantidos pela camada de serviço): todo projeto tem
 * exatamente um gestor, que é a pessoa que o criou, e possui zero ou mais
 * quadros.
 */
class Projeto {
    private:
        Identificador identificador; ///< Identificador do projeto (chave primária).
        Nome nome;                   ///< Nome do projeto.
        Texto descricao;             ///< Descrição do projeto.
        Timestamp inicio;            ///< Data e horário de início do projeto.
        Timestamp termino;           ///< Data e horário de término do projeto.

    public:
        /**
         * @brief Define o identificador do projeto.
         * @param identificador Identificador já validado pelo domínio Identificador.
         */
        void setIdentificador(const Identificador& identificador);

        /**
         * @brief Devolve o identificador do projeto.
         * @return Identificador do projeto.
         */
        Identificador getIdentificador() const;

        /**
         * @brief Define o nome do projeto.
         * @param nome Nome já validado pelo domínio Nome.
         */
        void setNome(const Nome& nome);

        /**
         * @brief Devolve o nome do projeto.
         * @return Nome do projeto.
         */
        Nome getNome() const;

        /**
         * @brief Define a descrição do projeto.
         * @param descricao Descrição já validada pelo domínio Texto.
         */
        void setDescricao(const Texto& descricao);

        /**
         * @brief Devolve a descrição do projeto.
         * @return Descrição do projeto.
         */
        Texto getDescricao() const;

        /**
         * @brief Define a data e o horário de início do projeto.
         * @param inicio Início já validado pelo domínio Timestamp.
         */
        void setInicio(const Timestamp& inicio);

        /**
         * @brief Devolve a data e o horário de início do projeto.
         * @return Início do projeto.
         */
        Timestamp getInicio() const;

        /**
         * @brief Define a data e o horário de término do projeto.
         * @param termino Término já validado pelo domínio Timestamp.
         */
        void setTermino(const Timestamp& termino);

        /**
         * @brief Devolve a data e o horário de término do projeto.
         * @return Término do projeto.
         */
        Timestamp getTermino() const;
};

#endif // PROJETO_H
