/**
* @file pilha_operandos.h
* @author Guilherme
* @brief
*/

#ifndef PILHA_OPERANDOS_H
#define PILHA_OPERANDOS_H

#include "../ClassLoader/classloader.h"

typedef struct pilhadeoperandos {
    u4 dado;
    struct pilhadeoperandos *prox;
} PilhaDeOperandos;

/**
*   @fn void InicializaPilhaDeOperandos(PilhaDeOperandos **pilhaOperandos)
*   @brief
*   @param pilhaOperandos
*/
void InicializaPilhaDeOperandos(PilhaDeOperandos **pilhaOperandos);

/**
*   @fn EmpilhaOperando32bits(PilhaDeOperandos **pilhaOperandos, u4 dado)
*   @brief
*   @param pilhaOperandos
*   @param dado
*/
void EmpilhaOperando32bits(PilhaDeOperandos **pilhaOperandos, u4 dado);

/**
*   @fn void EmpilhaOperando64bits(PilhaDeOperandos **pilhaOperandos, u8 dado)
*   @brief
*   @param pilhaOperandos
*   @param dado
*/
void EmpilhaOperando64bits(PilhaDeOperandos **pilhaOperandos, u8 dado);

/**
*   @fn void desalocaPilhaOperandos(PilhaDeOperandos **pilhaOperandos)
*   @brief
*   @param pilhaOperandos
*/
void desalocaPilhaOperandos(PilhaDeOperandos **pilhaOperandos);

/**
*   @fn u1 PilhaDeOperandosVazia(PilhaDeOperandos *pilhaOperandos)
*   @brief
*   @param pilhaOperandos
*/
u1 PilhaDeOperandosVazia(PilhaDeOperandos *pilhaOperandos);

/**
*   @fn u4 DesempilhaOperando32bits(PilhaDeOperandos **pilhaOperandos)
*   @brief
*   @param pilhaOperandos
*/
u4 DesempilhaOperando32bits(PilhaDeOperandos **pilhaOperandos);

/**
*   @fn u8 DesempilhaOperando64bits(PilhaDeOperandos **pilhaOperandos)
*   @brief
*   @param pilhaOperandos
*/
u8 DesempilhaOperando64bits(PilhaDeOperandos **pilhaOperandos);

#endif // PILHA_OPERANDOS_H
