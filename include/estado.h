#ifndef ESTADO_H
#define ESTADO_H

#include <string>
#include <stdexcept>

/**
 * @file estado.h
 * @brief Declaração do domínio Estado.
 */

/**
 * @brief Coluna em que um cartão de atividade se encontra no quadro.
 *
 * Valores aceitos: `A FAZER`, `FAZENDO` e `FEITO`.
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Estado {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Estado.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // ESTADO_H
