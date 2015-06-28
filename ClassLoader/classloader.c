/**
* @file classloader.c
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo que implementa o carregador de classes.
*/

#include "classloader.h"
#include "carregamento.h"

char *diretorio = NULL;
char *nome_arquivo = NULL;
int raiz = 1;

int carrega_classe(char *nome_completo, ClassFile *classe)
{
    FILE *arq_classe;
    char *caminho_arquivo;

    diretorio = recupera_nome_diretorio(nome_completo);
    nome_arquivo = recupera_nome_arquivo(nome_completo);
    if(raiz) {
        caminho_arquivo = (char *) malloc(strlen(nome_completo) * sizeof(char));
        strcpy(caminho_arquivo, nome_completo);
    }
    else {
        caminho_arquivo = (char *) malloc((strlen(diretorio) + strlen(nome_arquivo)) * sizeof(char));
        strcpy(caminho_arquivo, diretorio);
        strcat(caminho_arquivo, nome_arquivo);
    }
    if(!(arq_classe = fopen(caminho_arquivo, "rb")))
    {
        printf("ERRO: arquivo \"%s\" nao existe em \"%s\".\n", nome_completo, diretorio);
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

char* recupera_nome_diretorio(char *arquivo) {
    int tamanho = strlen(arquivo), barras = 0;
    char *diretorio = (char *) malloc((tamanho + 1) * sizeof(char));

    for(int i = 0; i < tamanho; i++) {
        if(arquivo[i] == '/') // Conta quantas barras existem no endereco do arquivo
            barras++;
    }

    int i = 0;

    if(barras > 0) {
        raiz = 0; // Nao esta na raiz
        while(barras > 0) { // Copia todo o caminho ate o diretorio
            diretorio[i] = arquivo[i];
            if(arquivo[i] == '/')
                barras--;
            i++;
        }
        diretorio[i] = '\0';
    }

    return diretorio;
}

char* recupera_nome_arquivo(char *arquivo) {
    if(raiz) {
        return arquivo;
    }

    int tamanho_diretorio = strlen(diretorio);
    int tamanho_total = strlen(arquivo);
    char *nome_arquivo = (char *) malloc((tamanho_total + 1) * sizeof(char));

    int j = 0;
    for(int i = tamanho_diretorio; i < tamanho_total; i++) {
        nome_arquivo[j] = arquivo[i];
        j++;
    }
    nome_arquivo[j] = '\0';

    return nome_arquivo;
}
