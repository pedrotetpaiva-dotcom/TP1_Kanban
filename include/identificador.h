#ifndef IDENTIFICADOR_H
#define IDENTIFICADOR_H

#include <string>
#include <stdexcept>

/**
 * @file identificador.h
 * @brief Declaração do domínio Identificador.
 */

/**
 * @brief Código de identificação de projeto, quadro ou cartão.
 *
 * Exatamente 6 caracteres: 3 letras seguidas de 3 dígitos (por exemplo `ABC123`).
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Identificador {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Identificador.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // IDENTIFICADOR_H
