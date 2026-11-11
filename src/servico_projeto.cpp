#include "servico_projeto.h"

using namespace std;

bool ServicoProjeto::criar(const Email& solicitante, const Projeto& projeto) {
    return true; // Simula sucesso na criacao
}

bool ServicoProjeto::ler(const Email& solicitante, Projeto* projeto) {
    return true;
}

bool ServicoProjeto::atualizar(const Email& solicitante, const Projeto& projeto) {
    return true;
}

bool ServicoProjeto::excluir(const Email& solicitante, const Identificador& projeto) {
    return true;
}

bool ServicoProjeto::listar(const Email& solicitante, std::list<Identificador>* projetos) {
    return true;
}
