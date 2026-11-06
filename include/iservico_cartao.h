#ifndef ISERVICO_CARTAO_H
#define ISERVICO_CARTAO_H

#include <list>
#include "email.h"
#include "identificador.h"

class CartaoAtividade;

/**
 * @file iservico_cartao.h
 * @brief Interface dos serviços sobre a entidade Cartão de atividade
 *        (serviços 16 a 26).
 */

/**
 * @brief Serviços sobre a entidade Cartão de atividade.
 */
class IServicoCartao {
    public:
        /**
         * @brief Cria um cartão em um quadro.
         *
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param quadro Identificador do quadro que receberá o cartão.
         * @param desenvolvedor E-mail da pessoa responsável pelo cartão.
         * @param cartao Dados do novo cartão.
         * @return @c false se o quadro ou o desenvolvedor não existe, se o
         *         solicitante não é o gestor do projeto ou se já existe
         *         cartão com o mesmo identificador.
         */
        virtual bool criar(const Email& solicitante, const Identificador& quadro,
                           const Email& desenvolvedor, const CartaoAtividade& cartao) = 0;

        /**
         * @brief Lê os dados de um cartão.
         * @param solicitante E-mail do usuário autenticado.
         * @param cartao Entrada: objeto com o identificador definido.
         *               Saída: objeto preenchido com os demais dados.
         * @return @c false se o cartão não existe.
         */
        virtual bool ler(const Email& solicitante, CartaoAtividade* cartao) = 0;

        /**
         * @brief Atualiza os dados de um cartão.
         *
         * O identificador não muda; a coluna só muda por meio de mover.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param cartao Cartão com os novos dados.
         * @return @c false se o cartão não existe ou se o solicitante não é o
         *         gestor do projeto.
         */
        virtual bool atualizar(const Email& solicitante, const CartaoAtividade& cartao) = 0;

        /**
         * @brief Exclui um cartão.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param cartao Identificador do cartão a excluir.
         * @return @c false se o cartão não existe ou se o solicitante não é o
         *         gestor do projeto.
         */
        virtual bool excluir(const Email& solicitante, const Identificador& cartao) = 0;

        /**
         * @brief Lista os cartões de um quadro.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Identificador do quadro.
         * @param cartoes Saída: identificadores dos cartões do quadro.
         * @return @c false se o quadro não existe.
         */
        virtual bool listar(const Email& solicitante, const Identificador& quadro,
                            std::list<Identificador>* cartoes) = 0;

        /**
         * @brief Move um cartão para a próxima coluna do quadro.
         *
         * As únicas movimentações são A FAZER para FAZENDO e FAZENDO para
         * FEITO. Ao entrar em FAZENDO o serviço registra o início do
         * trabalho; ao entrar em FEITO, o término.
         * @param solicitante E-mail do usuário autenticado.
         * @param cartao Identificador do cartão a mover.
         * @return @c false se o cartão não existe, se já está em FEITO ou se
         *         mover para FAZENDO ultrapassaria o limite de WIP do quadro.
         */
        virtual bool mover(const Email& solicitante, const Identificador& cartao) = 0;

        /**
         * @brief Lê o tempo de ciclo (cycle time) de um cartão.
         *
         * Tempo entre a entrada na coluna FAZENDO e a chegada a FEITO.
         * @param solicitante E-mail do usuário autenticado.
         * @param cartao Identificador do cartão.
         * @param minutos Saída: tempo de ciclo em minutos.
         * @return @c false se o cartão não existe ou ainda não está em FEITO.
         */
        virtual bool lerTempoCiclo(const Email& solicitante, const Identificador& cartao,
                                   long* minutos) = 0;

        /**
         * @brief Lê o tempo de ciclo médio dos cartões de um quadro.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Identificador do quadro.
         * @param minutos Saída: média dos tempos de ciclo, em minutos.
         * @return @c false se o quadro não existe ou não tem cartão em FEITO.
         */
        virtual bool lerTempoCicloMedio(const Email& solicitante, const Identificador& quadro,
                                        double* minutos) = 0;

        /**
         * @brief Lê o lead time de um cartão.
         *
         * Tempo entre a entrada na coluna A FAZER e a chegada a FEITO.
         * @param solicitante E-mail do usuário autenticado.
         * @param cartao Identificador do cartão.
         * @param minutos Saída: lead time em minutos.
         * @return @c false se o cartão não existe ou ainda não está em FEITO.
         */
        virtual bool lerLeadTime(const Email& solicitante, const Identificador& cartao,
                                 long* minutos) = 0;

        /**
         * @brief Lê o lead time médio dos cartões de um quadro.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Identificador do quadro.
         * @param minutos Saída: média dos lead times, em minutos.
         * @return @c false se o quadro não existe ou não tem cartão em FEITO.
         */
        virtual bool lerLeadTimeMedio(const Email& solicitante, const Identificador& quadro,
                                      double* minutos) = 0;

        /**
         * @brief Lê o WIP (work in progress) de um quadro.
         *
         * Número de cartões na coluna FAZENDO.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Identificador do quadro.
         * @param wip Saída: número de cartões em FAZENDO.
         * @return @c false se o quadro não existe.
         */
        virtual bool lerWIP(const Email& solicitante, const Identificador& quadro,
                            int* wip) = 0;

        virtual ~IServicoCartao() {}
};

#endif // ISERVICO_CARTAO_H
