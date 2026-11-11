#include "ctrl_apresentacao.h"
#include "pessoa.h" // Necessario para instanciar e passar os dados no cadastro
#include "nome.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Inicia os ponteiros conectando as interfaces
void CtrlApresentacaoAutenticacao::setServicoAutenticacao(IServicoAutenticacao* servico) {
    this->servicoAutenticacao = servico;
}

void CtrlApresentacaoAutenticacao::setServicoPessoa(IServicoPessoa* servico) {
    this->servicoPessoa = servico;
}

bool CtrlApresentacaoAutenticacao::executarLogin() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "       SISTEMA KANBAN - ACESSO         " << endl;
        cout << "=======================================" << endl;
        cout << "1 - Fazer Login" << endl;
        cout << "2 - Cadastrar nova conta" << endl;
        cout << "0 - Sair do Sistema" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 1) {
            Email emailDom;
            Senha senhaDom;
            string entradaEmail, entradaSenha;

            try {
                cout << "\n--- LOGIN ---" << endl;
                cout << "Digite seu Email: ";
                cin >> entradaEmail;
                emailDom.setValor(entradaEmail);

                cout << "Digite sua Senha: ";
                cin >> entradaSenha;
                senhaDom.setValor(entradaSenha);

                if (servicoAutenticacao != nullptr) {
                    bool logado = servicoAutenticacao->autenticar(emailDom, senhaDom);
                    if (logado) {
                        cout << "\n[Sucesso] Login validado pelo banco de dados!" << endl;
                        return true; // Vai para o menu principal
                    } else {
                        cout << "\n[Erro] Email ou senha incorretos." << endl;
                    }
                }
            } catch (invalid_argument &e) {
                cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
            }

        } else if (opcao == 2) {
            Pessoa novaPessoa;
            Nome nomeDom;
            Email emailDom;
            Senha senhaDom;
            string entradaNome, entradaEmail, entradaSenha;

            try {
                cout << "\n--- CADASTRO ---" << endl;
                cout << "Digite seu Nome e Sobrenome: ";
                cin.ignore(); // Limpa o buffer antes do getline
                getline(cin, entradaNome);
                nomeDom.setValor(entradaNome);

                cout << "Digite seu Email: ";
                cin >> entradaEmail;
                emailDom.setValor(entradaEmail);

                cout << "Digite sua Senha (exatamente 5 caracteres): ";
                cin >> entradaSenha;
                senhaDom.setValor(entradaSenha);

                // Monta a entidade Pessoa
                novaPessoa.setNome(nomeDom);
                novaPessoa.setEmail(emailDom);
                novaPessoa.setSenha(senhaDom);

                // Envia para o banco de dados
                if (servicoPessoa != nullptr) {
                    bool criado = servicoPessoa->criar(novaPessoa);
                    if (criado) {
                        cout << "\n[Sucesso] Conta criada no banco de dados! Voce ja pode fazer login." << endl;
                    } else {
                        cout << "\n[Erro] Nao foi possivel criar a conta. Email ja cadastrado?" << endl;
                    }
                }
            } catch (invalid_argument &e) {
                cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
                cout << "Cadastro cancelado. Revise os dados e tente novamente." << endl;
            }

        } else if (opcao == 0) {
            cout << "\nSaindo..." << endl;
            return false;
        } else {
            cout << "\nOpcao invalida!" << endl;
        }
    }

    return false;
}
