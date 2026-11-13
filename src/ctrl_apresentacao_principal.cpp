#include "ctrl_apresentacao_principal.h"
#include "ctrl_apresentacao_projeto.h"
#include "ctrl_apresentacao_quadro.h"
#include "ctrl_apresentacao_cartao.h"
#include <iostream>
#include <limits>

using namespace std;

CtrlApresentacaoPrincipal::CtrlApresentacaoPrincipal() {
    servicoProjeto = nullptr;
    servicoQuadro = nullptr;
    servicoCartao = nullptr;
    ctrlAutenticacao = nullptr;
}

void CtrlApresentacaoPrincipal::setServicoCartao(IServicoCartao* servico) {
    this->servicoCartao = servico;
}

void CtrlApresentacaoPrincipal::setCtrlAutenticacao(CtrlApresentacaoAutenticacao* ctrl) {
    this->ctrlAutenticacao = ctrl;
}

// Metodos para receber as interfaces de servico do main
void CtrlApresentacaoPrincipal::setServicoProjeto(IServicoProjeto* servico) {
    this->servicoProjeto = servico;
}

void CtrlApresentacaoPrincipal::setServicoQuadro(IServicoQuadro* servico) {
    this->servicoQuadro = servico;
}

void CtrlApresentacaoPrincipal::executarMenu() {
    int opcao = -1;
    CtrlApresentacaoProjeto ctrlProjeto;
    CtrlApresentacaoQuadro ctrlQuadro;
    CtrlApresentacaoCartao ctrlCartao;

    // Repassa os servicos e o usuario logado para as controladoras especificas
    Email usuario;
    if (ctrlAutenticacao != nullptr) {
        usuario = ctrlAutenticacao->getUsuarioLogado();
    }
    ctrlProjeto.setServico(servicoProjeto);
    ctrlProjeto.setUsuario(usuario);
    ctrlQuadro.setServico(servicoQuadro);
    ctrlQuadro.setUsuario(usuario);
    ctrlCartao.setServico(servicoCartao);
    ctrlCartao.setUsuario(usuario);

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "    SISTEMA KANBAN - MENU PRINCIPAL    " << endl;
        cout << "=======================================" << endl;
        cout << "1 - Gestao de Projetos" << endl;
        cout << "2 - Gestao de Quadros" << endl;
        cout << "3 - Gestao de Cartoes" << endl;
        cout << "4 - Gestao de Pessoas" << endl;
        cout << "0 - Sair da conta (logout)" << endl;
        cout << "Escolha uma opcao: ";
        if (!(cin >> opcao)) {
            if (cin.eof()) {
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
        }

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
            case 4:
                if (ctrlAutenticacao != nullptr) {
                    ctrlAutenticacao->executarMenuPessoas();
                }
                break;
            case 0:
                cout << "\nSaindo da conta. Ate logo!" << endl;
                break;
            default:
                cout << "\nOpcao invalida. Tente novamente." << endl;
        }
    }
}
