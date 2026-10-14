#include "tamanho.h"

void Tamanho::validar(std::string valor) {
    if (valor != "GRANDE" && valor != "MEDIO" && valor != "PEQUENO") {
        throw std::invalid_argument("Erro: Tamanho invalido. Use 'GRANDE', 'MEDIO' ou 'PEQUENO'.");
    }
}

void Tamanho::setValor(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Tamanho::getValor() const {
    return valor;
}
