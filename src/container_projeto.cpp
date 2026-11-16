#include "container_projeto.h"

bool ContainerProjeto::incluir(const Email& gestor, const Projeto& projeto) {
    Projeto existente;
    existente.setIdentificador(projeto.getIdentificador());
    if (pesquisar(&existente)) {
        return false;
    }
    Registro registro;
    registro.projeto = projeto;
    registro.gestor = gestor;
    container.push_back(registro);
    return true;
}

bool ContainerProjeto::pesquisar(Projeto* projeto) const {
    std::string chave = projeto->getIdentificador().getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->projeto.getIdentificador().getValor() == chave) {
            *projeto = it->projeto;
            return true;
        }
    }
    return false;
}

bool ContainerProjeto::pesquisarGestor(const Identificador& projeto, Email* gestor) const {
    std::string chave = projeto.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->projeto.getIdentificador().getValor() == chave) {
            *gestor = it->gestor;
            return true;
        }
    }
    return false;
}

bool ContainerProjeto::atualizar(const Projeto& projeto) {
    std::string chave = projeto.getIdentificador().getValor();
    for (std::list<Registro>::iterator it = container.begin(); it != container.end(); it++) {
        if (it->projeto.getIdentificador().getValor() == chave) {
            it->projeto = projeto;
            return true;
        }
    }
    return false;
}

bool ContainerProjeto::remover(const Identificador& projeto) {
    std::string chave = projeto.getValor();
    for (std::list<Registro>::iterator it = container.begin(); it != container.end(); it++) {
        if (it->projeto.getIdentificador().getValor() == chave) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerProjeto::possuiGestor(const Email& gestor) const {
    std::string chave = gestor.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->gestor.getValor() == chave) {
            return true;
        }
    }
    return false;
}

std::list<Projeto> ContainerProjeto::listar() const {
    std::list<Projeto> projetos;
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        projetos.push_back(it->projeto);
    }
    return projetos;
}
