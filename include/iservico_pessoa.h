#ifndef ISERVICO_PESSOA_H
#define ISERVICO_PESSOA_H

#include <list>
#include "email.h"

class Pessoa;

/**
 * @file iservico_pessoa.h
 * @brief Interface dos serviços sobre a entidade Pessoa (serviços 1 a 5).
 *
 *
 */

/**
 * @brief Serviços sobre a entidade Pessoa.
 *
 */
class IServicoPessoa {
    public:
        /**
         * @brief Cria uma pessoa (cria uma conta).
         *
         * @param pessoa Dados da nova pessoa.
         * @return @c false se já existe pessoa com o mesmo e-mail.
         */
        virtual bool criar(const Pessoa& pessoa) = 0;

        /**
         * @brief Lê os dados de uma pessoa.
         * @param pessoa Entrada: objeto com o e-mail definido.
         *               Saída: objeto preenchido com os demais dados.
         * @return @c false se não existe pessoa com esse e-mail.
         */
        virtual bool ler(Pessoa* pessoa) = 0;

        /**
         * @brief Atualiza os dados de uma pessoa.
         *
         * O e-mail identifica a pessoa e não pode ser alterado.
         * @param pessoa Pessoa com os novos dados.
         * @return @c false se não existe pessoa com o e-mail informado.
         */
        virtual bool atualizar(const Pessoa& pessoa) = 0;

        /**
         * @brief Exclui uma pessoa.
         * @param email E-mail da pessoa a excluir.
         * @return @c false se a pessoa não existe ou se a exclusão deixaria o
         *         sistema inconsistente (pessoa gestora de projeto ou
         *         desenvolvedora de cartão).
         */
        virtual bool excluir(const Email& email) = 0;

        /**
         * @brief Lista as pessoas cadastradas.
         * @param emails Saída: e-mails de todas as pessoas.
         * @return @c true se a listagem foi obtida.
         */
        virtual bool listar(std::list<Email>* emails) = 0;

        virtual ~IServicoPessoa() {}
};

#endif // ISERVICO_PESSOA_H
