#ifndef TAMANHO_H
#define TAMANHO_H

#include <string>
#include <stdexcept>

class Tamanho {
    private:
        std::string valor;
        void validar(std::string valor);

    public:
        void setValor(std::string valor);
        std::string getValor() const;
};

#endif // TAMANHO_H
