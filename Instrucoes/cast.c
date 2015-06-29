#include "cast.h"


void i_i2l(Frame* frame){
	frame->pc++;
	u8 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_i2f(Frame* frame){
	frame->pc++;
	u4 aux = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	float aux2 = (float)aux;
	u4 result;
	memcpy(&result,&aux2,sizeof(u4));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_i2d(Frame* frame){
	frame->pc++;
	u4 aux = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	double aux2 = (double)aux;
	u8 result;
	memcpy(&result,&aux2,sizeof(u8));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);

}

void i_l2i(Frame* frame){
	frame->pc++;
	u4 result = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_l2f(Frame* frame){
	frame->pc++;
	u8 aux = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	double aux2;
	memcpy(&aux2,&aux,sizeof(u8));
	float aux3 = (float)aux2;
	u4 result;
	memcpy(&result,&aux3,sizeof(u4));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_l2d(Frame* frame){
	frame->pc++;
	u8 aux = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	double aux2 = (double)aux;
	u8 result;
	memcpy(&result,&aux2,sizeof(u8));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_f2i(Frame* frame){
	frame->pc++;
	u4 aux = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	float aux2;
	memcpy(&aux2,&aux,sizeof(u4));
	u4 result = aux2;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_f2l(Frame* frame){
	frame->pc++;
	u4 aux = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	float aux2;
	memcpy(&aux2,&aux,sizeof(u4));
	u8 result = aux2;
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_f2d(Frame* frame){
	frame->pc++;
	u4 aux = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	float aux2;
	memcpy(&aux2,&aux,sizeof(u4));
	double aux3 = aux2;
	u8 result;
	memcpy(&result,&aux3,sizeof(u8));
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_d2i(Frame* frame){
	frame->pc++;
	u8 aux = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	double aux2;
	memcpy(&aux2,&aux,sizeof(u8));
	u4 result = aux2;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_d2l(Frame* frame){
	frame->pc++;
	u8 aux = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	double aux2;
	memcpy(&aux2,&aux,sizeof(u8));
	u8 result = aux2;
	EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_d2f(Frame* frame){
	frame->pc++;
	double aux = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	float aux2 = aux;
	u4 result;
	memcpy(&result,&aux2,sizeof(u4));
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_i2b(Frame* frame){
	frame->pc++;
	u4 aux = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u1 aux2 = (u1)aux;
	u4 result = aux2;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}


void i_i2c(Frame* frame){
	frame->pc++;
	u4 aux =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u2 aux2 = (u2)aux;
	u4 result = aux2;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}


void i_i2s(Frame* frame){
	frame->pc++;
	u4 aux =  DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u2 aux2 = (u2)aux;
	u4 result = aux2;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}
