#include "pop_dup_swap.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>

void i_pop(Frame* frame){

    DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
}

void i_pop2(Frame* frame){

    DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
}

void i_dup(Frame* frame){

    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_dup_x1(Frame* frame){

    u4 valueTop = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_dup_x2(Frame* frame){

    u4 valueTop = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 valuefloor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valuefloor);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valuefloor);
}


void i_dup2(Frame* frame){

    u4 valueTop = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
}

void i_dup2_x1(Frame* frame){

    u4 valueTop = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 valueFloor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueFloor);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueTop);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valueFloor);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}


void i_dup2_x2(Frame* frame){

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

void i_swap(Frame* frame){

    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value2);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value1);
}
