#ifndef CTRL_APRESENTACAO_H
#define CTRL_APRESENTACAO_H

#include "email.h"
#include "senha.h"
#include "iservico_autenticacao.h" // A interface que liga a sua camada à do Lucas

class CtrlApresentacaoAutenticacao {
    private:
        // O ponteiro para a interface declarada (Exigência do PDF)
        IServicoAutenticacao* servico;

    public:
        // Método para instanciar o serviço
        void setServicoAutenticacao(IServicoAutenticacao* servico);

        // O método de login agora devolve true (sucesso) ou false (falha)
        bool executarLogin();
};

#endif // CTRL_APRESENTACAO_H
