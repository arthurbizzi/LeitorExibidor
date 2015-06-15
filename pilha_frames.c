#include "pilha_frames.h"
#include "pilha_operandos.h"

Frame *ConstruirFrame(ClassFile *classe, method_info *method){
    Frame *frame;

    frame = (Frame *)malloc(sizeof(Frame));
    frame->method = method;
    frame->pc = 0;
    frame->pilhaOperandos = NULL;
    frame->TamanhoVetorVariaveisLocais = method->attributes->info.CodeAttribute.max_locals;
    frame->VetorVariaveisLocais = (u4 *)malloc(sizeof(u4) * frame->TamanhoVetorVariaveisLocais);
    frame->constant_pool_count = classe->constant_pool_count;
    frame->constant_pool = classe->constant_pool;
    frame->listaArrays = NULL;
    frame->listaObjetos = NULL;
    frame->returAddress = 0;

    return frame;
}

void InicializaPilhaDeFrames(PilhaDeFrames **pilhaFrames){
    *pilhaFrames = NULL;
    return;
}

u1 PilhaDeFramesVazia(PilhaDeFrames *pilhaFrame){
    if (pilhaFrame == NULL)
        return 1;
    else
        return 0;
}

void EmpilhaFrame(PilhaDeFrames **pilhaFrame, Frame *frame){
    PilhaDeFrames *pf1;
    pf1 = (PilhaDeFrames *)malloc(sizeof(PilhaDeFrames));
    pf1->dado = frame;
    pf1->prox = *pilhaFrame;
    *pilhaFrame = pf1;
    return;
}

Frame *DesempilhaFrame(PilhaDeFrames **pilhaFrame){
    PilhaDeFrames *pf1;
    Frame *frame;
    pf1 = (PilhaDeFrames *)malloc(sizeof(PilhaDeFrames));
    frame = (Frame *)malloc(sizeof(Frame));
    pf1 = *pilhaFrame;
    *pilhaFrame = pf1->prox;
    frame = pf1->dado;
    free(pf1);
    return frame;
}

void DestruirFrame(Frame *frame){
    desalocaPilhaOperandos(frame->pilhaOperandos);
    desalocaListaArrays(frame->listaArrays);
    desalocaListaObjetos(frame->listaObjetos);
    free(frame->VetorVariaveisLocais);
    free(frame);
}

void desalocaPilhaFrames(PilhaDeFrames **pilhaFrames){
    PilhaDeFrames *pf1;
    while (*pilhaFrames != NULL){
        pf1 = *pilhaFrames;
        *pilhaFrames = pf1->prox;
        DestruirFrame(pf1->dado);
        free(pf1);
    }
    return;
}
