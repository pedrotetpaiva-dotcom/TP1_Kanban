#include "ctrl_apresentacao.h"
#include <iostream>
#include <stdexcept>

using namespace std;

void CtrlApresentacaoAutenticacao::executarLogin() {
    Email emailDom;
    Senha senhaDom;
    string entradaEmail, entradaSenha;
    bool formatosValidos = false;

    cout << "=======================================" << endl;
    cout << "       SISTEMA KANBAN - LOGIN          " << endl;
    cout << "=======================================" << endl;

    // Mantém o usuário preso no menu até digitar formatos aceitáveis
    while (!formatosValidos) {
        try {
            cout << "Digite seu Email: ";
            cin >> entradaEmail;
            emailDom.setValor(entradaEmail); // Se o formato for inválido, o código "pula" para o catch

            cout << "Digite sua Senha (exatamente 6 caracteres): ";
            cin >> entradaSenha;
            senhaDom.setValor(entradaSenha);

            formatosValidos = true; // Só chega nesta linha se os dois setValor não derem erro
            cout << "\n[OK] Entradas capturadas e formatos validados pela Apresentacao!" << endl;

            // TODO: No futuro, nesta linha, você enviará "emailDom" e "senhaDom"
            // para a Camada de Serviço do Lucas verificar se o usuário existe no banco de dados.

        } catch (invalid_argument &e) {
            // Limpa a tela (opcional) e exibe o erro exato que as suas classes geraram
            cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
            cout << "Por favor, tente novamente.\n" << endl;
        }
    }
}
