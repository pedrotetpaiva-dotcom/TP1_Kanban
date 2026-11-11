#include "banco_dados.h"
#include <sqlite3.h>
#include <iostream>

using namespace std;

void BancoDados::inicializarTabelas() {
    sqlite3* bd;
    // Abre ou cria o arquivo do banco de dados na pasta do projeto
    int rc = sqlite3_open("kanban.db", &bd);

    if (rc) {
        cout << "[Erro] Nao foi possivel abrir o banco de dados: " << sqlite3_errmsg(bd) << endl;
        return;
    }

    // Codigo SQL para criar as tabelas estruturadas
    const char* sql =
        "CREATE TABLE IF NOT EXISTS pessoas ("
        "email TEXT PRIMARY KEY, "
        "senha TEXT, "
        "nome TEXT);"

        "CREATE TABLE IF NOT EXISTS projetos ("
        "id TEXT PRIMARY KEY, "
        "nome TEXT, "
        "descricao TEXT);"

        "CREATE TABLE IF NOT EXISTS quadros ("
        "id TEXT PRIMARY KEY, "
        "nome TEXT, "
        "descricao TEXT, "
        "limite INT, "
        "projeto_id TEXT, "
        "FOREIGN KEY(projeto_id) REFERENCES projetos(id));"

        "CREATE TABLE IF NOT EXISTS cartoes ("
        "id TEXT PRIMARY KEY, "
        "nome TEXT, "
        "descricao TEXT, "
        "coluna TEXT, "
        "quadro_id TEXT, "
        "FOREIGN KEY(quadro_id) REFERENCES quadros(id));";

    char* mensagemErro;
    rc = sqlite3_exec(bd, sql, nullptr, nullptr, &mensagemErro);

    if (rc != SQLITE_OK) {
        cout << "[Erro SQL] Falha ao criar tabelas: " << mensagemErro << endl;
        sqlite3_free(mensagemErro);
    } else {
        cout << "[Sucesso] Banco de dados e tabelas inicializados corretamente." << endl;
    }

    sqlite3_close(bd);
}
