#include "main.h"

typedef struct pilhadeoperandos {
    u4 dado;
    struct pilhadeoperandos *prox;
} PilhaDeOperandos;

void InicializaPilhaDeOperandos(PilhaDeOperandos **pilhaOperandos);
u1 PilhaDeOperandosVazia(PilhaDeOperandos *pilhaOperandos);
void EmpilhaOperando32bits(PilhaDeOperandos **pilhaOperandos, u4 dado);
void EmpilhaOperando64bits(PilhaDeOperandos **pilhaOperandos, l1 dado);
u4 DesempilhaOperando32bits(PilhaDeOperandos **pilhaOperandos);
l1 DesempilhaOperando64bits(PilhaDeOperandos **pilhaOperandos);
void desalocaPilhaOperandos(PilhaDeOperandos **pilhaOperandos);
