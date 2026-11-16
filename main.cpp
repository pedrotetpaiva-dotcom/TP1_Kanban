#include <iostream>
#include "ctrl_apresentacao.h"
#include "ctrl_apresentacao_principal.h"
#include "container_pessoa.h"
#include "container_projeto.h"
#include "container_quadro.h"
#include "container_cartao.h"
#include "ctrl_servico_autenticacao.h"
#include "ctrl_servico_pessoa.h"
#include "ctrl_servico_projeto.h"
#include "ctrl_servico_quadro.h"
#include "ctrl_servico_cartao.h"

using namespace std;

/**
 * @file main.cpp
 * @brief Ponto de entrada do sistema Kanban.
 */

/**
 * @brief Cria os contêineres e as controladoras de serviço, liga a camada de
 *        apresentação a elas e executa o sistema.
 * @return 0 ao encerrar.
 */
int main() {
    // Camada de servico: contêineres (dados em memoria) e controladoras
    ContainerPessoa containerPessoa;
    ContainerProjeto containerProjeto;
    ContainerQuadro containerQuadro;
    ContainerCartao containerCartao;

    CtrlServicoAutenticacao servicoAuth(&containerPessoa);
    CtrlServicoPessoa servicoPessoa(&containerPessoa, &containerProjeto, &containerCartao);
    CtrlServicoProjeto servicoProjeto(&containerPessoa, &containerProjeto, &containerQuadro);
    CtrlServicoQuadro servicoQuadro(&containerPessoa, &containerProjeto, &containerQuadro, &containerCartao);
    CtrlServicoCartao servicoCartao(&containerPessoa, &containerProjeto, &containerQuadro, &containerCartao);

    // Camada de apresentacao
    CtrlApresentacaoAutenticacao ctrlLogin;
    CtrlApresentacaoPrincipal ctrlPrincipal;

    ctrlLogin.setServicoAutenticacao(&servicoAuth);
    ctrlLogin.setServicoPessoa(&servicoPessoa);
    ctrlPrincipal.setServicoProjeto(&servicoProjeto);
    ctrlPrincipal.setServicoQuadro(&servicoQuadro);
    ctrlPrincipal.setServicoCartao(&servicoCartao);

    ctrlPrincipal.setCtrlAutenticacao(&ctrlLogin);

    // Cada login abre o menu principal; sair da conta volta a tela de acesso.
    // Os dados em memoria permanecem ate o programa ser encerrado.
    while (ctrlLogin.executarLogin()) {
        ctrlPrincipal.executarMenu();
    }
    cout << "\nSistema encerrado." << endl;

    return 0;
}
