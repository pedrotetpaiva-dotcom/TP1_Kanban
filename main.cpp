#include <iostream>
#include "ctrl_apresentacao.h"

using namespace std;

int main() {
    // Instancia a sua controladora de apresentação
    CtrlApresentacaoAutenticacao ctrlLogin;

    // Chama a tela para o usuário interagir
    ctrlLogin.executarLogin();

    return 0;
}
