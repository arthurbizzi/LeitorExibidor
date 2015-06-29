#include "comparacao.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


void i_lcmp(Frame* frame){
	frame->pc++;
	u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void i_fcmpl(Frame* frame){
	frame->pc++;
	float value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	float value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void i_fcmpg(Frame* frame){
	frame->pc++;
	float value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	float value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 > value2){
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void i_dcmpl(Frame* frame){
	frame->pc++;
	double value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	double value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void i_dcmpg(Frame* frame){
	frame->pc++;
	double value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	double value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 > value2){
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}
