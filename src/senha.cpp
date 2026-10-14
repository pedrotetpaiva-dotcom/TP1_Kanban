#include "senha.h"
#include <stdexcept> // Para usar o throw std::invalid_argument
#include <cctype>    // Para usar funções como isalpha e isdigit

// 1. A LÓGICA DE VALIDAÇÃO (A Cozinha)
void Senha::validar(std::string valor) {
    // Regra 1: Deve ter 6 caracteres
    if (valor.length() != 6) {
        throw std::invalid_argument("Erro: A senha deve ter exatamente 6 caracteres.");
    }

    bool temLetra = false;
    bool temDigito = false;

    // Analisa cada caractere da senha
    for (char c : valor) {
        // Regra 2: Só pode letra ou número
        if (!isalnum(c)) {
            throw std::invalid_argument("Erro: Senha só pode conter letras e números.");
        }
        if (isalpha(c)) temLetra = true;
        if (isdigit(c)) temDigito = true;
    }

    // Regra 3: Pelo menos uma letra e um dígito
    if (!temLetra || !temDigito) {
        throw std::invalid_argument("Erro: Senha deve conter pelo menos uma letra e um dígito.");
    }
}

// 2. O MÉTODO SET QUE O TRABALHO EXIGE
void Senha::setValor(std::string valor) {
    validar(valor);      // Se tiver erro, o "throw" para a execução aqui e avisa o erro
    this->valor = valor; // Se passou pela validação sem erros, nós guardamos o valor
}

// 3. O MÉTODO GET QUE O TRABALHO EXIGE
std::string Senha::getValor() const {
    return valor;
}
