#include "store.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


void i_istore(Frame* frame, u1 index)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = *value;
}

void i_lstore(Frame* frame, u1 index)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = (*value) >> 32;
    frame ->VetorVariaveisLocais[index+1] = (*value) & 0xFFFFF;
}

void i_fstore(Frame* frame, u1 index)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = *value;
}

void i_dstore(Frame* frame, u1 index)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = (*value) >> 32;
    frame ->VetorVariaveisLocais[index+1] = (*value) & 0xFFFFF;
}

void i_astore(Frame* frame, u1 index)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[index] = *value;
}

void i_istore_0(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = *value;
}

void i_istore_1(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = *value;
}

void i_istore_2(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = *value;
}

void i_istore_3(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = *value;
}

void i_lstore_0(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = (*value) >> 32;
    frame ->VetorVariaveisLocais[1] = (*value) & 0xFFFFF;
}

void i_slstore_1(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = (*value) >> 32;
    frame ->VetorVariaveisLocais[2] = (*value) & 0xFFFFF;
}

void i_lstore_2(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = (*value) >> 32;
    frame ->VetorVariaveisLocais[3] = (*value) & 0xFFFFF;
}

void i_lstore_3(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = (*value) >> 32;
    frame ->VetorVariaveisLocais[4] = (*value) & 0xFFFFF;
}

void i_fstore_0(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = *value;
}

void i_fstore_1(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = *value;
}

void i_fstore_2(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = *value;
}

void i_fstore_3(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = *value;
}

void i_dstore_0(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = (*value) >> 32;
    frame ->VetorVariaveisLocais[1] = (*value) & 0xFFFFF;
}

void i_dstore_1(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = (*value) >> 32;
    frame ->VetorVariaveisLocais[2] = (*value) & 0xFFFFF;
}

void i_dstore_2(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = (*value) >> 32;
    frame ->VetorVariaveisLocais[3] = (*value) & 0xFFFFF;
}

void i_dstore_3(Frame* frame)
{
    u8 *value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = (*value) >> 32;
    frame ->VetorVariaveisLocais[4] = (*value) & 0xFFFFF;
}

void i_astore_0(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[0] = *value;
}

void i_astore_1(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[1] = *value;
}

void i_astore_2(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[2] = *value;
}

void i_astore_3(Frame* frame)
{
    u4 *value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame->VetorVariaveisLocais[3] = *value;
}

void i_iastore(Frame* frame)
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

void i_lastore(Frame* frame)
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

void i_fastore(Frame* frame)
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

void i_dastore(Frame* frame)
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
void i_aastore(Frame* frame)
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

void i_bastore(Frame* frame)
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

void i_castore(Frame* frame)
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

void i_sastore(Frame* frame)
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
