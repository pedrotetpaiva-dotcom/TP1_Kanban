#include "papel.h"

void Papel::validar(std::string valor) {
    if (valor != "GESTOR" && valor != "DESENVOLVEDOR") {
        throw std::invalid_argument("Erro: Papel invalido. Use 'GESTOR' ou 'DESENVOLVEDOR'.");
    }
}

void Papel::setValor(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Papel::getValor() const {
    return valor;
}
