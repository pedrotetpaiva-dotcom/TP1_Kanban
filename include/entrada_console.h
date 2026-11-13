#ifndef ENTRADA_CONSOLE_H
#define ENTRADA_CONSOLE_H

#include <iostream>
#include <string>
#include <limits>

/**
 * @file entrada_console.h
 * @brief Funções auxiliares de leitura do teclado usadas pela camada de apresentação.
 */

/**
 * @brief Lê a opção numérica de um menu.
 * @return A opção digitada; 0 (voltar/sair) se a entrada terminou;
 *         -1 se o texto digitado não é um número.
 */
int lerOpcao();

/**
 * @brief Lê uma palavra (texto sem espaços).
 * @param texto Saída: palavra lida.
 * @return @c false se a entrada terminou.
 */
bool lerPalavra(std::string* texto);

/**
 * @brief Lê uma linha inteira, descartando o resto da linha anterior.
 * @param texto Saída: linha lida.
 * @return @c false se a entrada terminou.
 */
bool lerLinha(std::string* texto);

/**
 * @brief Mostra um rótulo, lê uma palavra e a atribui a um domínio.
 * @tparam D Classe de domínio com o método setValor(std::string).
 * @param rotulo Texto exibido ao usuário.
 * @param dominio Saída: domínio com o valor lido.
 * @return @c false se a entrada terminou.
 * @throws std::invalid_argument se o valor digitado é inválido para o domínio.
 */
template <class D>
bool pedirPalavra(const std::string& rotulo, D* dominio) {
    std::string texto;
    std::cout << rotulo;
    if (!lerPalavra(&texto)) {
        return false;
    }
    dominio->setValor(texto);
    return true;
}

/**
 * @brief Mostra um rótulo, lê uma linha e a atribui a um domínio.
 * @tparam D Classe de domínio com o método setValor(std::string).
 * @param rotulo Texto exibido ao usuário.
 * @param dominio Saída: domínio com o valor lido.
 * @return @c false se a entrada terminou.
 * @throws std::invalid_argument se o valor digitado é inválido para o domínio.
 */
template <class D>
bool pedirLinha(const std::string& rotulo, D* dominio) {
    std::string texto;
    std::cout << rotulo;
    if (!lerLinha(&texto)) {
        return false;
    }
    dominio->setValor(texto);
    return true;
}

#endif // ENTRADA_CONSOLE_H
