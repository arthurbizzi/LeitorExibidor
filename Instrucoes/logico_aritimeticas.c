#include "logico_aritimeticas.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


void i_iadd(Frame* frame){

    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	int32_t result = value1+value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_ladd(Frame* frame){

    int64_t value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    int64_t value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	int64_t result = value1+value2;
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

    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	int32_t result = value1-value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lsub(Frame* frame){

    int64_t value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    int64_t value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	int64_t result = value1-value2;
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

    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	int32_t result = value1*value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lmul(Frame* frame){

    int64_t value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    int64_t value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	int64_t result = value1*value2;
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

    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	int32_t result = value1/value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_ldiv(Frame* frame){

    int32_t value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	int32_t result = value1/value2;
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

    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	int32_t result = value1%value2;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lrem(Frame* frame){

    int64_t value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    int64_t value1 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
	int64_t result = value1%value2;
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
	float fresult = fmodf(fvalue1,fvalue2);
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

    int32_t value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t result = ~value;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lneg(Frame* frame){

    int64_t value = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    int64_t result = ~value;
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

	int32_t value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    value = (value << shifter);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_lshl(Frame* frame){

	int64_t value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    value = (value << shifter);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_ishr(Frame* frame){

	int32_t value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    value = (value >> shifter);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
}

void i_lshr(Frame* frame){

	int64_t value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 shifter = DesempilhaOperando32bits(&(frame->pilhaDeOperandos)) & 0x1F;
    value = (value >> shifter);
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&value);
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

	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = (value1 & value2);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_land(Frame* frame){

	u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 result = (value1 & value2);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_ior(Frame* frame){

	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = (value1 | value2);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lor(Frame* frame){

	u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 result = (value1 | value2);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_ixor(Frame* frame){

	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 result = (value1 ^ value2);

    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&result);
}

void i_lxor(Frame* frame){

	u8 value2 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    u8 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u8 result = (value1 ^ value2);

    EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&result);
}

void i_iinc(Frame* frame, u1 index, u1 inc){

	frame->VetorVariaveisLocais[index] += inc;
}
