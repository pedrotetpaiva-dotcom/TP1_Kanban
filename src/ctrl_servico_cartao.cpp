#include "ctrl_servico_cartao.h"
#include <ctime>
#include <cstdio>
#include <stdexcept>

namespace {

const char* const MESES[12] = {"JAN", "FEV", "MAR", "ABR", "MAI", "JUN", "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};

// Numero de dias entre 01/01/1970 e a data informada (calendario gregoriano).
long diasDesdeEpoca(int ano, int mes, int dia) {
    ano -= (mes <= 2) ? 1 : 0;
    long era = (ano >= 0 ? ano : ano - 399) / 400;
    long anoDaEra = ano - era * 400;
    long diaDoAno = (153 * (mes + (mes > 2 ? -3 : 9)) + 2) / 5 + dia - 1;
    long diaDaEra = anoDaEra * 365 + anoDaEra / 4 - anoDaEra / 100 + diaDoAno;
    return era * 146097 + diaDaEra - 719468;
}

// Converte um Timestamp (DIA-MES-ANO-HH:MM) em minutos desde 01/01/1970.
// Devolve false se o Timestamp estiver vazio ou mal formado.
bool paraMinutos(const Timestamp& timestamp, long* minutos) {
    int dia = 0, ano = 0, hora = 0, minuto = 0;
    char sigla[4] = {0, 0, 0, 0};
    if (std::sscanf(timestamp.getValor().c_str(), "%d-%3[A-Z]-%d-%d:%d", &dia, sigla, &ano, &hora, &minuto) != 5) {
        return false;
    }
    int mes = 0;
    for (int i = 0; i < 12; i++) {
        if (std::string(sigla) == MESES[i]) {
            mes = i + 1;
        }
    }
    if (mes == 0) {
        return false;
    }
    *minutos = diasDesdeEpoca(ano, mes, dia) * 1440L + hora * 60L + minuto;
    return true;
}

// Tempo, em minutos, entre dois Timestamps. Devolve false se algum for invalido.
bool diferencaEmMinutos(const Timestamp& de, const Timestamp& ate, long* minutos) {
    long inicio = 0, fim = 0;
    if (!paraMinutos(de, &inicio) || !paraMinutos(ate, &fim)) {
        return false;
    }
    *minutos = fim - inicio;
    return true;
}

}  // namespace

CtrlServicoCartao::CtrlServicoCartao(ContainerPessoa* containerPessoa, ContainerProjeto* containerProjeto,
                                     ContainerQuadro* containerQuadro, ContainerCartao* containerCartao) {
    this->containerPessoa = containerPessoa;
    this->containerProjeto = containerProjeto;
    this->containerQuadro = containerQuadro;
    this->containerCartao = containerCartao;
}

Timestamp CtrlServicoCartao::agora() const {
    std::time_t instante = std::time(0);
    std::tm* local = std::localtime(&instante);
    char texto[32];
    std::snprintf(texto, sizeof(texto), "%02d-%s-%04d-%02d:%02d", local->tm_mday, MESES[local->tm_mon],
                  local->tm_year + 1900, local->tm_hour, local->tm_min);
    Timestamp timestamp;
    timestamp.setValor(texto);
    return timestamp;
}

bool CtrlServicoCartao::obterAgora(Timestamp* instante) const {
    try {
        *instante = agora();
    } catch (const std::invalid_argument&) {
        return false;
    }
    return true;
}

bool CtrlServicoCartao::existeSolicitante(const Email& solicitante) const {
    Pessoa pessoa;
    pessoa.setEmail(solicitante);
    return containerPessoa->pesquisar(&pessoa);
}

bool CtrlServicoCartao::ehGestorDoQuadro(const Email& solicitante, const Identificador& quadro) const {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    Identificador projeto;
    if (!containerQuadro->pesquisarProjeto(quadro, &projeto)) {
        return false;
    }
    Email gestor;
    if (!containerProjeto->pesquisarGestor(projeto, &gestor)) {
        return false;
    }
    return gestor.getValor() == solicitante.getValor();
}

int CtrlServicoCartao::contarFazendo(const Identificador& quadro) const {
    int total = 0;
    std::list<CartaoAtividade> cartoes = containerCartao->listarPorQuadro(quadro);
    for (std::list<CartaoAtividade>::iterator it = cartoes.begin(); it != cartoes.end(); it++) {
        if (it->getEstado().getValor() == "FAZENDO") {
            total++;
        }
    }
    return total;
}

bool CtrlServicoCartao::criar(const Email& solicitante, const Identificador& quadro, const Email& desenvolvedor,
                              const CartaoAtividade& cartao) {
    if (!ehGestorDoQuadro(solicitante, quadro)) {
        return false;
    }
    Pessoa pessoa;
    pessoa.setEmail(desenvolvedor);
    if (!containerPessoa->pesquisar(&pessoa)) {
        return false;
    }
    Timestamp entrada;
    if (!obterAgora(&entrada)) {
        return false;
    }
    Estado aFazer;
    aFazer.setValor("A FAZER");
    Timestamp vazio;

    CartaoAtividade novo = cartao;
    novo.setEstado(aFazer);
    novo.setEntrada(entrada);
    novo.setInicio(vazio);
    novo.setTermino(vazio);
    return containerCartao->incluir(quadro, desenvolvedor, novo);
}

bool CtrlServicoCartao::ler(const Email& solicitante, CartaoAtividade* cartao) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    return containerCartao->pesquisar(cartao);
}

