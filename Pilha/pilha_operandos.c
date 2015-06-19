/**
* @file pilha_operandos.c
* @author Guilherme
* @brief
*/
#include "pilha_operandos.h"

void InicializaPilhaDeOperandos(PilhaDeOperandos **pilhaOperandos){
    *pilhaOperandos = NULL;
    return;
}

u1 PilhaDeOperandosVazia(PilhaDeOperandos *pilhaOperandos){
    if (pilhaOperandos == NULL)
        return 1;
    else
        return 0;
}

void EmpilhaOperando32bits(PilhaDeOperandos **pilhaOperandos, u4 *dado){
    PilhaDeOperandos *po1;
    u4 dado1;
    dado1 = *dado;
    po1 = (PilhaDeOperandos *)malloc(sizeof(PilhaDeOperandos));
    po1->dado = dado1;
    po1->prox = *pilhaOperandos;
    *pilhaOperandos = po1;
    return;
}

void EmpilhaOperando64bits(PilhaDeOperandos **pilhaOperandos, u8 *dado){
    u4 op;
    u8 dado1;
    dado1 = *dado;
    op = (u4)(dado1 & 0x00000000FFFFFFFF);
    EmpilhaOperando32bits(pilhaOperandos,&op);
    op = (u4)(dado1 >> 32);
    EmpilhaOperando32bits(pilhaOperandos,&op);
    return;
}

u4 DesempilhaOperando32bits(PilhaDeOperandos **pilhaOperandos){
    PilhaDeOperandos *po1;
    u4 op;
    po1 = (PilhaDeOperandos *)malloc(sizeof(PilhaDeOperandos));
    po1 = *pilhaOperandos;
    *pilhaOperandos = po1->prox;
    op = po1->dado;
    free(po1);
    return op;
}

u8 DesempilhaOperando64bits(PilhaDeOperandos **pilhaOperandos){
    u4 op32_1, op32_2;
    u8 op64;
    op32_1 = DesempilhaOperando32bits(pilhaOperandos);
    op32_2 = DesempilhaOperando32bits(pilhaOperandos);
    op64 = (u8)(op32_1 << 32) | (u8)op32_2;
    return op64;
}

void desalocaPilhaOperandos(PilhaDeOperandos **pilhaOperandos){
    PilhaDeOperandos *po1;
    while (*pilhaOperandos != NULL){
        po1 = *pilhaOperandos;
        *pilhaOperandos = po1->prox;
        free(po1);
    }
    return;
}
