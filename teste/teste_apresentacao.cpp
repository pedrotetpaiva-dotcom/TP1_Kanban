#include "teste.h"
#include "pessoa.h"
#include "projeto.h"
#include "quadro.h"
#include "cartao_atividade.h"
#include "ctrl_apresentacao.h"
#include "ctrl_apresentacao_projeto.h"
#include "ctrl_apresentacao_quadro.h"
#include "ctrl_apresentacao_cartao.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Os testes da apresentacao usam servicos FALSOS (mocks) que apenas registram
// a chamada recebida e devolvem um resultado programado, e trocam o teclado e a
// tela do programa por fluxos de texto. Assim verificamos, sem a camada de
// servico real, que a apresentacao valida os dados e chama a interface certa.

namespace {

class MockAutenticacao : public IServicoAutenticacao {
    public:
        bool resultado;
        int chamadas;
        string email;
        MockAutenticacao() : resultado(true), chamadas(0) {}
        bool autenticar(const Email& e, const Senha&) override { chamadas++; email = e.getValor(); return resultado; }
};

class MockPessoa : public IServicoPessoa {
    public:
        bool resultado;
        int criadas;
        string papelCriado;
        MockPessoa() : resultado(true), criadas(0) {}
        bool criar(const Pessoa& p) override { criadas++; papelCriado = p.getPapel().getValor(); return resultado; }
        bool ler(Pessoa*) override { return resultado; }
        bool atualizar(const Pessoa&) override { return resultado; }
        bool excluir(const Email&) override { return resultado; }
        bool listar(list<Email>*) override { return resultado; }
};

class MockProjeto : public IServicoProjeto {
    public:
        bool resultado;
        int criados;
        string solicitante, idCriado, nomeCriado;
        MockProjeto() : resultado(true), criados(0) {}
        bool criar(const Email& s, const Projeto& p) override {
            criados++; solicitante = s.getValor(); idCriado = p.getIdentificador().getValor();
            nomeCriado = p.getNome().getValor(); return resultado;
        }
        bool ler(const Email&, Projeto*) override { return resultado; }
        bool atualizar(const Email&, const Projeto&) override { return resultado; }
        bool excluir(const Email&, const Identificador&) override { return resultado; }
        bool listar(const Email&, list<Identificador>*) override { return resultado; }
};

class MockQuadro : public IServicoQuadro {
    public:
        bool resultado;
        int criados;
        string projeto;
        int limite;
        MockQuadro() : resultado(true), criados(0), limite(0) {}
        bool criar(const Email&, const Identificador& p, const Quadro& q) override {
            criados++; projeto = p.getValor(); limite = q.getLimite().getValor(); return resultado;
        }
        bool ler(const Email&, Quadro*) override { return resultado; }
        bool atualizar(const Email&, const Quadro&) override { return resultado; }
        bool excluir(const Email&, const Identificador&) override { return resultado; }
        bool listar(const Email&, const Identificador&, list<Identificador>*) override { return resultado; }
};

class MockCartao : public IServicoCartao {
    public:
        bool resultado;
        int criados, movidos;
        string desenvolvedor, movido;
        MockCartao() : resultado(true), criados(0), movidos(0) {}
        bool criar(const Email&, const Identificador&, const Email& d, const CartaoAtividade&) override {
            criados++; desenvolvedor = d.getValor(); return resultado;
        }
        bool ler(const Email&, CartaoAtividade*) override { return resultado; }
        bool atualizar(const Email&, const CartaoAtividade&) override { return resultado; }
        bool excluir(const Email&, const Identificador&) override { return resultado; }
        bool listar(const Email&, const Identificador&, list<Identificador>*) override { return resultado; }
        bool mover(const Email&, const Identificador& c) override { movidos++; movido = c.getValor(); return resultado; }
        bool lerTempoCiclo(const Email&, const Identificador&, long* m) override { *m = 90; return resultado; }
        bool lerTempoCicloMedio(const Email&, const Identificador&, double* m) override { *m = 45.5; return resultado; }
        bool lerLeadTime(const Email&, const Identificador&, long* m) override { *m = 120; return resultado; }
        bool lerLeadTimeMedio(const Email&, const Identificador&, double* m) override { *m = 60.25; return resultado; }
        bool lerWIP(const Email&, const Identificador&, int* w) override { *w = 2; return resultado; }
};

// Executa uma acao com o teclado simulado por 'entrada' e devolve o que foi escrito na tela.
template <class Acao>
string simular(const string& entrada, Acao acao) {
    istringstream in(entrada);
    ostringstream out;
    streambuf* teclado = cin.rdbuf(in.rdbuf());
    streambuf* tela = cout.rdbuf(out.rdbuf());
    acao();
    cin.rdbuf(teclado);
    cout.rdbuf(tela);
    cin.clear();
    return out.str();
}

bool contem(const string& texto, const string& trecho) {
    return texto.find(trecho) != string::npos;
}

Email usuario(const string& v) { Email e; e.setValor(v); return e; }

void testarAutenticacao() {
    secao("CtrlApresentacaoAutenticacao: login e cadastro");
    MockAutenticacao aut;
    MockPessoa pes;
    CtrlApresentacaoAutenticacao ctrl;
    ctrl.setServicoAutenticacao(&aut);
    ctrl.setServicoPessoa(&pes);

    bool entrou = false;
    string tela = simular("1\nana@x.com\nabc12\n", [&]() { entrou = ctrl.executarLogin(); });
    VERIFICAR_DESC(entrou, "login com credenciais aceitas devolve true");
    VERIFICAR_DESC(ctrl.getUsuarioLogado().getValor() == "ana@x.com", "guarda o e-mail do usuario logado");
    VERIFICAR_DESC(aut.chamadas == 1, "chama o servico de autenticacao uma vez");

    aut.resultado = false;
    tela = simular("1\nana@x.com\nabc12\n0\n", [&]() { entrou = ctrl.executarLogin(); });
    VERIFICAR_DESC(!entrou && contem(tela, "incorretos"), "login recusado mostra mensagem e nao entra");

    int antes = aut.chamadas;
    tela = simular("1\nemail-invalido\n0\n", [&]() { entrou = ctrl.executarLogin(); });
    VERIFICAR_DESC(aut.chamadas == antes && contem(tela, "ERRO DE FORMATO"),
                   "e-mail em formato invalido e barrado sem chamar o servico");

    tela = simular("1\nana@x.com\nabcde\n0\n", [&]() { entrou = ctrl.executarLogin(); });
    VERIFICAR_DESC(aut.chamadas == antes && contem(tela, "ERRO DE FORMATO"),
                   "senha em formato invalido e barrada sem chamar o servico");

    tela = simular("2\nAna Silva\nana@x.com\nabc12\nGESTOR\n0\n", [&]() { ctrl.executarLogin(); });
    VERIFICAR_DESC(pes.criadas == 1 && pes.papelCriado == "GESTOR" && contem(tela, "Conta criada"),
                   "cadastro valido chama criar pessoa com o papel digitado");

    tela = simular("2\nAna Silva\nana@x.com\nabc12\nCHEFE\n0\n", [&]() { ctrl.executarLogin(); });
    VERIFICAR_DESC(pes.criadas == 1 && contem(tela, "ERRO DE FORMATO"),
                   "cadastro com papel invalido e cancelado sem chamar o servico");

    pes.resultado = false;
    tela = simular("2\nAna Silva\nana@x.com\nabc12\nGESTOR\n0\n", [&]() { ctrl.executarLogin(); });
    VERIFICAR_DESC(contem(tela, "[Erro]"), "falha do servico no cadastro vira mensagem de erro");
}

void testarMenuPessoas() {
    secao("CtrlApresentacaoAutenticacao: menu de pessoas");
    MockAutenticacao aut;
    MockPessoa pes;
    CtrlApresentacaoAutenticacao ctrl;
    ctrl.setServicoAutenticacao(&aut);
    ctrl.setServicoPessoa(&pes);
    string tela = simular("4\n0\n", [&]() { ctrl.executarMenuPessoas(); });
    VERIFICAR_DESC(contem(tela, "PESSOAS CADASTRADAS"), "opcao 4 lista as pessoas");
    tela = simular("3\nbeto@x.com\n0\n", [&]() { ctrl.executarMenuPessoas(); });
    VERIFICAR_DESC(contem(tela, "Pessoa excluida"), "opcao 3 exclui a pessoa quando o servico aceita");
    tela = simular("9\n0\n", [&]() { ctrl.executarMenuPessoas(); });
    VERIFICAR_DESC(contem(tela, "Opcao invalida"), "opcao inexistente mostra aviso");
    tela = simular("abc\n0\n", [&]() { ctrl.executarMenuPessoas(); });
    VERIFICAR_DESC(contem(tela, "Opcao invalida"), "texto no lugar de numero nao trava o menu");
}

void testarProjeto() {
    secao("CtrlApresentacaoProjeto");
    MockProjeto srv;
    CtrlApresentacaoProjeto ctrl;
    ctrl.setServico(&srv);
    ctrl.setUsuario(usuario("ana@x.com"));

    string tela = simular("1\nPRJ001\nProjeto Um\nSistema de tarefas.\n05-NOV-2026-09:00\n30-NOV-2026-18:00\n0\n",
                          [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(srv.criados == 1 && srv.idCriado == "PRJ001" && srv.nomeCriado == "Projeto Um",
                   "criar projeto envia os dados digitados ao servico");
    VERIFICAR_DESC(srv.solicitante == "ana@x.com", "o usuario logado e enviado como solicitante");
    VERIFICAR_DESC(contem(tela, "Projeto criado"), "mensagem de sucesso");

    tela = simular("1\nAB1\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(srv.criados == 1 && contem(tela, "ERRO DE FORMATO"),
                   "identificador invalido e barrado sem chamar o servico");

    tela = simular("1\nPRJ002\nProjeto Dois\nsem maiuscula\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(srv.criados == 1 && contem(tela, "ERRO DE FORMATO"),
                   "descricao invalida e barrada sem chamar o servico");

    srv.resultado = false;
    tela = simular("1\nPRJ003\nProjeto Tres\nOutro texto.\n05-NOV-2026-09:00\n30-NOV-2026-18:00\n0\n",
                   [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "[Erro]"), "recusa do servico aparece como mensagem de erro");

    srv.resultado = true;
    tela = simular("5\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "PROJETOS"), "listar projetos");
    tela = simular("4\nPRJ001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "Projeto excluido"), "excluir projeto");
}

void testarQuadro() {
    secao("CtrlApresentacaoQuadro");
    MockQuadro srv;
    CtrlApresentacaoQuadro ctrl;
    ctrl.setServico(&srv);
    ctrl.setUsuario(usuario("ana@x.com"));

    string tela = simular("1\nPRJ001\nQDR001\nSprint Um\n3\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(srv.criados == 1 && srv.projeto == "PRJ001" && srv.limite == 3,
                   "criar quadro envia projeto e limite digitados");
    tela = simular("1\nPRJ001\nQDR002\nSprint Dois\n30\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(srv.criados == 1 && contem(tela, "ERRO DE FORMATO"), "limite fora de 1 a 25 e barrado");
    tela = simular("1\nPRJ001\nQDR002\nSprint Dois\nabc\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(srv.criados == 1 && contem(tela, "ERRO DE FORMATO"), "limite nao numerico e barrado");
    tela = simular("5\nPRJ001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "QUADROS DO PROJETO"), "listar quadros de um projeto");
}

void testarCartao() {
    secao("CtrlApresentacaoCartao");
    MockCartao srv;
    CtrlApresentacaoCartao ctrl;
    ctrl.setServico(&srv);
    ctrl.setUsuario(usuario("ana@x.com"));

    string tela = simular("1\nQDR001\nbeto@x.com\nCRT001\nTarefa Um\nFazer a tela.\nALTA\nMEDIO\n0\n",
                          [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(srv.criados == 1 && srv.desenvolvedor == "beto@x.com", "criar cartao envia o desenvolvedor");
    tela = simular("1\nQDR001\nbeto@x.com\nCRT002\nTarefa Dois\nFazer a tela.\nURGENTE\n0\n",
                   [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(srv.criados == 1 && contem(tela, "ERRO DE FORMATO"), "prioridade invalida e barrada");
    tela = simular("6\nCRT001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(srv.movidos == 1 && srv.movido == "CRT001" && contem(tela, "[Sucesso]"), "mover cartao");
    tela = simular("7\nCRT001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "90 minutos"), "mostra o tempo de ciclo devolvido pelo servico");
    tela = simular("8\nQDR001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "45.50 minutos"), "mostra o tempo de ciclo medio com duas casas");
    tela = simular("9\nCRT001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "120 minutos"), "mostra o lead time");
    tela = simular("10\nQDR001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "60.25 minutos"), "mostra o lead time medio");
    tela = simular("11\nQDR001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "WIP (cartoes em FAZENDO): 2"), "mostra o WIP");
    srv.resultado = false;
    tela = simular("6\nCRT001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "[Erro]"), "mover recusado pelo servico mostra erro");
    tela = simular("11\nQDR001\n0\n", [&]() { ctrl.executarMenu(); });
    VERIFICAR_DESC(contem(tela, "[Erro]"), "WIP indisponivel mostra erro");
}

}  // namespace

void executarTestesApresentacao() {
    cabecalho("TESTES DA CAMADA DE APRESENTACAO (com servicos falsos)");
    testarAutenticacao();
    testarMenuPessoas();
    testarProjeto();
    testarQuadro();
    testarCartao();
}
