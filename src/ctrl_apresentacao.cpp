#include "ctrl_apresentacao.h"
#include "pessoa.h"
#include "nome.h"
#include "papel.h"
#include "entrada_console.h"
#include <iostream>
#include <limits>
#include <list>
#include <stdexcept>
#include <string>

using namespace std;


CtrlApresentacaoAutenticacao::CtrlApresentacaoAutenticacao() {
    servicoAutenticacao = nullptr;
    servicoPessoa = nullptr;
}

void CtrlApresentacaoAutenticacao::setServicoAutenticacao(IServicoAutenticacao* servico) {
    this->servicoAutenticacao = servico;
}

void CtrlApresentacaoAutenticacao::setServicoPessoa(IServicoPessoa* servico) {
    this->servicoPessoa = servico;
}

Email CtrlApresentacaoAutenticacao::getUsuarioLogado() const {
    return usuarioLogado;
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
        opcao = lerOpcao();

        if (opcao == 1) {
            Email emailDom;
            Senha senhaDom;
            string entradaEmail, entradaSenha;

            try {
                cout << "\n--- LOGIN ---" << endl;
                cout << "Digite seu Email: ";
                if (!lerPalavra(&entradaEmail)) return false;
                emailDom.setValor(entradaEmail);

                cout << "Digite sua Senha: ";
                if (!lerPalavra(&entradaSenha)) return false;
                senhaDom.setValor(entradaSenha);

                if (servicoAutenticacao != nullptr && servicoAutenticacao->autenticar(emailDom, senhaDom)) {
                    usuarioLogado = emailDom;
                    cout << "\n[Sucesso] Login realizado." << endl;
                    return true;
                }
                cout << "\n[Erro] Email ou senha incorretos." << endl;
            } catch (invalid_argument &e) {
                cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
            }

        } else if (opcao == 2) {
            cadastrar();
        } else if (opcao == 0) {
            cout << "\nSaindo..." << endl;
            return false;
        } else {
            cout << "\nOpcao invalida!" << endl;
        }
    }

    return false;
}

void CtrlApresentacaoAutenticacao::cadastrar() {
    Pessoa novaPessoa;
    Nome nomeDom;
    Email emailDom;
    Senha senhaDom;
    Papel papelDom;
    string entradaNome, entradaEmail, entradaSenha, entradaPapel;

    try {
        cout << "\n--- CADASTRO ---" << endl;
        cout << "Digite seu Nome e Sobrenome: ";
        if (!lerLinha(&entradaNome)) return;
        nomeDom.setValor(entradaNome);

        cout << "Digite seu Email: ";
        if (!lerPalavra(&entradaEmail)) return;
        emailDom.setValor(entradaEmail);

        cout << "Digite sua Senha (exatamente 5 caracteres, letras e digitos): ";
        if (!lerPalavra(&entradaSenha)) return;
        senhaDom.setValor(entradaSenha);

        cout << "Digite seu Papel (GESTOR ou DESENVOLVEDOR): ";
        if (!lerPalavra(&entradaPapel)) return;
        papelDom.setValor(entradaPapel);

        novaPessoa.setNome(nomeDom);
        novaPessoa.setEmail(emailDom);
        novaPessoa.setSenha(senhaDom);
        novaPessoa.setPapel(papelDom);

        if (servicoPessoa != nullptr && servicoPessoa->criar(novaPessoa)) {
            cout << "\n[Sucesso] Conta criada! Voce ja pode fazer login." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel criar a conta. Email ja cadastrado?" << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
        cout << "Cadastro cancelado. Revise os dados e tente novamente." << endl;
    }
}

void CtrlApresentacaoAutenticacao::executarMenuPessoas() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\n=======================================" << endl;
        cout << "          MENU DE PESSOAS              " << endl;
        cout << "=======================================" << endl;
        cout << "1 - Ler dados de uma pessoa" << endl;
        cout << "2 - Atualizar pessoa" << endl;
        cout << "3 - Excluir pessoa" << endl;
        cout << "4 - Listar pessoas" << endl;
        cout << "0 - Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";
        opcao = lerOpcao();

        switch (opcao) {
            case 1: telaLer(); break;
            case 2: telaAtualizar(); break;
            case 3: telaExcluir(); break;
            case 4: telaListar(); break;
            case 0: cout << "\nVoltando..." << endl; break;
            default: cout << "\nOpcao invalida. Tente novamente." << endl;
        }
    }
}

