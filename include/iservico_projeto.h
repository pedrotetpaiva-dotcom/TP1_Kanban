#ifndef ISERVICO_PROJETO_H
#define ISERVICO_PROJETO_H

#include <list>
#include "email.h"
#include "identificador.h"

class Projeto;

/**
 * @file iservico_projeto.h
 * @brief Interface dos serviços sobre a entidade Projeto (serviços 6 a 10).
 */

/**
 * @brief Serviços sobre a entidade Projeto.
 *
 * Criar, atualizar e excluir são permitidos somente ao GESTOR do projeto.
 * Ler e listar são permitidos a GESTOR e DESENVOLVEDOR.
 */
class IServicoProjeto {
    public:
        /**
         * @brief Cria um projeto; o solicitante passa a ser o gestor dele.
         * @param solicitante E-mail do usuário autenticado (papel GESTOR).
         * @param projeto Dados do novo projeto.
         * @return @c false se o solicitante não é GESTOR ou se já existe
         *         projeto com o mesmo identificador.
         */
        virtual bool criar(const Email& solicitante, const Projeto& projeto) = 0;

        /**
         * @brief Lê os dados de um projeto.
         * @param solicitante E-mail do usuário autenticado.
         * @param projeto Entrada: objeto com o identificador definido.
         *                Saída: objeto preenchido com os demais dados.
         * @return @c false se o projeto não existe.
         */
        virtual bool ler(const Email& solicitante, Projeto* projeto) = 0;

        /**
         * @brief Atualiza os dados de um projeto.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param projeto Projeto com os novos dados; o identificador não muda.
         * @return @c false se o projeto não existe ou se o solicitante não é o
         *         gestor dele.
         */
        virtual bool atualizar(const Email& solicitante, const Projeto& projeto) = 0;

        /**
         * @brief Exclui um projeto.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param projeto Identificador do projeto a excluir.
         * @return @c false se o projeto não existe, se o solicitante não é o
         *         gestor dele ou se o projeto ainda possui quadros.
         */
        virtual bool excluir(const Email& solicitante, const Identificador& projeto) = 0;

        /**
         * @brief Lista os projetos.
         * @param solicitante E-mail do usuário autenticado.
         * @param projetos Saída: identificadores dos projetos.
         * @return @c true se a listagem foi obtida.
         */
        virtual bool listar(const Email& solicitante, std::list<Identificador>* projetos) = 0;

        virtual ~IServicoProjeto() {}
};

#endif // ISERVICO_PROJETO_H
