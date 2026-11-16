#include "container_pessoa.h"

bool ContainerPessoa::incluir(const Pessoa& pessoa) {
    Pessoa existente;
    existente.setEmail(pessoa.getEmail());
    if (pesquisar(&existente)) {
        return false;
    }
    container.push_back(pessoa);
    return true;
}

bool ContainerPessoa::pesquisar(Pessoa* pessoa) const {
    std::string chave = pessoa->getEmail().getValor();
    for (std::list<Pessoa>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->getEmail().getValor() == chave) {
            *pessoa = *it;
            return true;
        }
    }
    return false;
}

bool ContainerPessoa::atualizar(const Pessoa& pessoa) {
    std::string chave = pessoa.getEmail().getValor();
    for (std::list<Pessoa>::iterator it = container.begin(); it != container.end(); it++) {
        if (it->getEmail().getValor() == chave) {
            *it = pessoa;
            return true;
        }
    }
    return false;
}

bool ContainerPessoa::remover(const Email& email) {
    std::string chave = email.getValor();
    for (std::list<Pessoa>::iterator it = container.begin(); it != container.end(); it++) {
        if (it->getEmail().getValor() == chave) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

std::list<Pessoa> ContainerPessoa::listar() const {
    return container;
}
