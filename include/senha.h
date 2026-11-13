#ifndef SENHA_H
#define SENHA_H

#include <string>
#include <stdexcept>

/**
 * @file senha.h
 * @brief Declaração do domínio Senha.
 */

/**
 * @brief Senha de acesso de uma pessoa.
 *
 * Exatamente 5 caracteres, apenas letras e dígitos, com pelo menos uma letra e pelo menos um dígito.
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Senha {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Senha.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // SENHA_H
