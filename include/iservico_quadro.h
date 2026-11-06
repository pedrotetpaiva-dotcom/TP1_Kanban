#ifndef ISERVICO_QUADRO_H
#define ISERVICO_QUADRO_H

#include <list>
#include "email.h"
#include "identificador.h"

class Quadro;

/**
 * @file iservico_quadro.h
 * @brief Interface dos serviços sobre a entidade Quadro (serviços 11 a 15).
 */

/**
 * @brief Serviços sobre a entidade Quadro.
 *
 * Um quadro pertence a exatamente um projeto. Criar, atualizar e excluir são
 * permitidos somente ao GESTOR do projeto. Ler e listar são permitidos a
 * GESTOR e DESENVOLVEDOR.
 */
class IServicoQuadro {
    public:
        /**
         * @brief Cria um quadro dentro de um projeto.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param projeto Identificador do projeto que receberá o quadro.
         * @param quadro Dados do novo quadro.
         * @return @c false se o projeto não existe, se o solicitante não é o
         *         gestor dele ou se já existe quadro com o mesmo identificador.
         */
        virtual bool criar(const Email& solicitante, const Identificador& projeto,
                           const Quadro& quadro) = 0;

        /**
         * @brief Lê os dados de um quadro.
         * @param solicitante E-mail do usuário autenticado.
         * @param quadro Entrada: objeto com o identificador definido.
         *               Saída: objeto preenchido com os demais dados.
         * @return @c false se o quadro não existe.
         */
        virtual bool ler(const Email& solicitante, Quadro* quadro) = 0;

        /**
         * @brief Atualiza os dados de um quadro.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param quadro Quadro com os novos dados; o identificador não muda.
         * @return @c false se o quadro não existe ou se o solicitante não é o
         *         gestor do projeto.
         */
        virtual bool atualizar(const Email& solicitante, const Quadro& quadro) = 0;

        /**
         * @brief Exclui um quadro.
         * @param solicitante E-mail do usuário autenticado (gestor do projeto).
         * @param quadro Identificador do quadro a excluir.
         * @return @c false se o quadro não existe, se o solicitante não é o
         *         gestor do projeto ou se o quadro ainda possui cartões.
         */
        virtual bool excluir(const Email& solicitante, const Identificador& quadro) = 0;

        /**
         * @brief Lista os quadros de um projeto.
         * @param solicitante E-mail do usuário autenticado.
         * @param projeto Identificador do projeto.
         * @param quadros Saída: identificadores dos quadros do projeto.
         * @return @c false se o projeto não existe.
         */
        virtual bool listar(const Email& solicitante, const Identificador& projeto,
                            std::list<Identificador>* quadros) = 0;

        virtual ~IServicoQuadro() {}
};

#endif // ISERVICO_QUADRO_H
