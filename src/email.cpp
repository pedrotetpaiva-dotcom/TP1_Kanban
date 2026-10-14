#include "email.h"
#include <cctype>

void Email::validar(std::string valor) {
    // 1. Encontrar o '@' que separa as duas partes
    size_t posArroba = valor.find('@');

    // Verifica se não tem '@' ou se ele está nas bordas (ex: "@dominio.com" ou "nome@")
    if (posArroba == std::string::npos || posArroba == 0 || posArroba == valor.length() - 1) {
        throw std::invalid_argument("Erro: Formato invalido. Deve conter '@' separando a parte local do dominio.");
    }

    // Verifica se há mais de um '@' no texto
    if (valor.find('@', posArroba + 1) != std::string::npos) {
        throw std::invalid_argument("Erro: O email nao pode conter mais de um '@'.");
    }

    // Separa a string em duas metades
    std::string parteLocal = valor.substr(0, posArroba);
    std::string dominio = valor.substr(posArroba + 1);

    // 2. VALIDAÇÃO DA PARTE LOCAL
    if (parteLocal.length() > 64) {
        throw std::invalid_argument("Erro: A parte local excede o limite de 64 caracteres.");
    }
    if (parteLocal.front() == '.' || parteLocal.front() == '-' ||
        parteLocal.back() == '.' || parteLocal.back() == '-') {
        throw std::invalid_argument("Erro: Parte local nao pode iniciar ou terminar com ponto ou hifen.");
    }

    for (size_t i = 0; i < parteLocal.length(); i++) {
        char c = parteLocal[i];
        if (!isalnum(c) && c != '.' && c != '-') {
            throw std::invalid_argument("Erro: Caractere invalido na parte local.");
        }
        // Ponto ou hífen deve ser seguido por letra ou dígito[cite: 1]
        if ((c == '.' || c == '-') && i + 1 < parteLocal.length()) {
            if (!isalnum(parteLocal[i+1])) {
                throw std::invalid_argument("Erro: Ponto ou hifen na parte local deve ser seguido por letra ou digito.");
            }
        }
    }

    // 3. VALIDAÇÃO DO DOMÍNIO[cite: 1]
    if (dominio.length() > 255) {
        throw std::invalid_argument("Erro: O dominio excede o limite de 255 caracteres.");
    }

    // O domínio é composto por partes separadas por ponto[cite: 1]
    size_t posInicio = 0;
    size_t posPonto = dominio.find('.');

    while (posInicio < dominio.length()) {
        std::string parte = dominio.substr(posInicio, posPonto - posInicio);

        if (parte.empty()) {
            throw std::invalid_argument("Erro: Parte do dominio nao pode ser vazia.");
        }
        // Nenhuma parte do domínio pode iniciar ou terminar com hífen[cite: 1]
        if (parte.front() == '-' || parte.back() == '-') {
            throw std::invalid_argument("Erro: Parte do dominio nao pode iniciar ou terminar com hifen.");
        }
        for (char c : parte) {
            if (!isalnum(c) && c != '-') {
                throw std::invalid_argument("Erro: O dominio so pode conter letras, digitos ou hifen.");
            }
        }

        if (posPonto == std::string::npos) break; // Sai do ciclo se não houver mais pontos

        posInicio = posPonto + 1;
        posPonto = dominio.find('.', posInicio);
    }
}

void Email::setValor(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Email::getValor() const {
    return valor;
}