bool CtrlServicoCartao::atualizar(const Email& solicitante, const CartaoAtividade& cartao) {
    CartaoAtividade atual;
    atual.setIdentificador(cartao.getIdentificador());
    if (!containerCartao->pesquisar(&atual)) {
        return false;
    }
    Identificador quadro;
    if (!containerCartao->pesquisarQuadro(cartao.getIdentificador(), &quadro)) {
        return false;
    }
    if (!ehGestorDoQuadro(solicitante, quadro)) {
        return false;
    }
    atual.setNome(cartao.getNome());
    atual.setDescricao(cartao.getDescricao());
    atual.setPrioridade(cartao.getPrioridade());
    atual.setTamanho(cartao.getTamanho());
    return containerCartao->atualizar(atual);
}

bool CtrlServicoCartao::excluir(const Email& solicitante, const Identificador& cartao) {
    Identificador quadro;
    if (!containerCartao->pesquisarQuadro(cartao, &quadro)) {
        return false;
    }
    if (!ehGestorDoQuadro(solicitante, quadro)) {
        return false;
    }
    return containerCartao->remover(cartao);
}

bool CtrlServicoCartao::listar(const Email& solicitante, const Identificador& quadro,
                               std::list<Identificador>* cartoes) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    Quadro existente;
    existente.setIdentificador(quadro);
    if (!containerQuadro->pesquisar(&existente)) {
        return false;
    }
    cartoes->clear();
    std::list<CartaoAtividade> doQuadro = containerCartao->listarPorQuadro(quadro);
    for (std::list<CartaoAtividade>::iterator it = doQuadro.begin(); it != doQuadro.end(); it++) {
        cartoes->push_back(it->getIdentificador());
    }
    return true;
}

