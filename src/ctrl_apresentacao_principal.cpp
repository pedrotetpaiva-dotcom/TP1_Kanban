#include "ctrl_apresentacao_principal.h"
#include "ctrl_apresentacao_projeto.h"
#include "ctrl_apresentacao_quadro.h"
#include "ctrl_apresentacao_cartao.h"
#include <iostream>

using namespace std;

void CtrlApresentacaoPrincipal::executarMenu() {
    int opcao = -1;
    CtrlApresentacaoProjeto ctrlProjeto;
    CtrlApresentacaoQuadro ctrlQuadro;
    CtrlApresentacaoCartao ctrlCartao;

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "    SISTEMA KANBAN - MENU PRINCIPAL    " << endl;
        cout << "=======================================" << endl;
        cout << "1 - Gestao de Projetos" << endl;
        cout << "2 - Gestao de Quadros" << endl;
        cout << "3 - Gestao de Cartoes (Em construcao)" << endl;
        cout << "0 - Sair do Sistema" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                ctrlProjeto.executarMenu();
                break;
            case 2:
                ctrlQuadro.executarMenu();
                break;
            case 3:
                ctrlCartao.executarMenu();
                break;
            case 0:
                cout << "\nEncerrando a sessao. Ate logo!" << endl;
                break;
            default:
                cout << "\nOpcao invalida. Tente novamente." << endl;
        }
    }
}
