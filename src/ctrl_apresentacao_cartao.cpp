#include "ctrl_apresentacao_cartao.h"
#include "entrada_console.h"
#include "cartao_atividade.h"
#include <iomanip>
#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

CtrlApresentacaoCartao::CtrlApresentacaoCartao() {
    servico = nullptr;
}

void CtrlApresentacaoCartao::setServico(IServicoCartao* servico) {
    this->servico = servico;
}

void CtrlApresentacaoCartao::setUsuario(const Email& usuario) {
    this->usuario = usuario;
}

namespace {

// Mostra um Timestamp ou um traco se ainda nao foi registrado.
string ou_traco(const string& valor) {
    return valor.empty() ? "-" : valor;
}

}  // namespace

void CtrlApresentacaoCartao::executarMenu() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "         MENU DE CARTOES               " << endl;
        cout << "=======================================" << endl;
        cout << " 1 - Criar Cartao (Apenas Gestor do projeto)" << endl;
        cout << " 2 - Ler Dados do Cartao" << endl;
        cout << " 3 - Atualizar Cartao (Apenas Gestor do projeto)" << endl;
        cout << " 4 - Excluir Cartao (Apenas Gestor do projeto)" << endl;
        cout << " 5 - Listar Cartoes de um Quadro" << endl;
        cout << " 6 - Mover Cartao" << endl;
        cout << " 7 - Ler Tempo de Ciclo de um Cartao" << endl;
        cout << " 8 - Ler Tempo de Ciclo Medio de um Quadro" << endl;
        cout << " 9 - Ler Lead Time de um Cartao" << endl;
        cout << "10 - Ler Lead Time Medio de um Quadro" << endl;
        cout << "11 - Ler WIP de um Quadro" << endl;
        cout << " 0 - Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        opcao = lerOpcao();

        switch (opcao) {
            case 1: telaCriar(); break;
            case 2: telaLer(); break;
            case 3: telaAtualizar(); break;
            case 4: telaExcluir(); break;
            case 5: telaListar(); break;
            case 6: telaMover(); break;
            case 7: telaTempoCiclo(); break;
            case 8: telaTempoCicloMedio(); break;
            case 9: telaLeadTime(); break;
            case 10: telaLeadTimeMedio(); break;
            case 11: telaWIP(); break;
            case 0: cout << "\nVoltando..." << endl; break;
            default: cout << "\nOpcao invalida. Tente novamente." << endl;
        }
    }
}

