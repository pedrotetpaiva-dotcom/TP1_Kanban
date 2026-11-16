#include "ctrl_servico_autenticacao.h"

CtrlServicoAutenticacao::CtrlServicoAutenticacao(ContainerPessoa* containerPessoa) {
    this->containerPessoa = containerPessoa;
}

bool CtrlServicoAutenticacao::autenticar(const Email& email, const Senha& senha) {
    Pessoa pessoa;
    pessoa.setEmail(email);
    if (!containerPessoa->pesquisar(&pessoa)) {
        return false;
    }
    return pessoa.getSenha().getValor() == senha.getValor();
}
