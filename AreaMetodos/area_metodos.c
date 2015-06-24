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

int executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames) {
    int fim = 0;
    Frame *frame = ConstruirFrame(classe, metodo);

    EmpilhaFrame(&pilha_de_frames, frame);
    DestruirFrame(frame);
    while(!fim) {
        Frame *atual = DesempilhaFrame(&pilha_de_frames); // Recupera frame atual
        fim = executa_instrucoes(metodo, &atual);
        if(fim == ERRO_INSTRUCAO) {
            printf("ERRO: instrucao nao pode ser executada.\n");
            DestruirFrame(atual);
            return ERRO_INSTRUCAO;
        }
        if(!fim) {
            EmpilhaFrame(&pilha_de_frames, frame);
        }
        else {
            DestruirFrame(atual);
            fim = 1;
        }
    }

#warning BRUNO VEJA O QUE É PRA RETORNAR AQUI.
    return 0;
}

int executa_instrucoes(method_info *metodo, Frame *frame) {
    for(int i = 0; i < metodo->attributes_count; i++) {
        if(metodo->attributes[i].tag == ATTRTAG_Code) {
            attribute_info *codigo = &(metodo->attributes[i]);
            for(int j = 0; j < codigo->info.CodeAttribute.code_length; j++) {
                int status = executa_instrucao(codigo->info.CodeAttribute.code[i]);
                if(status) {
                    return ERRO_INSTRUCAO;
                }
            }
            return SUCESSO;
        }
    }
    return ERRO_INSTRUCAO;
}

int executa_instrucao(u4 opcode) {
    switch(opcode) {
        case 0x00:
            return SUCESSO;
        default:
            return ERRO_INSTRUCAO;
    }
}