void CtrlApresentacaoCartao::telaCriar() {
    try {
        cout << "\n--- CRIAR CARTAO ---" << endl;
        Identificador quadro, id; Email desenvolvedor; Nome nome; Texto descricao;
        Prioridade prioridade; Tamanho tamanho;
        if (!pedirPalavra("Identificador do quadro: ", &quadro)) return;
        if (!pedirPalavra("Email do desenvolvedor responsavel: ", &desenvolvedor)) return;
        if (!pedirPalavra("Identificador do novo cartao (ex. CRT001): ", &id)) return;
        if (!pedirLinha("Nome: ", &nome)) return;
        if (!pedirLinha("Descricao (comeca com maiuscula e termina com ponto): ", &descricao)) return;
        if (!pedirPalavra("Prioridade (ALTA, MEDIA ou BAIXA): ", &prioridade)) return;
        if (!pedirPalavra("Tamanho (GRANDE, MEDIO ou PEQUENO): ", &tamanho)) return;

        CartaoAtividade cartao;
        cartao.setIdentificador(id);
        cartao.setNome(nome);
        cartao.setDescricao(descricao);
        cartao.setPrioridade(prioridade);
        cartao.setTamanho(tamanho);

        if (servico != nullptr && servico->criar(usuario, quadro, desenvolvedor, cartao)) {
            cout << "\n[Sucesso] Cartao criado na coluna A FAZER." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel criar. O quadro e o desenvolvedor devem existir, voce deve ser o gestor do projeto e o identificador deve ser novo." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
        cout << "Operacao cancelada." << endl;
    }
}

void CtrlApresentacaoCartao::telaLer() {
    try {
        cout << "\n--- LER CARTAO ---" << endl;
        CartaoAtividade cartao;
        Identificador id;
        if (!pedirPalavra("Identificador do cartao: ", &id)) return;
        cartao.setIdentificador(id);

        if (servico != nullptr && servico->ler(usuario, &cartao)) {
            cout << "\nIdentificador: " << cartao.getIdentificador().getValor() << endl;
            cout << "Nome         : " << cartao.getNome().getValor() << endl;
            cout << "Descricao    : " << cartao.getDescricao().getValor() << endl;
            cout << "Prioridade   : " << cartao.getPrioridade().getValor() << endl;
            cout << "Estado       : " << cartao.getEstado().getValor() << endl;
            cout << "Tamanho      : " << cartao.getTamanho().getValor() << endl;
            cout << "Entrada      : " << ou_traco(cartao.getEntrada().getValor()) << endl;
            cout << "Inicio       : " << ou_traco(cartao.getInicio().getValor()) << endl;
            cout << "Termino      : " << ou_traco(cartao.getTermino().getValor()) << endl;
        } else {
            cout << "\n[Erro] Cartao nao encontrado." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoCartao::telaAtualizar() {
    try {
        cout << "\n--- ATUALIZAR CARTAO ---" << endl;
        cout << "(estado e instantes mudam apenas ao mover o cartao)" << endl;
        Identificador id; Nome nome; Texto descricao; Prioridade prioridade; Tamanho tamanho;
        if (!pedirPalavra("Identificador do cartao (nao pode ser alterado): ", &id)) return;
        if (!pedirLinha("Novo nome: ", &nome)) return;
        if (!pedirLinha("Nova descricao: ", &descricao)) return;
        if (!pedirPalavra("Nova prioridade (ALTA, MEDIA ou BAIXA): ", &prioridade)) return;
        if (!pedirPalavra("Novo tamanho (GRANDE, MEDIO ou PEQUENO): ", &tamanho)) return;

        CartaoAtividade cartao;
        cartao.setIdentificador(id);
        cartao.setNome(nome);
        cartao.setDescricao(descricao);
        cartao.setPrioridade(prioridade);
        cartao.setTamanho(tamanho);

        if (servico != nullptr && servico->atualizar(usuario, cartao)) {
            cout << "\n[Sucesso] Cartao atualizado." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel atualizar. O cartao deve existir e voce deve ser o gestor do projeto." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
        cout << "Atualizacao cancelada." << endl;
    }
}

void CtrlApresentacaoCartao::telaExcluir() {
    try {
        cout << "\n--- EXCLUIR CARTAO ---" << endl;
        Identificador id;
        if (!pedirPalavra("Identificador do cartao: ", &id)) return;

        if (servico != nullptr && servico->excluir(usuario, id)) {
            cout << "\n[Sucesso] Cartao excluido." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel excluir. O cartao deve existir e voce deve ser o gestor do projeto." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoCartao::telaListar() {
    try {
        cout << "\n--- CARTOES DO QUADRO ---" << endl;
        Identificador quadro;
        if (!pedirPalavra("Identificador do quadro: ", &quadro)) return;

        list<Identificador> ids;
        if (servico == nullptr || !servico->listar(usuario, quadro, &ids)) {
            cout << "\n[Erro] Nao foi possivel listar. O quadro existe?" << endl;
            return;
        }
        if (ids.empty()) {
            cout << "Nenhum cartao neste quadro." << endl;
        }
        for (list<Identificador>::iterator it = ids.begin(); it != ids.end(); it++) {
            cout << " - " << it->getValor() << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoCartao::telaMover() {
    try {
        cout << "\n--- MOVER CARTAO ---" << endl;
        cout << "(A FAZER -> FAZENDO -> FEITO)" << endl;
        Identificador id;
        if (!pedirPalavra("Identificador do cartao: ", &id)) return;

        if (servico != nullptr && servico->mover(usuario, id)) {
            CartaoAtividade cartao;
            cartao.setIdentificador(id);
            if (servico->ler(usuario, &cartao)) {
                cout << "\n[Sucesso] Cartao agora em " << cartao.getEstado().getValor() << "." << endl;
            } else {
                cout << "\n[Sucesso] Cartao movido." << endl;
            }
        } else {
            cout << "\n[Erro] Nao foi possivel mover. O cartao pode ja estar em FEITO ou o limite de WIP do quadro foi atingido." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoCartao::telaTempoCiclo() {
    try {
        cout << "\n--- TEMPO DE CICLO ---" << endl;
        Identificador id;
        if (!pedirPalavra("Identificador do cartao: ", &id)) return;
        long minutos = 0;
        if (servico != nullptr && servico->lerTempoCiclo(usuario, id, &minutos)) {
            cout << "\nTempo de ciclo: " << minutos << " minutos." << endl;
        } else {
            cout << "\n[Erro] Indisponivel. O cartao deve existir e estar em FEITO." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoCartao::telaTempoCicloMedio() {
    try {
        cout << "\n--- TEMPO DE CICLO MEDIO ---" << endl;
        Identificador quadro;
        if (!pedirPalavra("Identificador do quadro: ", &quadro)) return;
        double minutos = 0;
        if (servico != nullptr && servico->lerTempoCicloMedio(usuario, quadro, &minutos)) {
            cout << fixed << setprecision(2);
            cout << "\nTempo de ciclo medio: " << minutos << " minutos." << endl;
        } else {
            cout << "\n[Erro] Indisponivel. O quadro deve existir e ter cartoes em FEITO." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoCartao::telaLeadTime() {
    try {
        cout << "\n--- LEAD TIME ---" << endl;
        Identificador id;
        if (!pedirPalavra("Identificador do cartao: ", &id)) return;
        long minutos = 0;
        if (servico != nullptr && servico->lerLeadTime(usuario, id, &minutos)) {
            cout << "\nLead time: " << minutos << " minutos." << endl;
        } else {
            cout << "\n[Erro] Indisponivel. O cartao deve existir e estar em FEITO." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoCartao::telaLeadTimeMedio() {
    try {
        cout << "\n--- LEAD TIME MEDIO ---" << endl;
        Identificador quadro;
        if (!pedirPalavra("Identificador do quadro: ", &quadro)) return;
        double minutos = 0;
        if (servico != nullptr && servico->lerLeadTimeMedio(usuario, quadro, &minutos)) {
            cout << fixed << setprecision(2);
            cout << "\nLead time medio: " << minutos << " minutos." << endl;
        } else {
            cout << "\n[Erro] Indisponivel. O quadro deve existir e ter cartoes em FEITO." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoCartao::telaWIP() {
    try {
        cout << "\n--- WIP ---" << endl;
        Identificador quadro;
        if (!pedirPalavra("Identificador do quadro: ", &quadro)) return;
        int wip = 0;
        if (servico != nullptr && servico->lerWIP(usuario, quadro, &wip)) {
            cout << "\nWIP (cartoes em FAZENDO): " << wip << endl;
        } else {
            cout << "\n[Erro] Indisponivel. O quadro existe?" << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}
