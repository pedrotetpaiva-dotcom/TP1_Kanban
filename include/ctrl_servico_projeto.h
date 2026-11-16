#ifndef CTRL_SERVICO_PROJETO_H
#define CTRL_SERVICO_PROJETO_H

#include "iservico_projeto.h"
#include "container_pessoa.h"
#include "container_projeto.h"
#include "container_quadro.h"

/**
 * @file ctrl_servico_projeto.h
 * @brief Declaração da controladora de serviço de projetos.
 */

/**
 * @brief Controladora do módulo de serviço de projetos.
 *
 * Realiza a interface IServicoProjeto e implementa os serviços 6 a 10 da
 * especificação.
 *
 * Regras de acesso: criar, atualizar e excluir são permitidos somente ao
 * gestor do projeto, que é a pessoa que o criou e que tem o papel GESTOR.
 * Ler e listar são permitidos a qualquer pessoa autenticada, GESTOR ou
 * DESENVOLVEDOR. Em todos os serviços o solicitante precisa ter conta.
 *
 * Um projeto que ainda possui quadros não pode ser excluído, pois o quadro
 * precisa pertencer a um projeto.
 */
class CtrlServicoProjeto : public IServicoProjeto {
    private:
        ContainerPessoa* containerPessoa;   ///< Contêiner de pessoas.
        ContainerProjeto* containerProjeto; ///< Contêiner de projetos.
        ContainerQuadro* containerQuadro;   ///< Contêiner de quadros.

        bool existeSolicitante(const Email& solicitante) const;
        bool ehGestorDoProjeto(const Email& solicitante, const Identificador& projeto) const;

    public:
        /**
         * @brief Cria a controladora ligada aos contêineres de que depende.
         *
         * Os contêineres devem existir durante toda a vida da controladora.
         * @param containerPessoa Contêiner de pessoas, usado para conferir o
         *        solicitante e o seu papel.
         * @param containerProjeto Contêiner de projetos.
         * @param containerQuadro Contêiner de quadros, consultado antes de
         *        excluir um projeto.
         */
        CtrlServicoProjeto(ContainerPessoa* containerPessoa, ContainerProjeto* containerProjeto,
                           ContainerQuadro* containerQuadro);

        /**
         * @brief Cria um projeto; o solicitante passa a ser o gestor dele.
         * @param solicitante E-mail do usuário autenticado (papel GESTOR).
         * @param projeto Dados do novo projeto.
         * @return @c false se o solicitante não existe, se não é GESTOR ou se
         *         já existe projeto com o mesmo identificador.
         */
        bool criar(const Email& solicitante, const Projeto& projeto) override;

        /**
         * @brief Lê os dados de um projeto.
         * @param solicitante E-mail do usuário autenticado.
         * @param projeto Entrada: objeto com o identificador definido.
         *                Saída: objeto preenchido com os demais dados.
         * @return @c false se o solicitante não existe ou se o projeto não
         *         existe.
         */
        bool ler(const Email& solicitante, Projeto* projeto) override;

        /**
         * @brief Atualiza os dados de um projeto.
         *
         * O identificador e o gestor do projeto não mudam.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param projeto Projeto com os novos dados.
         * @return @c false se o projeto não existe ou se o solicitante não é o
         *         gestor dele.
         */
        bool atualizar(const Email& solicitante, const Projeto& projeto) override;

        /**
         * @brief Exclui um projeto.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param projeto Identificador do projeto a excluir.
         * @return @c false se o projeto não existe, se o solicitante não é o
         *         gestor dele ou se o projeto ainda possui quadros.
         */
        bool excluir(const Email& solicitante, const Identificador& projeto) override;

        /**
         * @brief Lista os projetos.
         * @param solicitante E-mail do usuário autenticado.
         * @param projetos Saída: identificador de cada projeto.
         * @return @c false se o solicitante não existe; @c true caso contrário,
         *         com lista vazia se não há projetos.
         */
        bool listar(const Email& solicitante, std::list<Identificador>* projetos) override;
};

#endif // CTRL_SERVICO_PROJETO_H
