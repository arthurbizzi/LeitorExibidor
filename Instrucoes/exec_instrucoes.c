//
// Created by kelvinec on 18/06/15.
//

#include "exec_instrucoes.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>

void nop()
{
    return;
};

void aconst_null(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 0;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
    return;
};

void iconst_m1(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = -1;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void iconst_0(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 0;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void iconst_1(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 1;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void iconst_2(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void iconst_3(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 3;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void iconst_4(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 4;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void iconst_5(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 5;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}
void lconst_0(Frame* frame)
{
    u8 *value = (u8*)malloc(sizeof(u8));
    *value = 0.0;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),value);
}

void lconst_1(Frame* frame)
{
    u8 *value = (u8*)malloc(sizeof(u8));
    *value = 1;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),1);
}

void fconst_0(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 0.0f;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void fconst_1(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 1.0f;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void fconst_2(Frame* frame)
{
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 2.0f;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void dconst_0(Frame* frame)
{
    u8 *value = (u8*)malloc(sizeof(u8));
    *value = 0.0d;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),value);
}

void dconst_1(Frame* frame)
{
    u8 *value = (u8*)malloc(sizeof(u8));
    *value = 1.0d;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),value);
}

void bipush(Frame* frame,u4* n)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),n);
}

void sipush(Frame* frame,u2* n)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),n);
}

void ldc(Frame* frame,u1 index, cp_info* constantPool)
{
    u1 tag = constantPool[index-1].tag;
    switch (tag)
    {
    case CONSTANT_Integer:  //Integer
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Integer.bytes);
        break;
    case CONSTANT_Float: //Float
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Float.bytes);
        break;
    case CONSTANT_String: //String, Need to see the correct reference to save it.
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.String.string_index);
        break;
    }
}

void ldc_w(Frame* frame,u1 index,u1 index2, cp_info* constantPool)
{
    u2 indexConcat = (index<<8) | index2;
    u1 tag = constantPool[index-1].tag;
    switch (tag)
    {
    case CONSTANT_Integer: //Integer
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Integer.bytes);
        break;
    case CONSTANT_Float: //Float
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Float.bytes);
        break;
    case CONSTANT_String: //String, Need to see the correct reference to save it.
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.String.string_index);
        break;
    }
}

void ldc2_w(Frame* frame,u1 index,u1 index2, cp_info* constantPool)
{
    u2 indexConcat = (index<<8) | index2;
    u1 tag = constantPool[indexConcat-1].tag;

    switch(tag)
    {
    case CONSTANT_Long:
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[indexConcat-1].info.Long.high_bytes);
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[indexConcat-1].info.Long.low_bytes);
        break;
    case CONSTANT_Double:
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[indexConcat-1].info.Double.high_bytes);
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[indexConcat-1].info.Double.low_bytes);
        break;
    }
}

void iload(Frame* frame,u1 index, u1 index2)
{
    u2 indexConcat =0;
    if(index2 != NULL)
    {
        indexConcat = (u2)(index<<8) | (u2)(index2);
    }
    else
    {
        indexConcat = (u2)index;
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
}

void lload(Frame* frame,u1 index, u1 index2)
{
    u2 indexConcat =0;
    if(index2 != NULL)
    {
        indexConcat = (u2)(index<<8) | (u2)(index2);
    }
    else
    {
        indexConcat = (u2)index;
    }
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
}

void fload(Frame* frame,u1 index, u1 index2)
{
    u2 indexConcat =0;
    if(index2 != NULL)
    {
        indexConcat = (u2)(index<<8) | (u2)index2;
    }
    else
    {
        indexConcat = (u2)index;
    }

#warning Need to see if smurf implementation cover this case, or need to mount the u4 field to pass to function store.
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
}

void dload(Frame* frame,u1 index, u1 index2)
{
    u2 indexConcat =0;

#warning definition of wide. chage this when function is implemened.
    if(index2 != NULL)
    {
        indexConcat = (u2)(index<<8) | (u2)(index2);
    }
    else
    {
        indexConcat = (u2)index;
    }
#warning Need to see if smurf implementation cover this case, or need to mount the u8 field to pass to function store.
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
}

void aload(Frame* frame,u1 index)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[index]));
}

