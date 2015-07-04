#include "const.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>

void i_aconst_null(Frame* frame)
{

    u4 *value = (u4*)malloc(sizeof(u4));
    *value = 0;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),value);
    return;
};

void i_iconst_m1(Frame* frame)
{
	int32_t f = -1;
    u4 value;
    memcpy(&value,&f,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_iconst_0(Frame* frame)
{
	int32_t f = 0;
    u4 value;
    memcpy(&value,&f,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_iconst_1(Frame* frame)
{

	int32_t f = 1;
    u4 value;
    memcpy(&value,&f,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_iconst_2(Frame* frame)
{

	int32_t f = 2;
    u4 value;
    memcpy(&value,&f,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_iconst_3(Frame* frame)
{

 	int32_t f = 3;
    u4 value;
    memcpy(&value,&f,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_iconst_4(Frame* frame)
{

	int32_t f = 4;
    u4 value;
    memcpy(&value,&f,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_iconst_5(Frame* frame)
{

	int32_t f = 5;
    u4 value;
    memcpy(&value,&f,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}
void i_lconst_0(Frame* frame)
{

    u8 value =  0;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}

void i_lconst_1(Frame* frame)
{

    u8 value =  1;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}

void i_fconst_0(Frame* frame)
{
	float value1 = 0.0;
    u4 value;
    memcpy(&value,&value1,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_fconst_1(Frame* frame)
{

	float value1 = 1.0;
    u4 value;
    memcpy(&value,&value1,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_fconst_2(Frame* frame)
{
	float value1 = 2.0;
    u4 value;
    memcpy(&value,&value1,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_dconst_0(Frame* frame)
{
	double value1 = 0.0;
    u8 value;
    memcpy(&value,&value1,sizeof(u8));
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}

void i_dconst_1(Frame* frame)
{
	double value1 = 1.0;
    u8 value;
    memcpy(&value,&value1,sizeof(u8));
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}
