//
// Created by kelvinec on 18/06/15.
//

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

void i_nop();
void i_bipush(Frame* frame,u4* n);
void i_sipush(Frame* frame,u2* n);
void i_ldc(Frame* frame,u1 index, cp_info* constantPool);
void i_ldc_w(Frame* frame,u1 index,u1 index2, cp_info* constantPool);
void i_ldc2_w(Frame* frame,u1 index,u1 index2, cp_info* constantPool);
void i_goto(Frame* frame, u1 index1, u1 index2);
void i_jsr(Frame* frame, u1 index, u1 index2);
void i_ret(Frame* frame, u1 index);
void i_invokeinterface(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 contagem, u1 zero);
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
ClassFile *i_RecuperaClasse(char *nome, ListaClasses **listadeclasses);



#endif //OTHERS_H
