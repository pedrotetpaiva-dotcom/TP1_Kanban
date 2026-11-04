#include "ctrl_apresentacao_quadro.h"
#include <iostream>

using namespace std;

void CtrlApresentacaoQuadro::executarMenu() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "         MENU DE QUADROS               " << endl;
        cout << "=======================================" << endl;
        cout << "1 - Criar Quadro (Apenas Gestor)" << endl;
        cout << "2 - Ler Dados do Quadro" << endl;
        cout << "3 - Excluir Quadro (Apenas Gestor)" << endl;
        cout << "0 - Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "\n[Apresentacao] Tela de Criar Quadro..." << endl;
                break;
            case 2:
                cout << "\n[Apresentacao] Tela de Ler Quadro..." << endl;
                break;
            case 3:
                cout << "\n[Apresentacao] Tela de Excluir Quadro..." << endl;
                break;
            case 0:
                cout << "\nVoltando..." << endl;
                break;
            default:
                cout << "\nOpcao invalida. Tente novamente." << endl;
        }
    }
}
