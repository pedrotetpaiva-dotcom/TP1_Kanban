#include "teste.h"
#include "email.h"
#include "estado.h"
#include "identificador.h"
#include "limite.h"
#include "nome.h"
#include "papel.h"
#include "prioridade.h"
#include "senha.h"
#include "tamanho.h"
#include "texto.h"
#include "timestamp.h"
#include <stdexcept>
#include <string>

using namespace std;

namespace {

string abreviar(const string& valor) {
    return valor.size() > 40 ? valor.substr(0, 37) + "..." : valor;
}

// Valor valido: setValor nao lanca excecao e getValor devolve o mesmo valor.
template <class D>
void aceita(const string& valor) {
    D dominio;
    bool lancou = false;
    try {
        dominio.setValor(valor);
    } catch (const invalid_argument&) {
        lancou = true;
    }
    verificar(!lancou && dominio.getValor() == valor, "aceita \"" + abreviar(valor) + "\"", __FILE__, __LINE__);
}

// Valor invalido: setValor lanca invalid_argument e o valor anterior (base) e mantido.
template <class D>
void rejeita(const string& valor, const string& base) {
    D dominio;
    dominio.setValor(base);
    bool lancou = false;
    try {
        dominio.setValor(valor);
    } catch (const invalid_argument&) {
        lancou = true;
    }
    verificar(lancou && dominio.getValor() == base, "rejeita \"" + abreviar(valor) + "\"", __FILE__, __LINE__);
}

void testarEmail() {
    secao("Dominio Email");
    const string base = "ana@x.com";
    aceita<Email>("a@b.com");
    aceita<Email>("ana.silva@unb.br");
    aceita<Email>("a-b.c1@sub-dom.exemplo.com");
    aceita<Email>("A1@b.com");
    aceita<Email>(string(64, 'a') + "@b.com");
    rejeita<Email>("", base);
    rejeita<Email>("semarroba.com", base);
    rejeita<Email>("@b.com", base);
    rejeita<Email>("a@", base);
    rejeita<Email>(".a@b.com", base);
    rejeita<Email>("a.@b.com", base);
    rejeita<Email>("-a@b.com", base);
    rejeita<Email>("a-@b.com", base);
    rejeita<Email>("a..b@c.com", base);
    rejeita<Email>("a.-b@c.com", base);
    rejeita<Email>("a b@c.com", base);
    rejeita<Email>("a_b@c.com", base);
    rejeita<Email>("a@b..com", base);
    rejeita<Email>("a@-b.com", base);
    rejeita<Email>("a@b-.com", base);
    rejeita<Email>("a@b.com.", base);
    rejeita<Email>(string(65, 'a') + "@b.com", base);
    rejeita<Email>("a@" + string(256, 'b'), base);
}

void testarEstado() {
    secao("Dominio Estado");
    aceita<Estado>("A FAZER");
    aceita<Estado>("FAZENDO");
    aceita<Estado>("FEITO");
    rejeita<Estado>("", "FEITO");
    rejeita<Estado>("A  FAZER", "FEITO");
    rejeita<Estado>("a fazer", "FEITO");
    rejeita<Estado>("FAZER", "FEITO");
    rejeita<Estado>("CONCLUIDO", "FEITO");
}

void testarIdentificador() {
    secao("Dominio Identificador");
    aceita<Identificador>("ABC123");
    aceita<Identificador>("abc123");
    aceita<Identificador>("aBc000");
    rejeita<Identificador>("", "ABC123");
    rejeita<Identificador>("AB1234", "ABC123");
    rejeita<Identificador>("ABCD12", "ABC123");
    rejeita<Identificador>("ABC12", "ABC123");
    rejeita<Identificador>("ABC1234", "ABC123");
    rejeita<Identificador>("123ABC", "ABC123");
    rejeita<Identificador>("A_C123", "ABC123");
    rejeita<Identificador>("ABC 12", "ABC123");
}

void testarLimite() {
    secao("Dominio Limite");
    const int validos[] = {1, 2, 13, 24, 25};
    for (int i = 0; i < 5; i++) {
        Limite l;
        bool lancou = false;
        try { l.setValor(validos[i]); } catch (const invalid_argument&) { lancou = true; }
        verificar(!lancou && l.getValor() == validos[i], "aceita " + to_string(validos[i]), __FILE__, __LINE__);
    }
    const int invalidos[] = {0, -1, 26, 100};
    for (int i = 0; i < 4; i++) {
        Limite l;
        l.setValor(5);
        bool lancou = false;
        try { l.setValor(invalidos[i]); } catch (const invalid_argument&) { lancou = true; }
        verificar(lancou && l.getValor() == 5, "rejeita " + to_string(invalidos[i]), __FILE__, __LINE__);
    }
}

void testarNome() {
    secao("Dominio Nome");
    aceita<Nome>("Ana");
    aceita<Nome>("Ana Silva");
    aceita<Nome>("a b c");
    aceita<Nome>("Abcdefghijklmno");   // 15 caracteres
    rejeita<Nome>("", "Ana");
    rejeita<Nome>("Abcdefghijklmnop", "Ana");  // 16 caracteres
    rejeita<Nome>("Ana  Silva", "Ana");        // dois espacos seguidos
    rejeita<Nome>(" Ana", "Ana");
    rejeita<Nome>("Ana ", "Ana");
    rejeita<Nome>("Ana1", "Ana");
    rejeita<Nome>("Ana.", "Ana");
    rejeita<Nome>("Jo\xc3\xa3o", "Ana");       // acento nao e letra a-z
}

void testarPapel() {
    secao("Dominio Papel");
    aceita<Papel>("GESTOR");
    aceita<Papel>("DESENVOLVEDOR");
    rejeita<Papel>("", "GESTOR");
    rejeita<Papel>("gestor", "GESTOR");
    rejeita<Papel>("ADMIN", "GESTOR");
}

void testarPrioridade() {
    secao("Dominio Prioridade");
    aceita<Prioridade>("ALTA");
    aceita<Prioridade>("MEDIA");
    aceita<Prioridade>("BAIXA");
    rejeita<Prioridade>("", "ALTA");
    rejeita<Prioridade>("MEDIO", "ALTA");
    rejeita<Prioridade>("alta", "ALTA");
    rejeita<Prioridade>("URGENTE", "ALTA");
}

void testarSenha() {
    secao("Dominio Senha");
    aceita<Senha>("abc12");
    aceita<Senha>("1a2b3");
    aceita<Senha>("A1bbb");
}

void testarSenhaRejeicoes() {
    rejeita<Senha>("", "abc12");
    rejeita<Senha>("abcde", "abc12");     // sem digito
    rejeita<Senha>("12345", "abc12");     // sem letra
    rejeita<Senha>("abc1", "abc12");      // 4 caracteres
    rejeita<Senha>("abc123", "abc12");    // 6 caracteres
    rejeita<Senha>("ab c1", "abc12");     // espaco
    rejeita<Senha>("abc1!", "abc12");     // sinal
}

void testarTamanho() {
    secao("Dominio Tamanho");
    aceita<Tamanho>("GRANDE");
    aceita<Tamanho>("MEDIO");
    aceita<Tamanho>("PEQUENO");
    rejeita<Tamanho>("", "GRANDE");
    rejeita<Tamanho>("pequeno", "GRANDE");
    rejeita<Tamanho>("ENORME", "GRANDE");
}

void testarTexto() {
    secao("Dominio Texto");
    aceita<Texto>("Ola.");
    aceita<Texto>("Fazer a tela.");
    aceita<Texto>("Ola, mundo.");
    aceita<Texto>("Sim; ok: 1 2 3.");
    aceita<Texto>("A" + string(28, 'b') + ".");           // 30 caracteres
    rejeita<Texto>("", "Ola.");
    rejeita<Texto>("A" + string(29, 'b') + ".", "Ola.");  // 31 caracteres
    rejeita<Texto>("ola.", "Ola.");                       // minuscula no inicio
    rejeita<Texto>("Ola", "Ola.");                        // sem ponto final
    rejeita<Texto>("Ola?.", "Ola.");                      // pontuacao seguida de pontuacao
    rejeita<Texto>("Ola,, mundo.", "Ola.");
    rejeita<Texto>("Ola-mundo.", "Ola.");                 // hifen nao e permitido
    rejeita<Texto>("1Ola.", "Ola.");                      // inicia com digito
    rejeita<Texto>(".", "Ola.");
}

void testarTimestamp() {
    secao("Dominio Timestamp");
    aceita<Timestamp>("01-JAN-2000-00:00");
    aceita<Timestamp>("31-DEZ-2099-23:59");
    aceita<Timestamp>("29-FEV-2028-10:30");   // ano bissexto
    aceita<Timestamp>("29-FEV-2000-12:00");   // 2000 e bissexto
    aceita<Timestamp>("30-ABR-2026-08:15");
    aceita<Timestamp>("31-MAR-2026-18:45");
    const string base = "05-NOV-2026-09:00";
    rejeita<Timestamp>("", base);
    rejeita<Timestamp>("29-FEV-2027-10:30", base);   // nao bissexto
    rejeita<Timestamp>("29-FEV-2100-10:30", base);   // fora do intervalo de anos
    rejeita<Timestamp>("31-ABR-2026-10:00", base);   // abril tem 30 dias
    rejeita<Timestamp>("32-JAN-2026-10:00", base);
    rejeita<Timestamp>("00-JAN-2026-10:00", base);
    rejeita<Timestamp>("15-XXX-2026-10:00", base);
    rejeita<Timestamp>("15-JAN-1999-10:00", base);
    rejeita<Timestamp>("15-JAN-2100-10:00", base);
    rejeita<Timestamp>("15-JAN-2026-24:00", base);
    rejeita<Timestamp>("15-JAN-2026-10:60", base);
    rejeita<Timestamp>("15/JAN/2026 10:00", base);
}

}  // namespace

void executarTestesDominios() {
    cabecalho("TESTES DOS DOMINIOS (11 classes)");
    testarEmail();
    testarEstado();
    testarIdentificador();
    testarLimite();
    testarNome();
    testarPapel();
    testarPrioridade();
    testarSenha();
    testarSenhaRejeicoes();
    testarTamanho();
    testarTexto();
    testarTimestamp();
}
