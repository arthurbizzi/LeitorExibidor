/*
*    Trabalho da Disciplina Software Básico, 2015-1
*    Alunos: Bruno Ribeiro das Virgens (11/0111141)
*            Guilherme de Sousa Castro (11/0148746)
*            Kelvin William Moreira Lima (11/0159560)
*
*    Compilar com o comando:
*    gcc -std=c99 main.c -o leitorexibidor.exe
*
*    Chamar com um dos comandos:
*    leitorexibidor.exe
*       Tanto o arquivo da classe quanto o arquivo do relatorio serao pedidos ao usuario
*    leitorexibidor.exe <arquivo da classe>
*       Nao sera gerado o arquivo do relatorio (somente impressao na tela)
*    leitorexibidor.exe <arquivo da classe> <arquivo do relatorio>
*       Esta chamada gerará relatório em arquivo e na tela.
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
    char nome_arquivo[21], nome_relatorio[21];
    char opcao;
    int header;

    printf("LEITOR E EXIBIDOR DE ARQUIVOS EM FORMATO .CLASS\n");
    switch(argc) {
        case 1:
            printf("Digite o nome do arquivo a ser lido, com extensao:\n");
            scanf("%s", nome_arquivo);
            printf("Deseja gerar relatorio em um arquivo texto? (s/n)\n");
            scanf("%c", &opcao);
            if(opcao == 's' || opcao == 'S') { /* Upper ou lower case */
                printf("Digite o nome do arquivo a ser gerado, com extensao:\n");
                scanf("%s", nome_relatorio);
                opcao = 's'; /* Garante lower case, para simplificar comparacao mais a frente */
            }
            break;
        case 2:
            strcpy(nome_arquivo, argv[1]);
            opcao = 'n';
            break;
        case 3:
            strcpy(nome_arquivo, argv[1]);
            strcpy(nome_relatorio, argv[2]);
            opcao = 's';
            break;
        default:
            printf("Digite o nome do arquivo a ser lido, com extensao:\n");
            scanf("%s", nome_arquivo);
            printf("Deseja gerar relatorio em um arquivo texto? (s/n)\n");
            scanf("%c", &opcao);
            if(opcao == 's' || opcao == 'S') { /* Upper ou lower case */
                printf("Digite o nome do arquivo a ser gerado, com extensao:\n");
                scanf("%s", nome_relatorio);
                opcao = 's'; /* Garante lower case, para simplificar comparacao mais a frente */
            }
    }
    if(!(arq_classe = fopen(nome_arquivo, "rb"))) {
        printf("ERRO: arquivo \"%s\" nao existe.\n", nome_arquivo);
        return ERRO_ARQUIVO;
    }
    /* Carregamento do Magic Number e da versao, juntamente com suas verificacoes */
    header = carrega_header(arq_classe, classe);
    if(header == ERRO_MAGIC) {
        printf("ERRO: magic number invalido.\n");
        return ERRO_MAGIC;
    } else if (header == ERRO_VERSION){
        printf("ERRO: versao invalida.\n");
        return ERRO_VERSION;
    }
    /* Carregamento dos demais itens */
    carrega_constantpool(arq_classe, classe);
    carrega_flagseclasses(arq_classe, classe);
    carrega_fields(arq_classe, classe);
    carrega_methods(arq_classe, classe);
    carrega_attributes(arq_classe, classe);

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

int carrega_header(FILE *arquivo, ClassFile *classe) {
    classe->magic = le_u4(arquivo);
    if(classe->magic != MAGIC_NUMBER)
        return ERRO_MAGIC;
    classe->minor_version = le_u2(arquivo);
    classe->major_version = le_u2(arquivo);
    if(classe->major_version != VERSION)
        return ERRO_VERSION;

    return SUCESSO;
}

