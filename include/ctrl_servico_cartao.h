#ifndef CTRL_SERVICO_CARTAO_H
#define CTRL_SERVICO_CARTAO_H

#include "iservico_cartao.h"
#include "container_pessoa.h"
#include "container_projeto.h"
#include "container_quadro.h"
#include "container_cartao.h"
#include "timestamp.h"

/**
 * @file ctrl_servico_cartao.h
 * @brief Declaração da controladora de serviço de cartões de atividade.
 */

/**
 * @brief Controladora do módulo de serviço de cartões de atividade.
 *
 * Realiza a interface IServicoCartao e implementa os serviços 16 a 26 da
 * especificação: o CRUD de cartões, mover, tempo de ciclo, tempo de ciclo
 * médio, lead time, lead time médio e WIP.
 *
 * Regras de acesso: criar, atualizar e excluir são permitidos somente ao
 * gestor do projeto ao qual o quadro do cartão pertence. Os demais serviços
 * são permitidos a qualquer pessoa autenticada, GESTOR ou DESENVOLVEDOR. Em
 * todos os serviços o solicitante precisa ter conta.
 *
 * Regras do método Kanban:
 * - um cartão nasce na coluna A FAZER, com o instante de entrada registrado;
 * - as únicas movimentações são A FAZER para FAZENDO e FAZENDO para FEITO, e
 *   cada uma registra o instante em que ocorreu;
 * - um cartão só pode entrar em FAZENDO se o quadro não atingiu o limite de
 *   WIP, que é o número máximo de cartões simultâneos nessa coluna;
 * - tempo de ciclo é o tempo entre a entrada em FAZENDO e a chegada a FEITO;
 *   lead time é o tempo entre a entrada em A FAZER e a chegada a FEITO;
 * - WIP é o número de cartões na coluna FAZENDO.
 *
 * Todos os tempos são medidos em minutos, que é a precisão do domínio
 * Timestamp. Os instantes registrados vêm do relógio do computador.
 */
class CtrlServicoCartao : public IServicoCartao {
    private:
        ContainerPessoa* containerPessoa;   ///< Contêiner de pessoas.
        ContainerProjeto* containerProjeto; ///< Contêiner de projetos (gestores).
        ContainerQuadro* containerQuadro;   ///< Contêiner de quadros.
        ContainerCartao* containerCartao;   ///< Contêiner de cartões.

        bool existeSolicitante(const Email& solicitante) const;
        bool ehGestorDoQuadro(const Email& solicitante, const Identificador& quadro) const;
        int contarFazendo(const Identificador& quadro) const;
        bool obterAgora(Timestamp* agora) const;

    protected:
        /**
         * @brief Devolve o instante atual, usado ao criar e ao mover cartões.
         *
         * A implementação padrão lê o relógio do computador, com precisão de
         * minutos. Uma classe derivada pode redefinir este método para
         * fornecer instantes controlados, por exemplo em testes.
         * @return Instante atual como Timestamp.
         * @throws std::invalid_argument se o relógio do computador está fora
         *         do intervalo de anos aceito pelo domínio Timestamp.
         */
        virtual Timestamp agora() const;

    public:
        /**
         * @brief Cria a controladora ligada aos contêineres de que depende.
         *
         * Os contêineres devem existir durante toda a vida da controladora.
         * @param containerPessoa Contêiner de pessoas, usado para conferir o
         *        solicitante e o desenvolvedor.
         * @param containerProjeto Contêiner de projetos, usado para conferir
         *        o gestor.
         * @param containerQuadro Contêiner de quadros, usado para obter o
         *        projeto e o limite de WIP.
         * @param containerCartao Contêiner de cartões.
         */
        CtrlServicoCartao(ContainerPessoa* containerPessoa, ContainerProjeto* containerProjeto,
                          ContainerQuadro* containerQuadro, ContainerCartao* containerCartao);

        /**
         * @brief Cria um cartão em um quadro.
         *
         * O cartão é criado na coluna A FAZER, com o instante de entrada
         * registrado; início e término ficam vazios, qualquer que seja o
         * estado ou os instantes do cartão recebido.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param quadro Identificador do quadro que receberá o cartão.
         * @param desenvolvedor E-mail da pessoa responsável pelo cartão.
         * @param cartao Dados do novo cartão.
         * @return @c false se o quadro ou o desenvolvedor não existe, se o
         *         solicitante não é o gestor do projeto, se já existe cartão
         *         com o mesmo identificador ou se não foi possível obter o
         *         instante atual.
         */
        bool criar(const Email& solicitante, const Identificador& quadro, const Email& desenvolvedor,
                   const CartaoAtividade& cartao) override;

