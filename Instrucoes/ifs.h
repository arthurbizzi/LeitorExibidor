/**
* @file ifs.h
* @author Kelvin
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de jumps condicionais.
*/


#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


/**
*   @fn void i_ifeq(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha um valor, se igual a zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifeq(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_ifne(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha um valor, se diferente de zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifne(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_iflt(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha um valor, se menor que zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_iflt(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_ifge(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha um valor, se maior ou igual a zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifge(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_ifgt(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha um valor, se maior que zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifgt(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_ifle(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha um valor, se menor ou igual a zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifle(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_if_icmpeq(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha dois inteiros, se forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpeq(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_if_icmpne(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha dois inteiros, se não forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpne(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_if_icmplt(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha dois inteiros, se o valor 1 for menor que o valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmplt(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_if_icmpge(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha dois inteiros, se o valor 1 for maior ou igual ao valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpge(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_if_icmpgt(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha dois inteiros, se o valor 1 for maior que valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpgt(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_if_icmple(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha dois inteiros, se o valor 1 for menor ou igual ao valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmple(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_if_acmpeq(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha duas referencias para objetos, se as referências forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_acmpeq(Frame* frame,u1 index1,u1 index2);

/**
*   @fn void i_if_acmpne(Frame* frame, u1 index1, u1 index2)
*   @brief Função que desempilha duas referencias para objetos, se as referências não forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_acmpne(Frame* frame,u1 index1,u1 index2);
