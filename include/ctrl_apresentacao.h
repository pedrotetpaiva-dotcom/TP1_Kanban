#ifndef CTRL_APRESENTACAO_H
#define CTRL_APRESENTACAO_H

#include "email.h"
#include "senha.h"
#include "iservico_autenticacao.h"
#include "iservico_pessoa.h" // Inclui a interface do servico de pessoa

class CtrlApresentacaoAutenticacao {
    private:
        // Ponteiros para as interfaces da Camada de Servico
        IServicoAutenticacao* servicoAutenticacao;
        IServicoPessoa* servicoPessoa;

    public:
        // Metodos para injetar as dependencias (conectar as camadas)
        void setServicoAutenticacao(IServicoAutenticacao* servico);
        void setServicoPessoa(IServicoPessoa* servico);

        // O metodo principal de acesso (agora engloba menu de login e cadastro)
        bool executarLogin();
};

#endif // CTRL_APRESENTACAO_H
