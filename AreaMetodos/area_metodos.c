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

void prepara_metodo(method_info *metodo, ClassFile *classe) {
    for(int i = 0; i < metodo->attributes_count; i++) {
        if(metodo->attributes[i].tag == ATTRTAG_Code) {
            if(metodo->attributes_count > 0) {

            }
            else {

            }
        }
    }
}

void executa_metodo(method_info *metodo, ClassFile *classe) {

}
