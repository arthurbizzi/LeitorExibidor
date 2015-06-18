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
