/**
* @file area_metodos.h
* @author Bruno
* @brief .
*/


#include "../main.h"
#include "../Heap/lista_arrays_objetos_classes.h"
#include "../Pilha/pilha_frames.h"
#include "../ClassLoader/classloader.h"

#ifndef AREA_METODOS_H
#define AREA_METODOS_H


#define ERRO_INSTRUCAO 30

/**
*   @fn method_info* recupera_main(ClassFile *classe)
*   @brief Funcao que recupera o metodo main de uma classe.
*   @param classe Classe carregada.
*   @return Retorna o metodo main, se encontrado, ou NULL, caso contrario.
*/
method_info* recupera_main(ClassFile *classe);

/**
*   @fn int executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames)
*   @brief Funcao que executa um metodo de uma classe.
*   @param metodo Metodo a ser executado.
*   @param classe Classe que contem o metodo.
*   @param pilha_de_frames Pilha que armazena os frames.
*   @return
*/
int executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames);

/**
*   @fn int executa_instrucoes(method_info *metodo, Frame *frame)
*   @brief Funcao que executa as instrucoes de um metodo.
*   @param metodo Metodo a ser executado.
*   @param frame Frame atual.
*   @return Status de execucao.
*/
int executa_instrucoes(method_info *metodo, Frame *frame);

/**
*   @fn int executa_instrucao(u4 opcode)
*   @brief Funcao que executa as instrucoes de um metodo.
*   @param opcode Metodo a ser executado.
*   @return Status de execucao.
*/
int executa_instrucao(u4 opcode);

#endif // AREA_METODOS_H
