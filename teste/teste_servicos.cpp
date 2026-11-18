#include "teste.h"
#include <iostream>
#include <cstdlib>
#include "ctrl_servico_autenticacao.h"
#include "ctrl_servico_pessoa.h"
#include "ctrl_servico_projeto.h"
#include "ctrl_servico_quadro.h"
#include "ctrl_servico_cartao.h"
using namespace std;
#define CHECK(c) VERIFICAR(c)

class CartaoRelogio : public CtrlServicoCartao {
public:
    string agoraTxt;
    CartaoRelogio(ContainerPessoa*a,ContainerProjeto*b,ContainerQuadro*c,ContainerCartao*d):CtrlServicoCartao(a,b,c,d){agoraTxt="10-JAN-2025-10:00";}
protected:
    Timestamp agora() const override { Timestamp t; t.setValor(agoraTxt); return t; }
};
Email E(const char*s){Email e;e.setValor(s);return e;}
Identificador I(const char*s){Identificador i;i.setValor(s);return i;}
Pessoa P(const char*em,const char*papel){Pessoa p;p.setEmail(E(em));Nome n;n.setValor("Fulano");p.setNome(n);Senha s;s.setValor("abc12");p.setSenha(s);Papel pp;pp.setValor(papel);p.setPapel(pp);return p;}
Projeto PR(const char*id){Projeto p;p.setIdentificador(I(id));Nome n;n.setValor("Proj");p.setNome(n);Texto t;t.setValor("Desc.");p.setDescricao(t);return p;}
Quadro Q(const char*id,int lim){Quadro q;q.setIdentificador(I(id));Nome n;n.setValor("Quad");q.setNome(n);Limite l;l.setValor(lim);q.setLimite(l);return q;}
CartaoAtividade C(const char*id){CartaoAtividade c;c.setIdentificador(I(id));Nome n;n.setValor("Card");c.setNome(n);Texto t;t.setValor("Desc.");c.setDescricao(t);Prioridade p;p.setValor("ALTA");c.setPrioridade(p);Tamanho t2;t2.setValor("MEDIO");c.setTamanho(t2);Estado e;e.setValor("FEITO");c.setEstado(e);return c;}

