#include "cast.h"


void i_i2l(Frame* frame){
	u8 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_i2f(Frame* frame){
	float result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_i2d(Frame* frame){
	double result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_l2i(Frame* frame){
	u4 result = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_l2f(Frame* frame){
	float result = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_l2d(Frame* frame){
	double result = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_f2i(Frame* frame){
	u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_f2l(Frame* frame){
	u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_f2d(Frame* frame){
	double result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_d2i(Frame* frame){
	double op = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u4 result = op;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_d2l(Frame* frame){
	double op = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = op;
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_d2f(Frame* frame){
	double op = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	float result = op;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_i2b(Frame* frame){
	u1 result =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 valor = result;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
}


void i_i2c(Frame* frame){
	u2 result =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 valor = result;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
}


void i_i2s(Frame* frame){
	u2 result =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 valor = result;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
}
