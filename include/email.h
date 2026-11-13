#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include <stdexcept>

/**
 * @file email.h
 * @brief Declaração do domínio Email.
 */

/**
 * @brief Endereço de e-mail.
 *
 * Formato `parte-local@domínio`. A parte local tem até 64 caracteres, só letras, dígitos, ponto e hífen, não começa nem termina com ponto ou hífen, e todo ponto ou hífen é seguido de letra ou dígito. O domínio tem até 255 caracteres, formado por partes separadas por ponto, com letras, dígitos e hífen, sem partes vazias e sem hífen no início ou no fim de uma parte.
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Email {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Email.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // EMAIL_H
