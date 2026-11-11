#include "projeto.h"

void Projeto::setIdentificador(const Identificador& id) { this->id = id; }
Identificador Projeto::getIdentificador() const { return id; }

void Projeto::setNome(const Texto& nome) { this->nome = nome; }
Texto Projeto::getNome() const { return nome; }

void Projeto::setDescricao(const Texto& descricao) { this->descricao = descricao; }
Texto Projeto::getDescricao() const { return descricao; }
