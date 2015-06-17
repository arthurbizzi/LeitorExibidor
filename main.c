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

#include "main.h"

int main(int argc, char **argv) {
    ClassFile *classe = (ClassFile *) malloc(sizeof(ClassFile));
    char nome_classe[21];
    char opcao;
    int status;

    switch(argc) {
        case 1:
            printf("Digite o nome do arquivo com a classe a ser carregada, com extensao:\n");
            scanf("%s", nome_classe);
            status = carrega_classe(nome_classe, classe);
            printf("Deseja imprimir as classes em tela (t), arquivo (a), ambos (s) ou nenhum (n)?\n");
            scanf("%c", &opcao);
            break;
        case 2:
            status = carrega_classe(argv[1], classe);
            break;
        default:
            printf("Quantidade incompativel de argumentos.\n");
            printf("Digite o nome do arquivo com a classe a ser carregada, com extensao:\n");
            scanf("%s", nome_classe);
            status = carrega_classe(nome_classe, classe);
            printf("Deseja imprimir as classes em tela (t), arquivo (a), ambos (s) ou nenhum (n)?\n");
            scanf("%c", &opcao);
            break;
    }

    if(status != SUCESSO) {
        printf("Execucao interrompida.");
        return status;
    }

    verifica_impressao(opcao, classe);

    printf("Fim da execucao.");
    return SUCESSO;
}

void verifica_impressao(char opcao, ClassFile *classe) {
    FILE *arquivo_saida;

    switch(opcao) {
        case 'n': // Nenhuma Impressao
            break;
        case 'a': // Impressao em Arquivo
            arquivo_saida = fopen("classes.txt", "a");
            if (!arquivo_saida)
                return ERRO_ARQUIVO;
            imprime_general_information_file(classe, arquivo_saida);
            imprime_constant_pool_file(classe, arquivo_saida);
            imprime_fields_file(classe, arquivo_saida);
            imprime_methods_file(classe, arquivo_saida);
            imprime_attributes_file(classe, arquivo_saida);
            fclose(arquivo_saida);
            break;
        case 't': // Impressao em Tela
            imprime_general_information(classe);
            imprime_constant_pool(classe);
            imprime_fields(classe);
            imprime_methods(classe);
            imprime_attributes(classe);
            break;
        case 's': // Impressao em Arquivo e em Tela
            imprime_general_information(classe);
            imprime_constant_pool(classe);
            imprime_fields(classe);
            imprime_methods(classe);
            imprime_attributes(classe);
            arquivo_saida = fopen("classes.txt", "a");
            if (!arquivo_saida)
                return ERRO_ARQUIVO;
            imprime_general_information_file(classe, arquivo_saida);
            imprime_constant_pool_file(classe, arquivo_saida);
            imprime_fields_file(classe, arquivo_saida);
            imprime_methods_file(classe, arquivo_saida);
            imprime_attributes_file(classe, arquivo_saida);
            fclose(arquivo_saida);
            break;
        default:
            break;
    }
}