void CtrlApresentacaoAutenticacao::telaLer() {
    string entradaEmail;
    try {
        cout << "\n--- LER PESSOA ---" << endl;
        cout << "Email da pessoa: ";
        if (!lerPalavra(&entradaEmail)) return;
        Pessoa pessoa;
        Email email;
        email.setValor(entradaEmail);
        pessoa.setEmail(email);

        if (servicoPessoa != nullptr && servicoPessoa->ler(&pessoa)) {
            cout << "\nNome : " << pessoa.getNome().getValor() << endl;
            cout << "Email: " << pessoa.getEmail().getValor() << endl;
            cout << "Papel: " << pessoa.getPapel().getValor() << endl;
        } else {
            cout << "\n[Erro] Pessoa nao encontrada." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoAutenticacao::telaAtualizar() {
    string entradaEmail, entradaNome, entradaSenha, entradaPapel;
    try {
        cout << "\n--- ATUALIZAR PESSOA ---" << endl;
        cout << "Email da pessoa (nao pode ser alterado): ";
        if (!lerPalavra(&entradaEmail)) return;
        Pessoa pessoa;
        Email email;
        email.setValor(entradaEmail);
        pessoa.setEmail(email);

        if (servicoPessoa == nullptr || !servicoPessoa->ler(&pessoa)) {
            cout << "\n[Erro] Pessoa nao encontrada." << endl;
            return;
        }

        Nome nome;
        Senha senha;
        Papel papel;
        cout << "Novo Nome e Sobrenome: ";
        if (!lerLinha(&entradaNome)) return;
        nome.setValor(entradaNome);
        cout << "Nova Senha (5 caracteres, letras e digitos): ";
        if (!lerPalavra(&entradaSenha)) return;
        senha.setValor(entradaSenha);
        cout << "Novo Papel (GESTOR ou DESENVOLVEDOR): ";
        if (!lerPalavra(&entradaPapel)) return;
        papel.setValor(entradaPapel);

        pessoa.setNome(nome);
        pessoa.setSenha(senha);
        pessoa.setPapel(papel);

        if (servicoPessoa->atualizar(pessoa)) {
            cout << "\n[Sucesso] Pessoa atualizada." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel atualizar. Um gestor com projetos nao pode virar desenvolvedor." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
        cout << "Atualizacao cancelada." << endl;
    }
}

void CtrlApresentacaoAutenticacao::telaExcluir() {
    string entradaEmail;
    try {
        cout << "\n--- EXCLUIR PESSOA ---" << endl;
        cout << "Email da pessoa: ";
        if (!lerPalavra(&entradaEmail)) return;
        Email email;
        email.setValor(entradaEmail);

        if (servicoPessoa != nullptr && servicoPessoa->excluir(email)) {
            cout << "\n[Sucesso] Pessoa excluida." << endl;
        } else {
            cout << "\n[Erro] Nao foi possivel excluir. A pessoa nao existe, e gestora de projeto ou e responsavel por cartao." << endl;
        }
    } catch (invalid_argument &e) {
        cout << "\n[ERRO DE FORMATO] " << e.what() << endl;
    }
}

void CtrlApresentacaoAutenticacao::telaListar() {
    list<Email> emails;
    cout << "\n--- PESSOAS CADASTRADAS ---" << endl;
    if (servicoPessoa == nullptr || !servicoPessoa->listar(&emails)) {
        cout << "[Erro] Nao foi possivel listar." << endl;
        return;
    }
    if (emails.empty()) {
        cout << "Nenhuma pessoa cadastrada." << endl;
    }
    for (list<Email>::iterator it = emails.begin(); it != emails.end(); it++) {
        cout << " - " << it->getValor() << endl;
    }
}
