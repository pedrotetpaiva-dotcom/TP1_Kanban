#include "servico_quadro.h"

using namespace std;

bool ServicoQuadro::criar(const Email& solicitante, const Identificador& projeto, const Quadro& quadro) {
    return true;
}

bool ServicoQuadro::ler(const Email& solicitante, Quadro* quadro) {
    return true;
}

bool ServicoQuadro::atualizar(const Email& solicitante, const Quadro& quadro) {
    return true;
}

bool ServicoQuadro::excluir(const Email& solicitante, const Identificador& quadro) {
    return true;
}

bool ServicoQuadro::listar(const Email& solicitante, const Identificador& projeto, std::list<Identificador>* quadros) {
    return true;
}
