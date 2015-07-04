#include "ifs.h"
#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


void i_ifeq(Frame* frame,u1 index1,u1 index2){

    int32_t result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d == 0? %c\n", result, result == 0 ? 'S' : 'N');
    if(result == 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_ifne(Frame* frame,u1 index1,u1 index2){
    int32_t result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d != 0? %c\n", result, result != 0 ? 'S' : 'N');
    if(result != 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_iflt(Frame* frame,u1 index1,u1 index2){
    int32_t result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d < 0? %c\n", result, result < 0 ? 'S' : 'N');
    if(result < 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_ifge(Frame* frame,u1 index1,u1 index2){
    int32_t result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d >= 0? %c\n", result, result >= 0 ? 'S' : 'N');
    if(result >= 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_ifgt(Frame* frame,u1 index1,u1 index2){
    int32_t result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d > 0? %c\n", result, result > 0 ? 'S' : 'N');
    if(result > 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_ifle(Frame* frame,u1 index1,u1 index2){
    int32_t result = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d <= 0? %c\n", result, result <= 0 ? 'S' : 'N');
    if(result <= 0){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_if_icmpeq(Frame* frame,u1 index1,u1 index2){
    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d == %d? %c\n", value1, value2, value1 == value2 ? 'S' : 'N');
    if(value1 == value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_if_icmpne(Frame* frame,u1 index1,u1 index2){
	int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d != %d? %c\n", value1, value2, value1 != value2 ? 'S' : 'N');
    if(value1 != value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_if_icmplt(Frame* frame,u1 index1,u1 index2){
    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d < %d? %c\n", value1, value2, value1 < value2 ? 'S' : 'N');
    if(value1 < value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_if_icmpge(Frame* frame,u1 index1,u1 index2){
    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d >= %d? %c\n", value1, value2, value1 >= value2 ? 'S' : 'N');
    if(value1 >= value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_if_icmpgt(Frame* frame,u1 index1,u1 index2){
    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d > %d? %c\n", value1, value2, value1 > value2 ? 'S' : 'N');
    if(value1 > value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_if_icmple(Frame* frame,u1 index1,u1 index2){
    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d <= %d? %c\n", value1, value2, value1 <= value2 ? 'S' : 'N');
    if(value1 <= value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_if_acmpeq(Frame* frame,u1 index1,u1 index2){
    int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d == %d? %c\n", value1, value2, value1 == value2 ? 'S' : 'N');
    if(value1 == value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}

void i_if_acmpne(Frame* frame,u1 index1,u1 index2){
	int32_t value2 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    int32_t value1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    #warning DEBUG
    //printf("\t\t%d != %d? %c\n", value1, value2, value1 != value2 ? 'S' : 'N');
    if(value1 != value2){
		int16_t offset = (((u2)index1)<<8)+index2;
		frame->pc += (offset - 3);
    }
}
