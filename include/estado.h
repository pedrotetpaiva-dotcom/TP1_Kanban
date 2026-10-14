#ifndef ESTADO_H
#define ESTADO_H

#include <string>
#include <stdexcept>

class Estado {
    private:
        std::string valor;
        void validar(std::string valor);

    public:
        void setValor(std::string valor);
        std::string getValor() const;
};

#endif // ESTADO_H
