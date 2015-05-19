#ifndef MAIN_H
#define MAIN_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defines */
#define SUCESSO 0
#define ERRO_ARQUIVO -1
#define ERRO_EXECUCAO -2
#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1

/* Typedefs */
typedef u1 unsigned char;
typedef u2 unsigned short;
typedef u4 unsigned int;

/* Estruturas */
typedef struct classfile {
    u4              magic;
    u2              minor_version;
    u2              major_version;
    u2              constant_pool_count;
    cp_info         constaqnt_pool[constant_pool_count - 1];
    u2              access_flags;
    u2              this_class;
    u2              super_class;
    u2              interfaces_count;
    u2              interfaces[interfaces_count];
    u2              fields_count;
    field_info      fields[fields_count];
    u2              methods_count;
    method_info     methods[methods_count];
    u2              attributes_count;
    attribute_info  attributes[attributes_count];
} ClassFile;

typedef struct cpinfo {
    u1              tag;
    u1              info[];
} cp_info;

typedef struct constantclassinfo {
    u1              tag;
    u2              name_index;
} CONSTANT_Class_info;

typedef struct constantfieldrefinfo {
    u1              tag;
    u2              class_index;
    u2              name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct constantnameandtypeinfo {
    u1              tag;
    u2              name_index;
    u2              descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct constantutf8info {
    u1              tag;
    u2              length;
    u1              bytes[length];
} CONSTANT_Utf8_info;

typedef struct constantmethodrefinfo {
    u1              tag;
    u2              class_index;
    u2              name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct constantinterfacemethodrefinfo {
    u1              tag;
    u2              class_index;
    u2              name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct constantstringinfo {
    u1              tag;
    u2              string_index;
} CONSTANT_String_info;

typedef struct constantintegerinfo {
    u1              tag;
    u4              bytes;
} CONSTANT_Integer_info;

typedef struct constantfloatinfo {
    u1              tag;
    u4              bytes;
} CONSTANT_Float_info;

typedef struct constantlonginfo {
    u1              tag;
    u4              high_bytes;
    u4              low_bytes;
} CONSTANT_Long_info;

typedef struct fieldinfo {
    u2              access_flags;
    u2              name_index;
    u2              descriptor_index;
    u2              attributes_count;
    attribute_info  attributes[attribute_count];
} field_info;

typedef struct attributeinfo {
    u2              attribute_name_index;
    u4              attribute_length;
    u1              info[attribute_length];
} attribute_info;

typedef struct methodinfo {
    u2              access_flags;
    u2              name_index;
    u2              descriptor_index;
    u2              attributes_count;
    attribute_info  attributes[attributes_count];
} method_info;
/* Prototipos */

#endif
