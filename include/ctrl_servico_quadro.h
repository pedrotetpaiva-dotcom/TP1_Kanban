#ifndef CTRL_SERVICO_QUADRO_H
#define CTRL_SERVICO_QUADRO_H

#include "iservico_quadro.h"
#include "container_pessoa.h"
#include "container_projeto.h"
#include "container_quadro.h"
#include "container_cartao.h"

/**
 * @file ctrl_servico_quadro.h
 * @brief Declaração da controladora de serviço de quadros.
 */

/**
 * @brief Controladora do módulo de serviço de quadros.
 *
 * Realiza a interface IServicoQuadro e implementa os serviços 11 a 15 da
 * especificação.
 *
 * Regras de acesso: criar, atualizar e excluir são permitidos somente ao
 * gestor do projeto ao qual o quadro pertence. Ler e listar são permitidos a
 * qualquer pessoa autenticada, GESTOR ou DESENVOLVEDOR. Em todos os serviços
 * o solicitante precisa ter conta.
 *
 * Regras de consistência: um quadro pertence a exatamente um projeto, não
 * pode ser excluído enquanto possuir cartões e não pode ter o limite de WIP
 * reduzido abaixo do número de cartões que já estão na coluna FAZENDO.
 */
class CtrlServicoQuadro : public IServicoQuadro {
    private:
        ContainerPessoa* containerPessoa;   ///< Contêiner de pessoas.
        ContainerProjeto* containerProjeto; ///< Contêiner de projetos (gestores).
        ContainerQuadro* containerQuadro;   ///< Contêiner de quadros.
        ContainerCartao* containerCartao;   ///< Contêiner de cartões.

        bool existeSolicitante(const Email& solicitante) const;
        bool ehGestorDoProjeto(const Email& solicitante, const Identificador& projeto) const;
        int contarFazendo(const Identificador& quadro) const;

    public:
        /**
         * @brief Cria a controladora ligada aos contêineres de que depende.
         *
         * Os contêineres devem existir durante toda a vida da controladora.
         * @param containerPessoa Contêiner de pessoas, usado para conferir o
         *        solicitante.
         * @param containerProjeto Contêiner de projetos, usado para conferir
         *        o projeto e o seu gestor.
         * @param containerQuadro Contêiner de quadros.
         * @param containerCartao Contêiner de cartões, consultado para
         *        contar o WIP e antes de excluir um quadro.
         */
        CtrlServicoQuadro(ContainerPessoa* containerPessoa, ContainerProjeto* containerProjeto,
                          ContainerQuadro* containerQuadro, ContainerCartao* containerCartao);

        /**
         * @brief Cria um quadro dentro de um projeto.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param projeto Identificador do projeto que receberá o quadro.
         * @param quadro Dados do novo quadro.
         * @return @c false se o projeto não existe, se o solicitante não é o
         *         gestor dele ou se já existe quadro com o mesmo identificador.
         */
        bool criar(const Email& solicitante, const Identificador& projeto, const Quadro& quadro) override;

        /**
         * @brief Lê os dados de um quadro.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Entrada: objeto com o identificador definido.
         *               Saída: objeto preenchido com os demais dados.
         * @return @c false se o solicitante não existe ou se o quadro não
         *         existe.
         */
        bool ler(const Email& solicitante, Quadro* quadro) override;

        /**
         * @brief Atualiza os dados de um quadro.
         *
         * O identificador e o projeto do quadro não mudam. O novo limite de
         * WIP não pode ser menor que o número de cartões na coluna FAZENDO.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param quadro Quadro com os novos dados.
         * @return @c false se o quadro não existe, se o solicitante não é o
         *         gestor do projeto ou se o novo limite é menor que o WIP atual.
         */
        bool atualizar(const Email& solicitante, const Quadro& quadro) override;

        /**
         * @brief Exclui um quadro.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param quadro Identificador do quadro a excluir.
         * @return @c false se o quadro não existe, se o solicitante não é o
         *         gestor do projeto ou se o quadro ainda possui cartões.
         */
        bool excluir(const Email& solicitante, const Identificador& quadro) override;

        /**
         * @brief Lista os quadros de um projeto.
         * @param solicitante E-mail do usuário autenticado.
         * @param projeto Identificador do projeto.
         * @param quadros Saída: identificador de cada quadro do projeto.
         * @return @c false se o solicitante não existe ou se o projeto não
         *         existe; @c true caso contrário, com lista vazia se o projeto
         *         não tem quadros.
         */
        bool listar(const Email& solicitante, const Identificador& projeto,
                    std::list<Identificador>* quadros) override;
};

#endif // CTRL_SERVICO_QUADRO_H
