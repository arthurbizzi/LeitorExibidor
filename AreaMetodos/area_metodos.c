/**
* @file area_metodos.c
* @author Bruno
* @brief Arquivo principal da implementacao do Leitor e Exibidor de arquivos no formato .class.
*/

#include "area_metodos.h"

method_info* recupera_main(ClassFile *classe) {
    u1 *nome;
    int index_nome;

    for(int i = 0; i < classe->methods_count; i++) { // Para cada metodo dentro da classe
        index_nome = classe->methods[i].name_index - 1;
        nome = classe->constant_pool[index_nome].info.Utf8.bytes;
        if(!strcmp("main", (char *) nome)) { // Se o nome do metodo for main
            return &classe->methods[i];
        }
    }
    return NULL;
}

void prepara_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames) {
    for(int i = 0; i < metodo->attributes_count; i++) {
        if(metodo->attributes[i].tag == ATTRTAG_Code) {
            if(metodo->attributes_count > 0) {
                Frame *frame = ConstruirFrame(classe, metodo);
                EmpilhaFrame(pilha_de_frames, frame);
            }
            else {
                Frame *frame = ConstruirFrame(classe, metodo);
                (metodo->attributes_count)++;
                metodo->attributes = (attribute_info *) malloc(sizeof(attribute_info));
                EmpilhaFrame(pilha_de_frames, frame);
            }
        }
    }
    DestruirFrame(frame);
}

void executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames) {
    int fim = 1;
    Frame *frame = ConstruirFrame(classe, metodo);

    EmpilhaFrame(&pilha_de_frames, frame);
    DestruirFrame(frame);
    while(fim) {
        Frame *atual = DesempilhaFrame(&pilha_de_frames); // Recupera frame atual
        fim = executa_instrucoes(metodo, &atual);
        if(fim == ERRO_INSTRUCAO) {
            printf("ERRO: instrucao nao pode ser executada.\n");
            DestruirFrame(atual);
            return; // ERRO_INSTRUCAO;
        }
        if(fim) {
            EmpilhaFrame(&pilha_de_frames, frame);
        }
    }

    DestruirFrame(atual);
}

int executa_instrucoes(method_info *metodo, Frame *frame) {

}
