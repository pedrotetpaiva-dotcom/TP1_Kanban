#ifndef CTRL_SERVICO_PESSOA_H
#define CTRL_SERVICO_PESSOA_H

#include "iservico_pessoa.h"
#include "container_pessoa.h"
#include "container_projeto.h"
#include "container_cartao.h"

/**
 * @file ctrl_servico_pessoa.h
 * @brief Declaração da controladora de serviço de pessoas.
 */

/**
 * @brief Controladora do módulo de serviço de pessoas.
 *
 * Realiza a interface IServicoPessoa e implementa os serviços 1 a 5 da
 * especificação. Todos os serviços são permitidos aos papéis GESTOR e
 * DESENVOLVEDOR, e por isso não recebem solicitante.
 *
 * Para manter o sistema consistente, uma pessoa não pode ser excluída
 * enquanto for gestora de projeto ou desenvolvedora de cartão, e uma pessoa
 * gestora de projeto não pode mudar de papel.
 */
class CtrlServicoPessoa : public IServicoPessoa {
    private:
        ContainerPessoa* containerPessoa;   ///< Contêiner de pessoas.
        ContainerProjeto* containerProjeto; ///< Contêiner de projetos (gestores).
        ContainerCartao* containerCartao;   ///< Contêiner de cartões (desenvolvedores).

    public:
        /**
         * @brief Cria a controladora ligada aos contêineres de que depende.
         *
         * Os contêineres devem existir durante toda a vida da controladora.
         * @param containerPessoa Contêiner de pessoas.
         * @param containerProjeto Contêiner de projetos, consultado para saber
         *        se uma pessoa é gestora.
         * @param containerCartao Contêiner de cartões, consultado para saber
         *        se uma pessoa é desenvolvedora.
         */
        CtrlServicoPessoa(ContainerPessoa* containerPessoa, ContainerProjeto* containerProjeto,
                          ContainerCartao* containerCartao);

        /**
         * @brief Cria uma pessoa (cria uma conta).
         *
         * Não exige autenticação.
         * @param pessoa Dados da nova pessoa.
         * @return @c false se já existe pessoa com o mesmo e-mail.
         */
        bool criar(const Pessoa& pessoa) override;

        /**
         * @brief Lê os dados de uma pessoa.
         * @param pessoa Entrada: objeto com o e-mail definido.
         *               Saída: objeto preenchido com os demais dados.
         * @return @c false se não existe pessoa com esse e-mail.
         */
        bool ler(Pessoa* pessoa) override;

        /**
         * @brief Atualiza os dados de uma pessoa.
         *
         * O e-mail identifica a pessoa e não é alterado. Uma pessoa que é
         * gestora de algum projeto não pode deixar de ser GESTOR.
         * @param pessoa Pessoa com os novos dados.
         * @return @c false se não existe pessoa com esse e-mail ou se a
         *         mudança de papel deixaria um projeto sem gestor GESTOR.
         */
        bool atualizar(const Pessoa& pessoa) override;

        /**
         * @brief Exclui uma pessoa.
         * @param email E-mail da pessoa a excluir.
         * @return @c false se a pessoa não existe, se é gestora de algum
         *         projeto ou se é desenvolvedora de algum cartão.
         */
        bool excluir(const Email& email) override;

        /**
         * @brief Lista as pessoas cadastradas.
         * @param emails Saída: e-mail de cada pessoa.
         * @return @c true sempre; a lista é vazia se não há pessoas.
         */
        bool listar(std::list<Email>* emails) override;
};

#endif // CTRL_SERVICO_PESSOA_H
