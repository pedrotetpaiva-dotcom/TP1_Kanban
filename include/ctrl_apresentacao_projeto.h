#ifndef CTRL_APRESENTACAO_PROJETO_H
#define CTRL_APRESENTACAO_PROJETO_H

#include "iservico_projeto.h"

class CtrlApresentacaoProjeto {
    private:
        IServicoProjeto* servicoProjeto;
    public:
        void setServicoProjeto(IServicoProjeto* servico);
        void executarMenu();
};

#endif // CTRL_APRESENTACAO_PROJETO_H
