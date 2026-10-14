#include "nome.h"
#include <cctype> // Para a função isalpha

void Nome::validar(std::string valor) {
    // Regra: Máximo 15 caracteres
    if (valor.length() > 15 || valor.empty()) {
        throw std::invalid_argument("Erro: O nome deve ter entre 1 e 15 caracteres.");
    }

    // Regra: O primeiro e o último caractere não podem ser espaços
    if (valor.front() == ' ') {
        throw std::invalid_argument("Erro: O primeiro caractere nao pode ser um espaco.");
    }
    if (valor.back() == ' ') {
        throw std::invalid_argument("Erro: O ultimo caractere nao pode ser um espaco.");
    }

    // Regra: Apenas letras e espaços, e espaço deve ser seguido de letra
    for (size_t i = 0; i < valor.length(); i++) {
        if (!isalpha(valor[i]) && valor[i] != ' ') {
            throw std::invalid_argument("Erro: O nome deve conter apenas letras e espacos.");
        }

        // Se encontrar um espaço, verifica se o próximo caractere é uma letra
        if (valor[i] == ' ' && i + 1 < valor.length()) {
            if (!isalpha(valor[i+1])) {
                throw std::invalid_argument("Erro: Um espaco em branco deve ser seguido por uma letra.");
            }
        }
    }
}

void Nome::setValor(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Nome::getValor() const {
    return valor;
}