        /**
         * @brief Lê os dados de um cartão.
         * @param solicitante E-mail do usuário autenticado.
         * @param cartao Entrada: objeto com o identificador definido.
         *               Saída: objeto preenchido com os demais dados.
         * @return @c false se o solicitante não existe ou se o cartão não
         *         existe.
         */
        bool ler(const Email& solicitante, CartaoAtividade* cartao) override;

        /**
         * @brief Atualiza os dados de um cartão.
         *
         * Somente nome, descrição, prioridade e tamanho são alterados. O
         * identificador, o estado, a entrada, o início e o término não mudam;
         * o estado só muda por meio de mover.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param cartao Cartão com os novos dados.
         * @return @c false se o cartão não existe ou se o solicitante não é o
         *         gestor do projeto.
         */
        bool atualizar(const Email& solicitante, const CartaoAtividade& cartao) override;

        /**
         * @brief Exclui um cartão.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param cartao Identificador do cartão a excluir.
         * @return @c false se o cartão não existe ou se o solicitante não é o
         *         gestor do projeto.
         */
        bool excluir(const Email& solicitante, const Identificador& cartao) override;

        /**
         * @brief Lista os cartões de um quadro.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Identificador do quadro.
         * @param cartoes Saída: identificador de cada cartão do quadro.
         * @return @c false se o solicitante não existe ou se o quadro não
         *         existe; @c true caso contrário, com lista vazia se o quadro
         *         não tem cartões.
         */
        bool listar(const Email& solicitante, const Identificador& quadro,
                    std::list<Identificador>* cartoes) override;

        /**
         * @brief Move um cartão para a próxima coluna do quadro.
         *
         * De A FAZER para FAZENDO registra o início do trabalho; de FAZENDO
         * para FEITO registra o término.
         * @param solicitante E-mail do usuário autenticado.
         * @param cartao Identificador do cartão a mover.
         * @return @c false se o solicitante ou o cartão não existe, se o
         *         cartão já está em FEITO, se mover para FAZENDO ultrapassaria
         *         o limite de WIP do quadro ou se o instante atual é anterior
         *         ao último instante registrado no cartão.
         */
        bool mover(const Email& solicitante, const Identificador& cartao) override;

        /**
         * @brief Lê o tempo de ciclo (cycle time) de um cartão.
         * @param solicitante E-mail do usuário autenticado.
         * @param cartao Identificador do cartão.
         * @param minutos Saída: tempo, em minutos, entre a entrada em FAZENDO
         *        e a chegada a FEITO.
         * @return @c false se o solicitante ou o cartão não existe ou se o
         *         cartão ainda não está em FEITO.
         */
        bool lerTempoCiclo(const Email& solicitante, const Identificador& cartao, long* minutos) override;

        /**
         * @brief Lê o tempo de ciclo médio dos cartões de um quadro.
         *
         * Considera somente os cartões que já estão em FEITO.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Identificador do quadro.
         * @param minutos Saída: média dos tempos de ciclo, em minutos.
         * @return @c false se o solicitante ou o quadro não existe ou se o
         *         quadro não tem cartão em FEITO.
         */
        bool lerTempoCicloMedio(const Email& solicitante, const Identificador& quadro,
                                double* minutos) override;

        /**
         * @brief Lê o lead time de um cartão.
         * @param solicitante E-mail do usuário autenticado.
         * @param cartao Identificador do cartão.
         * @param minutos Saída: tempo, em minutos, entre a entrada em A FAZER
         *        e a chegada a FEITO.
         * @return @c false se o solicitante ou o cartão não existe ou se o
         *         cartão ainda não está em FEITO.
         */
        bool lerLeadTime(const Email& solicitante, const Identificador& cartao, long* minutos) override;

        /**
         * @brief Lê o lead time médio dos cartões de um quadro.
         *
         * Considera somente os cartões que já estão em FEITO.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Identificador do quadro.
         * @param minutos Saída: média dos lead times, em minutos.
         * @return @c false se o solicitante ou o quadro não existe ou se o
         *         quadro não tem cartão em FEITO.
         */
        bool lerLeadTimeMedio(const Email& solicitante, const Identificador& quadro,
                              double* minutos) override;

        /**
         * @brief Lê o WIP (work in progress) de um quadro.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Identificador do quadro.
         * @param wip Saída: número de cartões na coluna FAZENDO.
         * @return @c false se o solicitante ou o quadro não existe.
         */
        bool lerWIP(const Email& solicitante, const Identificador& quadro, int* wip) override;
};

#endif // CTRL_SERVICO_CARTAO_H
