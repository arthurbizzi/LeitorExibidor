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
*   @fn void i_ireturn(PilhaDeFrames *pilhadeframes)
*   @brief Retorna um inteiro a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_ireturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_lreturn(PilhaDeFrames *pilhadeframes)
*   @brief Retorna um long a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_lreturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_freturn(PilhaDeFrames *pilhadeframes)
*   @brief Retorna um float a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_freturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_dreturn(PilhaDeFrames *pilhadeframes)
*   @brief Retorna um double a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_dreturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_areturn(PilhaDeFrames *pilhadeframes)
*   @brief Retorna uma referência a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_areturn(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_return(PilhaDeFrames *pilhadeframes)
*   @brief Retorna void a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_return(PilhaDeFrames *pilhadeframes);

/**
*   @fn void i_getstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
*   @brief identifica um field e coloca na pilha de operandos
*	@param frame
*   @param listadefields
*   @param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_getstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2);

/**
*   @fn void i_putstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
*   @brief pega um field da pilha de operandos e coloca na lista de fields
*	@param frame
*   @param listadefields
*   @param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_putstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2);

/**
*   @fn void i_getfield(Frame *frame, u1 indexbyte1, u1 indexbyte2)
*   @brief identifica um field de um objeto e coloca na pilha de operandos
*	@param frame
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_getfield(Frame *frame, u1 indexbyte1, u1 indexbyte2);

/**
*   @fn void i_getfield(Frame *frame, u1 indexbyte1, u1 indexbyte2)
*   @brief pega um valor e um objeto da pilha e coloca o valor no field correto do objeto
*	@param frame
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_putfield(Frame *frame, u1 indexbyte1, u1 indexbyte2);

/**
*   @fn void i_invokevirtual(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
*   @brief invoca um metodo ,que esta em um objeto na pilha de operandos junto com seus argumentos, e coloca o resultado na pilha de operandos o nome do metodo eh identificado por (indexbyte1<<8 + indexbyte2) no constant_pool do frame corrente
*	@param frame
*	@param pilhadeframes
*	@param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_invokevirtual(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, Heap *heap);

/**
*   @fn void i_invokespecial(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
*   @brief invoca um metodo ,que esta em um objeto na pilha de operandos junto com seus argumentos, e coloca o resultado na pilha de operandos o nome do metodo eh identificado por (indexbyte1<<8 + indexbyte2) no constant_pool do frame corrente
*	@param frame
*	@param pilhadeframes
*	@param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_invokespecial(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, Heap *heap);

/**
*   @fn void i_invokestatic(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
*   @brief invoca um metodo ,que tem seus argumentos na pilha de operandos, e coloca o resultado na pilha de operandos o nome do metodo eh identificado por (indexbyte1<<8 + indexbyte2) no constant_pool do frame corrente
*	@param frame
*	@param pilhadeframes
*	@param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_invokestatic(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, Heap *heap);

/**
*   @fn void i_invokeinterface(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, u1 contagem, u1 zero)
*   @brief invoca um metodo ,que esta em um objeto na pilha de operandos junto com seus argumentos, e coloca o resultado na pilha de operandos o nome do metodo eh identificado por (indexbyte1<<8 + indexbyte2) no constant_pool do frame corrente
*	@param frame
*	@param pilhadeframes
*	@param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @param contagem
*   @param zero
*   @return
*/
void i_invokeinterface(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, u1 contagem, u1 zero, Heap *heap);

/**
*   @fn void i_new(Frame *frame, u1 indexbyte1, u1 indexbyte2, ListaClasses *listadeclasses)
*   @brief cria um objeto do tipo da classe identificado por (indexbyte1<<8 + indexbyte2) indice do constant_pool do frame corrente, ecoloca o resultado na pilha.
*	@param frame
*   @param indexbyte1
*   @param indexbyte2
*	@param listadeclasses
*   @return
*/
void i_new(Frame *frame, u1 indexbyte1, u1 indexbyte2, ListaClasses *listadeclasses);

/**
*   @fn void i_newarray(Frame *frame, u1 atype)
*   @brief cria um novo array do tipo identificado por atype e tamanho pego da pilha e coloca o resultado na pilha
*	@param frame
*   @param atype
*   @return
*/
void i_newarray(Frame *frame, u1 atype);

/**
*   @fn void i_anewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2)
*   @brief cria um novo array do tipo identificado por (indexbyte1<<8 + indexbyte2) indice do constant_pool do frame corrente, e tamanho pego da pilha e coloca o resultado na pilha
*	@param frame
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_anewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2);

/**
*   @fn void i_arraylength(Frame *frame)
*   @brief pega a referencia de um array da pilha e empilha o seu tamanho
*	@param frame
*   @return
*/
void i_arraylength(Frame *frame);

/**
*   @fn void i_atrhow(Frame *frame)
*   @brief lança um erro ou exceção (aviso de que o restante da pilha é cancelado, deixando apenas uma referência para o Throwable)
*	@param frame
*   @return
*/
void i_atrhow(Frame *frame);

/**
*   @fn void i_checkcast(Frame *frame, u1 indexbyte1, u1 indexbyte2)
*   @brief verifica o tipo de um objeto, nome da classe identificado por (indexbyte1<<8 + indexbyte2) indice do constant pool corrente
*	@param frame
*	@param indexbyte1
*	@param indexbyte2
*   @return
*/
void i_checkcast(Frame *frame, u1 indexbyte1, u1 indexbyte2);

/**
*   @fn void i_instanceof(Frame *frame, u1 indexbyte1, u1 indexbyte2)
*   @brief identifica o tipo do objeto e poe na pilha o resultado
*	@param frame
*	@param indexbyte1
*	@param indexbyte2
*   @return
*/
void i_instanceof(Frame *frame, u1 indexbyte1, u1 indexbyte2);
void i_monitorenter(Frame *frame);
void i_monitorexit(Frame *frame);

/**
*   @fn void i_wide(Frame *frame, u1 opcode, u1 index, u1 index2, u1 constbyte1, u1 constbyte2)
*   @brief a função pega uma função identificada por opcode e extende ela pra receber 16_bits com (constbyte1<<8 + constbyte2)
*	@param frame
*	@param opcode
*	@param index
*	@param index2
*	@param constbyte1
*	@param constbyte2
*   @return
*/
void i_wide(Frame *frame, u1 opcode, u1 index, u1 index2, u1 constbyte1, u1 constbyte2);

/**
*   @fn void i_multianewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 dimensions)
*   @brief cria um array multidimensional de dimensão "dimensions" do tipo identificado por (indexbyte1<<8 + indexbyte2) indice do constant pool
*	@param frame
*	@param indexbyte1
*	@param indexbyte2
*	@param dimensions
*   @return
*/
void i_multianewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 dimensions);

