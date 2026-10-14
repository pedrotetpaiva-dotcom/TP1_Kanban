#ifndef TEXTO_H
#define TEXTO_H

#include <string>
#include <stdexcept>

class Texto {
    private:
        std::string valor;
        void validar(std::string valor);

    public:
        void setValor(std::string valor);
        std::string getValor() const;
};

#endif // TEXTO_H
