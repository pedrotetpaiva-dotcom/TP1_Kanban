#include <iostream>
#include "ctrl_apresentacao.h"
#include "ctrl_apresentacao_projeto.h"

using namespace std;

int main() {
    // 1. Instancia as suas Controladoras de Apresentação
    CtrlApresentacaoAutenticacao ctrlLogin;
    CtrlApresentacaoProjeto ctrlProjeto;

    // Como o Lucas ainda não fez o serviço, enviamos nullptr (nulo)
    ctrlLogin.setServicoAutenticacao(nullptr);

    // 2. Executa o fluxo
    if (ctrlLogin.executarLogin()) {
        // Se o login devolver true, abre o menu de projetos
        ctrlProjeto.executarMenu();
    } else {
        cout << "Sistema encerrado por falha na autenticacao." << endl;
    }

    return 0;
}
