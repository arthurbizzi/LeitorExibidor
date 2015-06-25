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
#include "Heap/heap.h"
#include "ClassLoader/carregamento.h"
#include "ClassLoader/classloader.h"
#include "ClassLoader/impressao.h"
#include "Pilha/pilha_frames.h"
#include "Pilha/pilha_operandos.h"
#include "AreaMetodos/area_metodos.h"
#include "Instrucoes/bridge_arquivosinstrucoes.h"

#define SUCESSO 0
#define ERRO_ARQUIVO -10 /// Arquivo nao encontrado.
#define ERRO_EXECUCAO -11 /// Execucao abortada.
#define ERRO_MAIN -12 /// Metodo main nao encontrado.

/**
*   @fn int main(int argc, char **argv)
*   @brief Funcao que dirige a execucao do programa.
*   @param argc Quantidade de argumentos passados pela linha de comando.
*   @param argv Argumentos passados pela linha de comando.
*   @return Status de execucao.
*/
int main(int argc, char **argv);

/**
*   @fn int verifica_impressao(ClassFile *classe, char opcao)
*   @brief Funcao que verifica como a classe deve ser exibida. O modificador e uma variavel global.
*   @param classe Classe que deve ser impressa (ou nao).
*   @param opcao Opcao de impressao.
*   @return Status de execucao.
*/
int verifica_impressao(ClassFile *classe, char opcao);

/**
*   @fn int executa_programa(ClassFile *classe)
*   @brief Funcao que executa o programa a partir do metodo main da primeira classe carregada.
*   @param classe Primeira classe carregada. Deve conter um metodo main.
*   @return Status de execucao.
*/
int executa_programa(ClassFile *classe);

#endif // MAIN_H
