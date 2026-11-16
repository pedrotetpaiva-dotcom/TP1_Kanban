#include "container_cartao.h"

bool ContainerCartao::incluir(const Identificador& quadro, const Email& desenvolvedor,
                              const CartaoAtividade& cartao) {
    CartaoAtividade existente;
    existente.setIdentificador(cartao.getIdentificador());
    if (pesquisar(&existente)) {
        return false;
    }
    Registro registro;
    registro.cartao = cartao;
    registro.quadro = quadro;
    registro.desenvolvedor = desenvolvedor;
    container.push_back(registro);
    return true;
}

bool ContainerCartao::pesquisar(CartaoAtividade* cartao) const {
    std::string chave = cartao->getIdentificador().getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->cartao.getIdentificador().getValor() == chave) {
            *cartao = it->cartao;
            return true;
        }
    }
    return false;
}

bool ContainerCartao::pesquisarQuadro(const Identificador& cartao, Identificador* quadro) const {
    std::string chave = cartao.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->cartao.getIdentificador().getValor() == chave) {
            *quadro = it->quadro;
            return true;
        }
    }
    return false;
}

bool ContainerCartao::pesquisarDesenvolvedor(const Identificador& cartao, Email* desenvolvedor) const {
    std::string chave = cartao.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->cartao.getIdentificador().getValor() == chave) {
            *desenvolvedor = it->desenvolvedor;
            return true;
        }
    }
    return false;
}

bool ContainerCartao::atualizar(const CartaoAtividade& cartao) {
    std::string chave = cartao.getIdentificador().getValor();
    for (std::list<Registro>::iterator it = container.begin(); it != container.end(); it++) {
        if (it->cartao.getIdentificador().getValor() == chave) {
            it->cartao = cartao;
            return true;
        }
    }
    return false;
}

bool ContainerCartao::remover(const Identificador& cartao) {
    std::string chave = cartao.getValor();
    for (std::list<Registro>::iterator it = container.begin(); it != container.end(); it++) {
        if (it->cartao.getIdentificador().getValor() == chave) {
            container.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerCartao::possuiCartoes(const Identificador& quadro) const {
    std::string chave = quadro.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->quadro.getValor() == chave) {
            return true;
        }
    }
    return false;
}

bool ContainerCartao::possuiCartoesDoDesenvolvedor(const Email& desenvolvedor) const {
    std::string chave = desenvolvedor.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->desenvolvedor.getValor() == chave) {
            return true;
        }
    }
    return false;
}

std::list<CartaoAtividade> ContainerCartao::listarPorQuadro(const Identificador& quadro) const {
    std::list<CartaoAtividade> cartoes;
    std::string chave = quadro.getValor();
    for (std::list<Registro>::const_iterator it = container.begin(); it != container.end(); it++) {
        if (it->quadro.getValor() == chave) {
            cartoes.push_back(it->cartao);
        }
    }
    return cartoes;
}
