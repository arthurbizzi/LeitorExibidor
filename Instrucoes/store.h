#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>

void istore(Frame* frame, u1 index);
void lstore(Frame* frame, u1 index);
void fstore(Frame* frame, u1 index);
void dstore(Frame* frame, u1 index);
void astore(Frame* frame, u1 index);
void istore_0(Frame* frame);
void istore_1(Frame* frame);
void istore_2(Frame* frame);
void istore_3(Frame* frame);
void lstore_0(Frame* frame);
void lstore_1(Frame* frame);
void lstore_2(Frame* frame);
void lstore_3(Frame* frame);
void fstore_0(Frame* frame);
void fstore_1(Frame* frame);
void fstore_2(Frame* frame);
void fstore_3(Frame* frame);
void dstore_0(Frame* frame);
void dstore_1(Frame* frame);
void dstore_2(Frame* frame);
void dstore_3(Frame* frame);
void astore_0(Frame* frame);
void astore_1(Frame* frame);
void astore_2(Frame* frame);
void astore_3(Frame* frame);
void iastore(Frame* frame);
void lastore(Frame* frame);
void fastore(Frame* frame);
void dastore(Frame* frame);
void aastore(Frame* frame);
void bastore(Frame* frame);
void castore(Frame* frame);
void sastore(Frame* frame);


