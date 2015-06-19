//
// Created by kelvinec on 18/06/15.
//

#include "exec_instrucoes.h"
#include "../Pilha/pilha_operandos.h"
#include "../ClassLoader/classloader.h"

void nop(){
    return;
};

void aconst_null(PilhaDeOperandos* pilhaDeOperandos){
    EmpilhaOperando32bits(&pilhaDeOperandos,0);
    return;
};

void iconst_m1(PilhaDeOperandos* pilhaDeOperandos){
    u4 number = -1;
    EmpilhaOperando32bits(&pilhaDeOperandos,&number);
}

void iconst_0(PilhaDeOperandos* pilhaDeOperandos) {
    u4 number = 0;
    EmpilhaOperando32bits(&pilhaDeOperandos,&number);
}

void iconst_1(PilhaDeOperandos* pilhaDeOperandos) {
    u4 number = 1;
    EmpilhaOperando32bits(&pilhaDeOperandos,&number);
}

void iconst_2(PilhaDeOperandos* pilhaDeOperandos) {
    u4 number = 2;
    EmpilhaOperando32bits(&pilhaDeOperandos,&number);
}

void iconst_3(PilhaDeOperandos* pilhaDeOperandos) {
    u4 number = 3;
    EmpilhaOperando32bits(&pilhaDeOperandos,&number);
}

void iconst_4(PilhaDeOperandos* pilhaDeOperandos) {
    u4 number = 4;
    EmpilhaOperando32bits(&pilhaDeOperandos,&number);
}

void iconst_5(PilhaDeOperandos* pilhaDeOperandos) {
    u4 number = 5;
    EmpilhaOperando32bits(&pilhaDeOperandos,&number);
}
void lconst_0(PilhaDeOperandos* pilhaDeOperandos) {
    u4 high = 0;
    u4 low = 0;
    EmpilhaOperando64bits(&pilhaDeOperandos,0);
}

void lconst_1(PilhaDeOperandos* pilhaDeOperandos) {
    u4 high = 1;
    u4 low = 0;
   EmpilhaOperando64bits(&pilhaDeOperandos,1);
}

void fconst_0(PilhaDeOperandos* pilhaDeOperandos) {
    float zeroNum = 0.0;
    EmpilhaOperando32bits(&pilhaDeOperandos,0);
}

void fconst_1(PilhaDeOperandos* pilhaDeOperandos) {
    float zeroNum = 1.0;
    EmpilhaOperando32bits(&pilhaDeOperandos,1);
}

void fconst_2(PilhaDeOperandos* pilhaDeOperandos) {
    float zeroNum = 2.0;
    EmpilhaOperando32bits(&pilhaDeOperandos,2);
}

void dconst_0(PilhaDeOperandos* pilhaDeOperandos) {
    long zeroNum = 0.0;
    EmpilhaOperando64bits(pilhaDeOperandos,0);
}

void dconst_1(PilhaDeOperandos* pilhaDeOperandos) {
    EmpilhaOperando64bits(&pilhaDeOperandos,1);
}

void bipush(PilhaDeOperandos* pilhaDeOperandos,u4* n){
    EmpilhaOperando32bits(&pilhaDeOperandos,*n);
}

void sipush(PilhaDeOperandos* pilhaDeOperandos,u2* n){
    EmpilhaOperando32bits(&pilhaDeOperandos,*n);
}

void ldc(PilhaDeOperandos* pilhaDeOperandos,u1 index, cp_info* constantPool){
    u1 tag = constantPool[index-1].tag;
    switch (tag){
        case 3: //Integer
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[index-1].info.Integer.bytes);
            break;
        case 4: //Float
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[index-1].info.Float.bytes);
            break;
        case 8: //String, Need to see the correct reference to save it.
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[index-1].info.String.string_index);
            break;
    }
}

void ldc_w(PilhaDeOperandos* pilhaDeOperandos,u1 index,u1 index2, cp_info* constantPool){
    u2 indexConcat = (index<<8) | index2;
    u1 tag = constantPool[index-1].tag;
   switch (tag){
        case 3: //Integer
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[index-1].info.Integer.bytes);
            break;
        case 4: //Float
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[index-1].info.Float.bytes);
            break;
        case 8: //String, Need to see the correct reference to save it.
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[index-1].info.String.string_index);
            break;
    }
}

