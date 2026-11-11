#include "servico_projeto.h"
#include "projeto.h"
#include <sqlite3.h>
#include <iostream>
#include <string>

using namespace std;

bool ServicoProjeto::criar(const Email& solicitante, const Projeto& projeto) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    // Comando SQL para inserir um novo projeto
    string sql = "INSERT INTO projetos (id, nome, descricao) VALUES ('" +
                 projeto.getIdentificador().getValor() + "', '" +
                 projeto.getNome().getValor() + "', '" +
                 projeto.getDescricao().getValor() + "');";

    char* erro;
    if (sqlite3_exec(bd, sql.c_str(), nullptr, nullptr, &erro) != SQLITE_OK) {
        sqlite3_free(erro);
        sqlite3_close(bd);
        return false; // Falha (ex: ID ja existe)
    }
    sqlite3_close(bd);
    return true;
}

bool ServicoProjeto::ler(const Email& solicitante, Projeto* projeto) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    // Comando SQL para procurar o projeto pelo ID
    string sql = "SELECT nome, descricao FROM projetos WHERE id = '" + projeto->getIdentificador().getValor() + "';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(bd);
        return false;
    }

    bool encontrou = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Texto nome, descricao;
        nome.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        descricao.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));

        projeto->setNome(nome);
        projeto->setDescricao(descricao);
        encontrou = true;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bd);
    return encontrou;
}

bool ServicoProjeto::atualizar(const Email& solicitante, const Projeto& projeto) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    string sql = "UPDATE projetos SET nome = '" + projeto.getNome().getValor() +
                 "', descricao = '" + projeto.getDescricao().getValor() +
                 "' WHERE id = '" + projeto.getIdentificador().getValor() + "';";

    char* erro;
    if (sqlite3_exec(bd, sql.c_str(), nullptr, nullptr, &erro) != SQLITE_OK) {
        sqlite3_free(erro);
        sqlite3_close(bd);
        return false;
    }
    sqlite3_close(bd);
    return true;
}

bool ServicoProjeto::excluir(const Email& solicitante, const Identificador& projeto) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    string sql = "DELETE FROM projetos WHERE id = '" + projeto.getValor() + "';";

    char* erro;
    if (sqlite3_exec(bd, sql.c_str(), nullptr, nullptr, &erro) != SQLITE_OK) {
        sqlite3_free(erro);
        sqlite3_close(bd);
        return false;
    }
    sqlite3_close(bd);
    return true;
}

bool ServicoProjeto::listar(const Email& solicitante, std::list<Identificador>* projetos) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    string sql = "SELECT id FROM projetos;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(bd);
        return false;
    }

    // Adiciona todos os IDs encontrados na lista
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Identificador id;
        id.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        projetos->push_back(id);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bd);
    return true;
}
