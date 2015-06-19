/**
* @file impressao.c
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo com as implementacoes de funcoes relacionadas a impressao do conteudo da classe em tela e em arquivo.
*/

#include "impressao.h"

void imprime_general_information(ClassFile *classe) {
    char *nomeThisClass, *nomeSuperClass;
    int index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;
    nomeThisClass = dereferencia(index, classe);
    index = classe->constant_pool[classe->super_class - 1].info.Class.name_index - 1;
    nomeSuperClass = dereferencia(index, classe);
    //nomeSuperClass = dereferencia(index, classe);
    printf("\n");
    printf(">>>General Information<<<\n");
    printf("Minor version:      \t%d\n", classe->minor_version);
    printf("Major version:      \t%d\n", classe->major_version);
    printf("Constant pool count:\t%d\n", classe->constant_pool_count);
    printf("Access flags:       \t0x%x\n", classe->access_flags);
    printf("This class:         \tCP INFO #%d < %s >\n", classe->this_class, nomeThisClass);
    printf("Super class:        \tCP INFO #%d < %s >\n", classe->super_class, nomeSuperClass);
    printf("Interfaces count:   \t%d\n", classe->interfaces_count);
    printf("Fields count:       \t%d\n", classe->fields_count);
    printf("Methods count:      \t%d\n", classe->methods_count);
    printf("Attributes count:   \t%d\n", classe->attributes_count);
    printf("\n");
    system("PAUSE");
}

