#ifndef PROJETO_H
#define PROJETO_H

#include "identificador.h"
#include "texto.h"

class Projeto {
    private:
        Identificador id;
        Texto nome;
        Texto descricao;

    public:
        void setIdentificador(const Identificador& id);
        Identificador getIdentificador() const;

        void setNome(const Texto& nome);
        Texto getNome() const;

        void setDescricao(const Texto& descricao);
        Texto getDescricao() const;
};

#endif // PROJETO_H
