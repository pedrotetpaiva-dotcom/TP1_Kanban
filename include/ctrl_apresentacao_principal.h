#ifndef CTRL_APRESENTACAO_PRINCIPAL_H
#define CTRL_APRESENTACAO_PRINCIPAL_H

#include "iservico_projeto.h"
#include "iservico_quadro.h"

class CtrlApresentacaoPrincipal {
    private:
        IServicoProjeto* servicoProjeto;
        IServicoQuadro* servicoQuadro;
    public:
        void setServicoProjeto(IServicoProjeto* servico);
        void setServicoQuadro(IServicoQuadro* servico);
        void executarMenu();
};

#endif // CTRL_APRESENTACAO_PRINCIPAL_H
