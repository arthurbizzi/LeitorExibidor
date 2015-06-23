/**
* @file area_metodos.h
* @author Bruno
* @brief .
*/

#ifndef AREA_METODOS_H
#define AREA_METODOS_H

#include "../main.h"
#include "../lista_arrays_objetos_classes.h"
#include "../ClassLoader/classloader.h"
#include "../Pilha/pilha_frames.h"

#define ERRO_INSTRUCAO 30

/**
*   @fn method_info* recupera_main(ClassFile *classe)
*   @brief Funcao que recupera o metodo main de uma classe.
*   @param classe Classe carregada.
*   @return Retorna o metodo main, se encontrado, ou NULL, caso contrario.
*/
method_info* recupera_main(ClassFile *classe);

/**
*   @fn void executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames)
*   @brief Funcao que executa um metodo de uma classe.
*   @param metodo Metodo a ser executado.
*   @param classe Classe que contem o metodo.
*   @param pilha_de_frames Pilha que armazena os frames.
*/
void executa_metodo(method_info *metodo, ClassFile *classe, struct pilhaframes *pilha_de_frames);

/**
*   @fn executa_instrucoes(method_info *metodo, Frame *frame)
*   @brief Funcao que executa as instrucoes de um metodo.
*   @param metodo Metodo a ser executado.
*   @param frame Frame atual.
*   @return Status de execucao.
*/
int executa_instrucoes(method_info *metodo, struct frame *frame);

int executa_instrucao(u4 opcode);

#endif // AREA_METODOS_H
