#include "ctrl_apresentacao_projeto.h"
#include "entrada_console.h"
#include "projeto.h"
#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

CtrlApresentacaoProjeto::CtrlApresentacaoProjeto() {
    servico = nullptr;
}

void CtrlApresentacaoProjeto::setServico(IServicoProjeto* servico) {
    this->servico = servico;
}

void CtrlApresentacaoProjeto::setUsuario(const Email& usuario) {
    this->usuario = usuario;
}

void CtrlApresentacaoProjeto::executarMenu() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "         MENU DE PROJETOS              " << endl;
        cout << "=======================================" << endl;
        cout << "1 - Criar Projeto (Apenas Gestor)" << endl;
        cout << "2 - Ler Dados do Projeto" << endl;
        cout << "3 - Atualizar Projeto (Apenas Gestor do projeto)" << endl;
        cout << "4 - Excluir Projeto (Apenas Gestor do projeto)" << endl;
        cout << "5 - Listar Projetos" << endl;
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

void CtrlApresentacaoProjeto::telaCriar() {
    try {
        cout << "\n--- CRIAR PROJETO ---" << endl;
        Identificador id; Nome nome; Texto descricao; Timestamp inicio, termino;
        if (!pedirPalavra("Identificador (3 letras e 3 digitos, ex. ABC123): ", &id)) return;
        if (!pedirLinha("Nome: ", &nome)) return;
        if (!pedirLinha("Descricao (comeca com maiuscula e termina com ponto): ", &descricao)) return;
        if (!pedirPalavra("Inicio (DIA-MES-ANO-HH:MM, ex. 05-NOV-2026-09:00): ", &inicio)) return;
        if (!pedirPalavra("Termino (DIA-MES-ANO-HH:MM): ", &termino)) return;

        Projeto projeto;
        projeto.setIdentificador(id);
        projeto.setNome(nome);
        projeto.setDescricao(descricao);
        projeto.setInicio(inicio);
        projeto.setTermino(termino);

        if (servico != nullptr && servico->criar(usuario, projeto)) {
            cout << "\n[Sucesso] Projeto criado. Voce e o gestor dele." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel criar. Apenas gestores criam projetos e o identificador deve ser novo." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
        cout << "Operacao cancelada." << endl;
    }
}

void CtrlApresentacaoProjeto::telaLer() {
    try {
        cout << "\n--- LER PROJETO ---" << endl;
        Projeto projeto;
        Identificador id;
        if (!pedirPalavra("Identificador do projeto: ", &id)) return;
        projeto.setIdentificador(id);

        if (servico != nullptr && servico->ler(usuario, &projeto)) {
            cout << "\nIdentificador: " << projeto.getIdentificador().getValor() << endl;
            cout << "Nome         : " << projeto.getNome().getValor() << endl;
            cout << "Descricao    : " << projeto.getDescricao().getValor() << endl;
            cout << "Inicio       : " << projeto.getInicio().getValor() << endl;
            cout << "Termino      : " << projeto.getTermino().getValor() << endl;
        } else {
            cout << "\n[Erro] Projeto nao encontrado." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoProjeto::telaAtualizar() {
    try {
        cout << "\n--- ATUALIZAR PROJETO ---" << endl;
        Identificador id; Nome nome; Texto descricao; Timestamp inicio, termino;
        if (!pedirPalavra("Identificador do projeto (nao pode ser alterado): ", &id)) return;
        if (!pedirLinha("Novo nome: ", &nome)) return;
        if (!pedirLinha("Nova descricao: ", &descricao)) return;
        if (!pedirPalavra("Novo inicio (DIA-MES-ANO-HH:MM): ", &inicio)) return;
        if (!pedirPalavra("Novo termino (DIA-MES-ANO-HH:MM): ", &termino)) return;

        Projeto projeto;
        projeto.setIdentificador(id);
        projeto.setNome(nome);
        projeto.setDescricao(descricao);
        projeto.setInicio(inicio);
        projeto.setTermino(termino);

        if (servico != nullptr && servico->atualizar(usuario, projeto)) {
            cout << "\n[Sucesso] Projeto atualizado." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel atualizar. O projeto deve existir e voce deve ser o gestor dele." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
        cout << "Atualizacao cancelada." << endl;
    }
}

void CtrlApresentacaoProjeto::telaExcluir() {
    try {
        cout << "\n--- EXCLUIR PROJETO ---" << endl;
        Identificador id;
        if (!pedirPalavra("Identificador do projeto: ", &id)) return;

        if (servico != nullptr && servico->excluir(usuario, id)) {
            cout << "\n[Sucesso] Projeto excluido." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel excluir. Voce deve ser o gestor e o projeto nao pode ter quadros." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoProjeto::telaListar() {
    list<Identificador> ids;
    cout << "\n--- PROJETOS ---" << endl;
    if (servico == nullptr || !servico->listar(usuario, &ids)) {
        cout << "[Erro] Nao foi possivel listar." << endl;
        return;
    }
    if (ids.empty()) {
        cout << "Nenhum projeto cadastrado." << endl;
    }
    for (list<Identificador>::iterator it = ids.begin(); it != ids.end(); it++) {
        cout << " - " << it->getValor() << endl;
    }
}
