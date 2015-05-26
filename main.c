/*
*    Trabalho da Disciplina Software Básico, 2015-1
*    Alunos: Bruno Ribeiro das Virgens (11/0111141)
*            Guilherme de Sousa Castro (11/0148746)
*            Kelvin William Moreira Lima (11/0159560)
*
*    Compilar com o comando:
*    gcc main.c -o leitorexibidor.exe
*
*    Chamar com o comando:
*    leitorexibidor.exe
*/

/**
* @file main.c
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo principal da implementacao do Leitor e Exibidor de arquivos no formato .class
*/

#include "main.h"

int main(int argc, char **argv) {
    FILE *arq_class;
    char nome_arquivo[21];

    printf("LEITOR E EXIBIDOR DE ARQUIVOS EM FORMATO .CLASS\n");
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
    if(!(arq_class = fopen(nome_arquivo, "rb"))) {
        printf("ERRO: arquivo %s nao existe!\n", nome_arquivo);
        return ERRO_ARQUIVO;
    }

    return SUCESSO;
}

int carrega_informacao_geral(FILE *origem) {

    return SUCESSO;
}
