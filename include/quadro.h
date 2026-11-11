#ifndef QUADRO_H
#define QUADRO_H

#include "identificador.h"
#include "texto.h"
#include "limite.h"

class Quadro {
    private:
        Identificador id;
        Texto nome;
        Texto descricao;
        Limite limite;

    public:
        void setIdentificador(const Identificador& id);
        Identificador getIdentificador() const;

        void setNome(const Texto& nome);
        Texto getNome() const;

        void setDescricao(const Texto& descricao);
        Texto getDescricao() const;

        void setLimite(const Limite& limite);
        Limite getLimite() const;
};

#endif // QUADRO_H
