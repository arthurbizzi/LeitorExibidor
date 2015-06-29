#include "load.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>

void i_iload(Frame* frame,u1 index)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[index]));
}

void i_lload(Frame* frame,u1 index)
{
	frame->pc++;
	u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_fload(Frame* frame,u1 index)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[index]));
}

void i_dload(Frame* frame,u1 index)
{
	frame->pc++;
	u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_aload(Frame* frame,u1 index)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[index]));
}

void i_iload_0(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[0]));
}

void i_iload_1(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
}

void i_iload_2(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
}

void i_iload_3(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
}

void i_lload_0(Frame* frame)
{
	frame->pc++;
	u4 index = 0;
	u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_lload_1(Frame* frame)
{
	frame->pc++;
  u4 index = 1;
u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_lload_2(Frame* frame)
{
	frame->pc++;
    u4 index = 2;
	u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_lload_3(Frame* frame)
{
	frame->pc++;
    u4 index = 3;
u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_fload_0(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[0]));
}

void i_fload_1(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
}

void i_fload_2(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
}

void i_fload_3(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
}

void i_dload_0(Frame* frame)
{
	frame->pc++;
    u4 index = 0;
u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_dload_1(Frame* frame)
{
	frame->pc++;
    u4 index = 1;
u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_dload_2(Frame* frame)
{
	frame->pc++;
    u4 index = 2;
u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_dload_3(Frame* frame)
{
	frame->pc++;
	u4 index = 3;
u8 result = (((u8)frame->VetorVariaveisLocais[index]) << 32) |(frame->VetorVariaveisLocais[index+1]);
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}


void i_aload_0(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[0]));
}

void i_aload_1(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[1]));
}

void i_aload_2(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[2]));
}

void i_aload_3(Frame* frame)
{
	frame->pc++;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[3]));
}

void i_iaload(Frame* frame)
{
	frame->pc++;
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 ref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4* arrayRef = (u4*)(uintptr_t) ref;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(arrayRef[index]));
}

void i_laload(Frame* frame)
{
	frame->pc++;
	u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 ref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8* arrayRef = (u8*)(uintptr_t) ref;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&(arrayRef[index]));
}

void i_faload(Frame* frame)
{
	frame->pc++;
	u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 ref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4* arrayRef = (u4*)(uintptr_t) ref;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(arrayRef[index]));
}

void i_daload(Frame* frame)
{
	frame->pc++;
   	u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 ref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8* arrayRef = (u8*)(uintptr_t) ref;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&(arrayRef[index]));
}

void i_aaload(Frame* frame)
{
	frame->pc++;
	u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 ref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4* arrayRef = (u4*)(uintptr_t) ref;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(arrayRef[index]));
}

void i_baload(Frame* frame)
{
	frame->pc++;
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 ref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u1* arrayRef = (u1*)(uintptr_t) ref;
    u4 result= arrayRef[index];
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_caload(Frame* frame)
{
	frame->pc++;
    u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 ref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u2* arrayRef = (u2*)(uintptr_t) ref;
    u4 result= arrayRef[index];
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_saload(Frame* frame)
{
	frame->pc++;
 u4 index =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 ref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u2* arrayRef = (u2*)(uintptr_t) ref;
    u4 result= arrayRef[index];
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}
