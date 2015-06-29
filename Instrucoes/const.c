#include "const.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>

void i_aconst_null(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 0;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
    return;
};

void i_iconst_m1(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = -1;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void i_iconst_0(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 0;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void i_iconst_1(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 1;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void i_iconst_2(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void i_iconst_3(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 3;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void i_iconst_4(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 4;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void i_iconst_5(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 5;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}
void i_lconst_0(Frame* frame)
{
	frame->pc++;
    u8 *value = (u8*)malloc(sizeof(u8));
    *value = 0.0;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),value);
}

void i_lconst_1(Frame* frame)
{
	frame->pc++;
    u8 *value = (u8*)malloc(sizeof(u8));
    *value = 1;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),value);
}

void i_fconst_0(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 0.0f;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void i_fconst_1(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 1.0f;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void i_fconst_2(Frame* frame)
{
	frame->pc++;
    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 2.0f;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
}

void i_dconst_0(Frame* frame)
{
	frame->pc++;
    u8 *value = (u8*)malloc(sizeof(u8));
    *value = 0.0d;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),value);
}

void i_dconst_1(Frame* frame)
{
	frame->pc++;
    u8 *value = (u8*)malloc(sizeof(u8));
    *value = 1.0d;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),value);
}
