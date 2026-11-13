#ifndef PRIORIDADE_H
#define PRIORIDADE_H

#include <string>
#include <stdexcept>

/**
 * @file prioridade.h
 * @brief Declaração do domínio Prioridade.
 */

/**
 * @brief Prioridade de um cartão de atividade.
 *
 * Valores aceitos: `ALTA`, `MEDIA` e `BAIXA`.
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Prioridade {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Prioridade.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // PRIORIDADE_H
