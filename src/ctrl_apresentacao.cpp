#include "ctrl_apresentacao.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Inicia o ponteiro conectando a interface
void CtrlApresentacaoAutenticacao::setServicoAutenticacao(IServicoAutenticacao* servico) {
    this->servico = servico;
}

bool CtrlApresentacaoAutenticacao::executarLogin() {
    Email emailDom;
    Senha senhaDom;
    string entradaEmail, entradaSenha;

    cout << "=======================================" << endl;
    cout << "       SISTEMA KANBAN - LOGIN          " << endl;
    cout << "=======================================" << endl;

    while (true) {
        try {
            cout << "Digite seu Email: ";
            cin >> entradaEmail;
            emailDom.setValor(entradaEmail);

            cout << "Digite sua Senha: ";
            cin >> entradaSenha;
            senhaDom.setValor(entradaSenha);

            // Verifica se o Lucas já conectou a Camada de Serviço
            if (servico != nullptr) {
                bool logado = servico->autenticar(emailDom, senhaDom);
                if (logado) {
                    cout << "\n[Sucesso] Login validado pelo banco de dados!" << endl;
                    return true;
                } else {
                    cout << "\n[Erro] Email ou senha incorretos." << endl;
                    return false;
                }
            } else {
                // Simulação temporária para a equipa continuar a testar a interface
                cout << "\n[Aviso] Servico offline. Simulando login com sucesso para testes..." << endl;
                return true;
            }

        } catch (invalid_argument &e) {
            cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
            cout << "Por favor, tente novamente.\n" << endl;
        }
    }
}
