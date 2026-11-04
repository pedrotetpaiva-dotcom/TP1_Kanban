#include "ctrl_apresentacao_cartao.h"
#include <iostream>

using namespace std;

void CtrlApresentacaoCartao::executarMenu() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "         MENU DE CARTOES               " << endl;
        cout << "=======================================" << endl;
        cout << "1 - Criar Cartao" << endl;
        cout << "2 - Ler Dados do Cartao" << endl;
        cout << "3 - Atualizar Cartao" << endl;
        cout << "4 - Excluir Cartao" << endl;
        cout << "5 - Mover Cartao" << endl;
        cout << "0 - Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "\n[Apresentacao] Tela de Criar Cartao..." << endl;
                break;
            case 2:
                cout << "\n[Apresentacao] Tela de Ler Cartao..." << endl;
                break;
            case 3:
                cout << "\n[Apresentacao] Tela de Atualizar Cartao..." << endl;
                break;
            case 4:
                cout << "\n[Apresentacao] Tela de Excluir Cartao..." << endl;
                break;
            case 5:
                cout << "\n[Apresentacao] Tela de Mover Cartao..." << endl;
                break;
            case 0:
                cout << "\nVoltando..." << endl;
                break;
            default:
                cout << "\nOpcao invalida. Tente novamente." << endl;
        }
    }
}
