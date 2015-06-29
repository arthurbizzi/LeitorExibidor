#include "ifs.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


void i_ifeq(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result == 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_ifne(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result != 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_iflt(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result < 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_ifge(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result >= 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_ifgt(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result > 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_ifle(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result <= 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_if_icmpeq(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 == value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_if_icmpne(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 != value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_if_icmplt(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 < value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_if_icmpge(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 >= value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_if_icmpgt(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 > value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_if_icmple(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
     u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 <= value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_if_acmpeq(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 == value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}

void i_if_acmpne(Frame* frame,u1 index1,u1 index2){
	frame->pc++;
	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 != value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += offset;
    }
}
