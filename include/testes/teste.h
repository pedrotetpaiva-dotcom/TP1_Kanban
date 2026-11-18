#ifndef TESTE_H
#define TESTE_H

#include <string>

/**
 * @file teste.h
 * @brief Mini biblioteca de verificação usada pelos programas de teste.
 */

/** @brief Imprime o título de um grupo de testes. */
void cabecalho(const std::string& titulo);

/** @brief Imprime o título de uma seção dentro de um grupo de testes. */
void secao(const std::string& titulo);

/**
 * @brief Registra o resultado de uma verificação e o imprime (OK ou FALHA).
 * @param condicao Resultado esperado como verdadeiro.
 * @param descricao Texto que descreve o que foi verificado.
 * @param arquivo Arquivo-fonte da verificação.
 * @param linha Linha da verificação.
 */
void verificar(bool condicao, const std::string& descricao, const char* arquivo, int linha);

/** @brief Total de verificações executadas até agora. */
int totalVerificacoes();

/** @brief Total de verificações que falharam até agora. */
int totalFalhas();

/** @brief Verifica uma condição, usando o texto da própria expressão como descrição. */
#define VERIFICAR(cond) verificar((cond), #cond, __FILE__, __LINE__)

/** @brief Verifica uma condição com uma descrição escrita à mão. */
#define VERIFICAR_DESC(cond, desc) verificar((cond), (desc), __FILE__, __LINE__)

void executarTestesDominios();
void executarTestesEntidades();
void executarTestesApresentacao();
void executarTestesServicos();

#endif // TESTE_H
