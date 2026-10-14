#ifndef IDENTIFICADOR_H
#define IDENTIFICADOR_H

#include <string>
#include <stdexcept>

class Identificador {
    private:
        std::string valor;
        void validar(std::string valor);

    public:
        void setValor(std::string valor);
        std::string getValor() const;
};

#endif // IDENTIFICADOR_H
