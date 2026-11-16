#include "ctrl_servico_quadro.h"

CtrlServicoQuadro::CtrlServicoQuadro(ContainerPessoa* containerPessoa, ContainerProjeto* containerProjeto,
                                     ContainerQuadro* containerQuadro, ContainerCartao* containerCartao) {
    this->containerPessoa = containerPessoa;
    this->containerProjeto = containerProjeto;
    this->containerQuadro = containerQuadro;
    this->containerCartao = containerCartao;
}

bool CtrlServicoQuadro::existeSolicitante(const Email& solicitante) const {
    Pessoa pessoa;
    pessoa.setEmail(solicitante);
    return containerPessoa->pesquisar(&pessoa);
}

bool CtrlServicoQuadro::ehGestorDoProjeto(const Email& solicitante, const Identificador& projeto) const {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    Email gestor;
    if (!containerProjeto->pesquisarGestor(projeto, &gestor)) {
        return false;
    }
    return gestor.getValor() == solicitante.getValor();
}

int CtrlServicoQuadro::contarFazendo(const Identificador& quadro) const {
    int total = 0;
    std::list<CartaoAtividade> cartoes = containerCartao->listarPorQuadro(quadro);
    for (std::list<CartaoAtividade>::iterator it = cartoes.begin(); it != cartoes.end(); it++) {
        if (it->getEstado().getValor() == "FAZENDO") {
            total++;
        }
    }
    return total;
}

bool CtrlServicoQuadro::criar(const Email& solicitante, const Identificador& projeto, const Quadro& quadro) {
    if (!ehGestorDoProjeto(solicitante, projeto)) {
        return false;
    }
    return containerQuadro->incluir(projeto, quadro);
}

bool CtrlServicoQuadro::ler(const Email& solicitante, Quadro* quadro) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    return containerQuadro->pesquisar(quadro);
}

bool CtrlServicoQuadro::atualizar(const Email& solicitante, const Quadro& quadro) {
    Identificador projeto;
    if (!containerQuadro->pesquisarProjeto(quadro.getIdentificador(), &projeto)) {
        return false;
    }
    if (!ehGestorDoProjeto(solicitante, projeto)) {
        return false;
    }
    if (quadro.getLimite().getValor() < contarFazendo(quadro.getIdentificador())) {
        return false;
    }
    return containerQuadro->atualizar(quadro);
}

bool CtrlServicoQuadro::excluir(const Email& solicitante, const Identificador& quadro) {
    Identificador projeto;
    if (!containerQuadro->pesquisarProjeto(quadro, &projeto)) {
        return false;
    }
    if (!ehGestorDoProjeto(solicitante, projeto)) {
        return false;
    }
    if (containerCartao->possuiCartoes(quadro)) {
        return false;
    }
    return containerQuadro->remover(quadro);
}

bool CtrlServicoQuadro::listar(const Email& solicitante, const Identificador& projeto,
                               std::list<Identificador>* quadros) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    Projeto existente;
    existente.setIdentificador(projeto);
    if (!containerProjeto->pesquisar(&existente)) {
        return false;
    }
    quadros->clear();
    std::list<Quadro> doProjeto = containerQuadro->listarPorProjeto(projeto);
    for (std::list<Quadro>::iterator it = doProjeto.begin(); it != doProjeto.end(); it++) {
        quadros->push_back(it->getIdentificador());
    }
    return true;
}
