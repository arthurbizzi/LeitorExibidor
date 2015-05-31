#ifndef MAIN_H
#define MAIN_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/* Defines */
/* Controle do Programa */
#define MAGIC_NUMBER 0xCAFEBABE
#define VERSION 46
#define SUCESSO 0
#define ERRO_ARQUIVO -1
#define ERRO_EXECUCAO -2
#define ERRO_MAGIC -3
#define ERRO_VERSION -4
/* Tags Válidos */
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
/* Flags */
#define ACC_PUBLIC 0x0001
#define ACC_PRIVATE 0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC 0x0008
#define ACC_FINAL 0x0010
#define ACC_SYNCHRONIZED 0x0020
#define ACC_SUPER 0x0020
#define ACC_VOLATILE 0x0040
#define ACC_TRANSIENT 0x0080
#define ACC_NATIVE 0x0100
#define ACC_INTERFACE 0x0200
#define ACC_ABSTRACT 0x0400
#define ACC_STRICT 0x0800

/* Typedefs */
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

/* Estruturas */
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
    u1              *bytes; // tamanho: length
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

typedef struct constantdoubleinfo {
    u1              tag;
    u4              high_bytes;
    u4              low_bytes;
} CONSTANT_Double_info;

typedef struct codeattribute {
    u2              max_stack;
    u2              max_locals;
    u4              code_length;
    u1              *code; // tamanho: code_length
    u2              exception_table_length;
    struct et {
        u2          start_pc;
        u2          end_pc;
        u2          handler_pc;
        u2          catch_type;
                    } *exception_table; // tamanho: exception_table_length
    u2              attributes_count;
    struct attributeinfo  *attributes; // tamanho: attributes_count
} ATTR_Code;

typedef struct constantvalueattribute {
    u2              constantvalue_index;
} ATTR_Constantvalue;

typedef struct exceptionsattribute {
    u2              number_of_exceptions;
    u2              *exception_index_table; // tamanho: number_of_exceptions
} ATTR_Exception;

typedef struct innerclasses {
    u2              number_of_classes;
    struct ic {
        u2          inner_class_info_index;
        u2          outer_class_info_index;
        u2          inner_name_index;
        u2          inner_class_access_flags;
    } *classes; // tamanho: number_of_classes
} ATTR_Innerclasses;

typedef struct linenumbertableattribute {
    u2              line_number_table_length;
    struct lnt {
        u2          start_pc;
        u2          line_number;
    } *line_number_table; // tamanho: line_number_table_length
} ATTR_Linenumbertable;

typedef struct localvariabletableattribute {
    u2              local_variable_table_length;
    struct lvt {
        u2          start_pc;
        u2          length;
        u2          name_index;
        u2          descriptor_index;
        u2          index;
    } *local_variable_table; // tamanho: local_variable_table_length
} ATTR_Localvariabletable;

typedef struct sourcefileattribute {
    u2              sourcefile_index;
} ATTR_Sourcefile;

typedef struct defaultattribute {
    u1              *data;
} ATTR_Default;

typedef struct cpinfo {
    u1              tag;
    union {
        CONSTANT_Class_info Class;
        CONSTANT_Double_info Double;
        CONSTANT_Fieldref_info Fieldref;
        CONSTANT_Float_info Float;
        CONSTANT_Integer_info Integer;
        CONSTANT_InterfaceMethodref_info InterfaceMethodref;
        CONSTANT_Long_info Long;
        CONSTANT_Methodref_info Methodref;
        CONSTANT_NameAndType_info NameAndType;
        CONSTANT_String_info String;
        CONSTANT_Utf8_info Utf8;
    } info;
} cp_info;

typedef struct attributeinfo {
    u2              attribute_name_index;
    u4              attribute_length;
    union {
        ATTR_Constantvalue      ConstantValue;
        ATTR_Code               CodeAttribute;
        ATTR_Exception          Exception;
        ATTR_Innerclasses       InnerClasses;
        ATTR_Sourcefile         Sourcefile;
        ATTR_Linenumbertable    LineNumberTable;
        ATTR_Localvariabletable LocalVariableTable;
        ATTR_Default            Default;
    } info;
} attribute_info;

typedef struct methodinfo {
    u2              access_flags;
    u2              name_index;
    u2              descriptor_index;
    u2              attributes_count;
    attribute_info  *attributes; // tamanho: attributes_count
} method_info;

typedef struct fieldinfo {
    u2              access_flags;
    u2              name_index;
    u2              descriptor_index;
    u2              attributes_count;
    attribute_info  *attributes; // tamanho: attribute_count
} field_info;

typedef struct classfile {
    u4              magic;
    u2              minor_version;
    u2              major_version;
    u2              constant_pool_count;
    cp_info         *constant_pool; // tamanho: constant_pool_count - 1
    u2              access_flags;
    u2              this_class;
    u2              super_class;
    u2              interfaces_count;
    u2              *interfaces; // tamanho: interfaces_count
    u2              fields_count;
    field_info      *fields; // tamanho: fields_count
    u2              methods_count;
    method_info     *methods;
    u2              attributes_count;
    attribute_info  *attributes; // tamanho: attributes_count
} ClassFile;

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

#endif
