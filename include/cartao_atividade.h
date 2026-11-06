#ifndef CARTAO_ATIVIDADE_H
#define CARTAO_ATIVIDADE_H

#include "identificador.h"
#include "nome.h"
#include "texto.h"
#include "prioridade.h"
#include "estado.h"
#include "tamanho.h"
#include "timestamp.h"

/**
 * @file cartao_atividade.h
 * @brief Declaração da entidade Cartão de atividade.
 */

/**
 * @brief Entidade que representa um cartão de atividade de um quadro Kanban.
 *
 * Um cartão tem identificador, nome, descrição, prioridade, estado, tamanho
 * e três instantes: entrada, início e término. O identificador identifica o
 * cartão (chave primária) e não pode ser alterado depois que o cartão é
 * criado no sistema.
 *
 * Os instantes servem ao cálculo das métricas do quadro:
 * - entrada: momento em que o cartão entra na coluna A FAZER;
 * - início: momento em que o cartão entra na coluna FAZENDO;
 * - término: momento em que o cartão chega à coluna FEITO.
 *
 * O tempo de ciclo vai do início ao término, e o lead time vai da entrada ao
 * término.
 *
 * Cada atributo é uma instância de classe domínio e já chega validado: o
 * formato é verificado pelo método @c setValor da própria classe domínio.
 * Por isso os métodos set desta classe não lançam exceção.
 *
 * Os atributos devem ser definidos pelos métodos set antes de serem lidos
 * pelos métodos get. Início e término só têm valor depois que o cartão é
 * movido para FAZENDO e para FEITO, respectivamente.
 *
 * Relacionamentos (mantidos pela camada de serviço): todo cartão pertence a
 * exatamente um quadro e tem exatamente uma pessoa como desenvolvedora.
 */
class CartaoAtividade {
    private:
        Identificador identificador; ///< Identificador do cartão (chave primária).
        Nome nome;                   ///< Nome do cartão.
        Texto descricao;             ///< Descrição da atividade.
        Prioridade prioridade;       ///< Prioridade: ALTA, MEDIA ou BAIXA.
        Estado estado;               ///< Coluna do cartão: A FAZER, FAZENDO ou FEITO.
        Tamanho tamanho;             ///< Tamanho: GRANDE, MÉDIO ou PEQUENO.
        Timestamp entrada;           ///< Instante de entrada na coluna A FAZER.
        Timestamp inicio;            ///< Instante de entrada na coluna FAZENDO.
        Timestamp termino;           ///< Instante de chegada à coluna FEITO.

    public:
        /**
         * @brief Define o identificador do cartão.
         * @param identificador Identificador já validado pelo domínio Identificador.
         */
        void setIdentificador(const Identificador& identificador);

        /**
         * @brief Devolve o identificador do cartão.
         * @return Identificador do cartão.
         */
        Identificador getIdentificador() const;

        /**
         * @brief Define o nome do cartão.
         * @param nome Nome já validado pelo domínio Nome.
         */
        void setNome(const Nome& nome);

        /**
         * @brief Devolve o nome do cartão.
         * @return Nome do cartão.
         */
        Nome getNome() const;

        /**
         * @brief Define a descrição da atividade.
         * @param descricao Descrição já validada pelo domínio Texto.
         */
        void setDescricao(const Texto& descricao);

        /**
         * @brief Devolve a descrição da atividade.
         * @return Descrição da atividade.
         */
        Texto getDescricao() const;

        /**
         * @brief Define a prioridade da atividade.
         * @param prioridade Prioridade já validada pelo domínio Prioridade.
         */
        void setPrioridade(const Prioridade& prioridade);

        /**
         * @brief Devolve a prioridade da atividade.
         * @return Prioridade da atividade.
         */
        Prioridade getPrioridade() const;

        /**
         * @brief Define o estado (coluna) do cartão.
         *
         * Pelo serviço de mover, o estado só avança de A FAZER para FAZENDO
         * e de FAZENDO para FEITO.
         * @param estado Estado já validado pelo domínio Estado.
         */
        void setEstado(const Estado& estado);

        /**
         * @brief Devolve o estado (coluna) do cartão.
         * @return Estado do cartão.
         */
        Estado getEstado() const;

        /**
         * @brief Define o tamanho da atividade.
         * @param tamanho Tamanho já validado pelo domínio Tamanho.
         */
        void setTamanho(const Tamanho& tamanho);

        /**
         * @brief Devolve o tamanho da atividade.
         * @return Tamanho da atividade.
         */
        Tamanho getTamanho() const;

        /**
         * @brief Define o instante de entrada do cartão na coluna A FAZER.
         * @param entrada Instante já validado pelo domínio Timestamp.
         */
        void setEntrada(const Timestamp& entrada);

        /**
         * @brief Devolve o instante de entrada do cartão na coluna A FAZER.
         * @return Instante de entrada (usado no cálculo do lead time).
         */
        Timestamp getEntrada() const;

        /**
         * @brief Define o instante de início do trabalho (entrada em FAZENDO).
         * @param inicio Instante já validado pelo domínio Timestamp.
         */
        void setInicio(const Timestamp& inicio);

        /**
         * @brief Devolve o instante de início do trabalho.
         * @return Instante de entrada em FAZENDO (usado no cálculo do tempo de ciclo).
         */
        Timestamp getInicio() const;

        /**
         * @brief Define o instante de término do trabalho (chegada a FEITO).
         * @param termino Instante já validado pelo domínio Timestamp.
         */
        void setTermino(const Timestamp& termino);

        /**
         * @brief Devolve o instante de término do trabalho.
         * @return Instante de chegada a FEITO (usado nos cálculos de tempo de
         *         ciclo e de lead time).
         */
        Timestamp getTermino() const;
};

#endif // CARTAO_ATIVIDADE_H
