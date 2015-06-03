/**
* @file imprime.c
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo com as implementacoes de funcoes relacionadas a impressao do conteudo da classe em tela e em arquivo.
*/

#include "imprime.h"

void imprime_general_information(ClassFile *classe) {
    printf("\n");
    printf(">>>General Information<<<\n");
    printf("Minor version:      \t%d\n", classe->minor_version);
    printf("Major version:      \t%d\n", classe->major_version);
    printf("Constant pool count:\t%d\n", classe->constant_pool_count);
    printf("Access flags:       \t0x%x\n", classe->access_flags);
    printf("This class:         \tcp info #%d\n", classe->this_class);
    printf("Super class:        \tcp info #%d\n", classe->super_class);
    printf("Interfaces count:   \t%d\n", classe->interfaces_count);
    printf("Fields count:       \t%d\n", classe->fields_count);
    printf("Methods count:      \t%d\n", classe->methods_count);
    printf("Attributes count:   \t%d\n", classe->attributes_count);
    printf("\n");
}

void imprime_constant_pool(ClassFile *classe) {
    l1 l;
    printf("\n");
    printf(">>>Constant Pool<<<\n");
    for (int i = 0;
         i < (classe->constant_pool_count - 1); i++) { /* Armazena os valores de cada elemento do constant pool */
        switch (classe->constant_pool[i].tag) { /* Existem respostas diferentes para cada tag */
            case CONSTANT_Class:
                printf("[%d]CONSTANT_Class_info:\n", (i + 1));
                printf("\tClass name:          \tcp info #%d\n", classe->constant_pool[i].info.Class.name_index);
                break;
            case CONSTANT_Fieldref:
                printf("[%d]CONSTANT_Fieldref_info:\n", (i + 1));
                printf("\tClass name:          \tcp inf #%d\n", classe->constant_pool[i].info.Fieldref.class_index);
                printf("\tName and type:       \tcp info #%d\n",
                       classe->constant_pool[i].info.Fieldref.name_and_type_index);
                break;
            case CONSTANT_Methodref:
                printf("[%d]CONSTANT_Methodref_info:\n", (i + 1));
                printf("\tClass name:          \tcp info #%d\n", classe->constant_pool[i].info.Methodref.class_index);
                printf("\tName and type:       \tcp info #%d\n",
                       classe->constant_pool[i].info.Methodref.name_and_type_index);
                break;
            case CONSTANT_InterfaceMethodref:
                printf("[%d]CONSTANT_InterceMethodref_info:\n", (i + 1));
                printf("\tClass name:          \tcp info #%d\n",
                       classe->constant_pool[i].info.InterfaceMethodref.class_index);
                printf("\tName and type:       \tcp info #%d\n",
                       classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
                break;
            case CONSTANT_String:
                printf("[%d]CONSTANT_String_info:\n", (i + 1));
                printf("\tString:              \tcp info #%d\n", classe->constant_pool[i].info.String.string_index);
                break;
            case CONSTANT_Integer:
                printf("[%d]CONSTANT_Integer_info:\n", (i + 1));
                printf("\tBytes:               \t0x%x\n", classe->constant_pool[i].info.Integer.bytes);
                printf("\tInteger:             \t%d\n", classe->constant_pool[i].info.Integer.bytes);
                break;
            case CONSTANT_Float:
                printf("[%d]CONSTANT_Float_info:\n", (i + 1));
                printf("\tBytes:               \t0x%x\n", classe->constant_pool[i].info.Float.bytes);
                printf("\tFloat:               \t%f\n", classe->constant_pool[i].info.Float.bytes);
                break;
            case CONSTANT_Long:
                l = (l1) classe->constant_pool[i].info.Long.high_bytes << 32;
                l = l | classe->constant_pool[i].info.Long.low_bytes;
                printf("[%d]CONSTANT_Long_info:\n", (i + 1));
                printf("\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Long.high_bytes);
                printf("\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Long.low_bytes);
                printf("\tLong:                \t%ld\n", l);
                i++;
                printf("[%d](large numeric continued)\n", (i + 1));
                break;
            case CONSTANT_Double:
                l = (l1) classe->constant_pool[i].info.Double.high_bytes << 32;
                l = l | classe->constant_pool[i].info.Double.low_bytes;
                printf("[%d]CONSTANT_Double_info:\n", (i + 1));
                printf("\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Double.high_bytes);
                printf("\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Double.low_bytes);
                printf("\tDouble:              \t%f\n", l);
                i++;
                printf("[%d](large numeric continued)\n", (i + 1));
                break;
            case CONSTANT_NameAndType:
                printf("[%d]CONSTANT_NameAndType_info:\n", (i + 1));
                printf("\tName:                \tcp info #%d\n", classe->constant_pool[i].info.NameAndType.name_index);
                printf("\tDescriptor:          \tcp info #%d\n",
                       classe->constant_pool[i].info.NameAndType.descriptor_index);
                break;
            case CONSTANT_Utf8:
                printf("[%d]CONSTANT_Utf8_info:\n", (i + 1));
                printf("\tLength of byte array:\t%d\n", classe->constant_pool[i].info.Utf8.length);
                printf("\tLength of string:    \t%d\n", classe->constant_pool[i].info.Utf8.length);
                printf("\tString:              \t");
                for (int j = 0; j < classe->constant_pool[i].info.Utf8.length; j++)
                    printf("%c", classe->constant_pool[i].info.Utf8.bytes[j]);
                printf("\n");
                break;
        }
    }
    printf("\n");
}

void imprime_fields(ClassFile *classe) {
    printf(">>>Fields<<<\n");
    for (int i = 0; i < classe->fields_count; i++) {
        printf("[%d]", i);
        for (int j = 0; j < classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.length; j++)
            printf("%c", classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.bytes[j]);
        printf("\n");
        printf("\tAccess Flags:    \t%d\n", classe->fields[i].access_flags);
        printf("\tName Index:      \t%d\n", classe->fields[i].name_index);
        printf("\tDescriptor Index:\t%d\n", classe->fields[i].descriptor_index);
        printf("\tAttributes Count:\t%d\n", classe->fields[i].attributes_count);
        for (int j = 0; j < classe->fields[i].attributes_count; j++) {
            printf("\t[%d]", j);
            for (int k = 0; k < classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index -
                                                      1].info.Utf8.length; k++)
                printf("%c", classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index -
                                                   1].info.Utf8.bytes[k]);
            printf("\n");
            imprime_attribute(&classe->fields[i].attributes[j], classe);
        }
    }
}

void imprime_attribute(attribute_info *attributeInfo, ClassFile *classe) {
    char *tipoAtributo;
    u2 index = attributeInfo->attribute_name_index - 1;
    tipoAtributo = (char *) malloc(classe->constant_pool[index].info.Utf8.length * sizeof(char));
    for (int l = 0; l < classe->constant_pool[index].info.Utf8.length; l++) {
        printf("%c", classe->constant_pool[index].info.Utf8.bytes[l]);
        tipoAtributo[l] = classe->constant_pool[index].info.Utf8.bytes[l];
    }
    printf("\n");
    printf("\t\tName Index:      \t%d\n", attributeInfo->attribute_name_index);
    printf("\t\tAttribute Lenght:\t%d\n", attributeInfo->attribute_length);

    if (attributeInfo->attribute_length > 0) {
        if (!strcmp(tipoAtributo, "ConstantValue")) {
            printf("\t\tConstant Value Index: \tCP INFO #%d", attributeInfo->info.ConstantValue.constantvalue_index);
        }
        else if (!strcmp(tipoAtributo, "Code")) {
            printf("\t\tMax Stack:          \t%d\n", attributeInfo->info.CodeAttribute.max_stack);
            printf("\t\tMax Locals:         \t%d\n", attributeInfo->info.CodeAttribute.max_locals);
            printf("\t\tCode Length:        \t%d\n", attributeInfo->info.CodeAttribute.code_length);
            printf("\t\tCode:\t ");
            for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++) {
                Instrucao instrucoes[0xCA];
                u1 opcode = attributeInfo->info.CodeAttribute.code[i];
                carrega_instrucoes(instrucoes);
                printf("OP: %x, INSTR: %s", opcode, instrucoes[opcode].mnemonico);
            }
            printf("\n\t\tException Table Length: \t%d\n", attributeInfo->info.CodeAttribute.exception_table_length);
            for (int i = 0; i < attributeInfo->info.CodeAttribute.exception_table_length; i++) {
                printf("\t\tStart PC:  \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].start_pc);
                printf("\t\tEnd PC:    \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].end_pc);
                printf("\t\tHandler PC:\t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].handler_pc);
                printf("\t\tEnd PC:    \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].catch_type);
            }
            printf("\t\tCode Attributes Count:\t%d\n", attributeInfo->info.CodeAttribute.attributes_count);
            for (int k = 0; k < attributeInfo->info.CodeAttribute.attributes_count; k++) {
                printf("\t\t[%d]", k);
                imprime_attribute(&(attributeInfo->info.CodeAttribute.attributes[k]), classe);
            }
        }
        else if (!strcmp(tipoAtributo, "Exceptions")) {
            printf("\t\tNumber of Exceptions:\t%d\n", attributeInfo->info.Exception.number_of_exceptions);
            for (int i = 0; i < attributeInfo->info.Exception.number_of_exceptions; i++) {
                printf("\t\tException Index:\tCP INFO #%d\n", attributeInfo->info.Exception.exception_index_table[i]);
            }
        }
        else if (!strcmp(tipoAtributo, "InnerClasses")) {
            printf("\t\tNumber of Classes:\t%d\n", attributeInfo->info.InnerClasses.number_of_classes);
            for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++) {
                printf("\t\tInner Class Index:       \tCP INFO #%d\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_class_info_index);
                printf("\t\tOuter Class Index:       \tCP INFO #%d\n",
                       attributeInfo->info.InnerClasses.classes[i].outer_class_info_index);
                printf("\t\tInner Class Name Index:  \tCP INFO #%d\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_name_index);
                printf("\t\tInner Class Access Flags:\t%d\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
            }
        }
        else if (!strcmp(tipoAtributo, "SourceFile")) {
            printf("\t\tSource File Index: \tCP INFO #%d\n", attributeInfo->info.Sourcefile.sourcefile_index);
        }
        else if (!strcmp(tipoAtributo, "LineNumberTable")) {
            printf("\t\tNumber of Lines:\t%d\n", attributeInfo->info.LineNumberTable.line_number_table_length);
            for (int i = 0; i < attributeInfo->info.LineNumberTable.line_number_table_length; i++) {
                printf("\t\tLine Number: \t%d\n", attributeInfo->info.LineNumberTable.line_number_table[i].line_number);
                printf("\t\tStart PC:    \t%d\n", attributeInfo->info.LineNumberTable.line_number_table[i].start_pc);
            }
        }
        else if (!strcmp(tipoAtributo, "LocalVariableTable")) {
            printf("\t\tTable Length:    \t%d\n", attributeInfo->info.LocalVariableTable.local_variable_table_length);
            for (int i = 0; i < attributeInfo->info.LocalVariableTable.local_variable_table_length; i++) {
                printf("\t\tStart PC:        \t%d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
                printf("\t\tLength:          \t%d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].length);
                printf("\t\tName Index:      \tCP INFO #%d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index);
                printf("\t\tDescriptor Index:\tCP INFO #%d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
                printf("\t\tIndex:           \t%d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].index);
            }
        }
        else {
            printf("\t\tDefault Data: \t");
            for (int i = 0; i < attributeInfo->attribute_length; i++) {
                printf("%x", attributeInfo->info.Default.data[i]);
            }
            printf("\n");
        }
    }
}

void imprime_methods(ClassFile *classe) {
    printf("\n");
    printf(">>>Methods<<<\n");
    printf("\n");
    printf("Methods Count: \t%d\n", classe->methods_count);

    for (int i = 0; i < classe->methods_count; i++) {
        printf("[%d]", i);
        for (int j = 0; j < classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.length; j++)
            printf("%c", classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.bytes[j]);
        printf("\n");
        printf("\tAccess Flags:    \t%d\n", classe->methods[i].access_flags);
        printf("\tName Index:      \tCP INFO #%d\n", classe->methods[i].name_index);
        printf("\tDescriptor Index:\tCP INFO #%d\n", classe->methods[i].descriptor_index);
        printf("\tAttributes Count:\t%d\n", classe->methods[i].attributes_count);
        for (int j = 0; j < classe->methods[i].attributes_count; j++) {
            printf("\t[%d]", j);
            imprime_attribute(&(classe->methods[i].attributes[j]), classe);
        }
    }
}

void imprime_attributes(ClassFile *classe) {
    printf("\n");
    printf(">>>Attributes<<<\n");
    printf("\n");
    printf("Attributes Count: \t%d\n", classe->attributes_count);
    for (int i = 0; i < classe->attributes_count; i++) {
        printf("\t[%d]", i);
        imprime_attribute(&(classe->attributes[i]), classe);
    }
}


void imprime_general_information_file(ClassFile *classe, FILE *file) {
    fprintf(file, "\n");
    fprintf(file, ">>>General Information<<<\n");
    fprintf(file, "Minor version:      \t%d\n", classe->minor_version);
    fprintf(file, "Major version:      \t%d\n", classe->major_version);
    fprintf(file, "Constant pool count:\t%d\n", classe->constant_pool_count);
    fprintf(file, "Access flags:       \t0x%x\n", classe->access_flags);
    fprintf(file, "This class:         \tcp info #%d\n", classe->this_class);
    fprintf(file, "Super class:        \tcp info #%d\n", classe->super_class);
    fprintf(file, "Interfaces count:   \t%d\n", classe->interfaces_count);
    fprintf(file, "Fields count:       \t%d\n", classe->fields_count);
    fprintf(file, "Methods count:      \t%d\n", classe->methods_count);
    fprintf(file, "Attributes count:   \t%d\n", classe->attributes_count);
    fprintf(file, "\n");
}

void imprime_constant_pool_file(ClassFile *classe, FILE *file) {
    l1 l;
    fprintf(file, "\n");
    fprintf(file, ">>>Constant Pool<<<\n");
    for (int i = 0;
         i < (classe->constant_pool_count - 1); i++) { /* Armazena os valores de cada elemento do constant pool */
        switch (classe->constant_pool[i].tag) { /* Existem respostas diferentes para cada tag */
            case CONSTANT_Class:
                fprintf(file, "[%d]CONSTANT_Class_info:\n", (i + 1));
                fprintf(file, "\tClass name:          \tcp info #%d\n", classe->constant_pool[i].info.Class.name_index);
                break;
            case CONSTANT_Fieldref:
                fprintf(file, "[%d]CONSTANT_Fieldref_info:\n", (i + 1));
                fprintf(file, "\tClass name:          \tcp inf #%d\n",
                        classe->constant_pool[i].info.Fieldref.class_index);
                fprintf(file, "\tName and type:       \tcp info #%d\n",
                        classe->constant_pool[i].info.Fieldref.name_and_type_index);
                break;
            case CONSTANT_Methodref:
                fprintf(file, "[%d]CONSTANT_Methodref_info:\n", (i + 1));
                fprintf(file, "\tClass name:          \tcp info #%d\n",
                        classe->constant_pool[i].info.Methodref.class_index);
                fprintf(file, "\tName and type:       \tcp info #%d\n",
                        classe->constant_pool[i].info.Methodref.name_and_type_index);
                break;
            case CONSTANT_InterfaceMethodref:
                fprintf(file, "[%d]CONSTANT_InterceMethodref_info:\n", (i + 1));
                fprintf(file, "\tClass name:          \tcp info #%d\n",
                        classe->constant_pool[i].info.InterfaceMethodref.class_index);
                fprintf(file, "\tName and type:       \tcp info #%d\n",
                        classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
                break;
            case CONSTANT_String:
                fprintf(file, "[%d]CONSTANT_String_info:\n", (i + 1));
                fprintf(file, "\tString:              \tcp info #%d\n",
                        classe->constant_pool[i].info.String.string_index);
                break;
            case CONSTANT_Integer:
                fprintf(file, "[%d]CONSTANT_Integer_info:\n", (i + 1));
                fprintf(file, "\tBytes:               \t0x%x\n", classe->constant_pool[i].info.Integer.bytes);
                fprintf(file, "\tInteger:             \t%d\n", classe->constant_pool[i].info.Integer.bytes);
                break;
            case CONSTANT_Float:
                fprintf(file, "[%d]CONSTANT_Float_info:\n", (i + 1));
                fprintf(file, "\tBytes:               \t0x%x\n", classe->constant_pool[i].info.Float.bytes);
                fprintf(file, "\tFloat:               \t%f\n", classe->constant_pool[i].info.Float.bytes);
                break;
            case CONSTANT_Long:
                l = (l1) classe->constant_pool[i].info.Long.high_bytes << 32;
                l = l | classe->constant_pool[i].info.Long.low_bytes;
                fprintf(file, "[%d]CONSTANT_Long_info:\n", (i + 1));
                fprintf(file, "\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Long.high_bytes);
                fprintf(file, "\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Long.low_bytes);
                fprintf(file, "\tLong:                \t%ld\n", l);
                i++;
                fprintf(file, "[%d](large numeric continued)\n", (i + 1));
                break;
            case CONSTANT_Double:
                l = (l1) classe->constant_pool[i].info.Double.high_bytes << 32;
                l = l | classe->constant_pool[i].info.Double.low_bytes;
                fprintf(file, "[%d]CONSTANT_Double_info:\n", (i + 1));
                fprintf(file, "\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Double.high_bytes);
                fprintf(file, "\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Double.low_bytes);
                fprintf(file, "\tDouble:              \t%f\n", l);
                i++;
                fprintf(file, "[%d](large numeric continued)\n", (i + 1));
                break;
            case CONSTANT_NameAndType:
                fprintf(file, "[%d]CONSTANT_NameAndType_info:\n", (i + 1));
                fprintf(file, "\tName:                \tcp info #%d\n",
                        classe->constant_pool[i].info.NameAndType.name_index);
                fprintf(file, "\tDescriptor:          \tcp info #%d\n",
                        classe->constant_pool[i].info.NameAndType.descriptor_index);
                break;
            case CONSTANT_Utf8:
                fprintf(file, "[%d]CONSTANT_Utf8_info:\n", (i + 1));
                fprintf(file, "\tLength of byte array:\t%d\n", classe->constant_pool[i].info.Utf8.length);
                fprintf(file, "\tLength of string:    \t%d\n", classe->constant_pool[i].info.Utf8.length);
                fprintf(file, "\tString:              \t");
                for (int j = 0; j < classe->constant_pool[i].info.Utf8.length; j++)
                    fprintf(file, "%c", classe->constant_pool[i].info.Utf8.bytes[j]);
                fprintf(file, "\n");
                break;
        }
    }
    fprintf(file, "\n");
}

void imprime_fields_file(ClassFile *classe, FILE *file) {
    fprintf(file, ">>>Fields<<<\n");
    for (int i = 0; i < classe->fields_count; i++) {
        fprintf(file, "[%d]", i);
        for (int j = 0; j < classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.length; j++)
            fprintf(file, "%c", classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.bytes[j]);
        fprintf(file, "\n");
        fprintf(file, "\tAccess Flags:    \t%d\n", classe->fields[i].access_flags);
        fprintf(file, "\tName Index:      \t%d\n", classe->fields[i].name_index);
        fprintf(file, "\tDescriptor Index:\t%d\n", classe->fields[i].descriptor_index);
        fprintf(file, "\tAttributes Count:\t%d\n", classe->fields[i].attributes_count);
        for (int j = 0; j < classe->fields[i].attributes_count; j++) {
            fprintf(file, "\t[%d]", j);
            for (int k = 0; k < classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index -
                                                      1].info.Utf8.length; k++)
                fprintf(file, "%c", classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index -
                                                          1].info.Utf8.bytes[k]);
            fprintf(file, "\n");
            imprime_attribute(&classe->fields[i].attributes[j], classe);
        }
    }
}

void imprime_attribute_file(attribute_info *attributeInfo, ClassFile *classe, FILE *file) {
    char *tipoAtributo;
    u2 index = attributeInfo->attribute_name_index - 1;
    tipoAtributo = (char *) malloc(classe->constant_pool[index].info.Utf8.length * sizeof(char));
    for (int l = 0; l < classe->constant_pool[index].info.Utf8.length; l++) {
        fprintf(file, "%c", classe->constant_pool[index].info.Utf8.bytes[l]);
        tipoAtributo[l] = classe->constant_pool[index].info.Utf8.bytes[l];
    }
    fprintf(file, "\n");
    fprintf(file, "\t\tName Index:      \t%d\n", attributeInfo->attribute_name_index);
    fprintf(file, "\t\tAttribute Lenght:\t%d\n", attributeInfo->attribute_length);

    if (attributeInfo->attribute_length > 0) {
        if (!strcmp(tipoAtributo, "ConstantValue")) {
            fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d",
                    attributeInfo->info.ConstantValue.constantvalue_index);
        }
        else if (!strcmp(tipoAtributo, "Code")) {
            fprintf(file, "\t\tMax Stack:          \t%d\n", attributeInfo->info.CodeAttribute.max_stack);
            fprintf(file, "\t\tMax Locals:         \t%d\n", attributeInfo->info.CodeAttribute.max_locals);
            fprintf(file, "\t\tCode Length:        \t%d\n", attributeInfo->info.CodeAttribute.code_length);
            fprintf(file, "\t\tCode:\t ");
            for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++) {
                Instrucao instrucoes[0xCA];
                u1 opcode = attributeInfo->info.CodeAttribute.code[i];
                carrega_instrucoes(instrucoes);
                fprintf(file, "OP: %x, INSTR: %s", opcode, instrucoes[opcode].mnemonico);
            }
            fprintf(file, "\n\t\tException Table Length: \t%d\n",
                    attributeInfo->info.CodeAttribute.exception_table_length);
            for (int i = 0; i < attributeInfo->info.CodeAttribute.exception_table_length; i++) {
                fprintf(file, "\t\tStart PC:  \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].start_pc);
                fprintf(file, "\t\tEnd PC:    \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].end_pc);
                fprintf(file, "\t\tHandler PC:\t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].handler_pc);
                fprintf(file, "\t\tEnd PC:    \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].catch_type);
            }
            fprintf(file, "\t\tCode Attributes Count:\t%d\n", attributeInfo->info.CodeAttribute.attributes_count);
            for (int k = 0; k < attributeInfo->info.CodeAttribute.attributes_count; k++) {
                fprintf(file, "\t\t[%d]", k);
                imprime_attribute(&(attributeInfo->info.CodeAttribute.attributes[k]), classe);
            }
        }
        else if (!strcmp(tipoAtributo, "Exceptions")) {
            fprintf(file, "\t\tNumber of Exceptions:\t%d\n", attributeInfo->info.Exception.number_of_exceptions);
            for (int i = 0; i < attributeInfo->info.Exception.number_of_exceptions; i++) {
                fprintf(file, "\t\tException Index:\tCP INFO #%d\n",
                        attributeInfo->info.Exception.exception_index_table[i]);
            }
        }
        else if (!strcmp(tipoAtributo, "InnerClasses")) {
            fprintf(file, "\t\tNumber of Classes:\t%d\n", attributeInfo->info.InnerClasses.number_of_classes);
            for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++) {
                fprintf(file, "\t\tInner Class Index:       \tCP INFO #%d\n",
                        attributeInfo->info.InnerClasses.classes[i].inner_class_info_index);
                fprintf(file, "\t\tOuter Class Index:       \tCP INFO #%d\n",
                        attributeInfo->info.InnerClasses.classes[i].outer_class_info_index);
                fprintf(file, "\t\tInner Class Name Index:  \tCP INFO #%d\n",
                        attributeInfo->info.InnerClasses.classes[i].inner_name_index);
                fprintf(file, "\t\tInner Class Access Flags:\t%d\n",
                        attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
            }
        }
        else if (!strcmp(tipoAtributo, "SourceFile")) {
            fprintf(file, "\t\tSource File Index: \tCP INFO #%d\n", attributeInfo->info.Sourcefile.sourcefile_index);
        }
        else if (!strcmp(tipoAtributo, "LineNumberTable")) {
            fprintf(file, "\t\tNumber of Lines:\t%d\n", attributeInfo->info.LineNumberTable.line_number_table_length);
            for (int i = 0; i < attributeInfo->info.LineNumberTable.line_number_table_length; i++) {
                fprintf(file, "\t\tLine Number: \t%d\n",
                        attributeInfo->info.LineNumberTable.line_number_table[i].line_number);
                fprintf(file, "\t\tStart PC:    \t%d\n",
                        attributeInfo->info.LineNumberTable.line_number_table[i].start_pc);
            }
        }
        else if (!strcmp(tipoAtributo, "LocalVariableTable")) {
            fprintf(file, "\t\tTable Length:    \t%d\n",
                    attributeInfo->info.LocalVariableTable.local_variable_table_length);
            for (int i = 0; i < attributeInfo->info.LocalVariableTable.local_variable_table_length; i++) {
                fprintf(file, "\t\tStart PC:        \t%d\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
                fprintf(file, "\t\tLength:          \t%d\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].length);
                fprintf(file, "\t\tName Index:      \tCP INFO #%d\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index);
                fprintf(file, "\t\tDescriptor Index:\tCP INFO #%d\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
                fprintf(file, "\t\tIndex:           \t%d\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].index);
            }
        }
        else {
            fprintf(file, "\t\tDefault Data: \t");
            for (int i = 0; i < attributeInfo->attribute_length; i++) {
                fprintf(file, "%x", attributeInfo->info.Default.data[i]);
            }
            fprintf(file, "\n");
        }
    }
}

void imprime_methods_file(ClassFile *classe, FILE *file) {
    fprintf(file, "\n");
    fprintf(file, ">>>Methods<<<\n");
    fprintf(file, "\n");
    fprintf(file, "Methods Count: \t%d\n", classe->methods_count);

    for (int i = 0; i < classe->methods_count; i++) {
        fprintf(file, "[%d]", i);
        for (int j = 0; j < classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.length; j++)
            fprintf(file, "%c", classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.bytes[j]);
        fprintf(file, "\n");
        fprintf(file, "\tAccess Flags:    \t%d\n", classe->methods[i].access_flags);
        fprintf(file, "\tName Index:      \tCP INFO #%d\n", classe->methods[i].name_index);
        fprintf(file, "\tDescriptor Index:\tCP INFO #%d\n", classe->methods[i].descriptor_index);
        fprintf(file, "\tAttributes Count:\t%d\n", classe->methods[i].attributes_count);
        for (int j = 0; j < classe->methods[i].attributes_count; j++) {
            fprintf(file, "\t[%d]", j);
            imprime_attribute(&(classe->methods[i].attributes[j]), classe);
        }
    }
}

void imprime_attributes_file(ClassFile *classe, FILE *file) {
    fprintf(file, "\n");
    fprintf(file, ">>>Attributes<<<\n");
    fprintf(file, "\n");
    fprintf(file, "Attributes Count: \t%d\n", classe->attributes_count);
    for (int i = 0; i < classe->attributes_count; i++) {
        fprintf(file, "\t[%d]", i);
        imprime_attribute(&(classe->attributes[i]), classe);
    }
}

void carrega_instrucoes(Instrucao *mapa) {
    FILE *arq_mapa = fopen("mapa.txt", "r");

    if (!(arq_mapa = fopen("mapa.txt", "r"))) {
        printf("ERRO: arquivo \"%s\" nao existe.\n", "mapa.txt");
        exit(ERRO_ARQUIVO);
    }

    for (int i = 0; i < 0xCA; i++) {
        fscanf(arq_mapa, "%s", mapa[i].mnemonico);
    }
    fclose(arq_mapa);
}
