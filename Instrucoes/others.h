//
// Created by kelvinec on 18/06/15.
//

/**
* @file others.h
* @author Kelvin, Guilherme, Bruno.
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções que não se classificaram em nenhum dos outros arquivos.s
*/

#include <math.h>
#include "../Pilha/pilha_frames.h"

#ifndef OTHERS_H
#define OTHERS_H

#define TipoReferencia  0
#define TipoBoolean     4
#define TipoChar        5
#define TipoFloat       6
#define TipoDouble      7
#define TipoByte        8
#define TipoShort       9
#define TipoInt         10
#define TipoLong        11

/**
*   @fn void i_nop()
*   @brief Não faz operação alguma.
*   @return
*/
void i_nop();

/**
*   @fn void i_bipush(Frame* frame, u4* n)
*   @brief Empilha um byte, como inteiro.
*	@param n Byte a ser empilhado.
*   @return
*/
void i_bipush(Frame* frame,u4* n);

/**
*   @fn void i_sipush(Frame* frame, u2* n)
*   @brief Empilha um short.
*	@param n Short a ser empilhado.
*   @return
*/
void i_sipush(Frame* frame,u2* n);

/**
*   @fn void i_ldc(Frame* frame, u1 index)
*   @brief Empilha uma única palavra constante.
*	@param index Empilha um indice a partir do Constant Pool(String, int or float).
*   @return
*/
void i_ldc(Frame* frame,u1 index, cp_info* constantPool);

/**
*   @fn void i_ldc(Frame* frame, u1 index)
*   @brief Empilha uma única palavra constante, porém tem o indice formado por 16bits.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_ldc_w(Frame* frame,u1 index,u1 index2, cp_info* constantPool);

/**
*   @fn void i_ldc2_w(Frame* frame, u1 index, u1 index2)
*   @brief Empilha uma palavra dupla constante, tendo o indice formado por 16bits.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_ldc2_w(Frame* frame,u1 index,u1 index2, cp_info* constantPool);

/**
*   @fn void i_goto(Frame* frame, u1 index1, u1 index2)
*   @brief Pula para outra instrução, tendo seu offset construído pelos 16bits de index.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_goto(Frame* frame, u1 index1, u1 index2);


/**
*   @fn void i_goto(Frame* frame, u1 index1, u1 index2)
*   @brief Pula para a subrotina indicada pelo branchoffset construdos pelo index. E empilha o endereço de retorno na pilha.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_jsr(Frame* frame, u1 index, u1 index2);

/**
*   @fn void i_ret(Frame* frame, u1 index1)
*   @brief Continua a execução a partir do endereço pego na variável local indicada pelo index.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_ret(Frame* frame, u1 index);

/**
*   @fn void i_ireturn(Frame* frame, u1 index1)
*   @brief Retorna um inteiro a partir de um método.
*	@param pilhadeframes  WHAT ?
*   @return
*/
void i_ireturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_lreturn(Frame* frame, u1 index1)
*   @brief Retorna um long a partir de um método.
*	@param pilhadeframes  WHAT ?
*   @return
*/
void i_lreturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_freturn(Frame* frame, u1 index1)
*   @brief Retorna um float a partir de um método.
*	@param pilhadeframes  WHAT ?
*   @return
*/
void i_freturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_return(Frame* frame, u1 index1)
*   @brief Retorna um double a partir de um método.
*	@param pilhadeframes  WHAT ?
*   @return
*/
void i_dreturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_return(Frame* frame, u1 index1)
*   @brief Retorna uma referência a partir de um método.
*	@param pilhadeframes  WHAT ?
*   @return
*/
void i_areturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_return(Frame* frame, u1 index1)
*   @brief Retorna void a partir de um método.
*	@param pilhadeframes  WHAT ?
*   @return
*/
void i_return(PilhaDeFrames *pilhadeframes);
void i_getstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2);
void i_putstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2);
void i_getfield(Frame *frame, u1 indexbyte1, u1 indexbyte2);
void i_putfield(Frame *frame, u1 indexbyte1, u1 indexbyte2);
void i_invokevirtual(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2);
void i_invokespecial(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2);
void i_invokestatic(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2);
void i_invokeinterface(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, u1 contagem, u1 zero);
void i_new(Frame *frame, u1 indexbyte1, u1 indexbyte2, ListaClasses *listadeclasses);
void i_newarray(Frame *frame, u1 atype);
void i_anewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2);
void i_arraylength(Frame *frame);
void i_atrhow(Frame *frame);
void i_checkcast(Frame *frame, u1 indexbyte1, u1 indexbyte2);
void i_instanceof(Frame *frame, u1 indexbyte1, u1 indexbyte2);
void i_monitorenter(Frame *frame);
void i_monitorexit(Frame *frame);
void i_wide(Frame *frame, u1 opcode, u1 index, u1 index2, u1 constbyte1, u1 constbyte2);
void i_multianewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 dimensions);
void i_ifnull(Frame *frame, u1 branchbyte1, u1 branchbyte2);
void i_ifnonnull(Frame *frame, u1 branchbyte1, u1 branchbyte2);
void i_goto_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4);
void i_jsr_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4);
char* i_dereferencia_instrucoes(u2 index, cp_info *cp);
staticField *i_RecuperaField(char *nome, ListaStaticField **listadefields);


#endif //OTHERS_H