void iload_0(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[0]));
}

void iload_1(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
}

void iload_2(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
}

void iload_3(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
}

void lload_0(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[0]));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
}

void lload_1(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
}

void lload_2(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
}

void lload_3(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[4]));
}

#warning essa seção precisa de revisão pra ver como fazer a correta implementação de ponto flutuante.
void fload_0(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[0]));
}

void fload_1(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
}

void fload_2(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
}

void fload_3(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
}

void dload_0(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[0]));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
}

void dload_1(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
}

void dload_2(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
}

void dload_3(Frame* frame)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[4]));
}

#warning fim da seção de ponto flutuante.

void aload_0(Frame* frame,u1 index)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[0]));
}

void aload_1(Frame* frame,u1 index)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
}

void aload_2(Frame* frame,u1 index)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
}

void aload_3(Frame* frame,u1 index)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
}

void iaload(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),iterator[index].dado->info.tipoInt);
    }
}

void laload(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        EmpilhaOperando64bits(&(frame->pilhaDeOperandos),iterator[index].dado->info.tipoLong);
    }
}

void faload(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),iterator[index].dado->info.tipoFloat);
    }
}

void daload(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        EmpilhaOperando64bits(&(frame->pilhaDeOperandos),iterator[index].dado->info.tipoDouble);
    }
}

#warning Precisar entender o funcionamento do AALOAD. Não ficou claro.
void aaload(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        EmpilhaOperando64bits(&(frame->pilhaDeOperandos),iterator[index].dado->info.tipoDouble);
    }
}

void baload(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),iterator[index].dado->info.tipoByte);
    }
}

void caload(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),iterator[index].dado->info.tipoChar);
    }
}

void saload(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),iterator[index].dado->info.tipoShort);
    }
}

void istore(Frame* frame, u1 index)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = *value;
}

void lstore(Frame* frame, u1 index)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = (*value) >> 32;
    frame ->VetorVariaveisLocais[index+1] = (*value) & 0xFFFFF;
}

void fstore(Frame* frame, u1 index)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = *value;
}

void dstore(Frame* frame, u1 index)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = (*value) >> 32;
    frame ->VetorVariaveisLocais[index+1] = (*value) & 0xFFFFF;
}

void astore(Frame* frame, u1 index)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = *value;
}

void istore_0(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = *value;
}

void istore_1(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = *value;
}

void istore_2(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = *value;
}

void istore_3(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = *value;
}

void lstore_0(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = (*value) >> 32;
    frame ->VetorVariaveisLocais[1] = (*value) & 0xFFFFF;
}

void lstore_1(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = (*value) >> 32;
    frame ->VetorVariaveisLocais[2] = (*value) & 0xFFFFF;
}

void lstore_2(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = (*value) >> 32;
    frame ->VetorVariaveisLocais[3] = (*value) & 0xFFFFF;
}

void lstore_3(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = (*value) >> 32;
    frame ->VetorVariaveisLocais[4] = (*value) & 0xFFFFF;
}

void fstore_0(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = *value;
}

void fstore_1(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = *value;
}

void fstore_2(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = *value;
}

void fstore_3(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = *value;
}

void dstore_0(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = (*value) >> 32;
    frame ->VetorVariaveisLocais[1] = (*value) & 0xFFFFF;
}

void dstore_1(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = (*value) >> 32;
    frame ->VetorVariaveisLocais[2] = (*value) & 0xFFFFF;
}

void dstore_2(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = (*value) >> 32;
    frame ->VetorVariaveisLocais[3] = (*value) & 0xFFFFF;
}

void dstore_3(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = (*value) >> 32;
    frame ->VetorVariaveisLocais[4] = (*value) & 0xFFFFF;
}

void astore_0(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = *value;
}

void astore_1(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = *value;
}

void astore_2(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = *value;
}

void astore_3(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = *value;
}

void iastore(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        iterator[index].dado->info.tipoInt = value;
    }
}

void lastore(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 value =  DesempilhaOperando64bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        iterator[index].dado->info.tipoLong = value;
    }
}

