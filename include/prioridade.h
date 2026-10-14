#ifndef PRIORIDADE_H
#define PRIORIDADE_H

#include <string>
#include <stdexcept>

class Prioridade {
    private:
        std::string valor;
        void validar(std::string valor);

    public:
        void setValor(std::string valor);
        std::string getValor() const;
};

#endif // PRIORIDADE_H
