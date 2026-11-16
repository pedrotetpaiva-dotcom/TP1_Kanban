#include "container_quadro.h"

bool ContainerQuadro::incluir(const Identificador& projeto, const Quadro& quadro) {
    Quadro existente;
    existente.setIdentificador(quadro.getIdentificador());
    if (pesquisar(&existente)) {
        return false;
    }
    Registro registro;
    registro.quadro = quadro;
    registro.projeto = projeto;
    container.push_back(registro);
    return true;
}

bool ContainerQuadro::pesquisar(Quadro* quadro) const {
    std::string chave = quadro->getIdentificador().getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->quadro.getIdentificador().getValor() == chave) {
            *quadro = it->quadro;
            return true;
        }
    }
    return false;
}

bool ContainerQuadro::pesquisarProjeto(const Identificador& quadro, Identificador* projeto) const {
    std::string chave = quadro.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->quadro.getIdentificador().getValor() == chave) {
            *projeto = it->projeto;
            return true;
        }
    }
    return false;
}

bool ContainerQuadro::atualizar(const Quadro& quadro) {
    std::string chave = quadro.getIdentificador().getValor();
    for (std::list<Registro>::iterator it = container.begin(); it != container.end(); it++) {
        if (it->quadro.getIdentificador().getValor() == chave) {
            it->quadro = quadro;
            return true;
        }
    }
    return false;
}

bool ContainerQuadro::remover(const Identificador& quadro) {
    std::string chave = quadro.getValor();
    for (std::list<Registro>::iterator it = container.begin(); it != container.end(); it++) {
        if (it->quadro.getIdentificador().getValor() == chave) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerQuadro::possuiQuadros(const Identificador& projeto) const {
    std::string chave = projeto.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->projeto.getValor() == chave) {
            return true;
        }
    }
    return false;
}

std::list<Quadro> ContainerQuadro::listarPorProjeto(const Identificador& projeto) const {
    std::list<Quadro> quadros;
    std::string chave = projeto.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->projeto.getValor() == chave) {
            quadros.push_back(it->quadro);
        }
    }
    return quadros;
}
