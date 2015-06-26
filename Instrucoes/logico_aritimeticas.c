#include "logico_aritimeticas.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


void i_iadd(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1+value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_ladd(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1+value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_fadd(Frame* frame){
    u4 result;
    u4 aux2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 aux1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float fvalue2;
    float fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u4));
    memcpy(&fvalue1,&aux1,sizeof(u4));
	float fresult = fvalue1+fvalue2;
	memcpy(&result,&fresult,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_dadd(Frame* frame){

    u8 result;
    u8 aux2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 aux1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double fvalue2;
    double fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u8));
    memcpy(&fvalue1,&aux1,sizeof(u8));
	double fresult = fvalue1+fvalue2;
	memcpy(&result,&fresult,sizeof(u8));
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);

}

void i_isub(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1-value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lsub(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1-value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_fsub(Frame* frame){
    u4 result;
    u4 aux2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 aux1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float fvalue2;
    float fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u4));
    memcpy(&fvalue1,&aux1,sizeof(u4));
	float fresult = fvalue1+fvalue2;
	memcpy(&result,&fresult,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_dsub(Frame* frame){
	u8 result;
    u8 aux2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 aux1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double fvalue2;
    double fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u8));
    memcpy(&fvalue1,&aux1,sizeof(u8));
	double fresult = fvalue1-fvalue2;
	memcpy(&result,&fresult,sizeof(u8));
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_imul(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1*value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lmul(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1*value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_fmul(Frame* frame){
    u4 result;
    u4 aux2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 aux1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float fvalue2;
    float fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u4));
    memcpy(&fvalue1,&aux1,sizeof(u4));
	float fresult = fvalue1*fvalue2;
	memcpy(&result,&fresult,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_dmul(Frame* frame){
	u8 result;
    u8 aux2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 aux1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double fvalue2;
    double fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u8));
    memcpy(&fvalue1,&aux1,sizeof(u8));
	double fresult = fvalue1*fvalue2;
	memcpy(&result,&fresult,sizeof(u8));
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_idiv(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1/value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_ldiv(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1/value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}


void i_fdiv(Frame* frame){
    u4 result;
    u4 aux2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 aux1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float fvalue2;
    float fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u4));
    memcpy(&fvalue1,&aux1,sizeof(u4));
	float fresult = fvalue1/fvalue2;
	memcpy(&result,&fresult,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_ddiv(Frame* frame){
   u8 result;
    u8 aux2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 aux1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double fvalue2;
    double fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u8));
    memcpy(&fvalue1,&aux1,sizeof(u8));
	double fresult = fvalue1/fvalue2;
	memcpy(&result,&fresult,sizeof(u8));
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_irem(Frame* frame){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	u4 result = value1%value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lrem(Frame* frame){
    u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	u8 result = value1%value2;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_frem(Frame* frame){
    u4 result;
    u4 aux2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 aux1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float fvalue2;
    float fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u4));
    memcpy(&fvalue1,&aux1,sizeof(u4));
	float fresult = fmod(fvalue1,fvalue2);
	memcpy(&result,&fresult,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_drem(Frame* frame){
   u8 result;
    u8 aux2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 aux1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double fvalue2;
    double fvalue1;
    memcpy(&fvalue2,&aux2,sizeof(u8));
    memcpy(&fvalue1,&aux1,sizeof(u8));
	double fresult = fmod(fvalue1,fvalue2);
	memcpy(&result,&fresult,sizeof(u8));
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_ineg(Frame* frame){
    u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = ~value;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lneg(Frame* frame){
    u8 value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 result = ~value;
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_fneg(Frame* frame){
	u4 result;
    u4 aux = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    float fvalue;
    memcpy(&fvalue,&aux,sizeof(u4));
	float fresult = fvalue*(-1);
	memcpy(&result,&fresult,sizeof(u4));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_dneg(Frame* frame){
	u8 result;
    u8 aux = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    double fvalue;
    memcpy(&fvalue,&aux,sizeof(u8));
	double fresult = fvalue*(-1);
	memcpy(&result,&fresult,sizeof(u8));
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_ishl(Frame* frame){
	u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    u4 signal = value >> 31;
    value = (value << shifter);
    if(signal == 0){
		value &= 0x7FFFFFFF;
    }else{
    	value |= 0x80000000;
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_lshl(Frame* frame){
	u8 value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    u4 signal = value >> 63;
    value = (value << shifter);
    if(signal == 0){
		value &= 0x7FFFFFFFFFFFFFFF;
    }else{
    	value |= 0x800000000000000;
    }
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}

void i_ishr(Frame* frame){
	u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    u4 signal = value >> 31;
    value &= 0x7FFFFFFF;
    value = (value >> shifter);
    if(signal == 0){
		value &= 0x7FFFFFFF;
    }else{
    	value |= 0x80000000;
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_lshr(Frame* frame){
	u8 value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    u4 signal = value >> 63;
    value &= 0x7FFFFFFFFFFFFFFF;
    value = (value >> shifter);
    if(signal == 0){
		value &= 0x7FFFFFFFFFFFFFFF;
    }else{
    	value |= 0x800000000000000;
    }
    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}

void i_iushr(Frame* frame){
	u4 value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    value = (value >> shifter);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_lushr(Frame* frame){
	u8 value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    value = (value >> shifter);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&value);
}

void i_iand(Frame* frame){
	u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = (value1 & value2);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_land(Frame* frame){
	u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 result = (value1 & value2);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_ior(Frame* frame){
	u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = (value1 | value2);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lor(Frame* frame){
	u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 result = (value1 | value2);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_ixor(Frame* frame){
	u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = (value1 ^ value2);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lxor(Frame* frame){
	u8 value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 result = (value1 ^ value2);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_iinc(Frame* frame, u1 index, u1 inc){
	frame->VetorVariaveisLocais[index] += inc;
}
