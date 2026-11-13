#include "ctrl_apresentacao_quadro.h"
#include "entrada_console.h"
#include "quadro.h"
#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

CtrlApresentacaoQuadro::CtrlApresentacaoQuadro() {
    servico = nullptr;
}

void CtrlApresentacaoQuadro::setServico(IServicoQuadro* servico) {
    this->servico = servico;
}

void CtrlApresentacaoQuadro::setUsuario(const Email& usuario) {
    this->usuario = usuario;
}

namespace {

// Pede o limite de WIP (numero inteiro) e o atribui ao dominio.
bool pedirLimite(const string& rotulo, Limite* limite) {
    int valor;
    cout << rotulo;
    if (!(cin >> valor)) {
        if (cin.eof()) {
            return false;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Erro: o limite deve ser um numero inteiro.");
    }
    limite->setValor(valor);
    return true;
}

}  // namespace

void CtrlApresentacaoQuadro::executarMenu() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "         MENU DE QUADROS               " << endl;
        cout << "=======================================" << endl;
        cout << "1 - Criar Quadro (Apenas Gestor do projeto)" << endl;
        cout << "2 - Ler Dados do Quadro" << endl;
        cout << "3 - Atualizar Quadro (Apenas Gestor do projeto)" << endl;
        cout << "4 - Excluir Quadro (Apenas Gestor do projeto)" << endl;
        cout << "5 - Listar Quadros de um Projeto" << endl;
        cout << "0 - Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        opcao = lerOpcao();

        switch (opcao) {
            case 1: telaCriar(); break;
            case 2: telaLer(); break;
            case 3: telaAtualizar(); break;
            case 4: telaExcluir(); break;
            case 5: telaListar(); break;
            case 0: cout << "\nVoltando..." << endl; break;
            default: cout << "\nOpcao invalida. Tente novamente." << endl;
        }
    }
}

void CtrlApresentacaoQuadro::telaCriar() {
    try {
        cout << "\n--- CRIAR QUADRO ---" << endl;
        Identificador projeto, id; Nome nome; Limite limite;
        if (!pedirPalavra("Identificador do projeto: ", &projeto)) return;
        if (!pedirPalavra("Identificador do novo quadro (ex. QDR001): ", &id)) return;
        if (!pedirLinha("Nome: ", &nome)) return;
        if (!pedirLimite("Limite de WIP (1 a 25): ", &limite)) return;

        Quadro quadro;
        quadro.setIdentificador(id);
        quadro.setNome(nome);
        quadro.setLimite(limite);

        if (servico != nullptr && servico->criar(usuario, projeto, quadro)) {
            cout << "\n[Sucesso] Quadro criado." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel criar. O projeto deve existir, voce deve ser o gestor dele e o identificador deve ser novo." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
        cout << "Operacao cancelada." << endl;
    }
}

void CtrlApresentacaoQuadro::telaLer() {
    try {
        cout << "\n--- LER QUADRO ---" << endl;
        Quadro quadro;
        Identificador id;
        if (!pedirPalavra("Identificador do quadro: ", &id)) return;
        quadro.setIdentificador(id);

        if (servico != nullptr && servico->ler(usuario, &quadro)) {
            cout << "\nIdentificador: " << quadro.getIdentificador().getValor() << endl;
            cout << "Nome         : " << quadro.getNome().getValor() << endl;
            cout << "Limite de WIP: " << quadro.getLimite().getValor() << endl;
        } else {
            cout << "\n[Erro] Quadro nao encontrado." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoQuadro::telaAtualizar() {
    try {
        cout << "\n--- ATUALIZAR QUADRO ---" << endl;
        Identificador id; Nome nome; Limite limite;
        if (!pedirPalavra("Identificador do quadro (nao pode ser alterado): ", &id)) return;
        if (!pedirLinha("Novo nome: ", &nome)) return;
        if (!pedirLimite("Novo limite de WIP (1 a 25): ", &limite)) return;

        Quadro quadro;
        quadro.setIdentificador(id);
        quadro.setNome(nome);
        quadro.setLimite(limite);

        if (servico != nullptr && servico->atualizar(usuario, quadro)) {
            cout << "\n[Sucesso] Quadro atualizado." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel atualizar. O quadro deve existir, voce deve ser o gestor do projeto e o limite nao pode ser menor que o WIP atual." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
        cout << "Atualizacao cancelada." << endl;
    }
}

void CtrlApresentacaoQuadro::telaExcluir() {
    try {
        cout << "\n--- EXCLUIR QUADRO ---" << endl;
        Identificador id;
        if (!pedirPalavra("Identificador do quadro: ", &id)) return;

        if (servico != nullptr && servico->excluir(usuario, id)) {
            cout << "\n[Sucesso] Quadro excluido." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel excluir. Voce deve ser o gestor do projeto e o quadro nao pode ter cartoes." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoQuadro::telaListar() {
    try {
        cout << "\n--- QUADROS DO PROJETO ---" << endl;
        Identificador projeto;
        if (!pedirPalavra("Identificador do projeto: ", &projeto)) return;

        list<Identificador> ids;
        if (servico == nullptr || !servico->listar(usuario, projeto, &ids)) {
            cout << "\n[Erro] Nao foi possivel listar. O projeto existe?" << endl;
            return;
        }
        if (ids.empty()) {
            cout << "Nenhum quadro neste projeto." << endl;
        }
        for (list<Identificador>::iterator it = ids.begin(); it != ids.end(); it++) {
            cout << " - " << it->getValor() << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}
