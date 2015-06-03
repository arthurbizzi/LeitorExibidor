//
// Created by kelvinec on 02/06/15.
//

#include "main.h"

#ifndef LEITOREXIBIDOR_IMPRIME_H
#define LEITOREXIBIDOR_IMPRIME_H

//Imprime Stdout
void imprime_general_information(ClassFile *classe);

void imprime_constant_pool(ClassFile *classe);

void imprime_attributes(ClassFile *classe);

void imprime_methods(ClassFile *classe);

void imprime_attribute(attribute_info *attributeInfo, ClassFile *classe);

void imprime_fields(ClassFile *classe);

//Imprime para arquivo
void imprime_general_information_file(ClassFile *classe, FILE *file);

void imprime_constant_pool_file(ClassFile *classe, FILE *file);

void imprime_attributes_file(ClassFile *classe, FILE *file);

void imprime_methods_file(ClassFile *classe, FILE *file);

void imprime_attribute_file(attribute_info *attributeInfo, ClassFile *classe, FILE *file);

void imprime_fields_file(ClassFile *classe, FILE *file);


#endif //LEITOREXIBIDOR_IMPRIME_H
