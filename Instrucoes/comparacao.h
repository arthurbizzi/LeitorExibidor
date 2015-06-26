/**
* @file cast.h
* @author Kelvin
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de comparação.
*/

#include "../Pilha/pilha_operandos.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"
#include <math.h>


/**
*   @fn void i_lcmp(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_lcmp(Frame* frame);

/**
*   @fn void i_fcmpl(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_fcmpl(Frame* frame);

/**
*   @fn void i_fcmpg(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_fcmpg(Frame* frame);

/**
*   @fn void i_dcmpl(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_dcmpl(Frame* frame);

/**
*   @fn void i_dcmpg(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_dcmpg(Frame* frame);

