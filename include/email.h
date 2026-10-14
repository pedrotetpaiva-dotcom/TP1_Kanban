#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include <stdexcept>

class Email {
    private:
        std::string valor;
        void validar(std::string valor);

    public:
        void setValor(std::string valor);
        std::string getValor() const;
};

#endif // EMAIL_H
