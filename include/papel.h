#ifndef PAPEL_H
#define PAPEL_H

#include <string>
#include <stdexcept>

/**
 * @file papel.h
 * @brief Declaração do domínio Papel.
 */

/**
 * @brief Papel de uma pessoa no sistema.
 *
 * Valores aceitos: `GESTOR` e `DESENVOLVEDOR`.
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Papel {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Papel.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // PAPEL_H
