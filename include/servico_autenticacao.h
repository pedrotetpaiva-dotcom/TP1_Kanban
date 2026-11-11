#ifndef SERVICO_AUTENTICACAO_H
#define SERVICO_AUTENTICACAO_H

#include "iservico_autenticacao.h"
#include "email.h"
#include "senha.h"

/**
 * @brief Classe responsavel pela logica de negocio da autenticacao.
 *
 * Implementa o contrato da interface IServicoAutenticacao.
 * Futuramente, esta classe fara a conexao com o banco de dados (SQLite)
 * para verificar se o usuario realmente existe no sistema.
 */
class ServicoAutenticacao : public IServicoAutenticacao {
    public:
        /**
         * @brief Verifica as credenciais de acesso do usuario.
         *
         * Compara o email e a senha fornecidos com os registros do sistema.
         *
         * @param email Referencia constante para um objeto da classe Email.
         * @param senha Referencia constante para um objeto da classe Senha.
         * @return true se as credenciais existirem no banco de dados.
         * @return false se as credenciais forem incorretas ou o usuario nao existir.
         */
        bool autenticar(const Email& email, const Senha& senha) override;
};

#endif // SERVICO_AUTENTICACAO_H
