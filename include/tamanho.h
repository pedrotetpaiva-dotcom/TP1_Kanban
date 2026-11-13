#ifndef TAMANHO_H
#define TAMANHO_H

#include <string>
#include <stdexcept>

/**
 * @file tamanho.h
 * @brief Declaração do domínio Tamanho.
 */

/**
 * @brief Tamanho estimado de um cartão de atividade.
 *
 * Valores aceitos: `GRANDE`, `MEDIO` e `PEQUENO`.
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Tamanho {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Tamanho.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // TAMANHO_H
