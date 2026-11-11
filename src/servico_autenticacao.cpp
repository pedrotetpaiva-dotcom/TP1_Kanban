#include "servico_autenticacao.h"
#include <sqlite3.h>
#include <iostream>

using namespace std;

bool ServicoAutenticacao::autenticar(const Email& email, const Senha& senha) {
    sqlite3* bd;
    int rc = sqlite3_open("kanban.db", &bd);
    if (rc != SQLITE_OK) return false;

    // Procura a senha correspondente ao email fornecido
    string sql = "SELECT senha FROM pessoas WHERE email = '" + email.getValor() + "';";
    sqlite3_stmt* stmt;

    // Prepara a consulta
    rc = sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_close(bd);
        return false;
    }

    bool autenticado = false;
    // Se o sqlite3_step retornar SQLITE_ROW, significa que achou o e-mail na tabela
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Pega a senha que esta gravada no banco de dados (coluna 0)
        string senhaBanco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        // Verifica se a senha do banco bate com a senha digitada
        if (senhaBanco == senha.getValor()) {
            autenticado = true;
        }
    }

    // Liberta a memoria e fecha o banco
    sqlite3_finalize(stmt);
    sqlite3_close(bd);

    return autenticado;
}