bool CtrlServicoCartao::mover(const Email& solicitante, const Identificador& cartao) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    CartaoAtividade atual;
    atual.setIdentificador(cartao);
    if (!containerCartao->pesquisar(&atual)) {
        return false;
    }
    Identificador idQuadro;
    if (!containerCartao->pesquisarQuadro(cartao, &idQuadro)) {
        return false;
    }
    Quadro quadro;
    quadro.setIdentificador(idQuadro);
    if (!containerQuadro->pesquisar(&quadro)) {
        return false;
    }
    Timestamp instante;
    if (!obterAgora(&instante)) {
        return false;
    }

    std::string estado = atual.getEstado().getValor();
    long minutos = 0;
    Estado novoEstado;
    if (estado == "A FAZER") {
        if (contarFazendo(idQuadro) >= quadro.getLimite().getValor()) {
            return false;
        }
        if (!diferencaEmMinutos(atual.getEntrada(), instante, &minutos) || minutos < 0) {
            return false;
        }
        novoEstado.setValor("FAZENDO");
        atual.setInicio(instante);
    } else if (estado == "FAZENDO") {
        if (!diferencaEmMinutos(atual.getInicio(), instante, &minutos) || minutos < 0) {
            return false;
        }
        novoEstado.setValor("FEITO");
        atual.setTermino(instante);
    } else {
        return false;
    }
    atual.setEstado(novoEstado);
    return containerCartao->atualizar(atual);
}

bool CtrlServicoCartao::lerTempoCiclo(const Email& solicitante, const Identificador& cartao, long* minutos) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    CartaoAtividade atual;
    atual.setIdentificador(cartao);
    if (!containerCartao->pesquisar(&atual) || atual.getEstado().getValor() != "FEITO") {
        return false;
    }
    return diferencaEmMinutos(atual.getInicio(), atual.getTermino(), minutos);
}

bool CtrlServicoCartao::lerTempoCicloMedio(const Email& solicitante, const Identificador& quadro, double* minutos) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    Quadro existente;
    existente.setIdentificador(quadro);
    if (!containerQuadro->pesquisar(&existente)) {
        return false;
    }
    long soma = 0;
    int feitos = 0;
    std::list<CartaoAtividade> cartoes = containerCartao->listarPorQuadro(quadro);
    for (std::list<CartaoAtividade>::iterator it = cartoes.begin(); it != cartoes.end(); it++) {
        long tempo = 0;
        if (it->getEstado().getValor() == "FEITO" && diferencaEmMinutos(it->getInicio(), it->getTermino(), &tempo)) {
            soma += tempo;
            feitos++;
        }
    }
    if (feitos == 0) {
        return false;
    }
    *minutos = static_cast<double>(soma) / feitos;
    return true;
}

bool CtrlServicoCartao::lerLeadTime(const Email& solicitante, const Identificador& cartao, long* minutos) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    CartaoAtividade atual;
    atual.setIdentificador(cartao);
    if (!containerCartao->pesquisar(&atual) || atual.getEstado().getValor() != "FEITO") {
        return false;
    }
    return diferencaEmMinutos(atual.getEntrada(), atual.getTermino(), minutos);
}

bool CtrlServicoCartao::lerLeadTimeMedio(const Email& solicitante, const Identificador& quadro, double* minutos) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    Quadro existente;
    existente.setIdentificador(quadro);
    if (!containerQuadro->pesquisar(&existente)) {
        return false;
    }
    long soma = 0;
    int feitos = 0;
    std::list<CartaoAtividade> cartoes = containerCartao->listarPorQuadro(quadro);
    for (std::list<CartaoAtividade>::iterator it = cartoes.begin(); it != cartoes.end(); it++) {
        long tempo = 0;
        if (it->getEstado().getValor() == "FEITO" && diferencaEmMinutos(it->getEntrada(), it->getTermino(), &tempo)) {
            soma += tempo;
            feitos++;
        }
    }
    if (feitos == 0) {
        return false;
    }
    *minutos = static_cast<double>(soma) / feitos;
    return true;
}

bool CtrlServicoCartao::lerWIP(const Email& solicitante, const Identificador& quadro, int* wip) {
    if (!existeSolicitante(solicitante)) {
        return false;
    }
    Quadro existente;
    existente.setIdentificador(quadro);
    if (!containerQuadro->pesquisar(&existente)) {
        return false;
    }
    *wip = contarFazendo(quadro);
    return true;
}
