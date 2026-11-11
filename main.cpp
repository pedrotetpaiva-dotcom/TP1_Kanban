#include <iostream>
#include "ctrl_apresentacao.h"
#include "ctrl_apresentacao_principal.h"
#include "servico_autenticacao.h"
#include "servico_pessoa.h"
#include "servico_projeto.h"
#include "servico_quadro.h"
#include "banco_dados.h"

using namespace std;

int main() {
    BancoDados::inicializarTabelas();

    CtrlApresentacaoAutenticacao ctrlLogin;
    CtrlApresentacaoPrincipal ctrlPrincipal;

    ServicoAutenticacao servicoAuth;
    ServicoPessoa servicoPessoa;
    ServicoProjeto servicoProjeto;
    ServicoQuadro servicoQuadro;

    // Conecta os servicos na tela de Login
    ctrlLogin.setServicoAutenticacao(&servicoAuth);
    ctrlLogin.setServicoPessoa(&servicoPessoa);

    // Conecta os servicos na tela Principal
    ctrlPrincipal.setServicoProjeto(&servicoProjeto);
    ctrlPrincipal.setServicoQuadro(&servicoQuadro);

    if (ctrlLogin.executarLogin()) {
        ctrlPrincipal.executarMenu();
    } else {
        cout << "Sistema encerrado por falha na autenticacao." << endl;
    }

    return 0;
}
