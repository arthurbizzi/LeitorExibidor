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
    int header;

    printf("LEITOR E EXIBIDOR DE ARQUIVOS EM FORMATO .CLASS\n");
    switch(argc) {
        case 1:
            printf("Digite o nome do arquivo a ser lido, com extensao:\n");
            scanf("%s", nome_arquivo);
            break;
        case 2:
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
    header = carrega_header(arq_classe, classe);
    if(header == ERRO_MAGIC) {
        printf("ERRO: magic number invalido.\n");
        return ERRO_MAGIC;
    } else if (header == ERRO_VERSION){
        printf("ERRO: versao invalida.\n");
        return ERRO_VERSION;
    }

    return SUCESSO;
}

int carrega_header(FILE *arquivo, ClassFile *classe) {
    classe->magic = le_u4(arquivo);
    if(classe->magic != MAGIC_NUMBER)
        return ERRO_MAGIC;
    classe->minor_version = le_u2(arquivo);
    classe->major_version = le_u2(arquivo);
    if(classe->major_version != VERSION)
        return ERRO_VERSION;
    classe->constant_pool_count = le_u2(arquivo);
    classe->constant_pool = (cp_info *)malloc(sizeof(cp_info)*(classe->constant_pool_count-1));
    for (int i=0;i<(classe->constant_pool_count-1);i++){
        classe->constant_pool[i]->tag = le_u1(arquivo);
        switch (classe->constant_pool[i]->tag){
            case CONSTANT_Class:
                classe->constant_pool[i]->info = (CONSTANT_Class_info *)malloc(sizeof(CONSTANT_Class_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->name_index = le_u2(arquivo);
            break;
            case CONSTANT_Fieldref:
                classe->constant_pool[i]->info = (CONSTANT_Fieldref_info *)malloc(sizeof(CONSTANT_Fieldref_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->class_index = le_u2(arquivo);
                classe->constant_pool[i]->info->name_and_type_index = le_u2(arquivo);
            break;
            case CONSTANT_Methodref:
                classe->constant_pool[i]->info = (CONSTANT_Methodref_info *)malloc(sizeof(CONSTANT_Methodref_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->class_index = le_u2(arquivo);
                classe->constant_pool[i]->info->name_and_type_index = le_u2(arquivo);
            break;
            case CONSTANT_InterfaceMethodref:
                classe->constant_pool[i]->info = (CONSTANT_InterfaceMethodref_info *)malloc(sizeof(CONSTANT_InterfaceMethodref_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->class_index = le_u2(arquivo);
                classe->constant_pool[i]->info->name_and_type_index = le_u2(arquivo);
            break;
            case CONSTANT_String:
                classe->constant_pool[i]->info = (CONSTANT_String_info *)malloc(sizeof(CONSTANT_String_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->string_index = le_u2(arquivo);
            break;
            case CONSTANT_Integer:
                classe->constant_pool[i]->info = (CONSTANT_Integer_info *)malloc(sizeof(CONSTANT_Integer_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->bytes = le_u4(arquivo);
            break;
            case CONSTANT_Float:
                classe->constant_pool[i]->info = (CONSTANT_Float_info *)malloc(sizeof(CONSTANT_Float_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->bytes = le_u4(arquivo);
            break;
            case CONSTANT_Long:
                classe->constant_pool[i]->info = (CONSTANT_Long_info *)malloc(sizeof(CONSTANT_Long_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->high_bytes = le_u4(arquivo);
                classe->constant_pool[i]->info->low_bytes = le_u4(arquivo);
            break;
            case CONSTANT_Double:
                classe->constant_pool[i]->info = (CONSTANT_Double_info *)malloc(sizeof(CONSTANT_Double_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->high_bytes = le_u4(arquivo);
                classe->constant_pool[i]->info->low_bytes = le_u4(arquivo);
            break;
            case CONSTANT_NameAndType:
                classe->constant_pool[i]->info = (CONSTANT_NameAndType_info *)malloc(sizeof(CONSTANT_NameAndType_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->name_index = le_u2(arquivo);
                classe->constant_pool[i]->info->descriptor_index = le_u2(arquivo);
            break;
            case CONSTANT_Utf8:
                classe->constant_pool[i]->info = (CONSTANT_Utf8_info *)malloc(sizeof(CONSTANT_Utf8_info));
                classe->constant_pool[i]->info->tag = le_u1(arquivo);
                classe->constant_pool[i]->info->lenght = le_u2(arquivo);
                classe->constant_pool[i]->info->bytes = (u1 *)malloc(sizeof(u1)*classe->constant_pool[i]->info->lenght);
                for (int j=0;j<classe->constant_pool[i]->info->lenght;j++)
                    classe->constant_pool[i]->info->bytes[j] = le_u1(arquivo);
            break;
        }
    }

    return SUCESSO;
}

u1 le_u1(FILE *arquivo) {
    u1 valor;
    valor = (getc(arquivo));
    return valor;
}

u2 le_u2(FILE *arquivo) {
    u2 valor;
    valor = (getc(arquivo)<<8|getc(arquivo));
    return valor;
}

u4 le_u4(FILE *arquivo) {
    u4 valor;
    valor = (getc(arquivo)<<24|getc(arquivo)<<16|getc(arquivo)<<8|getc(arquivo));
    return valor;
}
