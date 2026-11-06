#ifndef PESSOA_H
#define PESSOA_H

#include "email.h"
#include "nome.h"
#include "senha.h"
#include "papel.h"

/**
 * @file pessoa.h
 * @brief Declaração da entidade Pessoa.
 */

/**
 * @brief Entidade que representa uma pessoa usuária do sistema Kanban.
 *
 * Uma pessoa tem e-mail, nome, senha e papel (GESTOR ou DESENVOLVEDOR).
 * O e-mail identifica a pessoa (chave primária) e, por isso, não pode ser
 * alterado depois que a pessoa é criada no sistema.
 *
 * Cada atributo é uma instância de classe domínio e já chega validado: o
 * formato é verificado pelo método @c setValor da própria classe domínio.
 * Por isso os métodos set desta classe não lançam exceção.
 *
 * Os atributos devem ser definidos pelos métodos set antes de serem lidos
 * pelos métodos get.
 *
 * Relacionamentos (mantidos pela camada de serviço): uma pessoa pode ser
 * gestora de zero ou mais projetos e desenvolvedora de zero ou mais cartões
 * de atividade.
 */
class Pessoa {
    private:
        Email email;   ///< E-mail da pessoa (chave primária).
        Nome nome;     ///< Nome da pessoa.
        Senha senha;   ///< Senha de acesso da pessoa.
        Papel papel;   ///< Papel da pessoa: GESTOR ou DESENVOLVEDOR.

    public:
        /**
         * @brief Define o e-mail da pessoa.
         * @param email E-mail já validado pelo domínio Email.
         */
        void setEmail(const Email& email);

        /**
         * @brief Devolve o e-mail da pessoa.
         * @return E-mail da pessoa.
         */
        Email getEmail() const;

        /**
         * @brief Define o nome da pessoa.
         * @param nome Nome já validado pelo domínio Nome.
         */
        void setNome(const Nome& nome);

        /**
         * @brief Devolve o nome da pessoa.
         * @return Nome da pessoa.
         */
        Nome getNome() const;

        /**
         * @brief Define a senha da pessoa.
         * @param senha Senha já validada pelo domínio Senha.
         */
        void setSenha(const Senha& senha);

        /**
         * @brief Devolve a senha da pessoa.
         * @return Senha da pessoa.
         */
        Senha getSenha() const;

        /**
         * @brief Define o papel da pessoa.
         * @param papel Papel já validado pelo domínio Papel.
         */
        void setPapel(const Papel& papel);

        /**
         * @brief Devolve o papel da pessoa.
         * @return Papel da pessoa.
         */
        Papel getPapel() const;
};

#endif // PESSOA_H
