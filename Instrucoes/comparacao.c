#include "comparacao.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


void i_lcmp(Frame* frame){
	int64_t value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	int64_t value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 > value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void i_fcmpl(Frame* frame){
	u4 f2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 f1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	float value1, value2;
	memcpy(&value1, &f1, sizeof(u4));
	memcpy(&value2, &f2, sizeof(u4));
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 > value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void i_fcmpg(Frame* frame){
	u4 f2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 f1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	float value1, value2;
	memcpy(&value1, &f1, sizeof(u4));
	memcpy(&value2, &f2, sizeof(u4));
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 > value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void i_dcmpl(Frame* frame){
	u8 f2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 f1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	double value1,value2;
	memcpy(&value1, &f1, sizeof(u8));
	memcpy(&value2, &f2, sizeof(u8));
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 > value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}

void i_dcmpg(Frame* frame){
	u8 f2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 f1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = 0;
	double value1, value2;
	memcpy(&value1, &f1, sizeof(u8));
	memcpy(&value2, &f2, sizeof(u8));
	if(value1 == value2){
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 > value2){
		result = 1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else if(value1 < value2){
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}else{
		result = -1;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
	}
}
