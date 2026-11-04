#include <iostream>
#include "ctrl_apresentacao.h"
#include "ctrl_apresentacao_principal.h"

using namespace std;

int main() {
    CtrlApresentacaoAutenticacao ctrlLogin;
    CtrlApresentacaoPrincipal ctrlPrincipal;

    // Simula a falta do banco de dados do Lucas por enquanto
    ctrlLogin.setServicoAutenticacao(nullptr);

    // Executa o fluxo: Se passar no login, abre o menu principal
    if (ctrlLogin.executarLogin()) {
        ctrlPrincipal.executarMenu();
    } else {
        cout << "Sistema encerrado por falha na autenticacao." << endl;
    }

    return 0;
}