void imprime_constant_pool(ClassFile *classe) {
    u8 l;
    char *derreferencia = NULL, *derreferencia2 = NULL, *derreferencia3 = NULL;
    printf("\n");
    printf(">>>Constant Pool<<<\n");
    int index = 0;
    for (int i = 0;
         i < (classe->constant_pool_count - 1); i++) { /* Armazena os valores de cada elemento do constant pool */
        switch (classe->constant_pool[i].tag) { /* Existem respostas diferentes para cada tag */
            case CONSTANT_Class:
                index = classe->constant_pool[i].info.Class.name_index - 1;
                derreferencia = dereferencia(index, classe);
                printf("[%d]CONSTANT_Class_info:\n", (i + 1));
                printf("\tClass name:          \tCP INFO #%d < %s >\n", classe->constant_pool[i].info.Class.name_index,
                       derreferencia);
                break;
            case CONSTANT_Fieldref:
                index = classe->constant_pool[i].info.Fieldref.class_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index, classe);
                printf("[%d]CONSTANT_Fieldref_info:\n", (i + 1));
                printf("\tClass name:          \tCP INFO #%d < %s >\n",
                       classe->constant_pool[i].info.Fieldref.class_index, derreferencia);
                index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
                derreferencia = dereferencia(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
                derreferencia2 = dereferencia(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                              classe);
                printf("\tName and type:       \tCP INFO #%d  < %s%s >\n",
                       classe->constant_pool[i].info.Fieldref.name_and_type_index, derreferencia, derreferencia2);
                break;
            case CONSTANT_Methodref:
                index = classe->constant_pool[i].info.Fieldref.class_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index, classe);
                printf("[%d]CONSTANT_Methodref_info:\n", (i + 1));
                printf("\tClass name:          \tCP INFO #%d < %s >\n",
                       classe->constant_pool[i].info.Methodref.class_index, derreferencia);
                index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
                derreferencia = dereferencia(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
                derreferencia2 = dereferencia(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                              classe);
                printf("\tName and type:       \tCP INFO #%d < %s%s >\n",
                       classe->constant_pool[i].info.Methodref.name_and_type_index, derreferencia, derreferencia2);
                break;
            case CONSTANT_InterfaceMethodref:
                index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.class_index - 1].info.Class.name_index - 1;
                derreferencia = dereferencia(index, classe);
                index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.name_index - 1;
                derreferencia2 = dereferencia(index, classe);
                index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.descriptor_index - 1;
                derreferencia3 = dereferencia(index, classe);
                derreferencia2 = strcat(derreferencia2,derreferencia3);
                printf("[%d]CONSTANT_InterceMethodref_info:\n", (i + 1));
                printf("\tClass name:          \tCP INFO #%d < %s >\n",
                       classe->constant_pool[i].info.InterfaceMethodref.class_index, derreferencia);
                printf("\tName and type:       \tCP INFO #%d < %s >\n",
                       classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index, derreferencia2);
                break;
            case CONSTANT_String:
                index = classe->constant_pool[i].info.String.string_index - 1;
                derreferencia = dereferencia(index, classe);
                printf("[%d]CONSTANT_String_info:\n", (i + 1));
                printf("\tString:              \tCP INFO #%d < %s >\n", classe->constant_pool[i].info.String.string_index, derreferencia);
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
                l = (u8) classe->constant_pool[i].info.Long.high_bytes << 32;
                l = l | classe->constant_pool[i].info.Long.low_bytes;
                printf("[%d]CONSTANT_Long_info:\n", (i + 1));
                printf("\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Long.high_bytes);
                printf("\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Long.low_bytes);
                printf("\tLong:                \t%ld\n", l);
                i++;
                printf("[%d](large numeric continued)\n", (i + 1));
                break;
            case CONSTANT_Double:
                l = (u8) classe->constant_pool[i].info.Double.high_bytes << 32;
                l = l | classe->constant_pool[i].info.Double.low_bytes;
                printf("[%d]CONSTANT_Double_info:\n", (i + 1));
                printf("\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Double.high_bytes);
                printf("\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Double.low_bytes);
                printf("\tDouble:              \t%f\n", l);
                i++;
                printf("[%d](large numeric continued)\n", (i + 1));
                break;
            case CONSTANT_NameAndType:
                index = classe->constant_pool[i].info.NameAndType.name_index - 1;
                derreferencia = dereferencia(index, classe);
                index = classe->constant_pool[i].info.NameAndType.descriptor_index - 1;
                derreferencia2 = dereferencia(index, classe);
                printf("[%d]CONSTANT_NameAndType_info:\n", (i + 1));
                printf("\tName:                \tCP INFO #%d < %s >\n", classe->constant_pool[i].info.NameAndType.name_index, derreferencia);
                printf("\tDescriptor:          \tCP INFO #%d < %s >\n",
                       classe->constant_pool[i].info.NameAndType.descriptor_index, derreferencia2);
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
    char *derreferencia = NULL, *derreferencia2 = NULL;
    int index = 0;
    printf(">>>Fields<<<\n");
    for (int i = 0; i < classe->fields_count; i++) {
        printf("[%d]", i);
        for (int j = 0; j < classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.length; j++)
            printf("%c", classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.bytes[j]);
        printf("\n");
        index = classe->fields[i].name_index - 1;
        derreferencia = dereferencia(index, classe);
        index = classe->fields[i].descriptor_index - 1;
        derreferencia2 = dereferencia(index, classe);
        printf("\tAccess Flags:    \t%d\n", classe->fields[i].access_flags);
        printf("\tName Index:      \tCP INFO #%d < %s >\n", classe->fields[i].name_index, derreferencia);
        printf("\tDescriptor Index:\tCP INFO #%d < %s >\n", classe->fields[i].descriptor_index, derreferencia2);
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
    char *derreferencia = NULL;
    u8 l;
    char *tipoAtributo;
    u2 index = attributeInfo->attribute_name_index - 1, index1;
    float f;
    int i;
    tipoAtributo = (char *) malloc(classe->constant_pool[index].info.Utf8.length * sizeof(char));
    for (int l = 0; l < classe->constant_pool[index].info.Utf8.length; l++) {
        printf("%c", classe->constant_pool[index].info.Utf8.bytes[l]);
        tipoAtributo[l] = classe->constant_pool[index].info.Utf8.bytes[l];
    }
    index = attributeInfo->attribute_name_index - 1;
    derreferencia = dereferencia(index,classe);
    printf("\n");
    printf("\t\tName Index:      \tCP INFO #%d < %s >\n", attributeInfo->attribute_name_index, derreferencia);
    printf("\t\tAttribute Lenght:\t%d\n", attributeInfo->attribute_length);

    if (attributeInfo->attribute_length > 0) {
        if (!strcmp(tipoAtributo, "ConstantValue")) {
            index = attributeInfo->info.ConstantValue.constantvalue_index - 1;
            switch (classe->constant_pool[index].tag){
                case CONSTANT_Long:
                    l = (u8)classe->constant_pool[index].info.Long.high_bytes<<32|classe->constant_pool[index].info.Long.low_bytes;
                    printf("\t\tConstant Value Index: \tCP INFO #%d < %ld >", attributeInfo->info.ConstantValue.constantvalue_index, l);
                break;
                case CONSTANT_Double:
                    l = (u8)classe->constant_pool[index].info.Double.high_bytes<<32|classe->constant_pool[index].info.Double.low_bytes;
                    printf("\t\tConstant Value Index: \tCP INFO #%d < %f >", attributeInfo->info.ConstantValue.constantvalue_index, l);
                break;
                case CONSTANT_Float:
                    f = (float)classe->constant_pool[index].info.Float.bytes;
                    printf("\t\tConstant Value Index: \tCP INFO #%d < %f >", attributeInfo->info.ConstantValue.constantvalue_index, f);
                break;
                case CONSTANT_Integer:
                    i = (int)classe->constant_pool[index].info.Integer.bytes;
                    printf("\t\tConstant Value Index: \tCP INFO #%d < %d >", attributeInfo->info.ConstantValue.constantvalue_index, i);
                break;
                case CONSTANT_String:
                    index1 = classe->constant_pool[index].info.String.string_index - 1;
                    derreferencia = dereferencia(index1,classe);
                    printf("\t\tConstant Value Index: \tCP INFO #%d < %s >", attributeInfo->info.ConstantValue.constantvalue_index, derreferencia);
                break;
            }
        }
        else if (!strcmp(tipoAtributo, "Code")) {
            printf("\t\tMax Stack:          \t%d\n", attributeInfo->info.CodeAttribute.max_stack);
            printf("\t\tMax Locals:         \t%d\n", attributeInfo->info.CodeAttribute.max_locals);
            printf("\t\tCode Length:        \t%d\n", attributeInfo->info.CodeAttribute.code_length);
            printf("\t\tCode:\t \n");
            for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++) {
                Instrucao mapa[0xCA];
                u1 opcode = attributeInfo->info.CodeAttribute.code[i];
                carrega_instrucoes(mapa);
                printf("\t\t\t\t\t%d: %s\n", i, mapa[opcode].mnemonico);
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
                index = attributeInfo->info.Exception.exception_index_table[i] - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tException Index:\tCP INFO #%d < %s >\n", attributeInfo->info.Exception.exception_index_table[i], derreferencia);
            }
        }
        else if (!strcmp(tipoAtributo, "InnerClasses")) {
            printf("\t\tNumber of Classes:\t%d\n", attributeInfo->info.InnerClasses.number_of_classes);
            for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++) {
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tInner Class Index:       \tCP INFO #%d < %s >\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_class_info_index, derreferencia);
                index = attributeInfo->info.InnerClasses.classes[i].outer_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tOuter Class Index:       \tCP INFO #%d < %s >\n",
                       attributeInfo->info.InnerClasses.classes[i].outer_class_info_index, derreferencia);
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tInner Name Index:  \tCP INFO #%d < %s >\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_name_index, derreferencia);
                printf("\t\tInner Class Access Flags:\t%d\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
            }
        }
        else if (!strcmp(tipoAtributo, "SourceFile")) {
            index = attributeInfo->info.Sourcefile.sourcefile_index - 1;
            derreferencia = dereferencia(index,classe);
            printf("\t\tSource File Index: \tCP INFO #%d < %s >\n", attributeInfo->info.Sourcefile.sourcefile_index, derreferencia);
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
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tName Index:      \tCP INFO #%d < %s >\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index, derreferencia);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tDescriptor Index:\tCP INFO #%d < %s >\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index, derreferencia);
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
    char *derreferencia = NULL;
    int index = 0;
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
        index = classe->methods[i].name_index - 1;
        derreferencia = dereferencia(index,classe);
        printf("\tName Index:      \tCP INFO #%d < %s >\n", classe->methods[i].name_index, derreferencia);
        index = classe->methods[i].descriptor_index - 1;
        derreferencia = dereferencia(index,classe);
        printf("\tDescriptor Index:\tCP INFO #%d < %s >\n", classe->methods[i].descriptor_index, derreferencia);
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
    char *derreferencia = NULL;
    int index = 0;
    fprintf(file, ">>>General Information<<<\n");
    fprintf(file, "Minor version:      \t%d\n", classe->minor_version);
    fprintf(file, "Major version:      \t%d\n", classe->major_version);
    fprintf(file, "Constant pool count:\t%d\n", classe->constant_pool_count);
    fprintf(file, "Access flags:       \t0x%x\n", classe->access_flags);
    index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;
    derreferencia = dereferencia(index,classe);
    fprintf(file, "This class:         \tCP INFO #%d < %s >\n", classe->this_class, derreferencia);
    index = classe->constant_pool[classe->super_class - 1].info.Class.name_index - 1;
    derreferencia = dereferencia(index,classe);
    fprintf(file, "Super class:        \tCP INFO #%d < %s >\n", classe->super_class, derreferencia);
    fprintf(file, "Interfaces count:   \t%d\n", classe->interfaces_count);
    fprintf(file, "Fields count:       \t%d\n", classe->fields_count);
    fprintf(file, "Methods count:      \t%d\n", classe->methods_count);
    fprintf(file, "Attributes count:   \t%d\n", classe->attributes_count);
    fprintf(file, "\n");
}

void imprime_constant_pool_file(ClassFile *classe, FILE *file) {
    char *derreferencia = NULL, *derreferencia2 = NULL, *derreferencia3 = NULL;
    int index = 0;
    u8 l;
    fprintf(file, "\n");
    fprintf(file, ">>>Constant Pool<<<\n");
    for (int i = 0;
         i < (classe->constant_pool_count - 1); i++) { /* Armazena os valores de cada elemento do constant pool */
        switch (classe->constant_pool[i].tag) { /* Existem respostas diferentes para cada tag */
            case CONSTANT_Class:
                index = classe->constant_pool[i].info.Class.name_index - 1;
                derreferencia = dereferencia(index, classe);
                fprintf(file, "[%d]CONSTANT_Class_info:\n", (i + 1));
                fprintf(file, "\tClass name:          \tCP INFO #%d < %s >\n", classe->constant_pool[i].info.Class.name_index, derreferencia);
                break;
            case CONSTANT_Fieldref:
                index = classe->constant_pool[i].info.Fieldref.class_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index, classe);
                fprintf(file, "[%d]CONSTANT_Fieldref_info:\n", (i + 1));
                fprintf(file, "\tClass name:          \tCP INFO #%d < %s >\n",
                        classe->constant_pool[i].info.Fieldref.class_index, derreferencia);
                index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
                derreferencia = dereferencia(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
                derreferencia2 = dereferencia(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                              classe);
                fprintf(file, "\tName and type:       \tCP INFO #%d < %s%s >\n",
                        classe->constant_pool[i].info.Fieldref.name_and_type_index, derreferencia, derreferencia2);
                break;
            case CONSTANT_Methodref:
                index = classe->constant_pool[i].info.Fieldref.class_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index, classe);
                fprintf(file, "[%d]CONSTANT_Methodref_info:\n", (i + 1));
                fprintf(file, "\tClass name:          \tCP INFO #%d < %s >\n",
                        classe->constant_pool[i].info.Methodref.class_index, derreferencia);
                index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
                derreferencia = dereferencia(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
                derreferencia2 = dereferencia(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                              classe);
                fprintf(file, "\tName and type:       \tCP INFO #%d < %s%s >\n",
                        classe->constant_pool[i].info.Methodref.name_and_type_index, derreferencia, derreferencia2);
                break;
            case CONSTANT_InterfaceMethodref:
                index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.class_index - 1].info.Class.name_index - 1;
                derreferencia = dereferencia(index, classe);
                index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.name_index - 1;
                derreferencia2 = dereferencia(index, classe);
                index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.descriptor_index - 1;
                derreferencia3 = dereferencia(index, classe);
                derreferencia2 = strcat(derreferencia2,derreferencia3);
                fprintf(file, "[%d]CONSTANT_InterceMethodref_info:\n", (i + 1));
                fprintf(file, "\tClass name:          \tCP INFO #%d < %s >\n",
                        classe->constant_pool[i].info.InterfaceMethodref.class_index, derreferencia);
                fprintf(file, "\tName and type:       \tCP INFO #%d < %s >\n",
                        classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index, derreferencia2);
                break;
            case CONSTANT_String:
                index = classe->constant_pool[i].info.String.string_index - 1;
                derreferencia = dereferencia(index, classe);
                fprintf(file, "[%d]CONSTANT_String_info:\n", (i + 1));
                fprintf(file, "\tString:              \tCP INFO #%d < %s >\n",
                        classe->constant_pool[i].info.String.string_index, derreferencia);
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
                l = (u8) classe->constant_pool[i].info.Long.high_bytes << 32;
                l = l | classe->constant_pool[i].info.Long.low_bytes;
                fprintf(file, "[%d]CONSTANT_Long_info:\n", (i + 1));
                fprintf(file, "\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Long.high_bytes);
                fprintf(file, "\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Long.low_bytes);
                fprintf(file, "\tLong:                \t%ld\n", l);
                i++;
                fprintf(file, "[%d](large numeric continued)\n", (i + 1));
                break;
            case CONSTANT_Double:
                l = (u8) classe->constant_pool[i].info.Double.high_bytes << 32;
                l = l | classe->constant_pool[i].info.Double.low_bytes;
                fprintf(file, "[%d]CONSTANT_Double_info:\n", (i + 1));
                fprintf(file, "\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Double.high_bytes);
                fprintf(file, "\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Double.low_bytes);
                fprintf(file, "\tDouble:              \t%f\n", l);
                i++;
                fprintf(file, "[%d](large numeric continued)\n", (i + 1));
                break;
            case CONSTANT_NameAndType:
                index = classe->constant_pool[i].info.NameAndType.name_index - 1;
                derreferencia = dereferencia(index, classe);
                index = classe->constant_pool[i].info.NameAndType.descriptor_index - 1;
                derreferencia2 = dereferencia(index, classe);
                fprintf(file, "[%d]CONSTANT_NameAndType_info:\n", (i + 1));
                fprintf(file, "\tName:                \tCP INFO #%d < %s >\n",
                        classe->constant_pool[i].info.NameAndType.name_index, derreferencia);
                fprintf(file, "\tDescriptor:          \tCP INFO #%d < %s >\n",
                        classe->constant_pool[i].info.NameAndType.descriptor_index, derreferencia2);
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
    char *derreferencia = NULL, *derreferencia2 = NULL;
    int index = 0;
    fprintf(file, ">>>Fields<<<\n");
    for (int i = 0; i < classe->fields_count; i++) {
        index = classe->fields[i].name_index - 1;
        derreferencia = dereferencia(index, classe);
        index = classe->fields[i].descriptor_index - 1;
        derreferencia2 = dereferencia(index, classe);
        fprintf(file, "[%d]", i);
        for (int j = 0; j < classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.length; j++)
            fprintf(file, "%c", classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.bytes[j]);
        fprintf(file, "\n");
        fprintf(file, "\tAccess Flags:    \t%d\n", classe->fields[i].access_flags);
        fprintf(file, "\tName Index:      \tCP INFO #%d %s\n", classe->fields[i].name_index, derreferencia);
        fprintf(file, "\tDescriptor Index:\tCP INFO #%d %s\n", classe->fields[i].descriptor_index, derreferencia2);
        fprintf(file, "\tAttributes Count:\t%d\n", classe->fields[i].attributes_count);
        for (int j = 0; j < classe->fields[i].attributes_count; j++) {
            fprintf(file, "\t[%d]", j);
            for (int k = 0; k < classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index -
                                                      1].info.Utf8.length; k++)
                fprintf(file, "%c", classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index -
                                                          1].info.Utf8.bytes[k]);
            fprintf(file, "\n");
            imprime_attribute_file(&classe->fields[i].attributes[j], classe, file);
        }
    }
}

void imprime_attribute_file(attribute_info *attributeInfo, ClassFile *classe, FILE *file) {
    char *derreferencia = NULL;
    char *tipoAtributo;
    u2 index = attributeInfo->attribute_name_index - 1;
    u8 l;
    float f;
    int i;
    tipoAtributo = (char *) malloc(classe->constant_pool[index].info.Utf8.length * sizeof(char));
    for (int l = 0; l < classe->constant_pool[index].info.Utf8.length; l++) {
        fprintf(file, "%c", classe->constant_pool[index].info.Utf8.bytes[l]);
        tipoAtributo[l] = classe->constant_pool[index].info.Utf8.bytes[l];
    }
    index = attributeInfo->attribute_name_index - 1;
    derreferencia = dereferencia(index,classe);
    fprintf(file, "\n");
    fprintf(file, "\t\tName Index:      \tCP INFO #%d < %s >\n", attributeInfo->attribute_name_index, derreferencia);
    fprintf(file, "\t\tAttribute Lenght:\t%d\n", attributeInfo->attribute_length);

    if (attributeInfo->attribute_length > 0) {
        if (!strcmp(tipoAtributo, "ConstantValue")) {
            index = attributeInfo->info.ConstantValue.constantvalue_index - 1;
            switch (classe->constant_pool[index].tag){
                case CONSTANT_Long:
                    l = (u8)classe->constant_pool[index].info.Long.high_bytes<<32|classe->constant_pool[index].info.Long.low_bytes;
                    fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d < %ld >", attributeInfo->info.ConstantValue.constantvalue_index, l);
                break;
                case CONSTANT_Double:
                    l = (u8)classe->constant_pool[index].info.Double.high_bytes<<32|classe->constant_pool[index].info.Double.low_bytes;
                    fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d < %f >", attributeInfo->info.ConstantValue.constantvalue_index, l);
                break;
                case CONSTANT_Float:
                    f = (float)classe->constant_pool[index].info.Float.bytes;
                    fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d < %f >", attributeInfo->info.ConstantValue.constantvalue_index, f);
                break;
                case CONSTANT_Integer:
                    i = (int)classe->constant_pool[index].info.Integer.bytes;
                    fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d < %d >", attributeInfo->info.ConstantValue.constantvalue_index, i);
                break;
                case CONSTANT_String:
                    index = classe->constant_pool[index].info.String.string_index - 1;
                    derreferencia = dereferencia(index,classe);
                    fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d < %s >", attributeInfo->info.ConstantValue.constantvalue_index, derreferencia);
                break;
            }
        }
        else if (!strcmp(tipoAtributo, "Code")) {
            fprintf(file, "\t\tMax Stack:          \t%d\n", attributeInfo->info.CodeAttribute.max_stack);
            fprintf(file, "\t\tMax Locals:         \t%d\n", attributeInfo->info.CodeAttribute.max_locals);
            fprintf(file, "\t\tCode Length:        \t%d\n", attributeInfo->info.CodeAttribute.code_length);
            fprintf(file, "\t\tCode:\t \n");
            for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++) {
                Instrucao mapa[0xCA];
                u1 opcode = attributeInfo->info.CodeAttribute.code[i];
                carrega_instrucoes(mapa);
                fprintf(file, "\t\t\t\t\t%d: %s\n", i, mapa[opcode].mnemonico);
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
                imprime_attribute_file(&(attributeInfo->info.CodeAttribute.attributes[k]), classe, file);
            }
        }
        else if (!strcmp(tipoAtributo, "Exceptions")) {
            fprintf(file, "\t\tNumber of Exceptions:\t%d\n", attributeInfo->info.Exception.number_of_exceptions);
            for (int i = 0; i < attributeInfo->info.Exception.number_of_exceptions; i++) {
                index = attributeInfo->info.Exception.exception_index_table[i] - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tException Index:\tCP INFO #%d < %s >\n",
                        attributeInfo->info.Exception.exception_index_table[i], derreferencia);
            }
        }
        else if (!strcmp(tipoAtributo, "InnerClasses")) {
            fprintf(file, "\t\tNumber of Classes:\t%d\n", attributeInfo->info.InnerClasses.number_of_classes);
            for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++) {
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tInner Class Index:       \tCP INFO #%d < %s >\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_class_info_index, derreferencia);
                index = attributeInfo->info.InnerClasses.classes[i].outer_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tOuter Class Index:       \tCP INFO #%d < %s >\n",
                       attributeInfo->info.InnerClasses.classes[i].outer_class_info_index, derreferencia);
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tInner Name Index:        \tCP INFO #%d < %s >\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_name_index, derreferencia);
                fprintf(file, "\t\tInner Class Access Flags:\t%d\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
            }
        }
        else if (!strcmp(tipoAtributo, "SourceFile")) {
            index = attributeInfo->info.Sourcefile.sourcefile_index - 1;
            derreferencia = dereferencia(index,classe);
            fprintf(file, "\t\tSource File Index: \tCP INFO #%d < %s >\n", attributeInfo->info.Sourcefile.sourcefile_index, derreferencia);
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
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tName Index:      \tCP INFO #%d < %s >\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index, derreferencia);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tDescriptor Index:\tCP INFO #%d < %s >\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index, derreferencia);
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
    char *derreferencia = NULL;
    int index = 0;
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
        index = classe->methods[i].name_index - 1;
        derreferencia = dereferencia(index,classe);
        fprintf(file, "\tName Index:      \tCP INFO #%d < %s >\n", classe->methods[i].name_index, derreferencia);
        index = classe->methods[i].descriptor_index - 1;
        derreferencia = dereferencia(index,classe);
        fprintf(file, "\tDescriptor Index:\tCP INFO #%d < %s >\n", classe->methods[i].descriptor_index, derreferencia);
        fprintf(file, "\tAttributes Count:\t%d\n", classe->methods[i].attributes_count);
        for (int j = 0; j < classe->methods[i].attributes_count; j++) {
            fprintf(file, "\t[%d]", j);
            imprime_attribute_file(&(classe->methods[i].attributes[j]), classe, file);
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
        imprime_attribute_file(&(classe->attributes[i]), classe, file);
    }
}

void carrega_instrucoes(Instrucao *mapa) {
    FILE *arq_mapa = fopen("mapa.txt", "r");

    if (!(arq_mapa = fopen("mapa.txt", "r"))) {
        printf("ERRO: arquivo \"%s\" nao existe.\n", "mapa.txt");
        exit(ERRO_ARQUIVO);
    }

    for (int i = 0; i < 0xCA; i++) {
        fscanf(arq_mapa, "%[^\n]s", mapa[i].mnemonico);
    }
    fclose(arq_mapa);
}

char* dereferencia(u2 index, ClassFile *classe) {
    char *nome;
    int i;
    nome = (char *) malloc((classe->constant_pool[index].info.Utf8.length + 1) * sizeof(char));
    for (i = 0; i < classe->constant_pool[index].info.Utf8.length; i++) {
        nome[i] = classe->constant_pool[index].info.Utf8.bytes[i];
    }
    nome[i] = '\0';
    return nome;
}

int verifica_match(ClassFile *classe, char *nome) {
    char *temp, *nomeThisClass;
    char c;
    int i = 0, index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;

    temp = (char *) malloc(strlen(nome) * sizeof(char));
    while(c != '.') {
        c = nome[i];
        temp[i] = nome[i];
        i++;
    }
    i+=1;
    temp[i] = '\0';
    nomeThisClass = dereferencia(index, classe);
    if(!strcmp(temp, nomeThisClass)) {
        return ERRO_MATCHING;
    }
    return SUCESSO;
}
