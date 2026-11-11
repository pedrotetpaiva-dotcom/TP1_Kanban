#include "quadro.h"

void Quadro::setIdentificador(const Identificador& id) { this->id = id; }
Identificador Quadro::getIdentificador() const { return id; }

void Quadro::setNome(const Texto& nome) { this->nome = nome; }
Texto Quadro::getNome() const { return nome; }

void Quadro::setDescricao(const Texto& descricao) { this->descricao = descricao; }
Texto Quadro::getDescricao() const { return descricao; }

void Quadro::setLimite(const Limite& limite) { this->limite = limite; }
Limite Quadro::getLimite() const { return limite; }
