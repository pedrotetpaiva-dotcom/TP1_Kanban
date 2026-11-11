#include "servico_pessoa.h"

using namespace std;

bool ServicoPessoa::criar(const Pessoa& pessoa) {
    return true;
}

bool ServicoPessoa::ler(Pessoa* pessoa) {
    return true;
}

bool ServicoPessoa::atualizar(const Pessoa& pessoa) {
    return true;
}

bool ServicoPessoa::excluir(const Email& email) {
    return true;
}

bool ServicoPessoa::listar(std::list<Email>* emails) {
    return true;
}
