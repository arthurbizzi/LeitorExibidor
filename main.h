#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "ClassLoader/carregamento.h"
#include "ClassLoader/classloader.h"
#include "ClassLoader/impressao.h"
#include "Pilha/pilha_frames.h"
#include "Pilha/pilha_operandos.h"

#define SUCESSO 0
#define ERRO_ARQUIVO -1
#define ERRO_EXECUCAO -2

/**
*   @fn int main(int argc, char **argv)
*   @brief Funcao que dirige a execucao do programa
*   @param argc Quantidade de argumentos passados pela linha de comando
*   @param argv Argumentos passados pela linha de comando
*   @return Status de execução: SUCESSO, ERRO_MAGIC, ERRO_VERSION ou ERRO_ARQUIVO
*/
int main(int argc, char **argv);

#endif // MAIN_H
