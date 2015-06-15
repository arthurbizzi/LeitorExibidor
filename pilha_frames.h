#include "main.h"
#include "pilha_operandos.h"

typedef struct frame {
    method_info         *method;
    u4                  pc;
    PilhaDeOperandos    *pilhaOperandos;
    u4                  TamanhoVetorVariaveisLocais;
    u4                  *VetorVariaveisLocais;
    u2                  constant_pool_count;
    cp_info             *constant_pool;
    //listaArrays         *listaArrays;
    //listaObjetos        *listaObjetos;
    u4                  returAddress;
}Frame;

typedef struct pilhaframes{
    Frame *dado;
    struct pilhaframes *prox;
}PilhaDeFrames;

Frame *ConstruirFrame(ClassFile *classe, method_info *method);
void InicializaPilhaDeFrames(PilhaDeFrames **pilhaFrames);
u1 PilhaDeFramesVazia(PilhaDeFrames *pilhaFrame);
void EmpilhaFrame(PilhaDeFrames **pilhaFrame, Frame *frame);
Frame *DesempilhaFrame(PilhaDeFrames **pilhaFrame);
void DestruirFrame(Frame *frame);
void desalocaPilhaFrames(PilhaDeFrames **pilhaFrames);
