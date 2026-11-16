#include "ctrl_servico_pessoa.h"

CtrlServicoPessoa::CtrlServicoPessoa(ContainerPessoa* containerPessoa, ContainerProjeto* containerProjeto,
                                     ContainerCartao* containerCartao) {
    this->containerPessoa = containerPessoa;
    this->containerProjeto = containerProjeto;
    this->containerCartao = containerCartao;
}

bool CtrlServicoPessoa::criar(const Pessoa& pessoa) {
    return containerPessoa->incluir(pessoa);
}

bool CtrlServicoPessoa::ler(Pessoa* pessoa) {
    return containerPessoa->pesquisar(pessoa);
}

bool CtrlServicoPessoa::atualizar(const Pessoa& pessoa) {
    Pessoa atual;
    atual.setEmail(pessoa.getEmail());
    if (!containerPessoa->pesquisar(&atual)) {
        return false;
    }
    bool deixaDeSerGestor = atual.getPapel().getValor() == "GESTOR" && pessoa.getPapel().getValor() != "GESTOR";
    if (deixaDeSerGestor && containerProjeto->possuiGestor(pessoa.getEmail())) {
        return false;
    }
    return containerPessoa->atualizar(pessoa);
}

bool CtrlServicoPessoa::excluir(const Email& email) {
    Pessoa atual;
    atual.setEmail(email);
    if (!containerPessoa->pesquisar(&atual)) {
        return false;
    }
    if (containerProjeto->possuiGestor(email)) {
        return false;
    }
    if (containerCartao->possuiCartoesDoDesenvolvedor(email)) {
        return false;
    }
    return containerPessoa->remover(email);
}

bool CtrlServicoPessoa::listar(std::list<Email>* emails) {
    emails->clear();
    std::list<Pessoa> pessoas = containerPessoa->listar();
    for (std::list<Pessoa>::iterator it = pessoas.begin(); it != pessoas.end(); it++) {
        emails->push_back(it->getEmail());
    }
    return true;
}
