#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <string>
#include <stdexcept>

/**
 * @file timestamp.h
 * @brief Declaração do domínio Timestamp.
 */

/**
 * @brief Instante de tempo com precisão de minutos.
 *
 * Formato `DIA-MES-ANO-HH:MM`, com mês abreviado em português (`JAN`, `FEV`, `MAR`, `ABR`, `MAI`, `JUN`, `JUL`, `AGO`, `SET`, `OUT`, `NOV`, `DEZ`), ano de 2000 a 2099 e hora de 00:00 a 23:59. O dia respeita o mês e os anos bissextos (por exemplo `29-FEV-2028-10:30`).
 *
 * O valor só é armazenado depois de validado: um valor inválido lança
 * std::invalid_argument e o objeto mantém o valor anterior.
 */
class Timestamp {
    private:
        std::string valor;                  ///< Valor já validado.
        void validar(std::string valor);    ///< Verifica as regras do domínio.

    public:
        /**
         * @brief Define o valor do domínio.
         * @param valor Valor a ser armazenado.
         * @throws std::invalid_argument se o valor não obedece às regras de Timestamp.
         */
        void setValor(std::string valor);

        /**
         * @brief Devolve o valor armazenado.
         * @return Valor atual (vazio se nenhum valor foi definido).
         */
        std::string getValor() const;
};

#endif // TIMESTAMP_H
