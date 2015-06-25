#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>

void i_istore(Frame* frame, u1 index);
void i_lstore(Frame* frame, u1 index);
void i_fstore(Frame* frame, u1 index);
void i_dstore(Frame* frame, u1 index);
void i_astore(Frame* frame, u1 index);
void i_istore_0(Frame* frame);
void i_istore_1(Frame* frame);
void i_istore_2(Frame* frame);
void i_istore_3(Frame* frame);
void i_lstore_0(Frame* frame);
void i_lstore_1(Frame* frame);
void i_lstore_2(Frame* frame);
void i_lstore_3(Frame* frame);
void i_fstore_0(Frame* frame);
void i_fstore_1(Frame* frame);
void i_fstore_2(Frame* frame);
void i_fstore_3(Frame* frame);
void i_dstore_0(Frame* frame);
void i_dstore_1(Frame* frame);
void i_dstore_2(Frame* frame);
void i_dstore_3(Frame* frame);
void i_astore_0(Frame* frame);
void i_astore_1(Frame* frame);
void i_astore_2(Frame* frame);
void i_astore_3(Frame* frame);
void i_iastore(Frame* frame);
void i_lastore(Frame* frame);
void i_fastore(Frame* frame);
void i_dastore(Frame* frame);
void i_aastore(Frame* frame);
void i_bastore(Frame* frame);
void i_castore(Frame* frame);
void i_sastore(Frame* frame);


