#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <string>
#include <stdexcept>

class Timestamp {
    private:
        std::string valor;
        void validar(std::string valor);

    public:
        void setValor(std::string valor);
        std::string getValor() const;
};

#endif // TIMESTAMP_H
