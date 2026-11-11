#include "servico_cartao.h"

using namespace std;

bool ServicoCartao::criar(const Email& solicitante, const Identificador& quadro, const Email& desenvolvedor, const CartaoAtividade& cartao) {
    return true;
}

bool ServicoCartao::ler(const Email& solicitante, CartaoAtividade* cartao) {
    return true;
}

bool ServicoCartao::atualizar(const Email& solicitante, const CartaoAtividade& cartao) {
    return true;
}

bool ServicoCartao::excluir(const Email& solicitante, const Identificador& cartao) {
    return true;
}

bool ServicoCartao::listar(const Email& solicitante, const Identificador& quadro, std::list<Identificador>* cartoes) {
    return true;
}

bool ServicoCartao::mover(const Email& solicitante, const Identificador& cartao) {
    return true;
}

bool ServicoCartao::lerTempoCiclo(const Email& solicitante, const Identificador& cartao, long* minutos) {
    return true;
}

bool ServicoCartao::lerTempoCicloMedio(const Email& solicitante, const Identificador& quadro, double* minutos) {
    return true;
}

bool ServicoCartao::lerLeadTime(const Email& solicitante, const Identificador& cartao, long* minutos) {
    return true;
}

bool ServicoCartao::lerLeadTimeMedio(const Email& solicitante, const Identificador& quadro, double* minutos) {
    return true;
}

bool ServicoCartao::lerWIP(const Email& solicitante, const Identificador& quadro, int* wip) {
    return true;
}
