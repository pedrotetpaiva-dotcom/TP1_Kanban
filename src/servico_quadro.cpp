#include "servico_quadro.h"
#include "quadro.h"
#include <sqlite3.h>
#include <iostream>
#include <string>

using namespace std;

bool ServicoQuadro::criar(const Email& solicitante, const Identificador& projeto, const Quadro& quadro) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    string sql = "INSERT INTO quadros (id, nome, descricao, limite, projeto_id) VALUES ('" +
                 quadro.getIdentificador().getValor() + "', '" +
                 quadro.getNome().getValor() + "', '" +
                 quadro.getDescricao().getValor() + "', " +
                 to_string(quadro.getLimite().getValor()) + ", '" +
                 projeto.getValor() + "');";

    char* erro;
    if (sqlite3_exec(bd, sql.c_str(), nullptr, nullptr, &erro) != SQLITE_OK) {
        sqlite3_free(erro);
        sqlite3_close(bd);
        return false;
    }
    sqlite3_close(bd);
    return true;
}

bool ServicoQuadro::ler(const Email& solicitante, Quadro* quadro) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    string sql = "SELECT nome, descricao, limite FROM quadros WHERE id = '" + quadro->getIdentificador().getValor() + "';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(bd);
        return false;
    }

    bool encontrou = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Texto nome, descricao;
        Limite limite;

        nome.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        descricao.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        limite.setValor(sqlite3_column_int(stmt, 2));

        quadro->setNome(nome);
        quadro->setDescricao(descricao);
        quadro->setLimite(limite);

        encontrou = true;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bd);
    return encontrou;
}

bool ServicoQuadro::atualizar(const Email& solicitante, const Quadro& quadro) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    string sql = "UPDATE quadros SET nome = '" + quadro.getNome().getValor() +
                 "', descricao = '" + quadro.getDescricao().getValor() +
                 "', limite = " + to_string(quadro.getLimite().getValor()) +
                 " WHERE id = '" + quadro.getIdentificador().getValor() + "';";

    char* erro;
    if (sqlite3_exec(bd, sql.c_str(), nullptr, nullptr, &erro) != SQLITE_OK) {
        sqlite3_free(erro);
        sqlite3_close(bd);
        return false;
    }
    sqlite3_close(bd);
    return true;
}

bool ServicoQuadro::excluir(const Email& solicitante, const Identificador& quadro) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    string sql = "DELETE FROM quadros WHERE id = '" + quadro.getValor() + "';";

    char* erro;
    if (sqlite3_exec(bd, sql.c_str(), nullptr, nullptr, &erro) != SQLITE_OK) {
        sqlite3_free(erro);
        sqlite3_close(bd);
        return false;
    }
    sqlite3_close(bd);
    return true;
}

bool ServicoQuadro::listar(const Email& solicitante, const Identificador& projeto, std::list<Identificador>* quadros) {
    sqlite3* bd;
    if (sqlite3_open("kanban.db", &bd) != SQLITE_OK) return false;

    // Lista apenas os quadros que pertencem ao projeto especifico
    string sql = "SELECT id FROM quadros WHERE projeto_id = '" + projeto.getValor() + "';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(bd);
        return false;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Identificador id;
        id.setValor(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        quadros->push_back(id);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(bd);
    return true;
}
