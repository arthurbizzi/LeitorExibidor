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
    FILE *arq_classe;
    ClassFile *classe = (ClassFile *) malloc(sizeof(ClassFile));
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
    if(!(arq_classe = fopen(nome_arquivo, "rb"))) {
        printf("ERRO: arquivo \"%s\" nao existe.\n", nome_arquivo);
        return ERRO_ARQUIVO;
    }
    if(carrega_header(arq_classe, classe) == ERRO_MAGIC) {
        printf("ERRO: magic number invalido.\n");
        return ERRO_MAGIC;
    }
    return SUCESSO;
}

int carrega_header(FILE *arquivo, ClassFile *classe) {
    classe->magic = le_u4(arquivo);
    if(classe->magic != MAGIC_NUMBER)
        return ERRO_MAGIC;
    return SUCESSO;
}

u1 le_u1(FILE *arquivo) {
    u1 valor;
    fread(&valor, sizeof(u1), 1, arquivo);
    return valor;
}

u2 le_u2(FILE *arquivo) {
    u2 valor;
    fread(&valor, sizeof(u2), 1, arquivo);
    return valor;
}

u4 le_u4(FILE *arquivo) {
    u4 valor;
    fread(&valor, sizeof(u4), 1, arquivo);
    return valor;
}
