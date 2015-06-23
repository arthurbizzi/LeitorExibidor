/**
* @file main.h
* @author Bruno, Guilherme, Kelvin
* @brief
*/

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Heap/lista_arrays_objetos_classes.h"
#include "Heap/heap.h"
#include "ClassLoader/carregamento.h"
#include "ClassLoader/classloader.h"
#include "ClassLoader/impressao.h"
#include "Pilha/pilha_frames.h"
#include "Pilha/pilha_operandos.h"
#include "AreaMetodos/area_metodos.h"

#define SUCESSO 0
#define ERRO_ARQUIVO -10 /// Arquivo nao encontrado.
#define ERRO_EXECUCAO -11 /// Execucao abortada.
#define ERRO_MAIN -12 /// Metodo main nao encontrado.

/**
*   @fn int main(int argc, char **argv)
*   @brief Funcao que dirige a execucao do programa.
*   @param argc Quantidade de argumentos passados pela linha de comando.
*   @param argv Argumentos passados pela linha de comando.
*   @return Status de execução: SUCESSO, ERRO_MAGIC, ERRO_VERSION, ERRO_ARQUIVO, ERRO_EXECUCAO ou ERRO_MAIN.
*/
int main(int argc, char **argv);

/**
*   @fn void verifica_impressao(ClassFile *classe)
*   @brief Funcao que verifica como a classe deve ser exibida. O modificador e uma variavel global.
*   @param classe Classe que deve ser impressa (ou nao).
*   @return Status de execucao: SUCESSO ou ERRO_ARQUIVO.
*/
int verifica_impressao(ClassFile *classe, char opcao);

/**
*   @fn int executa_programa()
*   @brief Funcao que executa o programa a partir do metodo main da primeira classe carregada.
*   @return Retorna o metodo main, se encontrado, ou NULL, caso contrario.
*/
int executa_programa(ClassFile *classe);

#endif // MAIN_H