void executarTestesServicos(){
    cabecalho("TESTES DA CAMADA DE SERVICO (controladoras + conteineres)");
    ContainerPessoa cp; ContainerProjeto cj; ContainerQuadro cq; ContainerCartao cc;
    CtrlServicoAutenticacao aut(&cp);
    CtrlServicoPessoa sp(&cp,&cj,&cc);
    CtrlServicoProjeto sj(&cp,&cj,&cq);
    CtrlServicoQuadro sq(&cp,&cj,&cq,&cc);
    CartaoRelogio sc(&cp,&cj,&cq,&cc);
    Email g=E("gestor@x.com"), d=E("dev@x.com"), g2=E("gest2@x.com"), nx=E("nao@x.com");
    Senha ok; ok.setValor("abc12"); Senha b2; b2.setValor("abc13");
    secao("Pessoas");
    CHECK(sp.criar(P("gestor@x.com","GESTOR")));
    CHECK(!sp.criar(P("gestor@x.com","GESTOR")));
    CHECK(sp.criar(P("dev@x.com","DESENVOLVEDOR")));
    CHECK(sp.criar(P("gest2@x.com","GESTOR")));
    CHECK(aut.autenticar(g,ok)); CHECK(!aut.autenticar(g,b2)); CHECK(!aut.autenticar(nx,ok));
    Pessoa lp; lp.setEmail(d); CHECK(sp.ler(&lp)); CHECK(lp.getPapel().getValor()=="DESENVOLVEDOR");
    list<Email> le; CHECK(sp.listar(&le)); CHECK(le.size()==3);
    secao("Projetos");
    CHECK(!sj.criar(d,PR("PRJ001")));      // dev nao cria
    CHECK(!sj.criar(nx,PR("PRJ001")));
    CHECK(sj.criar(g,PR("PRJ001")));
    CHECK(!sj.criar(g,PR("PRJ001")));
    Projeto lj; lj.setIdentificador(I("PRJ001")); CHECK(sj.ler(d,&lj)); CHECK(!sj.ler(nx,&lj));
    CHECK(!sj.atualizar(g2,PR("PRJ001"))); CHECK(!sj.atualizar(d,PR("PRJ001"))); CHECK(sj.atualizar(g,PR("PRJ001")));
    list<Identificador> li; CHECK(sj.listar(d,&li)); CHECK(li.size()==1);
    secao("Consistencia: papel e exclusao de pessoa");
    CHECK(!sp.atualizar(P("gestor@x.com","DESENVOLVEDOR")));
    CHECK(sp.atualizar(P("gest2@x.com","DESENVOLVEDOR")));
    CHECK(sp.atualizar(P("gest2@x.com","GESTOR")));
    CHECK(!sp.excluir(g)); // gestor de projeto
    secao("Quadros");
    CHECK(!sq.criar(d,I("PRJ001"),Q("QDR001",1))); CHECK(!sq.criar(g2,I("PRJ001"),Q("QDR001",1)));
    CHECK(!sq.criar(g,I("PRJ999"),Q("QDR001",1)));
    CHECK(sq.criar(g,I("PRJ001"),Q("QDR001",1)));
    CHECK(!sq.criar(g,I("PRJ001"),Q("QDR001",2)));
    CHECK(sq.criar(g,I("PRJ001"),Q("QDR002",3)));
    Quadro lq; lq.setIdentificador(I("QDR001")); CHECK(sq.ler(d,&lq)); CHECK(lq.getLimite().getValor()==1); CHECK(!sq.ler(nx,&lq));
    li.clear(); CHECK(sq.listar(d,I("PRJ001"),&li)); CHECK(li.size()==2); CHECK(!sq.listar(d,I("PRJ999"),&li)); CHECK(!sq.listar(nx,I("PRJ001"),&li));
    CHECK(!sj.excluir(g,I("PRJ001"))); // tem quadros
    secao("Cartoes: criar, ler, atualizar");
    CHECK(!sc.criar(d,I("QDR001"),d,C("CRT001"))); CHECK(!sc.criar(g2,I("QDR001"),d,C("CRT001")));
    CHECK(!sc.criar(g,I("QDR999"),d,C("CRT001"))); CHECK(!sc.criar(g,I("QDR001"),nx,C("CRT001")));
    CHECK(sc.criar(g,I("QDR001"),d,C("CRT001")));
    CHECK(!sc.criar(g,I("QDR001"),d,C("CRT001")));
    CHECK(sc.criar(g,I("QDR001"),d,C("CRT002")));
    CartaoAtividade lc; lc.setIdentificador(I("CRT001")); CHECK(sc.ler(d,&lc));
    CHECK(lc.getEstado().getValor()=="A FAZER"); CHECK(lc.getEntrada().getValor()=="10-JAN-2025-10:00"); CHECK(lc.getInicio().getValor()==""); CHECK(lc.getTermino().getValor()=="");
    CHECK(!sc.ler(nx,&lc));
    CHECK(!sp.excluir(d)); // dev de cartao
    CHECK(!sq.excluir(g,I("QDR001"))); // tem cartoes
    secao("Atualizar preserva estado e instantes");
    CartaoAtividade nova=C("CRT001"); Nome nn; nn.setValor("Novo nome"); nova.setNome(nn); Prioridade pb; pb.setValor("BAIXA"); nova.setPrioridade(pb);
    CHECK(!sc.atualizar(d,nova)); CHECK(sc.atualizar(g,nova));
    sc.ler(d,&lc); CHECK(lc.getNome().getValor()=="Novo nome"); CHECK(lc.getPrioridade().getValor()=="BAIXA"); CHECK(lc.getEstado().getValor()=="A FAZER");
    secao("Metricas sem cartoes em FEITO");
    double m=0; long mi=0; int wip=-1;
    CHECK(!sc.lerTempoCicloMedio(d,I("QDR001"),&m)); CHECK(!sc.lerLeadTimeMedio(d,I("QDR001"),&m));
    CHECK(!sc.lerTempoCiclo(d,I("CRT001"),&mi)); CHECK(!sc.lerLeadTime(d,I("CRT001"),&mi));
    CHECK(sc.lerWIP(d,I("QDR001"),&wip)); CHECK(wip==0);
    CHECK(!sc.lerWIP(nx,I("QDR001"),&wip)); CHECK(!sc.lerWIP(d,I("QDR999"),&wip));
    secao("Mover e metricas (entrada 10:00, inicio 10:30, termino 12:00)");
    sc.agoraTxt="10-JAN-2025-10:30";
    CHECK(!sc.mover(nx,I("CRT001")));
    CHECK(sc.mover(d,I("CRT001")));
    sc.ler(d,&lc); CHECK(lc.getEstado().getValor()=="FAZENDO"); CHECK(lc.getInicio().getValor()=="10-JAN-2025-10:30");
    sc.lerWIP(d,I("QDR001"),&wip); CHECK(wip==1);
    CHECK(!sc.mover(d,I("CRT002")));   // WIP limit 1
    sc.agoraTxt="10-JAN-2025-10:29";
    CHECK(!sc.mover(d,I("CRT001")));   // relogio voltou
    sc.agoraTxt="10-JAN-2025-12:00";
    CHECK(sc.mover(d,I("CRT001")));
    sc.ler(d,&lc); CHECK(lc.getEstado().getValor()=="FEITO"); CHECK(lc.getTermino().getValor()=="10-JAN-2025-12:00");
    CHECK(!sc.mover(d,I("CRT001")));   // FEITO
    CHECK(sc.lerTempoCiclo(d,I("CRT001"),&mi)); CHECK(mi==90);
    CHECK(sc.lerLeadTime(d,I("CRT001"),&mi)); CHECK(mi==120);
    sc.lerWIP(d,I("QDR001"),&wip); CHECK(wip==0);
    CHECK(sc.mover(g,I("CRT002")));    // agora cabe (gestor tambem move)
    // segundo cartao: entrada 10:00 inicio 12:00 termino 29-FEV-2028-... usa viradas
    sc.agoraTxt="11-JAN-2025-12:00";
    CHECK(sc.mover(d,I("CRT002")));
    CHECK(sc.lerTempoCiclo(d,I("CRT002"),&mi)); CHECK(mi==1440);       // inicio 12:00 10-JAN -> 12:00 11-JAN
    CHECK(sc.lerLeadTime(d,I("CRT002"),&mi)); CHECK(mi==1560);        // 10:00 10-JAN -> 12:00 11-JAN
    CHECK(sc.lerTempoCicloMedio(d,I("QDR001"),&m)); CHECK(m==(90+1440)/2.0);
    CHECK(sc.lerLeadTimeMedio(d,I("QDR001"),&m)); CHECK(m==(120+1560)/2.0);
    CHECK(!sc.lerTempoCicloMedio(nx,I("QDR001"),&m)); CHECK(!sc.lerTempoCicloMedio(d,I("QDR999"),&m));
    secao("Datas: virada de ano e ano bissexto");
    sc.agoraTxt="31-DEZ-2027-23:30"; CHECK(sc.criar(g,I("QDR002"),d,C("CRT003")));
    sc.agoraTxt="29-FEV-2028-00:30"; CHECK(sc.mover(d,I("CRT003")));
    sc.agoraTxt="01-MAR-2028-00:30"; CHECK(sc.mover(d,I("CRT003")));
    CHECK(sc.lerTempoCiclo(d,I("CRT003"),&mi)); CHECK(mi==1440);
    CHECK(sc.lerLeadTime(d,I("CRT003"),&mi)); CHECK(mi==86460);
    secao("Limite de WIP");
    CHECK(sq.criar(g,I("PRJ001"),Q("QDR003",3)));
    CHECK(sc.criar(g,I("QDR003"),d,C("CRT004"))); CHECK(sc.criar(g,I("QDR003"),d,C("CRT005")));
    CHECK(sc.mover(d,I("CRT004"))); CHECK(sc.mover(d,I("CRT005")));
    CHECK(!sq.atualizar(g,Q("QDR003",1)));
    CHECK(sq.atualizar(g,Q("QDR003",2)));
    CHECK(!sq.atualizar(g2,Q("QDR003",5))); CHECK(!sq.atualizar(g,Q("QDR999",5)));
    secao("Exclusoes");
    li.clear(); CHECK(sc.listar(d,I("QDR003"),&li)); CHECK(li.size()==2); CHECK(!sc.listar(nx,I("QDR003"),&li)); CHECK(!sc.listar(d,I("QDR999"),&li));
    CHECK(!sc.excluir(d,I("CRT004"))); CHECK(sc.excluir(g,I("CRT004"))); CHECK(!sc.excluir(g,I("CRT004"))); CHECK(sc.excluir(g,I("CRT005")));
    CHECK(!sq.excluir(g2,I("QDR003"))); CHECK(sq.excluir(g,I("QDR003")));
    secao("Exclusao em cascata ordenada");
    sc.excluir(g,I("CRT001"));sc.excluir(g,I("CRT002"));sc.excluir(g,I("CRT003"));
    CHECK(sq.excluir(g,I("QDR001")));CHECK(sq.excluir(g,I("QDR002")));
    CHECK(!sj.excluir(g2,I("PRJ001"))); CHECK(sj.excluir(g,I("PRJ001")));
    CHECK(sp.excluir(g)); CHECK(sp.excluir(d)); CHECK(!sp.excluir(d));
    secao("Relogio real do computador");
    { CtrlServicoCartao real(&cp,&cj,&cq,&cc); sp.criar(P("gestor@x.com","GESTOR")); sp.criar(P("dev@x.com","DESENVOLVEDOR"));
      CtrlServicoCartao* r=&real; (void)r;
      sj.criar(g,PR("PRJ002")); sq.criar(g,I("PRJ002"),Q("QDR009",2));
      CHECK(real.criar(g,I("QDR009"),d,C("CRT009"))); CHECK(real.mover(d,I("CRT009"))); CHECK(real.mover(d,I("CRT009")));
      CHECK(real.lerTempoCiclo(d,I("CRT009"),&mi)); CHECK(mi>=0&&mi<=2); }
}
