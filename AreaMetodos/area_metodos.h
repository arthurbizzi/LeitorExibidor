/**
* @file area_metodos.h
* @author Bruno
* @brief Arquivo com definicoes de prototipos das funcoes relativas a area de metodos.
*/

#include "../main.h"
#include "../Pilha/pilha_frames.h"

#ifndef AREA_METODOS_H
#define AREA_METODOS_H

#define ERRO_INSTRUCAO 30

/**
*   @fn method_info* recupera_metodo(ClassFile *classe, char *nome_metodo)
*   @brief Funcao que recupera um metodo main de uma classe.
*   @param classe Classe carregada.
*	@param nome_metodo Nome do metodo a ser recuperado.
*   @return Metodo correspondente a nome_metodo, se encontrado, NULL, caso contrario.
*/
method_info* recupera_metodo(ClassFile *classe, char *nome_metodo);

/**
*   @fn int executa_inits(ClassFile *classe, PilhaDeFrames *pilha_de_frames, Heap *heap)
*   @brief Funcao que executa os metodos inicializadores de uma classe.
*   @param classe Classe carregada.
*	@param pilha_de_frames Pilha de frames atual.
*	@param heap Heap do programa.
*   @return Status de execucao.
*/
int executa_init(ClassFile *classe, PilhaDeFrames *pilha_de_frames, Heap *heap);

/**
*   @fn void prepara_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames **pilha_de_frames, Heap **heap)
*   @brief Funcao que prepara um metodo de uma classe.
*   @param metodo Metodo a ser preparado.
*   @param classe Classe que contem o metodo.
*   @param pilha_de_frames Pilha que armazena os frames.
*   @param heap Heap do programa.
*/
void prepara_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames **pilha_de_frames, Heap **heap);

/**
*   @fn int executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames)
*   @brief Funcao que executa um metodo de uma classe.
*   @param metodo Metodo a ser executado.
*   @param classe Classe que contem o metodo.
*   @param pilha_de_frames Pilha que armazena os frames.
*   @return Status de execucao.
*/
int executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames);

/**
*   @fn int executa_instrucoes(method_info *metodo, Frame *frame)
*   @brief Funcao que executa cada instrucao de um metodo.
*   @param metodo Metodo a ser executado.
*   @param frame Frame atual.
*   @return Status de execucao.
*/
int executa_instrucoes(method_info *metodo, Frame *frame);

/**
*   @fn int executa_instrucao(u4 opcode)
*   @brief Funcao que executa uma instrucao especifica.
*   @param opcode Opcode da instrucao a ser executada.
*   @return Status de execucao.
*/
int executa_instrucao(u4 opcode);

/**
*   @fn void decodifica_geral(Frame *frame)
*   @brief Funcao que decodifica instrucoes com assinaturas diferenciadas.
*   @param frame Frame atual.
*/
void decodifica_geral(Frame *frame);

/**
*   @fn void decodifica_load(Frame *frame)
*   @brief Funcao que decodifica instrucoes do tipo load.
*   @param frame Frame atual.
*/
void decodifica_load(Frame *frame);

/**
*   @fn void decodifica_store(Frame *frame)
*   @brief Funcao que decodifica instrucoes do tipo store.
*   @param frame Frame atual.
*/
void decodifica_store(Frame *frame);

/**
*   @fn void decodifica_if(Frame *frame)
*   @brief Funcao que decodifica instrucoes do tipo if.
*   @param frame Frame atual.
*/
void decodifica_if(Frame *frame);

/**
*   @fn void carrega_instrucoes()
*   @brief Funcao que carrega o vetor de instrucoes.
*/
void carrega_instrucoes();


#endif // AREA_METODOS_H
