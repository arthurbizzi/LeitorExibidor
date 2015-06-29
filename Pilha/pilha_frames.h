/**
* @file pilha_frames.h
* @author Guilherme
* @brief
*/


#include "../Heap/heap.h"
#include "pilha_operandos.h"

#ifndef PILHA_FRAMES_H
#define PILHA_FRAMES_H

typedef struct frame{
    method_info             *method;
    u4                      pc;
    PilhaDeOperandos        *pilhaDeOperandos;
    u4                      TamanhoVetorVariaveisLocais;
    u4                      *VetorVariaveisLocais;
    u2                      constant_pool_count;
    cp_info                 *constant_pool;
    struct listadearrays    *listaArrays;
    struct listadeobjetos   *listaObjetos;
    u4                      returAddress;
    ClassFile               *classe;
    attribute_info          *codigo;
} Frame;

typedef struct pilhadeframes
{
    Frame *dado;
    struct pilhaframes *prox;
} PilhaDeFrames;

/**
*   @fn void InicializaPilhaDeFrames(PilhaDeFrames **pilhaFrames)
*   @brief
*   @param pilhaFrames
*/
void InicializaPilhaDeFrames(PilhaDeFrames **pilhaFrames);

/**
*   @fn void EmpilhaFrame(PilhaDeFrames **pilhaFrame, Frame *frame)
*   @brief
*   @param pilhaFrame
*   @param frame
*/
void EmpilhaFrame(PilhaDeFrames **pilhaFrame, Frame *frame);

/**
*   @fn void DestruirFrame(Frame *frame)
*   @brief
*   @param frame
*/
void DestruirFrame(Frame *frame);

/**
*   @fn void desalocaPilhaFrames(PilhaDeFrames **pilhaFrames)
*   @brief
*   @param pilhaFrames
*/
void desalocaPilhaFrames(PilhaDeFrames **pilhaFrames);

/**
*   @fn Frame *ConstruirFrame(ClassFile *classe, method_info *method)
*   @brief
*   @param classe
*   @param method
*/
Frame *ConstruirFrame(ClassFile *classe, method_info *method);

/**
*   @fn Frame *DesempilhaFrame(PilhaDeFrames **pilhaFrame)
*   @brief
*   @param pilhaFrame
*/
Frame *DesempilhaFrame(PilhaDeFrames **pilhaFrame);

/**
*   @fn u1 PilhaDeFramesVazia(PilhaDeFrames *pilhaFrame)
*   @brief
*   @param pilhaFrame
*/
u1 PilhaDeFramesVazia(PilhaDeFrames *pilhaFrame);

#endif // PILHA_FRAMES_H
