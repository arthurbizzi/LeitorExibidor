//
// Created by kelvinec on 18/06/15.
//

#include "exec_instrucoes.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"

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



#pragma mark - SMURF PART


void wide()
{
    return;
}

void multianewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 dimensions)
{
    u4 *valores;
    int i;
    char *tipo;
    u2 index;
    index = (indexbyte1 << 8 | indexbyte2);
    index = ((frame->constant_pool[index - 1].info.Class.name_index) - 1);
    tipo = dereferencia1(index, frame->constant_pool);
    for (i = 0; i < dimensions; i++)
    {
        valores[i] = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    }
    i = strlen(tipo) - 1;
    switch (i)
    {
    case 1:
        if (!strcmp(tipo, "[B"))
        {

        }
        break;
    case 2:
        break;
    case 3:
        break;
    }

    if (!strcmp(tipo,"["))
    {

    }

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