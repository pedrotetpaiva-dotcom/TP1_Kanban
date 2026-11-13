#ifndef TEXTO_H
#define TEXTO_H

#include <string>
#include <stdexcept>

/**
 * @file texto.h
 * @brief Declaração do domínio Texto.
 */

/**
 * @brief Texto descritivo livre, usado em descrições.
 *
 * De 1 a 30 caracteres. Começa com letra maiúscula e termina com ponto. Um sinal de pontuação não pode ser seguido de outro.
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Texto {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Texto.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // TEXTO_H
