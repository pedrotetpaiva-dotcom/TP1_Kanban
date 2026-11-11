#ifndef PESSOA_H
#define PESSOA_H

#include "nome.h"
#include "email.h"
#include "senha.h"

/**
 * @brief Entidade que representa um utilizador do sistema.
 *
 * Agrupa os dominios Nome, Email e Senha.
 */
class Pessoa {
    private:
        Nome nome;
        Email email;
        Senha senha;

    public:
        /** @brief Define o nome da pessoa. */
        void setNome(const Nome& nome);
        /** @brief Retorna o nome da pessoa. */
        Nome getNome() const;

        /** @brief Define o email da pessoa. */
        void setEmail(const Email& email);
        /** @brief Retorna o email da pessoa. */
        Email getEmail() const;

        /** @brief Define a senha da pessoa. */
        void setSenha(const Senha& senha);
        /** @brief Retorna a senha da pessoa. */
        Senha getSenha() const;
};

#endif // PESSOA_H
