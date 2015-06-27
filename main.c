/**
* @file main.c
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo principal da implementacao do Leitor e Exibidor de arquivos no formato .class.
*/
/*
*    Trabalho da Disciplina Software Basico, 2015-1
*    Alunos: Bruno Ribeiro das Virgens (11/0111141)
*            Guilherme de Sousa Castro (11/0148746)
*            Kelvin William Moreira Lima (11/0159560)
*
*    Compilar com o IDE DevC++.
*
*    Chamar com um dos comandos:
*    jvm.exe <arquivo da classe>
*       Nao sera gerado o arquivo do relatorio (somente impressao na tela).
*    jvm.exe <arquivo da classe> <opcao de impressao>
*       Chamada do class loader: nao executara o programa, somente exibira a classe.
*    A chamada sem argumentos pedira ao usuario os dados necessarios para rodar o programa.
*/

#include "main.h"

int main(int argc, char **argv) {
    ClassFile *classe = (ClassFile *) malloc(sizeof(ClassFile));
    char nome_classe[21];
    char opcao; /// Modo de impressao (t - tela, a - arquivo, s - ambos, n - nenhum)
    int status;

    switch(argc) {
        case 2:
            status = carrega_classe(argv[1], classe);
            opcao = 'n';
            break;
        case 3:
            status = carrega_classe(argv[1], classe);
            opcao = argv[2][0];
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
        printf("Carregamento interrompido.\n");
        return status;
    }

    if(verifica_impressao(classe, opcao) == ERRO_ARQUIVO) { // Verifica onde imprimir o conteudo da classe
        printf("ERRO: arquivo nao pode ser criado.\n");
        return ERRO_ARQUIVO;
    }

    if(opcao == 'n') { // Modo classloader se op != n
        status = executa_programa(classe); // Executa o codigo da classe a partir de main
    }

    free(classe);

    if(status == SUCESSO) {
        printf("Fim da execucao.\n");
        return SUCESSO;
    }
    else {
        printf("Execucao interrompida.\n");
        return status;
    }
}

int verifica_impressao(ClassFile *classe, char opcao) {
    FILE *arquivo_saida;
    char *nome_arquivo;
    int index;
    #warning SMURF
    // Nada não, valeu por consertar o erro.
    index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;
    nome_arquivo = dereferencia(index, classe); // Recupera nome da classe
    strcat(nome_arquivo, ".txt"); // Adiciona extensao txt
    switch(opcao) {
        case 'a': // Impressao em Arquivo
            arquivo_saida = fopen(nome_arquivo, "w");
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
        default: // Impressao em Arquivo e em Tela
            imprime_general_information(classe);
            imprime_constant_pool(classe);
            imprime_fields(classe);
            imprime_methods(classe);
            imprime_attributes(classe);
            arquivo_saida = fopen(nome_arquivo, "w");
            if (!arquivo_saida)
                return ERRO_ARQUIVO;
            imprime_general_information_file(classe, arquivo_saida);
            imprime_constant_pool_file(classe, arquivo_saida);
            imprime_fields_file(classe, arquivo_saida);
            imprime_methods_file(classe, arquivo_saida);
            imprime_attributes_file(classe, arquivo_saida);
            fclose(arquivo_saida);
            break;
    }
    return SUCESSO;
}

int executa_programa(ClassFile *classe) {
    PilhaDeFrames *pilha_de_frames; /// Pilha de frames do programa
    ListaClasses *lista_de_classes; /// Lista de classes carregadas no programa
    method_info *metodo_main;
    ClassFile *classe_inicial;

    InicializaListaDeClasses(&lista_de_classes);
    InsereListaDeClasses(&lista_de_classes, classe);
    classe_inicial = RecuperaIesimaClasse(0, &lista_de_classes); // Recupera a primeira classe
    carrega_instrucoes();
    InicializaPilhaDeFrames(&pilha_de_frames);

    if(!(metodo_main = recupera_main(classe_inicial))) {
        printf("ERRO: Metodo MAIN nao encontrado.\n");
        return ERRO_MAIN;
    }

    prepara_metodo(metodo_main, classe_inicial, pilha_de_frames);
    executa_metodo(metodo_main, classe_inicial, pilha_de_frames);

    desalocaListaDeClasses(&lista_de_classes);
    desalocaPilhaFrames(&pilha_de_frames);

    return SUCESSO;
}
