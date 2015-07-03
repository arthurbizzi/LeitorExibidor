/**
* @file pilha_operandos.h
* @author Guilherme
* @brief
*/

#include "../ClassLoader/classloader.h"

#ifndef PILHA_OPERANDOS_H
#define PILHA_OPERANDOS_H

typedef struct pilhadeoperandos
{
    u4 dado;
    struct pilhadeoperandos *prox;
} PilhaDeOperandos;

/**
*   @fn void InicializaPilhaDeOperandos(PilhaDeOperandos **pilhaOperandos)
*   @brief Funcao que inicializa a pilha de operandos de um frame.
*   @param pilhaOperandos Estrutura que contera a pilha de operandos.
*/
void InicializaPilhaDeOperandos(PilhaDeOperandos **pilhaOperandos);

/**
*   @fn void EmpilhaOperando32bits(PilhaDeOperandos **pilhaOperandos, u4 *dado)
*   @brief Funcao que empilha um operando de 32 bits na pilha de operandos.
*   @param pilhaOperandos Estrutura que contem a pilha de operandos.
*   @param dado Dado a ser empilhado.
*/
void EmpilhaOperando32bits(PilhaDeOperandos **pilhaOperandos, u4 *dado);

/**
*   @fn void EmpilhaOperando64bits(PilhaDeOperandos **pilhaOperandos, u8 *dado)
*   @brief Funcao que empilha um operando de 64 bits na pilha de operandos.
*   @param pilhaOperandos Estrutura que contem a pilha de operandos.
*   @param dado Dado a ser empilhado.
*/
void EmpilhaOperando64bits(PilhaDeOperandos **pilhaOperandos, u8 *dado);

/**
*   @fn void desalocaPilhaOperandos(PilhaDeOperandos **pilhaOperandos)
*   @brief Funcao que desaloca completamente uma pilha de operandos.
*   @param pilhaOperandos Pilha a ser destruida.
*/
void desalocaPilhaOperandos(PilhaDeOperandos **pilhaOperandos);

/**
*   @fn u1 PilhaDeOperandosVazia(PilhaDeOperandos *pilhaOperandos)
*   @brief Funcao que verifica se a pilha de operandos esta vazia.
*   @param pilhaOperandos Estrutura que contem a pilha de operandos.
*/
u1 PilhaDeOperandosVazia(PilhaDeOperandos *pilhaOperandos);

/**
*   @fn u4 DesempilhaOperando32bits(PilhaDeOperandos **pilhaOperandos)
*   @brief Funcao que desempilha um operando de 32 bits da pilha de operandos.
*   @param pilhaOperandos Estrutura que contem a pilha de operandos.
*   @return Topo (u4) da pilha de operandos.
*/
u4 DesempilhaOperando32bits(PilhaDeOperandos **pilhaOperandos);

/**
*   @fn u8 DesempilhaOperando64bits(PilhaDeOperandos **pilhaOperandos)
*   @brief Funcao que desempilha um operando de 64 bits da pilha de operandos.
*   @param pilhaOperandos Estrutura que contem a pilha de operandos.
*   @return Topo (u8) da pilha de operandos.
*/
u8 DesempilhaOperando64bits(PilhaDeOperandos **pilhaOperandos);

void ImprimePilhaOperandos(PilhaDeOperandos **pilhaOperandos, int modificador);

#endif // PILHA_OPERANDOS_H
