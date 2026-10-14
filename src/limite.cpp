#include "limite.h"

void Limite::validar(int valor) {
    if (valor < 1 || valor > 25) {
        throw std::invalid_argument("Erro: O limite deve ser um numero entre 1 e 25.");
    }
}

void Limite::setValor(int valor) {
    validar(valor);
    this->valor = valor;
}

int Limite::getValor() const {
    return valor;
}
