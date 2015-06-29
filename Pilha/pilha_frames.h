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
    struct pilhadeframes    *pilhaDeFrames;
    u4                      TamanhoVetorVariaveisLocais;
    u4                      *VetorVariaveisLocais;
    u2                      constant_pool_count;
    cp_info                 *constant_pool;
    u4                      returAddress;
    ClassFile               *classe;
    attribute_info          *codigo;
    struct heap             *heap;
} Frame;

typedef struct pilhadeframes
{
    Frame *dado;
    struct pilhaframes *prox;
} PilhaDeFrames;

/**
*   @fn void InicializaPilhaDeFrames(PilhaDeFrames **pilhaFrames)
*   @brief Funcao que inicializa a pilha de frames.
*   @param pilhaFrames Estrutura que contera a pilha de frames.
*/
void InicializaPilhaDeFrames(PilhaDeFrames **pilhaFrames);

/**
*   @fn void EmpilhaFrame(PilhaDeFrames **pilhaFrame, Frame *frame)
*   @brief Funcao que empilha um frame pilha de frames.
*   @param pilhaFrame Estrutura que contem a pilha de frames.
*   @param frame Dado a ser empilhado.
*/
void EmpilhaFrame(PilhaDeFrames **pilhaFrame, Frame *frame);

/**
*   @fn void DestruirFrame(Frame *frame)
*   @brief Funcao que destroi um frame.
*   @param frame Frame a ser destruido.
*/
void DestruirFrame(Frame *frame);

/**
*   @fn void desalocaPilhaFrames(PilhaDeFrames **pilhaFrames)
*   @brief Funcao que desaloca completamente uma pilha de frames.
*   @param pilhaFrames Pilha a ser destruida.
*/
void desalocaPilhaFrames(PilhaDeFrames **pilhaFrames);

/**
*   @fn Frame *ConstruirFrame(ClassFile *classe, method_info *method)
*   @brief Funcao que constroi um frame a partir de uma classe e de um metodo.
*   @param classe Estrutura que contem a classe atual.
*   @param method Estrutura que contem o metodo atual.
*   @param listaStaticField Lista de fields estaticos.
*   @param pilhaDeFrames Pilha de frames atual.
*/
Frame *ConstruirFrame(ClassFile *classe, method_info *method, PilhaDeFrames *pilhaDeFrames, Heap *listaStaticField);

/**
*   @fn Frame *DesempilhaFrame(PilhaDeFrames **pilhaFrame)
*   @brief Funcao que desempilha um frame da pilha de frames.
*   @param pilhaFrames Estrutura que contem a pilha de frames.
*   @return Topo da pilha de frames (frame corrente).
*/
Frame *DesempilhaFrame(PilhaDeFrames **pilhaFrame);

/**
*   @fn u1 PilhaDeFramesVazia(PilhaDeOperandos *pilhaFrames)
*   @brief Funcao que verifica se a pilha de frames esta vazia.
*   @param pilhaFrames Estrutura que contem a pilha de frames.
*/
u1 PilhaDeFramesVazia(PilhaDeFrames *pilhaFrame);

#endif // PILHA_FRAMES_H
