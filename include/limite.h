#ifndef LIMITE_H
#define LIMITE_H

#include <stdexcept>

class Limite {
    private:
        int valor;
        void validar(int valor);

    public:
        void setValor(int valor);
        int getValor() const;
};

#endif // LIMITE_H
