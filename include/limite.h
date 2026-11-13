#ifndef LIMITE_H
#define LIMITE_H

#include <stdexcept>

/**
 * @file limite.h
 * @brief Declaração do domínio Limite.
 */

/**
 * @brief Limite de WIP de um quadro.
 *
 * Número máximo de cartões simultâneos na coluna FAZENDO, inteiro de 1 a 25.
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Limite {
    private:
        int valor;                  ///< Valor já validado.
        void validar(int valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do limite.
         * @param valor Número de 1 a 25.
         * @throws std::invalid_argument se o valor está fora do intervalo.
         */
        void setValor(int valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Limite atual.
         */
        int getValor() const;
};

#endif // LIMITE_H
