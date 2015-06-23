#include "ifs.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


void i_ifeq(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result == 0){
		frame->pc += (index1<<8)+index2;
    }
}

void i_ifne(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result != 0){
		frame->pc += (index1<<8)+index2;
    }
}

void i_iflt(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result < 0){
		frame->pc += (index1<<8)+index2;
    }
}

void i_ifge(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result >= 0){
		frame->pc += (index1<<8)+index2;
    }
}

void i_ifgt(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result > 0){
		frame->pc += (index1<<8)+index2;
    }
}

void i_ifle(Frame* frame,u1 index1,u2 index2){
    u4 result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(result <= 0){
		frame->pc += (index1<<8)+index2;
    }
}

void i_if_icmpeq(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 == value2){
		frame->pc += (index1<<8)+index2;
    }
}

void i_if_icmpne(Frame* frame,u1 index1,u2 index2){
	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 != value2){
		frame->pc += (index1<<8)+index2;
    }
}

void i_if_icmplt(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 < value2){
		frame->pc += (index1<<8)+index2;
    }
}

void i_if_icmpge(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 >= value2){
		frame->pc += (index1<<8)+index2;
    }
}

void i_if_icmpgt(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 > value2){
		frame->pc += (index1<<8)+index2;
    }
}

void i_if_icmple(Frame* frame,u1 index1,u2 index2){
     u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 <= value2){
		frame->pc += (index1<<8)+index2;
    }
}

void i_if_acmpeq(Frame* frame,u1 index1,u2 index2){
    u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 == value2){
		frame->pc += (index1<<8)+index2;
    }
}

void i_if_acmpne(Frame* frame,u1 index1,u2 index2){
	u4 value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    u4 value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(value1 != value2){
		frame->pc += (index1<<8)+index2;
    }
}