void ldc2_w(PilhaDeOperandos* pilhaDeOperandos,u1 index,u1 index2, cp_info* constantPool){
    u2 indexConcat = (index<<8) | index2;
    u1 tag = constantPool[indexConcat-1].tag;

    switch(tag){
        case 5:
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[indexConcat-1].info.Long.high_bytes);
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[indexConcat-1].info.Long.low_bytes);
            break;
        case 6:
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[indexConcat-1].info.Double.high_bytes);
            EmpilhaOperando32bits(&pilhaDeOperandos,constantPool[indexConcat-1].info.Double.low_bytes);
            break;
    }
}

void iload(PilhaDeOperandos* pilhaDeOperandos,u1 index, u1 index2, field_info* fields){
    u2 indexConcat =0;
    if(index2 != NULL){
        indexConcat = (u2)(index<<8) | (u2)(index2);
    }else{
        indexConcat = (u2)index;
    }
#warning Need to teste this implementation. In my mind its incomplete. Need to access something on this structure.
//    EmpilhaOperando32bits(&pilhaDeOperandos,fields[indexConcat]);
}

void lload(PilhaDeOperandos* pilhaDeOperandos,u1 index, u1 index2, field_info* fields){
    u2 indexConcat =0;
    if(index2 != NULL){
        indexConcat = (u2)(index<<8) | (u2)(index2);
    }else{
        indexConcat = (u2)index;
    }
//#warning Need to teste this implementation. In my mind its incomplete. Need to access something on this structure.
//    push(fields[indexConcat]);
//    push(fields[indexConcat+1]);
}

void fload(PilhaDeOperandos* pilhaDeOperandos,u1 index, u1 index2, field_info* fields){
    u2 indexConcat =0;
    if(index2 != NULL){
        indexConcat = (u2)(index<<8) | (u2)index2;
    }else{
        indexConcat = (u2)index;
    }
#warning Need to teste this implementation. In my mind its incomplete. Need to access something on this structure.
//    push(fields[indexConcat]);
}

void dload(PilhaDeOperandos* pilhaDeOperandos,u1 index, u1 index2, field_info* fields){
    u2 indexConcat =0;
    if(index2 != NULL){
        indexConcat = (u2)(index<<8) | (u2)(index2);
    }else{
        indexConcat = (u2)index;
    }
#warning Need to teste this implementation. In my mind its incomplete. Need to access something on this structure.
//    push(fields[indexConcat]);
//    push(fields[indexConcat+1]);
}


#minha parte.


void wide(){
    return;
}

void multianewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 dimensions){
    u4 *valores;
    int i;
    char *tipo;
    u2 index;
    index = (indexbyte1 << 8 | indexbyte2);
    index = ((frame->constant_pool[index - 1].info.Class.name_index) - 1);
    tipo = dereferencia1(index, frame->constant_pool);
    for (i = 0; i < dimensions; i++){
        valores[i] = DesempilhaOperando32bits(&(frame->pilhaOperandos));
    }
    i = strlen(tipo) - 1;
    switch (i){
        case 1:
            if (!strcmp(tipo, "[B")){

            }
        break;
        case 2:
        break;
        case 3:
        break;
    }

    if (!strcmp(tipo,"[")){

    }

    return;
}

void ifnull(Frame *frame, u1 branchbyte1, u1 branchbyte2){
    u4 objref;
    u2 branchoffset;
    branchoffset = (branchbyte1 << 8 | branchbyte2);
    objref = DesempilhaOperando32bits(&(frame->pilhaOperandos));
    if (objref == NULL)
        frame->pc = frame->pc + branchoffset;

    return;
}

void ifnonnull(Frame *frame, u1 branchbyte1, u1 branchbyte2){
    u4 objref;
    u2 branchoffset;
    branchoffset = (branchbyte1 << 8 | branchbyte2);
    objref = DesempilhaOperando32bits(&(frame->pilhaOperandos));
    if (objref != NULL)
        frame->pc = frame->pc + branchoffset;

    return;
}

void goto_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4){
    u4 branchoffset;
    branchoffset = (branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4);
    frame->pc = frame->pc + branchoffset;
    return;
}

void jsr_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4){
    u4 branchoffset;
    branchoffset = (branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4);
    EmpilhaOperando32bits(&(frame->pilhaOperandos),&(frame->pc + 5));
    frame->pc = frame->pc + branchoffset;
    return;
}

char* dereferencia1(u2 index, cp_info *cp) {
    char *nome;
    int i;
    nome = (char *) malloc((cp[index].info.Utf8.length + 1) * sizeof(char));
    for (i = 0; i < cp[index].info.Utf8.length; i++) {
        nome[i] = cp[index].info.Utf8.bytes[i];
    }
    nome[i] = '\0';
    return nome;
}
