#include "servico_pessoa.h"
#include "pessoa.h" // Necessario para reconhecer os metodos da pessoa
#include <sqlite3.h>
#include <iostream>

using namespace std;

bool ServicoPessoa::criar(const Pessoa& pessoa) {
    sqlite3* bd;
    // Abre a conexao com o banco
    int rc = sqlite3_open("kanban.db", &bd);
    if (rc != SQLITE_OK) return false;

    // Monta a query de insercao.
    // Assumimos que as suas classes de dominio usam o padrao .getValor()
    string sql = "INSERT INTO pessoas (email, senha, nome) VALUES ('" +
                 pessoa.getEmail().getValor() + "', '" +
                 pessoa.getSenha().getValor() + "', '" +
                 pessoa.getNome().getValor() + "');";

    char* mensagemErro;
    rc = sqlite3_exec(bd, sql.c_str(), nullptr, nullptr, &mensagemErro);

    if (rc != SQLITE_OK) {
        // Se der erro (ex: e-mail ja existe, violando a PRIMARY KEY)
        sqlite3_free(mensagemErro);
        sqlite3_close(bd);
        return false;
    }

    sqlite3_close(bd);
    return true; // Conta criada com sucesso!
}

// ... Pode manter os metodos ler(), atualizar(), excluir() e listar() com 'return true;' por enquanto ...
bool ServicoPessoa::ler(Pessoa* pessoa) { return true; }
bool ServicoPessoa::atualizar(const Pessoa& pessoa) { return true; }
bool ServicoPessoa::excluir(const Email& email) { return true; }
bool ServicoPessoa::listar(std::list<Email>* emails) { return true; }
