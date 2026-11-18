#include "teste.h"
#include "pessoa.h"
#include "projeto.h"
#include "quadro.h"
#include "cartao_atividade.h"
#include <string>

using namespace std;

namespace {

Email email(const string& v) { Email e; e.setValor(v); return e; }
Nome nome(const string& v) { Nome n; n.setValor(v); return n; }
Senha senha(const string& v) { Senha s; s.setValor(v); return s; }
Papel papel(const string& v) { Papel p; p.setValor(v); return p; }
Identificador id(const string& v) { Identificador i; i.setValor(v); return i; }
Texto texto(const string& v) { Texto t; t.setValor(v); return t; }
Timestamp ts(const string& v) { Timestamp t; t.setValor(v); return t; }
Limite limite(int v) { Limite l; l.setValor(v); return l; }
Prioridade prioridade(const string& v) { Prioridade p; p.setValor(v); return p; }
Estado estado(const string& v) { Estado e; e.setValor(v); return e; }
Tamanho tamanho(const string& v) { Tamanho t; t.setValor(v); return t; }

void testarPessoa() {
    secao("Entidade Pessoa (email, nome, senha, papel)");
    Pessoa p;
    p.setEmail(email("ana@x.com"));
    p.setNome(nome("Ana Silva"));
    p.setSenha(senha("abc12"));
    p.setPapel(papel("GESTOR"));
    VERIFICAR(p.getEmail().getValor() == "ana@x.com");
    VERIFICAR(p.getNome().getValor() == "Ana Silva");
    VERIFICAR(p.getSenha().getValor() == "abc12");
    VERIFICAR(p.getPapel().getValor() == "GESTOR");
    p.setPapel(papel("DESENVOLVEDOR"));
    VERIFICAR_DESC(p.getPapel().getValor() == "DESENVOLVEDOR" && p.getEmail().getValor() == "ana@x.com",
                   "alterar um atributo nao muda os demais");
    Pessoa copia = p;
    VERIFICAR_DESC(copia.getEmail().getValor() == "ana@x.com", "a copia mantem os atributos");
}

void testarProjeto() {
    secao("Entidade Projeto (identificador, nome, descricao, inicio, termino)");
    Projeto p;
    p.setIdentificador(id("PRJ001"));
    p.setNome(nome("Projeto Um"));
    p.setDescricao(texto("Sistema de tarefas."));
    p.setInicio(ts("05-NOV-2026-09:00"));
    p.setTermino(ts("30-NOV-2026-18:00"));
    VERIFICAR(p.getIdentificador().getValor() == "PRJ001");
    VERIFICAR(p.getNome().getValor() == "Projeto Um");
    VERIFICAR(p.getDescricao().getValor() == "Sistema de tarefas.");
    VERIFICAR(p.getInicio().getValor() == "05-NOV-2026-09:00");
    VERIFICAR(p.getTermino().getValor() == "30-NOV-2026-18:00");
}

void testarQuadro() {
    secao("Entidade Quadro (identificador, nome, limite)");
    Quadro q;
    q.setIdentificador(id("QDR001"));
    q.setNome(nome("Sprint Um"));
    q.setLimite(limite(3));
    VERIFICAR(q.getIdentificador().getValor() == "QDR001");
    VERIFICAR(q.getNome().getValor() == "Sprint Um");
    VERIFICAR(q.getLimite().getValor() == 3);
}

void testarCartao() {
    secao("Entidade CartaoAtividade (9 atributos)");
    CartaoAtividade c;
    c.setIdentificador(id("CRT001"));
    c.setNome(nome("Tarefa Um"));
    c.setDescricao(texto("Fazer a tela."));
    c.setPrioridade(prioridade("ALTA"));
    c.setEstado(estado("A FAZER"));
    c.setTamanho(tamanho("MEDIO"));
    c.setEntrada(ts("05-NOV-2026-09:00"));
    c.setInicio(ts("05-NOV-2026-10:00"));
    c.setTermino(ts("05-NOV-2026-12:00"));
    VERIFICAR(c.getIdentificador().getValor() == "CRT001");
    VERIFICAR(c.getNome().getValor() == "Tarefa Um");
    VERIFICAR(c.getDescricao().getValor() == "Fazer a tela.");
    VERIFICAR(c.getPrioridade().getValor() == "ALTA");
    VERIFICAR(c.getEstado().getValor() == "A FAZER");
    VERIFICAR(c.getTamanho().getValor() == "MEDIO");
    VERIFICAR(c.getEntrada().getValor() == "05-NOV-2026-09:00");
    VERIFICAR(c.getInicio().getValor() == "05-NOV-2026-10:00");
    VERIFICAR(c.getTermino().getValor() == "05-NOV-2026-12:00");
    c.setEstado(estado("FEITO"));
    VERIFICAR_DESC(c.getEstado().getValor() == "FEITO" && c.getNome().getValor() == "Tarefa Um",
                   "alterar o estado nao muda os demais atributos");
}

}  // namespace

void executarTestesEntidades() {
    cabecalho("TESTES DAS ENTIDADES (4 classes)");
    testarPessoa();
    testarProjeto();
    testarQuadro();
    testarCartao();
}
