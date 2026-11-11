#include <iostream>
#include "ctrl_apresentacao.h"
#include "ctrl_apresentacao_principal.h"
#include "servico_autenticacao.h" // Adicione esta linha

using namespace std;

int main() {
    CtrlApresentacaoAutenticacao ctrlLogin;
    CtrlApresentacaoPrincipal ctrlPrincipal;
    ServicoAutenticacao servicoAuth; // Instancia o servico real que voce acabou de criar

    // Injeta o servico real na apresentacao (adeus nullptr)
    ctrlLogin.setServicoAutenticacao(&servicoAuth);

    // Executa o fluxo
    if (ctrlLogin.executarLogin()) {
        ctrlPrincipal.executarMenu();
    } else {
        cout << "Sistema encerrado por falha na autenticacao." << endl;
    }

    return 0;
}