void fastore(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        iterator[index].dado->info.tipoFloat = value;
    }
}

void dastore(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 value =  DesempilhaOperando64bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        iterator[index].dado->info.tipoDouble = value;
    }
}

#warning Need to see implemetation of this function.
void aastore(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 value =  DesempilhaOperando64bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        iterator[index].dado->info.tipoDouble = value;
    }
}

void bastore(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u1 value =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        iterator[index].dado->info.tipoByte = value;
    }
}

void castore(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u1 value =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        iterator[index].dado->info.tipoChar = value;
    }
}

void sastore(Frame* frame)
{
    u4 arrayRef = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u2 value =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    ListaArrays* iterator = frame->listaArrays;
    while(iterator!= NULL)
    {
        if(iterator = arrayRef)
        {
            break;
        }
        iterator = iterator->prox;
    }
    if(iterator!=NULL)
    {
        iterator[index].dado->info.tipoShort = value;
    }
}

void pop(Frame* frame){
    DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
}

void pop2(Frame* frame){
    DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
}

void dup(Frame* frame){
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void dup_x1(Frame* frame){
    u4 valueTop = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void dup_x2(Frame* frame){
    u4 valueTop = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 valuefloor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valuefloor);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valuefloor);
}


void dup2(Frame* frame){
    u4 valueTop = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
}

void dup2_x1(Frame* frame){
    u4 valueTop = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 valueFloor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueFloor);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueFloor);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}


void dup2_x2(Frame* frame){
    u4 value4 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value3 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value1);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value2);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value3);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value4);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value1);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value2);
}

void swap(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value2);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value1);
}

