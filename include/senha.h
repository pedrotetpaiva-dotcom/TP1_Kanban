#ifndef SENHA_H
#define SENHA_H

#include <string>

class Senha {
    private:
        std::string valor; // O atributo privado
        void validar(std::string valor); // Método auxiliar para organizar as regras

    public:
        // Métodos públicos exigidos pelo trabalho
        void setValor(std::string valor);
        std::string getValor() const;
};

#endif // SENHA_H
