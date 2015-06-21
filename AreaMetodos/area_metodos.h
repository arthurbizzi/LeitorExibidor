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
#include "../Pilha/pilha_operandos.h"

/**
*   @fn method_info* recupera_main()
*   @brief Funcao que recupera o metodo main da primeira classe carregada.
*   @return Retorna o metodo main, se encontrado, ou NULL, caso contrario.
*/
method_info* recupera_main();

void prepara_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames);

void executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames);

#endif // AREA_METODOS_H