void iadd(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1+value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void ladd(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1+value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

#warning see this implementation
void fadd(Frame* frame){
    float value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1+value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void dadd(Frame* frame){
    double value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1+value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void isub(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1-value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void lsub(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1-value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

#warning see this implementation
void fsub(Frame* frame){
    float value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1-value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void dsub(Frame* frame){
    double value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1-value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void imul(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1*value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void lmul(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1*value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

#warning see this implementation
void fmul(Frame* frame){
    float value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1*value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void dmul(Frame* frame){
    double value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1*value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void idiv(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1/value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void ldiv(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1/value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

#warning see this implementation
void fdiv(Frame* frame){
    float value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1/value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void ddiv(Frame* frame){
    double value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1/value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void irem(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1%value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void lrem(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1%value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

#warning see this implementation
void frem(Frame* frame){
    float value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1%value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void drem(Frame* frame){
    double value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1%value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void ineg(Frame* frame){
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = ~value;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void lneg(Frame* frame){
    u8 value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 result = ~value;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void fneg(Frame* frame){
    float value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = ~value;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void dneg(Frame* frame){
    double value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 result = ~value;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void ishl(Frame* frame){
	u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    u4 signal = value >> 31;
    value = (value << shifter);
    if(signal == 0){
		value &= 0x7FFFFFFF;
    }else{
    	value |= 0x80000000;
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void lshl(Frame* frame){
	u8 value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    u4 signal = value >> 63;
    value = (value << shifter);
    if(signal == 0){
		value &= 0x7FFFFFFFFFFFFFFF;
    }else{
    	value |= 0x800000000000000;
    }
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}

void ishr(Frame* frame){
	u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    u4 signal = value >> 31;
    value &= 0x7FFFFFFF;
    value = (value >> shifter);
    if(signal == 0){
		value &= 0x7FFFFFFF;
    }else{
    	value |= 0x80000000;
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void lshr(Frame* frame){
	u8 value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    u4 signal = value >> 63;
    value &= 0x7FFFFFFFFFFFFFFF;
    value = (value >> shifter);
    if(signal == 0){
		value &= 0x7FFFFFFFFFFFFFFF;
    }else{
    	value |= 0x800000000000000;
    }
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}

void iushr(Frame* frame){
	u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    value = (value >> shifter);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void lushr(Frame* frame){
	u8 value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    value = (value >> shifter);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}

void iand(Frame* frame){
	u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = (value1 & value2);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void land(Frame* frame){
	u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 result = (value1 & value2);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void ior(Frame* frame){
	u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = (value1 | value2);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void lor(Frame* frame){
	u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 result = (value1 | value2);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void ixor(Frame* frame){
	u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = (value1 ^ value2);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void lxor(Frame* frame){
	u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 result = (value1 ^ value2);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

#warning needs to implement wide.
void iinc(Frame* frame, u1 index, u1 inc){
	frame->VetorVariaveisLocais[index] += inc;
}

void i2l(Frame* frame){
	u8 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

#warning Need to see this implementation
void i2f(Frame* frame){
	float result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

#warning Need to see this implementation
void i2d(Frame* frame){
	double result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void l2i(Frame* frame){
	u4 result = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void l2f(Frame* frame){
	float result = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void l2d(Frame* frame){
	double result = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void f2i(Frame* frame){
	u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void f2l(Frame* frame){
	u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void f2d(Frame* frame){
	double result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void d2i(Frame* frame){
	double op = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = op;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void d2l(Frame* frame){
	double op = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = op;
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void d2f(Frame* frame){
	double op = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	float result = op;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i2b(Frame* frame){
	u1 result =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}


void i2c(Frame* frame){
	char result =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}


void i2s(Frame* frame){
	u2 result =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void lcmp(Frame* frame){
	u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void fcmpl(Frame* frame){
	float value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	float value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void fcmpg(Frame* frame){
	float value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	float value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 > value2){
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void dcmpl(Frame* frame){
	double value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	double value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void dcmpg(Frame* frame){
	double value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	double value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 > value2){
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void ifeq(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result == 0){
		frame->pc += (index1<<8)+index2;
    }
}

void ifne(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result != 0){
		frame->pc += (index1<<8)+index2;
    }
}

void iflt(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result < 0){
		frame->pc += (index1<<8)+index2;
    }
}

void ifge(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result >= 0){
		frame->pc += (index1<<8)+index2;
    }
}

void ifgt(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result > 0){
		frame->pc += (index1<<8)+index2;
    }
}

void ifle(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result <= 0){
		frame->pc += (index1<<8)+index2;
    }
}

void if_icmpeq(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 == value2){
		frame->pc += (index1<<8)+index2;
    }
}

void if_icmpne(Frame* frame,u1 index1,u2 index2){
	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 != value2){
		frame->pc += (index1<<8)+index2;
    }
}

void if_icmplt(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 < value2){
		frame->pc += (index1<<8)+index2;
    }
}

void if_icmpge(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 >= value2){
		frame->pc += (index1<<8)+index2;
    }
}

void if_icmpgt(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 > value2){
		frame->pc += (index1<<8)+index2;
    }
}

void if_icmple(Frame* frame,u1 index1,u2 index2){
     u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 <= value2){
		frame->pc += (index1<<8)+index2;
    }
}

void if_acmpeq(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 == value2){
		frame->pc += (index1<<8)+index2;
    }
}

void if_acmpne(Frame* frame,u1 index1,u2 index2){
	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 != value2){
		frame->pc += (index1<<8)+index2;
    }
}

void i_goto(Frame* frame, u1 index1, u1 index2){
	frame->pc += (u2)((index1<<8)+index2);
}

#warning alinhar como incremento do ponteiro de PC é feito
void jsr(Frame* frame, u1 index, u1 index2){
	frame->pc += 1;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &(frame->pc));
}

#warning precis ser olhado com mais cuidado
void ret(Frame* frame, u1 index){
	frame->pc = frame->VetorVariaveisLocais[index];
}



#pragma mark - SMURF PART

void invokeinterface(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 contagem, u1 zero)
{

    return;
}

void new(Frame *frame, u1 indexbyte1, u1 indexbyte2, ListaClasses *listadeclasses)
{
    Objeto *obj;
    char *tipo;
    u2 index;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    tipo = dereferencia_instrucoes(index, frame->constant_pool);
    obj = (Objeto *)malloc(sizeof(Objeto));
    obj->classe = RecuperaClasse(tipo,&listadeclasses);
    obj->tamanhotipoField = 0;
    obj->tipofield = NULL;
    obj->tamanhotipoArray = 0;
    obj->tipoarray = NULL;
    return;
}

void newarray(Frame *frame, u1 atype)
{
    u4 valor;
    tArray *a;
    a = (tArray *)malloc(sizeof(tArray));
    valor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    switch (atype)
    {
    case TipoByte:
        a->tag = TipoByte;
        a->info.tipoByte = (u1 *)malloc(sizeof(u1) * valor);
        break;
    case TipoChar:
        a->tag = TipoChar;
        a->info.tipoChar = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case TipoDouble:
        a->tag = TipoDouble;
        a->info.tipoDouble = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case TipoFloat:
        a->tag = TipoFloat;
        a->info.tipoFloat = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case TipoInt:
        a->tag = TipoInt;
        a->info.tipoInt = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case TipoLong:
        a->tag = TipoLong;
        a->info.tipoLong = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case TipoReferencia:
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case TipoShort:
        a->tag = TipoShort;
        a->info.tipoShort = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case TipoBoolean:
        a->tag = TipoBoolean;
        a->info.tipoBoolean = (u1 *)malloc(sizeof(u1) * valor);
        break;
    default:
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &a);
    return;
}

void anewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    char *tipo;
    u2 index;
    u4 i, valor;
    tArray *a;
    a = (tArray *)malloc(sizeof(tArray));
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    tipo = dereferencia_instrucoes(index, frame->constant_pool);
    valor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    i = 0;
    while (tipo[i] == '[')
    {
        i++;
    }
    switch (tipo[i])
    {
    case 'B':
        a->tag = TipoByte;
        a->info.tipoByte = (u1 *)malloc(sizeof(u1) * valor);
        break;
    case 'C':
        a->tag = TipoChar;
        a->info.tipoChar = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case 'D':
        a->tag = TipoDouble;
        a->info.tipoDouble = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case 'F':
        a->tag = TipoFloat;
        a->info.tipoFloat = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'I':
        a->tag = TipoInt;
        a->info.tipoInt = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'J':
        a->tag = TipoLong;
        a->info.tipoLong = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case 'L':
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'S':
        a->tag = TipoShort;
        a->info.tipoShort = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case 'Z':
        a->tag = TipoBoolean;
        a->info.tipoBoolean = (u1 *)malloc(sizeof(u1) * valor);
        break;
    default:
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &a);
    return;
}

void arraylength(Frame *frame)
{
    tArray *a;
    a = (tArray *)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &(a->tamanho));
    return;
}

void atrhow(Frame *frame)
{

    return;
}

void checkcast(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    char *nomeclasse, *nomeclasseobjeto;
    Objeto *obj;
    u2 index;
    u4 valor = 0;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    obj = (Objeto *)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    nomeclasse = dereferencia_instrucoes(index, frame->constant_pool);
    nomeclasseobjeto = dereferencia_instrucoes(obj->classe->constant_pool[obj->classe->this_class - 1].info.Class.name_index - 1, obj->classe->constant_pool);
    if (obj == NULL)
    {
        printf("Erro: Referencia nula\n");
    } else if (!strcmp(nomeclasse,nomeclasseobjeto))
    {
        printf(" Erro: Objeto do tipo errado\n");
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), (u4 *)obj);
    return;
}

void instanceof(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    char *nomeclasse, *nomeclasseobjeto;
    Objeto *obj;
    u2 index;
    u4 valor = 0;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    obj = (Objeto *)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    nomeclasse = dereferencia_instrucoes(index, frame->constant_pool);
    nomeclasseobjeto = dereferencia_instrucoes(obj->classe->constant_pool[obj->classe->this_class - 1].info.Class.name_index - 1, obj->classe->constant_pool);
    if (obj == NULL)
    {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
    } else if (!strcmp(nomeclasse,nomeclasseobjeto))
    {
        valor = 1;
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
    } else
    {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
    }
    return;
}

void monitorenter(Frame *frame)
{
    return;
}

void monitorexit(Frame *frame)
{
    return;
}

void wide(Frame *frame, u1 opcode, u1 index, u1 index2, u1 constbyte1, u1 constbyte2)
{
    int16_t valor;
    u4 value;
    u2 indexConcat = 0;
    indexConcat = (u2)(index<<8) | (u2)(index2);
    switch (opcode)
    {
        case 0x15:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x16:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat + 1]));
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x17:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x18:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat + 1]));
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x19:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x36:
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
        break;
        case 0x37:
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat + 1] = value;
        break;
        case 0x38:
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
        break;
        case 0x39:
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat + 1] = value;
        break;
        case 0x3a:
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
        break;
        case 0x84:
            valor = (int16_t)(constbyte1<<8) | (int16_t)(constbyte2);
            frame->VetorVariaveisLocais[indexConcat] += valor;
        break;
    }
    return;
}

void multianewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 dimensions)
{
    u4 valor = 1;
    int i;
    char *tipo;
    u2 index;
    tArray *a;
    a = (tArray *)malloc(sizeof(tArray));
    index = (u2)(indexbyte1 << 8 | indexbyte2);
    index = ((frame->constant_pool[index - 1].info.Class.name_index) - 1);
    tipo = dereferencia_instrucoes(index, frame->constant_pool);
    for (i = 0; i < dimensions; i++)
    {
        valor *= DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    }
    i = 0;
    while (tipo[i] == '[')
    {
        i++;
    }
    a->tamanho = valor;
    switch (tipo[i])
    {
    case 'B':
        a->tag = TipoByte;
        a->info.tipoByte = (u1 *)malloc(sizeof(u1) * valor);
        break;
    case 'C':
        a->tag = TipoChar;
        a->info.tipoChar = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case 'D':
        a->tag = TipoDouble;
        a->info.tipoDouble = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case 'F':
        a->tag = TipoFloat;
        a->info.tipoFloat = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'I':
        a->tag = TipoInt;
        a->info.tipoInt = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'J':
        a->tag = TipoLong;
        a->info.tipoLong = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case 'L':
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'S':
        a->tag = TipoShort;
        a->info.tipoShort = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case 'Z':
        a->tag = TipoBoolean;
        a->info.tipoBoolean = (u1 *)malloc(sizeof(u1) * valor);
        break;
    default:
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &a);
    return;
}

void ifnull(Frame *frame, u1 branchbyte1, u1 branchbyte2)
{
    u4 objref;
    u2 branchoffset;
    branchoffset = (branchbyte1 << 8 | branchbyte2);
    objref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if (objref == NULL)
        frame->pc = frame->pc + branchoffset;

    return;
}

void ifnonnull(Frame *frame, u1 branchbyte1, u1 branchbyte2)
{
    u4 objref;
    u2 branchoffset;
    branchoffset = (branchbyte1 << 8 | branchbyte2);
    objref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if (objref != NULL)
        frame->pc = frame->pc + branchoffset;

    return;
}

void goto_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4)
{
    u4 branchoffset;
    branchoffset = (branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4);
    frame->pc = frame->pc + branchoffset;
    return;
}

void jsr_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4)
{
    u4 branchoffset, pc;
    branchoffset = (branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4);
    pc = frame->pc + 5;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &pc);
    frame->pc = frame->pc + branchoffset;
    return;
}

char* dereferencia_instrucoes(u2 index, cp_info *cp)
{
    char *nome;
    int i;
    nome = (char *) malloc((cp[index].info.Utf8.length + 1) * sizeof(char));
    for (i = 0; i < cp[index].info.Utf8.length; i++)
    {
        nome[i] = cp[index].info.Utf8.bytes[i];
    }
    nome[i] = '\0';
    return nome;
}

ClassFile *RecuperaClasse(char *nome, ListaClasses **listadeclasses)
{
    ListaClasses *lc1;
    int index;
    char *nomeThisClass;
    lc1 = *listadeclasses;
    while (lc1 != NULL)
    {
        index = lc1->dado->constant_pool[lc1->dado->this_class - 1].info.Class.name_index - 1;
        nomeThisClass = dereferencia(index, lc1->dado);
        if (!strcmp(nome,nomeThisClass))
            return lc1->dado;
        lc1 = lc1->prox;
    }
    return NULL;
}