/**
*   @fn void i_ifnull(Frame *frame, u1 branchbyte1, u1 branchbyte2)
*   @brief se valor pego na pilha for NULL pula para indice (branchbyte1<<8 + branchbyte2)
*	@param frame
*	@param branchbyte1
*	@param branchbyte2
*   @return
*/
void i_ifnull(Frame *frame, u1 branchbyte1, u1 branchbyte2);

/**
*   @fn void i_ifnannull(Frame *frame, u1 branchbyte1, u1 branchbyte2)
*   @brief se valor pego na pilha não for NULL pula para indice (branchbyte1<<8 + branchbyte2)
*	@param frame
*	@param branchbyte1
*	@param branchbyte2
*   @return
*/
void i_ifnonnull(Frame *frame, u1 branchbyte1, u1 branchbyte2);

/**
*   @fn void i_goto_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4)
*   @brief pula para indice (branchbyte1<<24 + branchbyte2<<16 + branchbyte3<<8 + branchbyte4)
*	@param frame
*	@param branchbyte1
*	@param branchbyte2
*	@param branchbyte3
*	@param branchbyte4
*   @return
*/
void i_goto_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4);

/**
*   @fn void i_jsr_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4)
*   @brief pula para indice (branchbyte1<<24 + branchbyte2<<16 + branchbyte3<<8 + branchbyte4) e coloca na pilha o endereço da proxima instrução apos jsr_w
*	@param frame
*	@param branchbyte1
*	@param branchbyte2
*	@param branchbyte3
*	@param branchbyte4
*   @return
*/
void i_jsr_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4);

/**
*   @fn char* i_dereferencia_instrucoes(u2 index, cp_info *cp)
*   @brief retorna o nome que esta em um tipo utf8 de cp que esta em index
*	@param index
*	@param cp
*   @return
*/
char* i_dereferencia_instrucoes(u2 index, cp_info *cp);

/**
*   @fn staticField *i_RecuperaField(char *nome, ListaStaticField **listadefields)
*   @brief retorna um staticField identificado por nome da listadefields
*	@param nome
*	@param listadefields
*   @return
*/
staticField *i_RecuperaField(char *nome, ListaStaticField **listadefields);


#endif //OTHERS_H
