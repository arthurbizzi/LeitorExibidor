/**
* @file classloader.c
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo que implementa o carregador de classes.
*/

#include "classloader.h"
#include "carregamento.h"

char *diretorio = NULL;
int raiz = 1;

int carrega_classe(char *nome_arquivo, ClassFile *classe)
{
    FILE *arq_classe;
    char *caminho_arquivo = NULL;

    diretorio = recupera_diretorio(nome_arquivo);

    if(raiz) {
        strcpy(caminho_arquivo, nome_arquivo);
    }
    else {
        strcpy(caminho_arquivo, diretorio);
        strcat(caminho_arquivo, nome_arquivo);
    }

    if(!(arq_classe = fopen(caminho_arquivo, "rb")))
    {
        printf("ERRO: arquivo \"%s\" nao existe em \"%s\".\n", nome_arquivo, diretorio);
        return ERRO_ARQUIVO;
    }
    /* Carregamento do Magic Number e da versao, juntamente com suas verificacoes */
    switch(carrega_header(arq_classe, classe))
    {
    case ERRO_MAGIC:
        printf("ERRO: magic number invalido.\n");
        fclose(arq_classe);
        return ERRO_MAGIC;
    case ERRO_VERSION:
        printf("ERRO: versao invalida.\n");
        fclose(arq_classe);
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

    if(verifica_match(classe, nome_arquivo) == ERRO_MATCHING)
    {
        printf("ERRO: nome do arquivo e diferente do nome da classe.\n");
        fclose(arq_classe);
        return ERRO_MATCHING;
    }

    fclose(arq_classe);
    return SUCESSO;
}

char* recupera_diretorio(char *caminho) {
    int tamanho = strlen(caminho), barras = 0;
    char *temp = (char *) malloc(tamanho * sizeof(char));

    for(int i = 0; i < tamanho; i++) {
        if(caminho[i] == '/')
            barras++;
    }

    if(barras > 0) {
        int i = 0;
        raiz = 0;
        while(barras > 0) {
            temp[i] = caminho[i];
            if(caminho[i] == '/')
                barras--;
            i++;
        }
        temp[i] = '\0';
    }

    return temp;
}
