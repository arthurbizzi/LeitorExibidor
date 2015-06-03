//
// Created by kelvinec on 02/06/15.
//

#ifndef LEITOREXIBIDOR_CARREGAMENTO_H
#define LEITOREXIBIDOR_CARREGAMENTO_H

#include <stdio.h>
#include "main.h"

/* Protótipos */

u1 le_u1(FILE *arquivo);

u2 le_u2(FILE *arquivo);

u4 le_u4(FILE *arquivo);

int carrega_header(FILE *arquivo, ClassFile *classe);

void carrega_constantpool(FILE *arquivo, ClassFile *classe);

void carrega_flagseclasses(FILE *arquivo, ClassFile *classe);

void carrega_interfaces(FILE *arquivo, ClassFile *classe);

void carrega_fields(FILE *arquivo, ClassFile *classe);

void carrega_methods(FILE *arquivo, ClassFile *classe);

void carrega_attributes(FILE *arquivo, ClassFile *classe);

void carrega_attribute(FILE *arquivo, ClassFile *classe, attribute_info *atributo);

void carrega_instrucoes(Instrucao *mapa);

#endif //LEITOREXIBIDOR_CARREGAMENTO_H
