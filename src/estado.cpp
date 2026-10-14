#include "estado.h"

// A LÓGICA DE VALIDAÇÃO
void Estado::validar(std::string valor) {
    // Se o valor for diferente de TODAS as opções permitidas, lança erro
    if (valor != "A FAZER" && valor != "FAZENDO" && valor != "FEITO") {
        throw std::invalid_argument("Erro: Estado invalido. Use 'A FAZER', 'FAZENDO' ou 'FEITO'.");
    }
}

void Estado::setValor(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Estado::getValor() const {
    return valor;
}
