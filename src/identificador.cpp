#include "identificador.h"
#include <cctype>

void Identificador::validar(std::string valor) {
    if (valor.length() != 6) {
        throw std::invalid_argument("Erro: O identificador deve ter exatamente 6 caracteres.");
    }

    for (int i = 0; i < 3; i++) {
        if (!isalpha(valor[i])) {
            throw std::invalid_argument("Erro: Os tres primeiros caracteres devem ser letras.");
        }
    }

    for (int i = 3; i < 6; i++) {
        if (!isdigit(valor[i])) {
            throw std::invalid_argument("Erro: Os tres ultimos caracteres devem ser digitos (0-9).");
        }
    }
}

void Identificador::setValor(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Identificador::getValor() const {
    return valor;
}
