#include "servico_autenticacao.h"
#include <iostream>

using namespace std;

bool ServicoAutenticacao::autenticar(const Email& email, const Senha& senha) {
    // TODO: Implementar a consulta SQL ao banco de dados no futuro.

    // Por enquanto, simula que a autenticacao no banco deu certo.
    // A formatacao do email e senha ja foi validada pelas classes de Dominio.
    return true;
}
