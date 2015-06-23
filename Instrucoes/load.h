#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>

void i_iload(Frame* frame,u1 index, u1 index2);
void i_lload(Frame* frame,u1 index, u1 index2);
void i_fload(Frame* frame,u1 index, u1 index2);
void i_dload(Frame* frame,u1 index, u1 index2);
void i_aload(Frame* frame,u1 index);
void i_iload_0(Frame* frame);
void i_iload_1(Frame* frame);
void i_iload_2(Frame* frame);
void i_iload_3(Frame* frame);
void i_lload_0(Frame* frame);
void i_lload_1(Frame* frame);
void i_lload_2(Frame* frame);
void i_lload_3(Frame* frame);
void i_fload_0(Frame* frame);
void i_fload_1(Frame* frame);
void i_fload_2(Frame* frame);
void i_fload_3(Frame* frame);
void i_dload_0(Frame* frame);
void i_dload_1(Frame* frame);
void i_dload_2(Frame* frame);
void i_dload_3(Frame* frame);
void i_aload_0(Frame* frame,u1 index);
void i_aload_1(Frame* frame,u1 index);
void i_aload_2(Frame* frame,u1 index);
void i_aload_3(Frame* frame,u1 index);
void i_iaload(Frame* frame);
void i_laload(Frame* frame);
void i_faload(Frame* frame);
void i_daload(Frame* frame);
void i_aaload(Frame* frame);
void i_baload(Frame* frame);
void i_caload(Frame* frame);
void i_saload(Frame* frame);

