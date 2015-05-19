/***********************************************************************
*    Trabalho da Disciplina Software B�sico, 2015-1
*    Alunos: Bruno Ribeiro das Virgens (11/0111141)
*            Guilherme de Sousa Castro (11/0148746)
*            Kelvin William Moreira Lima (11/0159560)
*
*    Compilar com o comando:
*    gcc main.c -o leitorexibidor.exe
*
*    Chamadas poss�veis:
*    (1) leitorexibidor.exe <arquivo>
*        <arquivo> deve possuir a extens�o (.class).
*    (2) leitorexibidor.exe
*        o nome do arquivo a ser lido ser� pedido pelo programa.
***********************************************************************/
/**
* @file main.c
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo principal da implementa��o do Leitor e Exibidor de arquivos no formato .class
*/

#include "main.h"

int main(int argc, char **argv) {
    char nome_arquivo[21];

    printf("LEITOR E EXIBIDOR DE ARQUIVO EM FORMATO .CLASS\n");
    switch(argc) {
        case 0:
            printf("Digite o nome do arquivo a ser lido, com extensao:\n");
            scanf("%s", nome_arquivo);
            break;
        case 1:
            strcpy(nome_arquivo, argv[1]);
            break;
        default:
            printf("CHAMADA COM NUMERO INCOMPATIVEL DE ARGUMENTOS.\n");
            printf("Digite o nome do arquivo a ser lido, com extensao:\n");
            scanf("%s", nome_arquivo);
    }

    return ler_arquivo(nome_arquivo);
}

int ler_arquivo(const char *nome_arquivo) {
    FILE *arquivo;

    if(!(arquivo = fopen(nome_arquivo, "rb"))) {
        printf("ERRO: arquivo %s nao existe!\n", nome_arquivo);
        return ERRO_ARQUIVO;
    }

    return SUCESSO;
}
