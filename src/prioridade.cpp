#include "prioridade.h"

void Prioridade::validar(std::string valor) {
    if (valor != "ALTA" && valor != "MEDIA" && valor != "BAIXA") {
        throw std::invalid_argument("Erro: Prioridade invalida. Use 'ALTA', 'MEDIA' ou 'BAIXA'.");
    }
}

void Prioridade::setValor(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Prioridade::getValor() const {
    return valor;
}
