#include "ctrl_apresentacao_projeto.h"
#include <iostream>

using namespace std;

void CtrlApresentacaoProjeto::executarMenu() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "         MENU DE PROJETOS              " << endl;
        cout << "=======================================" << endl;
        cout << "1 - Criar Projeto (Apenas Gestor)" << endl;
        cout << "2 - Ler Dados do Projeto" << endl;
        cout << "3 - Atualizar Projeto (Apenas Gestor)" << endl;
        cout << "4 - Excluir Projeto (Apenas Gestor)" << endl;
        cout << "5 - Listar Projetos" << endl;
        cout << "0 - Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "\n[Apresentacao] Tela de Criar Projeto..." << endl;
                // Aqui você vai pedir os dados (Identificador, Nome, Texto, etc.)
                break;
            case 2:
                cout << "\n[Apresentacao] Tela de Ler Projeto..." << endl;
                break;
            // TODO: Adicionar os outros cases
            case 0:
                cout << "\nVoltando..." << endl;
                break;
            default:
                cout << "\nOpcao invalida. Tente novamente." << endl;
        }
    }
}
