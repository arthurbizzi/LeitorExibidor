/**
* @file main.c
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo principal da implementacao do Leitor e Exibidor de arquivos no formato .class.
*
*    Trabalho da Disciplina Software Basico, 2015-1
*    Alunos: Bruno Ribeiro das Virgens (11/0111141)
*            Guilherme de Sousa Castro (11/0148746)
*            Kelvin William Moreira Lima (11/0159560)
*
*    Compilar com o comando:
*    gcc -std=c99 main.c imprime.c carregamento.c -o leitorexibidor.exe
*    Ou simplesmente com a IDE DevC++
*
*    Chamar com um dos comandos:
*    leitorexibidor.exe
*       Tanto o arquivo da classe quanto o arquivo do relatorio serao pedidos ao usuario
*    leitorexibidor.exe <arquivo da classe>
*       Nao sera gerado o arquivo do relatorio (somente impressao na tela)
*    leitorexibidor.exe <arquivo da classe> <arquivo do relatorio>
*       Esta chamada gerará relatório em arquivo e na tela.
*
*    Observacao: o arquivo "mapa.txt" deve estar na pasta dos codigos-fonte.
*/

#include "classloader.h"
#include "carregamento.h"

int carrega_classe(char *nome_arquivo, ClassFile *classe) {
    FILE *arq_classe;

    if(!(arq_classe = fopen(nome_arquivo, "rb"))) {
        printf("ERRO: arquivo \"%s\" nao existe.\n", nome_arquivo);
        return ERRO_ARQUIVO;
    }
    /* Carregamento do Magic Number e da versao, juntamente com suas verificacoes */
    switch(carrega_header(arq_classe, classe)) {
        case ERRO_MAGIC:
            printf("ERRO: magic number invalido.\n");
            return ERRO_MAGIC;
        case ERRO_VERSION:
            printf("ERRO: versao invalida.\n");
            return ERRO_VERSION;
        default:
            break;
    }

    /* Carregamento dos demais itens */
    carrega_constantpool(arq_classe, classe);
    carrega_flagseclasses(arq_classe, classe);
    carrega_interfaces(arq_classe, classe);
    carrega_fields(arq_classe, classe);
    carrega_methods(arq_classe, classe);
    carrega_attributes(arq_classe, classe);

    if(verifica_match(classe, nome_arquivo) == ERRO_MATCHING) {
        printf("ERRO: nome do arquivo e diferente do nome da classe.\n");
        return ERRO_MATCHING;
    }

    fclose(arq_classe);
    return SUCESSO;
}
