#include "texto.h"
#include <cctype>

// Função auxiliar para verificar as pontuações permitidas[cite: 1]
bool isPontuacao(char c) {
    return c == ',' || c == ';' || c == '.' || c == ':' || c == '?' || c == '!';
}

void Texto::validar(std::string valor) {
    // Regra: Até 30 caracteres[cite: 1]
    if (valor.length() > 30 || valor.empty()) {
        throw std::invalid_argument("Erro: O texto deve ter entre 1 e 30 caracteres.");
    }

    // Regra: O primeiro caractere deve ser obrigatoriamente uma letra maiúscula[cite: 1]
    if (!isupper(valor[0])) {
        throw std::invalid_argument("Erro: O primeiro caractere deve ser uma letra maiuscula.");
    }

    // Regra: O último caractere deve ser obrigatoriamente um ponto[cite: 1]
    if (valor.back() != '.') {
        throw std::invalid_argument("Erro: O ultimo caractere deve ser um ponto.");
    }

    // Regra: Validação de caracteres e repetição de pontuação[cite: 1]
    for (size_t i = 0; i < valor.length(); i++) {
        char c = valor[i];

        // Verifica se é letra, dígito, espaço ou pontuação permitida[cite: 1]
        if (!isalnum(c) && c != ' ' && !isPontuacao(c)) {
            throw std::invalid_argument("Erro: Caractere invalido detetado no texto.");
        }

        // Se for pontuação, verifica se a próxima também é pontuação[cite: 1]
        if (isPontuacao(c) && i + 1 < valor.length()) {
            if (isPontuacao(valor[i+1])) {
                throw std::invalid_argument("Erro: Um sinal de pontuacao nao pode ser seguido por outro.");
            }
        }
    }
}

void Texto::setValor(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Texto::getValor() const {
    return valor;
}