void carrega_constantpool(FILE *arquivo, ClassFile *classe) {
    classe->constant_pool_count = le_u2(arquivo);
    classe->constant_pool = (cp_info *) malloc(sizeof(cp_info)*(classe->constant_pool_count-1));
    for (int i=0;i<(classe->constant_pool_count-1);i++){
        classe->constant_pool[i].tag = le_u1(arquivo);
        switch (classe->constant_pool[i].tag){
            case CONSTANT_Class:
                classe->constant_pool[i].info.Class.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.Class.name_index = le_u2(arquivo);
                break;
            case CONSTANT_Fieldref:
                classe->constant_pool[i].info.Fieldref.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.Fieldref.class_index = le_u2(arquivo);
                classe->constant_pool[i].info.Fieldref.name_and_type_index = le_u2(arquivo);
                break;
            case CONSTANT_Methodref:
                classe->constant_pool[i].info.Methodref.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.Methodref.class_index = le_u2(arquivo);
                classe->constant_pool[i].info.Methodref.name_and_type_index = le_u2(arquivo);
                break;
            case CONSTANT_InterfaceMethodref:
                classe->constant_pool[i].info.InterfaceMethodref.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.InterfaceMethodref.class_index = le_u2(arquivo);
                classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index = le_u2(arquivo);
                break;
            case CONSTANT_String:
                classe->constant_pool[i].info.String.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.String.string_index = le_u2(arquivo);
                break;
            case CONSTANT_Integer:
                classe->constant_pool[i].info.Integer.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.Integer.bytes = le_u4(arquivo);
                break;
            case CONSTANT_Float:
                classe->constant_pool[i].info.Float.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.Float.bytes = le_u4(arquivo);
                break;
            case CONSTANT_Long:
                classe->constant_pool[i].info.Long.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.Long.high_bytes = le_u4(arquivo);
                classe->constant_pool[i].info.Long.low_bytes = le_u4(arquivo);
                break;
            case CONSTANT_Double:
                classe->constant_pool[i].info.Double.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.Double.high_bytes = le_u4(arquivo);
                classe->constant_pool[i].info.Double.low_bytes = le_u4(arquivo);
                break;
            case CONSTANT_NameAndType:
                classe->constant_pool[i].info.NameAndType.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.NameAndType.name_index = le_u2(arquivo);
                classe->constant_pool[i].info.NameAndType.descriptor_index = le_u2(arquivo);
                break;
            case CONSTANT_Utf8:
                classe->constant_pool[i].info.Utf8.tag = classe->constant_pool[i].tag;
                classe->constant_pool[i].info.Utf8.length = le_u2(arquivo);
                classe->constant_pool[i].info.Utf8.bytes = (u1 *) malloc(sizeof(u1)*classe->constant_pool[i].info.Utf8.length);
                for (int j=0;j<classe->constant_pool[i].info.Utf8.length;j++)
                    classe->constant_pool[i].info.Utf8.bytes[j] = le_u1(arquivo);
                break;
        }
    }

}

void carrega_flagseclasses(FILE *arquivo, ClassFile *classe) {
    classe->access_flags = le_u2(arquivo);
    classe->this_class = le_u2(arquivo);
    classe->super_class = le_u2(arquivo);
}

void carrega_interfaces(FILE *arquivo, ClassFile *classe) {
    classe->interfaces_count = le_u2(arquivo);
    classe->interfaces = (u2 *) malloc(classe->interfaces_count * sizeof(u2));

    for(int i = 0; i < classe->interfaces_count; i++)
        classe->interfaces[i] = le_u2(arquivo);
}

void carrega_fields(FILE *arquivo, ClassFile *classe) {
    classe->fields_count = le_u2(arquivo);
    classe->fields = (field_info *) malloc(classe->fields_count * sizeof(field_info));

    for(int i = 0; i < classe->fields_count; i++) {
        classe->fields->access_flags = le_u2(arquivo);
        classe->fields->name_index = le_u2(arquivo);
        classe->fields->descriptor_index = le_u2(arquivo);
        classe->fields->attributes_count = le_u2(arquivo);
        classe->fields->attributes = (attribute_info *) malloc(classe->fields->attributes_count * sizeof(attribute_info));
        for(int j = 0; j < classe->fields->attributes_count; j++) {
            // fuck.
        }
    }
}

void carrega_methods(FILE *arquivo, ClassFile *classe) {

}

void carrega_attributes(FILE *arquivo, ClassFile *classe) {

}
