#include "ctrl_servico_projeto.h"

CtrlServicoProjeto::CtrlServicoProjeto(ContainerPessoa* containerPessoa, ContainerProjeto* containerProjeto,
                                       ContainerQuadro* containerQuadro) {
    this->containerPessoa = containerPessoa;
    this->containerProjeto = containerProjeto;
    this->containerQuadro = containerQuadro;
}

bool CtrlServicoProjeto::existeSolicitante(const Email& solicitante) const {
    Pessoa pessoa;
    pessoa.setEmail(solicitante);
    return containerPessoa->pesquisar(&pessoa);
}

bool CtrlServicoProjeto::ehGestorDoProjeto(const Email& solicitante, const Identificador& projeto) const {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    Email gestor;
    if (!containerProjeto->pesquisarGestor(projeto, &gestor)) {
        return false;
    }
    return gestor.getValor() == solicitante.getValor();
}

bool CtrlServicoProjeto::criar(const Email& solicitante, const Projeto& projeto) {
    Pessoa pessoa;
    pessoa.setEmail(solicitante);
    if (!containerPessoa->pesquisar(&pessoa)) {
        return false;
    }
    if (pessoa.getPapel().getValor() != "GESTOR") {
        return false;
    }
    return containerProjeto->incluir(solicitante, projeto);
}

bool CtrlServicoProjeto::ler(const Email& solicitante, Projeto* projeto) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    return containerProjeto->pesquisar(projeto);
}

bool CtrlServicoProjeto::atualizar(const Email& solicitante, const Projeto& projeto) {
    if (!ehGestorDoProjeto(solicitante, projeto.getIdentificador())) {
        return false;
    }
    return containerProjeto->atualizar(projeto);
}

bool CtrlServicoProjeto::excluir(const Email& solicitante, const Identificador& projeto) {
    if (!ehGestorDoProjeto(solicitante, projeto)) {
        return false;
    }
    if (containerQuadro->possuiQuadros(projeto)) {
        return false;
    }
    return containerProjeto->remover(projeto);
}

bool CtrlServicoProjeto::listar(const Email& solicitante, std::list<Identificador>* projetos) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    projetos->clear();
    std::list<Projeto> existentes = containerProjeto->listar();
    for (std::list<Projeto>::iterator it = existentes.begin(); it != existentes.end(); it++) {
        projetos->push_back(it->getIdentificador());
    }
    return true;
}
