/**
* @file pilha_frames.c
* @author Guilherme
* @brief
*/

#include "pilha_frames.h"
#include "../Heap/heap.h"

Frame *ConstruirFrame(ClassFile *classe, method_info *method, PilhaDeFrames *pilhaDeFrames, Heap *heap)
{
    Frame *frame;

    frame = (Frame *) malloc(sizeof(Frame));
    frame->method = method;
    frame->pc = 0;
    frame->pilhaDeOperandos = NULL;
    frame->pilhaDeFrames = pilhaDeFrames;
    frame->TamanhoVetorVariaveisLocais = method->attributes->info.CodeAttribute.max_locals;
    frame->VetorVariaveisLocais = (u4 *) malloc(sizeof(u4) * frame->TamanhoVetorVariaveisLocais);
    frame->constant_pool_count = classe->constant_pool_count;
    frame->constant_pool = classe->constant_pool;
    frame->returAddress = 0;
    frame->classe = classe;

    attribute_info *codigo = NULL;
    for(int i = 0; i < method->attributes_count; i++) {
        if(method->attributes[i].tag == ATTRTAG_Code) {
            codigo = &(method->attributes[i]);
            break;
        }
    }

    frame->codigo = codigo;
    frame->heap = heap;

    return frame;
}

void InicializaPilhaDeFrames(PilhaDeFrames **pilhaFrames)
{
    *pilhaFrames = NULL;
    return;
}

//u1 PilhaDeFramesVazia(PilhaDeFrames *pilhaFrame)
//{
//    if (pilhaFrame == NULL)
//        return 1;
//    else
//        return 0;
//}

PilhaDeFrames* EmpilhaFrame(PilhaDeFrames *pilhaFrame, Frame *frame)
{
    PilhaDeFrames *pf1;
    PilhaDeFrames *interat = pilhaFrame;
	pf1 = (PilhaDeFrames *)malloc(sizeof(PilhaDeFrames));
	pf1->dado = frame;
	if(pilhaFrame == NULL){
		pf1->prox = NULL;
		interat = pf1;
		return interat;
	}
    pf1->prox = interat;
    interat = pf1;
    return interat;
}

Frame *DesempilhaFrame(PilhaDeFrames **pilhaFrame)
{
    PilhaDeFrames *pf1 = *pilhaFrame;
    Frame *frame = pf1->dado;
    *pilhaFrame = pf1->prox;
    free(pf1);
    return frame;
}

void DestruirFrame(Frame *frame)
{
    desalocaPilhaOperandos(&frame->pilhaDeOperandos);
    if (frame->TamanhoVetorVariaveisLocais != 0)
        free(frame->VetorVariaveisLocais);
    free(frame);
}

//void desalocaPilhaFrames(PilhaDeFrames **pilhaFrames)
//{
//    PilhaDeFrames *lc1;
//    while (*pilhaFrames != NULL)
//    {
//        free((*pilhaFrames)->dado);
//        lc1 = *pilhaFrames;
//        *pilhaFrames = lc1->prox;
//        free(lc1);
//    }
//    return;
//}
