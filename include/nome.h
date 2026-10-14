#ifndef NOME_H
#define NOME_H

#include <string>
#include <stdexcept>

class Nome {
    private:
        std::string valor;
        void validar(std::string valor);

    public:
        void setValor(std::string valor);
        std::string getValor() const;
};

#endif // NOME_H
