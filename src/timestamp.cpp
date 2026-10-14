#include "timestamp.h"
#include <vector>
#include <cctype>

// Função auxiliar para verificar se a string contém apenas dígitos
bool contemApenasDigitos(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void Timestamp::validar(std::string valor) {
    // 1. Separar a string pelos hifens
    std::vector<std::string> partes;
    size_t posInicio = 0, posHifen = 0;

    while ((posHifen = valor.find('-', posInicio)) != std::string::npos) {
        partes.push_back(valor.substr(posInicio, posHifen - posInicio));
        posInicio = posHifen + 1;
    }
    partes.push_back(valor.substr(posInicio));

    // A especificação exige exatamente 4 partes: DIA, MÊS, ANO e HORÁRIO
    if (partes.size() != 4) {
        throw std::invalid_argument("Erro: Formato de Timestamp invalido. Use DIA-MES-ANO-HORARIO.");
    }

    std::string diaStr = partes[0];
    std::string mesStr = partes[1];
    std::string anoStr = partes[2];
    std::string horarioStr = partes[3];

    // 2. Validação do ANO (2000 a 2099)
    if (!contemApenasDigitos(anoStr)) throw std::invalid_argument("Erro: O ano deve conter apenas numeros.");
    int ano = std::stoi(anoStr);
    if (ano < 2000 || ano > 2099) {
        throw std::invalid_argument("Erro: O ano deve estar entre 2000 e 2099.");
    }

    // 3. Validação do MÊS e determinação dos dias limite[cite: 1]
    int diasNoMes = 31;
    if (mesStr == "ABR" || mesStr == "JUN" || mesStr == "SET" || mesStr == "NOV") {
        diasNoMes = 30;
    } else if (mesStr == "FEV") {
        // Cálculo do ano bissexto[cite: 1]
        bool isBissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        diasNoMes = isBissexto ? 29 : 28;
    } else if (mesStr != "JAN" && mesStr != "MAR" && mesStr != "MAI" && mesStr != "JUL" &&
               mesStr != "AGO" && mesStr != "OUT" && mesStr != "DEZ") {
        throw std::invalid_argument("Erro: Mes invalido. Use JAN, FEV, MAR, etc.");
    }

    // 4. Validação do DIA (1 a 31, respeitando o limite do mês e ano bissexto)[cite: 1]
    if (!contemApenasDigitos(diaStr)) throw std::invalid_argument("Erro: O dia deve conter apenas numeros.");
    int dia = std::stoi(diaStr);
    if (dia < 1 || dia > diasNoMes) {
        throw std::invalid_argument("Erro: Dia invalido para o mes e ano especificados.");
    }

    // 5. Validação do HORÁRIO (00:00 a 23:59)[cite: 1]
    size_t posDoisPontos = horarioStr.find(':');
    if (posDoisPontos == std::string::npos) throw std::invalid_argument("Erro: Horario deve conter ':'.");

    std::string horaStr = horarioStr.substr(0, posDoisPontos);
    std::string minStr = horarioStr.substr(posDoisPontos + 1);

    if (!contemApenasDigitos(horaStr) || !contemApenasDigitos(minStr)) {
        throw std::invalid_argument("Erro: Horario deve conter apenas numeros.");
    }

    int hora = std::stoi(horaStr);
    int minuto = std::stoi(minStr);

    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
        throw std::invalid_argument("Erro: Horario invalido. Use 00:00 a 23:59.");
    }
}

void Timestamp::setValor(std::string valor) {
    validar(valor);
    this->valor = valor;
}

std::string Timestamp::getValor() const {
    return valor;
}
