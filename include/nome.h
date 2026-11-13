#ifndef NOME_H
#define NOME_H

#include <string>
#include <stdexcept>

/**
 * @file nome.h
 * @brief Declaração do domínio Nome.
 */

/**
 * @brief Nome de pessoa, projeto, quadro ou cartão.
 *
 * De 1 a 15 caracteres, apenas letras e espaços. Não pode começar nem terminar com espaço, e todo espaço deve ser seguido de uma letra.
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Nome {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Nome.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // NOME_H
