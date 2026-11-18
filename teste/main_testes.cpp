#include "teste.h"
#include <iostream>

static int total = 0;
static int falhas = 0;

void cabecalho(const std::string& titulo) {
    std::cout << "\n==================================================" << std::endl;
    std::cout << " " << titulo << std::endl;
    std::cout << "==================================================" << std::endl;
}

void secao(const std::string& titulo) {
    std::cout << "\n--- " << titulo << " ---" << std::endl;
}

void verificar(bool condicao, const std::string& descricao, const char* arquivo, int linha) {
    total++;
    if (condicao) {
        std::cout << "  [OK]    " << descricao << std::endl;
    } else {
        falhas++;
        std::cout << "  [FALHA] " << descricao << "  (" << arquivo << ":" << linha << ")" << std::endl;
    }
}

int totalVerificacoes() { return total; }
int totalFalhas() { return falhas; }

int main() {
    executarTestesDominios();
    executarTestesEntidades();
    executarTestesApresentacao();
    executarTestesServicos();

    cabecalho("RESUMO");
    std::cout << " Verificacoes: " << total << std::endl;
    std::cout << " Falhas      : " << falhas << std::endl;
    std::cout << (falhas == 0 ? " RESULTADO: TODOS OS TESTES PASSARAM" : " RESULTADO: HA TESTES COM FALHA") << std::endl;
    return falhas == 0 ? 0 : 1;
}
