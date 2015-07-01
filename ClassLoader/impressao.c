/**
* @file impressao.c
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo com as implementacoes de funcoes relacionadas a impressao do conteudo da classe em tela e em arquivo.
*/

#include "impressao.h"

void imprime_general_information(ClassFile *classe)
{
    char *nomeThisClass, *nomeSuperClass;
    int index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;
    nomeThisClass = dereferencia(index, classe);
    index = classe->constant_pool[classe->super_class - 1].info.Class.name_index - 1;
    nomeSuperClass = dereferencia(index, classe);
    printf("\n");
    printf(">>>General Information<<<\n");
    printf("Minor version:      \t%d\n", classe->minor_version);
    printf("Major version:      \t%d\n", classe->major_version);
    printf("Constant pool count:\t%d\n", classe->constant_pool_count);
    printf("Access flags:       \t0x%x\n", classe->access_flags);
    printf("This class:         \tCP INFO #%d <%s>\n", classe->this_class, nomeThisClass);
    printf("Super class:        \tCP INFO #%d <%s>\n", classe->super_class, nomeSuperClass);
    printf("Interfaces count:   \t%d\n", classe->interfaces_count);
    printf("Fields count:       \t%d\n", classe->fields_count);
    printf("Methods count:      \t%d\n", classe->methods_count);
    printf("Attributes count:   \t%d\n", classe->attributes_count);
    printf("\n");
}

void imprime_constant_pool(ClassFile *classe)
{
    u8 l;
    char *derreferencia = NULL, *derreferencia2 = NULL, *derreferencia3 = NULL;
    printf("\n");
    printf(">>>Constant Pool<<<\n");
    int index = 0;
    float fvalue;
    double dvalue;
    for (int i = 0;  i < (classe->constant_pool_count - 1); i++)   /* Armazena os valores de cada elemento do constant pool */
    {
        switch (classe->constant_pool[i].tag)   /* Existem respostas diferentes para cada tag */
        {
        case CONSTANT_Class:
            index = classe->constant_pool[i].info.Class.name_index - 1;
            derreferencia = dereferencia(index, classe);
            printf("[%d]CONSTANT_Class_info:\n", (i + 1));
            printf("\tClass name:          \tCP INFO #%d <%s>\n", classe->constant_pool[i].info.Class.name_index,
                   derreferencia);
            break;
        case CONSTANT_Fieldref:
            index = classe->constant_pool[i].info.Fieldref.class_index - 1;
            index = classe->constant_pool[index].info.Class.name_index - 1;
            derreferencia = dereferencia(index, classe);
            printf("[%d]CONSTANT_Fieldref_info:\n", (i + 1));
            printf("\tClass name:          \tCP INFO #%d <%s>\n",
                   classe->constant_pool[i].info.Fieldref.class_index, derreferencia);
            index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
            derreferencia = dereferencia(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
            derreferencia2 = dereferencia(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                          classe);
            printf("\tName and type:       \tCP INFO #%d  <%s%s>\n",
                   classe->constant_pool[i].info.Fieldref.name_and_type_index, derreferencia, derreferencia2);
            break;
        case CONSTANT_Methodref:
            index = classe->constant_pool[i].info.Fieldref.class_index - 1;
            index = classe->constant_pool[index].info.Class.name_index - 1;
            derreferencia = dereferencia(index, classe);
            printf("[%d]CONSTANT_Methodref_info:\n", (i + 1));
            printf("\tClass name:          \tCP INFO #%d <%s>\n",
                   classe->constant_pool[i].info.Methodref.class_index, derreferencia);
            index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
            derreferencia = dereferencia(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
            derreferencia2 = dereferencia(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                          classe);
            printf("\tName and type:       \tCP INFO #%d <%s%s>\n",
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
            printf("\tClass name:          \tCP INFO #%d <%s>\n",
                   classe->constant_pool[i].info.InterfaceMethodref.class_index, derreferencia);
            printf("\tName and type:       \tCP INFO #%d <%s>\n",
                   classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index, derreferencia2);
            break;
        case CONSTANT_String:
            index = classe->constant_pool[i].info.String.string_index - 1;
            derreferencia = dereferencia(index, classe);
            printf("[%d]CONSTANT_String_info:\n", (i + 1));
            printf("\tString:              \tCP INFO #%d <%s>\n", classe->constant_pool[i].info.String.string_index, derreferencia);
            break;
        case CONSTANT_Integer:
            printf("[%d]CONSTANT_Integer_info:\n", (i + 1));
            printf("\tBytes:               \t0x%x\n", classe->constant_pool[i].info.Integer.bytes);
            printf("\tInteger:             \t%d\n", classe->constant_pool[i].info.Integer.bytes);
            break;
        case CONSTANT_Float:
			memcpy(&fvalue,&(classe->constant_pool[i].info.Float.bytes),sizeof(u4));
            printf("[%d]CONSTANT_Float_info:\n", (i + 1));
            printf("\tBytes:               \t0x%x\n", classe->constant_pool[i].info.Float.bytes);
            printf("\tFloat:               \t%f\n", fvalue);
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
            memcpy(&dvalue,&l,sizeof(u8));
            printf("[%d]CONSTANT_Double_info:\n", (i + 1));
            printf("\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Double.high_bytes);
            printf("\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Double.low_bytes);
            printf("\tDouble:              \t%f\n",dvalue);
            i++;
            printf("[%d](large numeric continued)\n", (i + 1));
            break;
        case CONSTANT_NameAndType:
            index = classe->constant_pool[i].info.NameAndType.name_index - 1;
            derreferencia = dereferencia(index, classe);
            index = classe->constant_pool[i].info.NameAndType.descriptor_index - 1;
            derreferencia2 = dereferencia(index, classe);
            printf("[%d]CONSTANT_NameAndType_info:\n", (i + 1));
            printf("\tName:                \tCP INFO #%d <%s>\n", classe->constant_pool[i].info.NameAndType.name_index, derreferencia);
            printf("\tDescriptor:          \tCP INFO #%d <%s>\n",
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

void imprime_fields(ClassFile *classe)
{
    char *derreferencia = NULL, *derreferencia2 = NULL;
    int index = 0;
    printf(">>>Fields<<<\n");
    for (int i = 0; i < classe->fields_count; i++)
    {
        printf("[%d]", i);
        for (int j = 0; j < classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.length; j++)
            printf("%c", classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.bytes[j]);
        printf("\n");
        index = classe->fields[i].name_index - 1;
        derreferencia = dereferencia(index, classe);
        index = classe->fields[i].descriptor_index - 1;
        derreferencia2 = dereferencia(index, classe);
        printf("\tAccess Flags:    \t%d\n", classe->fields[i].access_flags);
        printf("\tName Index:      \tCP INFO #%d <%s>\n", classe->fields[i].name_index, derreferencia);
        printf("\tDescriptor Index:\tCP INFO #%d <%s>\n", classe->fields[i].descriptor_index, derreferencia2);
        printf("\tAttributes Count:\t%d\n", classe->fields[i].attributes_count);
        for (int j = 0; j < classe->fields[i].attributes_count; j++)
        {
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

void imprime_attribute(attribute_info *attributeInfo, ClassFile *classe)
{
    char *derreferencia = NULL;
    u8 l;
    char *tipoAtributo = NULL;
    u2 index = attributeInfo->attribute_name_index - 1,index1;
    int i,iterat;
    tipoAtributo = (char *) malloc((classe->constant_pool[index].info.Utf8.length+1) * sizeof(char));
    float fvalue;
    double dvalue;
    for (iterat = 0; iterat < classe->constant_pool[index].info.Utf8.length; iterat++)
    {
        printf("%c", classe->constant_pool[index].info.Utf8.bytes[iterat]);
        tipoAtributo[iterat] = classe->constant_pool[index].info.Utf8.bytes[iterat];
    }
    tipoAtributo[iterat] = '\0';
    index = attributeInfo->attribute_name_index - 1;
    derreferencia = dereferencia(index,classe);
    printf("\n");
    printf("\t\tName Index:      \tCP INFO #%d <%s>\n", attributeInfo->attribute_name_index, derreferencia);
    printf("\t\tAttribute Lenght:\t%d\n", attributeInfo->attribute_length);

    if (attributeInfo->attribute_length > 0)
    {
        if (!strcmp(tipoAtributo, "ConstantValue"))
        {
            index = attributeInfo->info.ConstantValue.constantvalue_index - 1;

            switch (classe->constant_pool[index].tag)
            {
            case CONSTANT_Long:
                l = (u8)classe->constant_pool[index].info.Long.high_bytes<<32|classe->constant_pool[index].info.Long.low_bytes;
                printf("\t\tConstant Value Index: \tCP INFO #%d <%ld>", attributeInfo->info.ConstantValue.constantvalue_index, l);
                break;
            case CONSTANT_Double:
                l = (u8)classe->constant_pool[index].info.Double.high_bytes<<32|classe->constant_pool[index].info.Double.low_bytes;
				memcpy(&dvalue,&(classe->constant_pool[index].info.Float.bytes),sizeof(u8));
                printf("\t\tConstant Value Index: \tCP INFO #%d <%f>", attributeInfo->info.ConstantValue.constantvalue_index, dvalue);
                break;
            case CONSTANT_Float:
				memcpy(&fvalue,&(classe->constant_pool[index].info.Float.bytes),sizeof(u4));
                printf("\t\tConstant Value Index: \tCP INFO #%d <%f>", attributeInfo->info.ConstantValue.constantvalue_index, fvalue);
                break;
            case CONSTANT_Integer:
                i = (int32_t)classe->constant_pool[index].info.Integer.bytes;
                printf("\t\tConstant Value Index: \tCP INFO #%d <%d>", attributeInfo->info.ConstantValue.constantvalue_index, i);
                break;
            case CONSTANT_String:
                index1 = classe->constant_pool[index].info.String.string_index - 1;
                derreferencia = dereferencia(index1,classe);
                printf("\t\tConstant Value Index: \tCP INFO #%d <%s>", attributeInfo->info.ConstantValue.constantvalue_index, derreferencia);
                break;
            }
        }
        else if (!strcmp(tipoAtributo, "Code"))
        {
            printf("\t\tMax Stack:          \t%d\n", attributeInfo->info.CodeAttribute.max_stack);
            printf("\t\tMax Locals:         \t%d\n", attributeInfo->info.CodeAttribute.max_locals);
            printf("\t\tCode Length:        \t%d\n", attributeInfo->info.CodeAttribute.code_length);
            printf("\t\tCode:\t \n");
            for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++)
            {
                Instrucao mapa[0xCA];
                u1 opcode = attributeInfo->info.CodeAttribute.code[i], instrIndex1, instrIndex2;
                u2 instrIndex;
                int16_t offset;
                char *instrRef;
                carrega_mnemonicos(mapa);
                printf("\t\t\t\t\t%d: %s\t", i, mapa[opcode].mnemonico);
                int j;
                double dvalue;
                switch(mapa[opcode].req_cp) {
                    case REQ_METHODREF_1:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i];
                        instrRef = dereferencia_methodinfo(instrIndex - 1, classe);
                        printf("#%hu\t<%s>\t", instrIndex, instrRef);
                        break;
                    case REQ_METHODREF_2:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << 8));
                        instrRef = dereferencia_methodinfo(instrIndex - 1, classe);
                        printf("#%hu\t<%s>\t", instrIndex, instrRef);
                        break;
                    case REQ_FIELDREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << 8));
                        instrRef = dereferencia_fieldrefinfo(instrIndex - 1, classe);
                        printf("#%hu\t<%s>\t", instrIndex, instrRef);
                        break;
                    case REQ_JMPREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        offset = (int16_t) (instrIndex2 | (instrIndex1 << 8));
                        printf("%d\t(%d)\t", (offset - 2) + i, offset);
                        break;
                    case REQ_LDCREF_1:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i] - 1;
                        printf("%hu\t", instrIndex + 1);
                        switch(classe->constant_pool[instrIndex].tag) {
                            case CONSTANT_Integer:
                                printf("<%d>\t", classe->constant_pool[instrIndex].info.Integer.bytes);
                                break;
                            case CONSTANT_Float:
                                memcpy(&fvalue, &(classe->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
                                printf("<%f>\t", fvalue);
                                break;
                            case CONSTANT_Long:
                                l = (u8) classe->constant_pool[instrIndex].info.Long.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Long.low_bytes;
                                printf("<%ld>\t", l);
                                break;
                            case CONSTANT_Double:
                                l = (u8) classe->constant_pool[instrIndex].info.Double.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Double.low_bytes;
                                memcpy(&dvalue,&l,sizeof(u8));
                                printf("<%f>\t", dvalue);
                                break;
                        }
                        break;
                    case REQ_LDCREF_2:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << sizeof(u1))) - 1;
                        printf("%hu\t", instrIndex + 1);
                        switch(classe->constant_pool[instrIndex].tag) {
                            case CONSTANT_Integer:
                                printf("<%d>\t", classe->constant_pool[instrIndex].info.Integer.bytes);
                                break;
                            case CONSTANT_Float:
                                memcpy(&fvalue, &(classe->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
                                printf("<%f>\t", fvalue);
                                break;
                            case CONSTANT_Long:
                                l = (u8) classe->constant_pool[instrIndex].info.Long.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Long.low_bytes;
                                printf("<%ld>\t", l);
                                break;
                            case CONSTANT_Double:
                                l = (u8) classe->constant_pool[instrIndex].info.Double.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Double.low_bytes;
                                memcpy(&dvalue,&l,sizeof(u8));
                                printf("<%f>\t", dvalue);
                                break;
                        }
                        break;
                    case REQ_ARRAYREF:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i];
                        printf("%hu\t", instrIndex);
                        switch(instrIndex) {
                            case 0:
                                printf("(ref)\t");
                                break;
                            case 4:
                                printf("(boolean)\t");
                                break;
                            case 5:
                                printf("(char)\t");
                                break;
                            case 6:
                                printf("(float)\t");
                                break;
                            case 7:
                                printf("(double)\t");
                                break;
                            case 8:
                                printf("(byte)\t");
                                break;
                            case 9:
                                printf("(short)\t");
                                break;
                            case 10:
                                printf("(int)\t");
                                break;
                            case 11:
                                printf("(long)\t");
                                break;
                            default:
                                break;
                        }
                        break;
                    case REQ_IINCREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        printf("%hu by %hu\t", instrIndex1, instrIndex2);
                        break;
                    default:
                        for(j = 0; j < mapa[opcode].operandos; j++) {
                            printf("%hu\t", attributeInfo->info.CodeAttribute.code[++i]);
                        }
                        break;
                }
                printf("\n");
            }
            printf("\n\t\tException Table Length: \t%d\n", attributeInfo->info.CodeAttribute.exception_table_length);
            for (int i = 0; i < attributeInfo->info.CodeAttribute.exception_table_length; i++)
            {
                printf("\t\tStart PC:  \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].start_pc);
                printf("\t\tEnd PC:    \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].end_pc);
                printf("\t\tHandler PC:\t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].handler_pc);
                printf("\t\tEnd PC:    \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].catch_type);
            }
            printf("\t\tCode Attributes Count:\t%d\n", attributeInfo->info.CodeAttribute.attributes_count);
            for (int k = 0; k < attributeInfo->info.CodeAttribute.attributes_count; k++)
            {
                printf("\t\t[%d]", k);
                imprime_attribute(&(attributeInfo->info.CodeAttribute.attributes[k]), classe);
            }
        }
        else if (!strcmp(tipoAtributo, "Exceptions"))
        {
            printf("\t\tNumber of Exceptions:\t%d\n", attributeInfo->info.Exception.number_of_exceptions);
            for (int i = 0; i < attributeInfo->info.Exception.number_of_exceptions; i++)
            {
                index = attributeInfo->info.Exception.exception_index_table[i] - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tException Index:\tCP INFO #%d <%s>\n", attributeInfo->info.Exception.exception_index_table[i], derreferencia);
            }
        }
        else if (!strcmp(tipoAtributo, "InnerClasses"))
        {
            printf("\t\tNumber of Classes:\t%d\n", attributeInfo->info.InnerClasses.number_of_classes);
            for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++)
            {
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tInner Class Index:       \tCP INFO #%d <%s>\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_class_info_index, derreferencia);
                index = attributeInfo->info.InnerClasses.classes[i].outer_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tOuter Class Index:       \tCP INFO #%d <%s>\n",
                       attributeInfo->info.InnerClasses.classes[i].outer_class_info_index, derreferencia);
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tInner Name Index:  \tCP INFO #%d <%s>\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_name_index, derreferencia);
                printf("\t\tInner Class Access Flags:\t%d\n",
                       attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
            }
        }
        else if (!strcmp(tipoAtributo, "SourceFile"))
        {
            index = attributeInfo->info.Sourcefile.sourcefile_index - 1;
            derreferencia = dereferencia(index,classe);
            printf("\t\tSource File Index: \tCP INFO #%d <%s>\n", attributeInfo->info.Sourcefile.sourcefile_index, derreferencia);
        }
        else if (!strcmp(tipoAtributo, "LineNumberTable"))
        {
            printf("\t\tNumber of Lines:\t%d\n", attributeInfo->info.LineNumberTable.line_number_table_length);
            for (int i = 0; i < attributeInfo->info.LineNumberTable.line_number_table_length; i++)
            {
                printf("\t\tLine Number: \t%d\n", attributeInfo->info.LineNumberTable.line_number_table[i].line_number);
                printf("\t\tStart PC:    \t%d\n", attributeInfo->info.LineNumberTable.line_number_table[i].start_pc);
            }
        }
        else if (!strcmp(tipoAtributo, "LocalVariableTable"))
        {
            printf("\t\tTable Length:    \t%d\n", attributeInfo->info.LocalVariableTable.local_variable_table_length);
            for (int i = 0; i < attributeInfo->info.LocalVariableTable.local_variable_table_length; i++)
            {
                printf("\t\tStart PC:        \t%d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
                printf("\t\tLength:          \t%d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].length);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tName Index:      \tCP INFO #%d <%s>\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index, derreferencia);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index - 1;
                derreferencia = dereferencia(index,classe);
                printf("\t\tDescriptor Index:\tCP INFO #%d <%s>\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index, derreferencia);
                printf("\t\tIndex:           \t%d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].index);
            }
        }
        else
        {
            printf("\t\tDefault Data: \t");
            for (int i = 0; i < attributeInfo->attribute_length; i++)
            {
                printf("%x", attributeInfo->info.Default.data[i]);
            }
            printf("\n");
        }
    }
}

void imprime_methods(ClassFile *classe)
{
    char *derreferencia = NULL;
    int index = 0;
    printf("\n");
    printf(">>>Methods<<<\n");
    printf("\n");
    printf("Methods Count: \t%d\n", classe->methods_count);

    for (int i = 0; i < classe->methods_count; i++)
    {
        printf("[%d]", i);
        for (int j = 0; j < classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.length; j++)
            printf("%c", classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.bytes[j]);
        printf("\n");
        printf("\tAccess Flags:    \t%d\n", classe->methods[i].access_flags);
        index = classe->methods[i].name_index - 1;
        derreferencia = dereferencia(index,classe);
        printf("\tName Index:      \tCP INFO #%d <%s>\n", classe->methods[i].name_index, derreferencia);
        index = classe->methods[i].descriptor_index - 1;
        derreferencia = dereferencia(index,classe);
        printf("\tDescriptor Index:\tCP INFO #%d <%s>\n", classe->methods[i].descriptor_index, derreferencia);
        printf("\tAttributes Count:\t%d\n", classe->methods[i].attributes_count);
        for (int j = 0; j < classe->methods[i].attributes_count; j++)
        {
            printf("\t[%d]", j);
            imprime_attribute(&(classe->methods[i].attributes[j]), classe);
        }
    }
}

void imprime_attributes(ClassFile *classe)
{
    printf("\n");
    printf(">>>Attributes<<<\n");
    printf("\n");
    printf("Attributes Count: \t%d\n", classe->attributes_count);
    for (int i = 0; i < classe->attributes_count; i++)
    {
        printf("\t[%d]", i);
        imprime_attribute(&(classe->attributes[i]), classe);
    }
}

void imprime_general_information_file(ClassFile *classe, FILE *file)
{
    char *derreferencia = NULL;
    int index = 0;
    fprintf(file, ">>>General Information<<<\n");
    fprintf(file, "Minor version:      \t%d\n", classe->minor_version);
    fprintf(file, "Major version:      \t%d\n", classe->major_version);
    fprintf(file, "Constant pool count:\t%d\n", classe->constant_pool_count);
    fprintf(file, "Access flags:       \t0x%x\n", classe->access_flags);
    index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;
    derreferencia = dereferencia(index,classe);
    fprintf(file, "This class:         \tCP INFO #%d <%s>\n", classe->this_class, derreferencia);
    index = classe->constant_pool[classe->super_class - 1].info.Class.name_index - 1;
    derreferencia = dereferencia(index,classe);
    fprintf(file, "Super class:        \tCP INFO #%d <%s>\n", classe->super_class, derreferencia);
    fprintf(file, "Interfaces count:   \t%d\n", classe->interfaces_count);
    fprintf(file, "Fields count:       \t%d\n", classe->fields_count);
    fprintf(file, "Methods count:      \t%d\n", classe->methods_count);
    fprintf(file, "Attributes count:   \t%d\n", classe->attributes_count);
    fprintf(file, "\n");
}

void imprime_constant_pool_file(ClassFile *classe, FILE *file)
{
    char *derreferencia = NULL, *derreferencia2 = NULL, *derreferencia3 = NULL;
    int index = 0;
    u8 l;
    fprintf(file, "\n");
    fprintf(file, ">>>Constant Pool<<<\n");
    for (int i = 0;
            i < (classe->constant_pool_count - 1); i++)   /* Armazena os valores de cada elemento do constant pool */
    {
    float fvalue;
    double dvalue;
        switch (classe->constant_pool[i].tag)   /* Existem respostas diferentes para cada tag */
        {
        case CONSTANT_Class:
            index = classe->constant_pool[i].info.Class.name_index - 1;
            derreferencia = dereferencia(index, classe);
            fprintf(file, "[%d]CONSTANT_Class_info:\n", (i + 1));
            fprintf(file, "\tClass name:          \tCP INFO #%d <%s>\n", classe->constant_pool[i].info.Class.name_index, derreferencia);
            break;
        case CONSTANT_Fieldref:
            index = classe->constant_pool[i].info.Fieldref.class_index - 1;
            index = classe->constant_pool[index].info.Class.name_index - 1;
            derreferencia = dereferencia(index, classe);
            fprintf(file, "[%d]CONSTANT_Fieldref_info:\n", (i + 1));
            fprintf(file, "\tClass name:          \tCP INFO #%d <%s>\n",
                    classe->constant_pool[i].info.Fieldref.class_index, derreferencia);
            index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
            derreferencia = dereferencia(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
            derreferencia2 = dereferencia(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                          classe);
            fprintf(file, "\tName and type:       \tCP INFO #%d <%s%s>\n",
                    classe->constant_pool[i].info.Fieldref.name_and_type_index, derreferencia, derreferencia2);
            break;
        case CONSTANT_Methodref:
            index = classe->constant_pool[i].info.Fieldref.class_index - 1;
            index = classe->constant_pool[index].info.Class.name_index - 1;
            derreferencia = dereferencia(index, classe);
            fprintf(file, "[%d]CONSTANT_Methodref_info:\n", (i + 1));
            fprintf(file, "\tClass name:          \tCP INFO #%d <%s>\n",
                    classe->constant_pool[i].info.Methodref.class_index, derreferencia);
            index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
            derreferencia = dereferencia(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
            derreferencia2 = dereferencia(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                          classe);
            fprintf(file, "\tName and type:       \tCP INFO #%d <%s%s>\n",
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
            fprintf(file, "\tClass name:          \tCP INFO #%d <%s>\n",
                    classe->constant_pool[i].info.InterfaceMethodref.class_index, derreferencia);
            fprintf(file, "\tName and type:       \tCP INFO #%d <%s>\n",
                    classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index, derreferencia2);
            break;
        case CONSTANT_String:
            index = classe->constant_pool[i].info.String.string_index - 1;
            derreferencia = dereferencia(index, classe);
            fprintf(file, "[%d]CONSTANT_String_info:\n", (i + 1));
            fprintf(file, "\tString:              \tCP INFO #%d <%s>\n",
                    classe->constant_pool[i].info.String.string_index, derreferencia);
            break;
        case CONSTANT_Integer:
            fprintf(file, "[%d]CONSTANT_Integer_info:\n", (i + 1));
            fprintf(file, "\tBytes:               \t0x%x\n", classe->constant_pool[i].info.Integer.bytes);
            fprintf(file, "\tInteger:             \t%d\n", classe->constant_pool[i].info.Integer.bytes);
            break;
        case CONSTANT_Float:

            memcpy(&fvalue,&(classe->constant_pool[i].info.Float.bytes),sizeof(u4));
            fprintf(file, "[%d]CONSTANT_Float_info:\n", (i + 1));
            fprintf(file, "\tBytes:               \t0x%x\n", classe->constant_pool[i].info.Float.bytes);
            fprintf(file, "\tFloat:               \t%f\n", fvalue);
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
            memcpy(&dvalue,&l,sizeof(u8));
            fprintf(file, "[%d]CONSTANT_Double_info:\n", (i + 1));
            fprintf(file, "\tHigh bytes:          \t0x%x\n", classe->constant_pool[i].info.Double.high_bytes);
            fprintf(file, "\tLow bytes:           \t0x%x\n", classe->constant_pool[i].info.Double.low_bytes);
            fprintf(file, "\tDouble:              \t%f\n", dvalue);
            i++;
            fprintf(file, "[%d](large numeric continued)\n", (i + 1));
            break;
        case CONSTANT_NameAndType:
            index = classe->constant_pool[i].info.NameAndType.name_index - 1;
            derreferencia = dereferencia(index, classe);
            index = classe->constant_pool[i].info.NameAndType.descriptor_index - 1;
            derreferencia2 = dereferencia(index, classe);
            fprintf(file, "[%d]CONSTANT_NameAndType_info:\n", (i + 1));
            fprintf(file, "\tName:                \tCP INFO #%d <%s>\n",
                    classe->constant_pool[i].info.NameAndType.name_index, derreferencia);
            fprintf(file, "\tDescriptor:          \tCP INFO #%d <%s>\n",
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

void imprime_fields_file(ClassFile *classe, FILE *file)
{
    char *derreferencia = NULL, *derreferencia2 = NULL;
    int index = 0;
    fprintf(file, ">>>Fields<<<\n");
    for (int i = 0; i < classe->fields_count; i++)
    {
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
        for (int j = 0; j < classe->fields[i].attributes_count; j++)
        {
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

void imprime_attribute_file(attribute_info *attributeInfo, ClassFile *classe, FILE *file)
{
    char *derreferencia = NULL;
    char *tipoAtributo=NULL;
    u2 index = attributeInfo->attribute_name_index - 1;
    u8 l;
    int i,iterat;
    tipoAtributo = (char *) malloc((classe->constant_pool[index].info.Utf8.length + 1) * sizeof(char));
    for (iterat = 0; iterat < classe->constant_pool[index].info.Utf8.length; iterat++)
    {
        fprintf(file, "%c", classe->constant_pool[index].info.Utf8.bytes[iterat]);
        tipoAtributo[iterat] = classe->constant_pool[index].info.Utf8.bytes[iterat];
    }
    tipoAtributo[iterat] = '\0';
    index = attributeInfo->attribute_name_index - 1;
    derreferencia = dereferencia(index,classe);
    fprintf(file, "\n");
    fprintf(file, "\t\tName Index:      \tCP INFO #%d <%s>\n", attributeInfo->attribute_name_index, derreferencia);
    fprintf(file, "\t\tAttribute Lenght:\t%d\n", attributeInfo->attribute_length);

    if (attributeInfo->attribute_length > 0)
    {
        if (!strcmp(tipoAtributo, "ConstantValue"))
        {
            index = attributeInfo->info.ConstantValue.constantvalue_index - 1;
            float fvalue;
            double dvalue;
            switch (classe->constant_pool[index].tag)
            {
            case CONSTANT_Long:
                l = (u8)classe->constant_pool[index].info.Long.high_bytes<<32|classe->constant_pool[index].info.Long.low_bytes;
                fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d <%ld>", attributeInfo->info.ConstantValue.constantvalue_index, l);
                break;
            case CONSTANT_Double:
                l = (u8)classe->constant_pool[index].info.Double.high_bytes<<32|classe->constant_pool[index].info.Double.low_bytes;
                memcpy(&dvalue,&l,sizeof(u8));
                fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d <%f>", attributeInfo->info.ConstantValue.constantvalue_index, dvalue);
                break;
            case CONSTANT_Float:
				memcpy(&fvalue,&(classe->constant_pool[index].info.Float.bytes),sizeof(u4));
                fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d <%f>", attributeInfo->info.ConstantValue.constantvalue_index, fvalue);
                break;
            case CONSTANT_Integer:
                i = (int)classe->constant_pool[index].info.Integer.bytes;
                fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d <%d>", attributeInfo->info.ConstantValue.constantvalue_index, i);
                break;
            case CONSTANT_String:
                index = classe->constant_pool[index].info.String.string_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tConstant Value Index: \tCP INFO #%d <%s>", attributeInfo->info.ConstantValue.constantvalue_index, derreferencia);
                break;
            }
        }
        else if (!strcmp(tipoAtributo, "Code"))
        {
            fprintf(file, "\t\tMax Stack:          \t%d\n", attributeInfo->info.CodeAttribute.max_stack);
            fprintf(file, "\t\tMax Locals:         \t%d\n", attributeInfo->info.CodeAttribute.max_locals);
            fprintf(file, "\t\tCode Length:        \t%d\n", attributeInfo->info.CodeAttribute.code_length);
            fprintf(file, "\t\tCode:\t \n");
            for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++)
            {
                Instrucao mapa[0xCA];
                u1 opcode = attributeInfo->info.CodeAttribute.code[i], instrIndex1, instrIndex2;
                u2 instrIndex;
                int16_t offset;
                char *instrRef;
                carrega_mnemonicos(mapa);
                fprintf(file, "\t\t\t\t\t%d: %s\t", i, mapa[opcode].mnemonico);
                int j;
                double dvalue;
                float fvalue;
                switch(mapa[opcode].req_cp) {
                    case REQ_METHODREF_1:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i];
                        instrRef = dereferencia_methodinfo(instrIndex - 1, classe);
                        fprintf(file, "#%hu\t<%s>\t", instrIndex, instrRef);
                        break;
                    case REQ_METHODREF_2:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << 8));
                        instrRef = dereferencia_methodinfo(instrIndex - 1, classe);
                        fprintf(file, "#%hu\t<%s>\t", instrIndex, instrRef);
                        break;
                    case REQ_FIELDREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << 8));
                        instrRef = dereferencia_fieldrefinfo(instrIndex - 1, classe);
                        fprintf(file, "#%hu\t<%s>\t", instrIndex, instrRef);
                        break;
                    case REQ_JMPREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        offset = (int16_t) (instrIndex2 | (instrIndex1 << 8));
                        fprintf(file, "%d\t(%d)\t", (offset - 2) + i, offset);
                        break;
                    case REQ_LDCREF_1:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i] - 1;
                        fprintf(file, "%hu\t", instrIndex + 1);
                        switch(classe->constant_pool[instrIndex].tag) {
                            case CONSTANT_Integer:
                                fprintf(file, "<%d>\t", classe->constant_pool[instrIndex].info.Integer.bytes);
                                break;
                            case CONSTANT_Float:
                                memcpy(&fvalue, &(classe->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
                                fprintf(file, "<%f>\t", fvalue);
                                break;
                            case CONSTANT_Long:
                                l = (u8) classe->constant_pool[instrIndex].info.Long.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Long.low_bytes;
                                fprintf(file, "<%ld>\t", l);
                                break;
                            case CONSTANT_Double:
                                l = (u8) classe->constant_pool[instrIndex].info.Double.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Double.low_bytes;
                                memcpy(&dvalue,&l,sizeof(u8));
                                fprintf(file, "<%f>\t", dvalue);
                                break;
                        }
                        break;
                    case REQ_LDCREF_2:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << sizeof(u1))) - 1;
                        fprintf(file, "%hu\t", instrIndex + 1);
                        switch(classe->constant_pool[instrIndex].tag) {
                            case CONSTANT_Integer:
                                fprintf(file, "<%d>\t", classe->constant_pool[instrIndex].info.Integer.bytes);
                                break;
                            case CONSTANT_Float:
                                memcpy(&fvalue, &(classe->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
                                fprintf(file, "<%f>\t", fvalue);
                                break;
                            case CONSTANT_Long:
                                l = (u8) classe->constant_pool[instrIndex].info.Long.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Long.low_bytes;
                                fprintf(file, "<%ld>\t", l);
                                break;
                            case CONSTANT_Double:
                                l = (u8) classe->constant_pool[instrIndex].info.Double.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Double.low_bytes;
                                memcpy(&dvalue,&l,sizeof(u8));
                                fprintf(file, "<%f>\t", dvalue);
                                break;
                        }
                        break;
                    case REQ_ARRAYREF:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i];
                        fprintf(file, "%hu\t", instrIndex);
                        switch(instrIndex) {
                            case 0:
                                fprintf(file, "(ref)\t");
                                break;
                            case 4:
                                fprintf(file, "(boolean)\t");
                                break;
                            case 5:
                                fprintf(file, "(char)\t");
                                break;
                            case 6:
                                fprintf(file, "(float)\t");
                                break;
                            case 7:
                                fprintf(file, "(double)\t");
                                break;
                            case 8:
                                fprintf(file, "(byte)\t");
                                break;
                            case 9:
                                fprintf(file, "(short)\t");
                                break;
                            case 10:
                                fprintf(file, "(int)\t");
                                break;
                            case 11:
                                fprintf(file, "(long)\t");
                                break;
                            default:
                                break;
                        }
                        break;
                    case REQ_IINCREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        fprintf(file, "%hu by %hu\t", instrIndex1, instrIndex2);
                        break;
                    default:
                        for(j = 0; j < mapa[opcode].operandos; j++) {
                            fprintf(file, "%hu\t", attributeInfo->info.CodeAttribute.code[++i]);
                        }
                        break;
                }
                fprintf(file, "\n");
            }
            fprintf(file, "\n\t\tException Table Length: \t%d\n", attributeInfo->info.CodeAttribute.exception_table_length);
            for (int i = 0; i < attributeInfo->info.CodeAttribute.exception_table_length; i++)
            {
                fprintf(file, "\t\tStart PC:  \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].start_pc);
                fprintf(file, "\t\tEnd PC:    \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].end_pc);
                fprintf(file, "\t\tHandler PC:\t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].handler_pc);
                fprintf(file, "\t\tEnd PC:    \t%d\n", attributeInfo->info.CodeAttribute.exception_table[i].catch_type);
            }
            fprintf(file, "\t\tCode Attributes Count:\t%d\n", attributeInfo->info.CodeAttribute.attributes_count);
            for (int k = 0; k < attributeInfo->info.CodeAttribute.attributes_count; k++)
            {
                fprintf(file, "\t\t[%d]", k);
                imprime_attribute(&(attributeInfo->info.CodeAttribute.attributes[k]), classe);
            }
        }
        else if (!strcmp(tipoAtributo, "Exceptions"))
        {
            fprintf(file, "\t\tNumber of Exceptions:\t%d\n", attributeInfo->info.Exception.number_of_exceptions);
            for (int i = 0; i < attributeInfo->info.Exception.number_of_exceptions; i++)
            {
                index = attributeInfo->info.Exception.exception_index_table[i] - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tException Index:\tCP INFO #%d <%s>\n",
                        attributeInfo->info.Exception.exception_index_table[i], derreferencia);
            }
        }
        else if (!strcmp(tipoAtributo, "InnerClasses"))
        {
            fprintf(file, "\t\tNumber of Classes:\t%d\n", attributeInfo->info.InnerClasses.number_of_classes);
            for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++)
            {
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tInner Class Index:       \tCP INFO #%d <%s>\n",
                        attributeInfo->info.InnerClasses.classes[i].inner_class_info_index, derreferencia);
                index = attributeInfo->info.InnerClasses.classes[i].outer_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tOuter Class Index:       \tCP INFO #%d <%s>\n",
                        attributeInfo->info.InnerClasses.classes[i].outer_class_info_index, derreferencia);
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tInner Name Index:        \tCP INFO #%d <%s>\n",
                        attributeInfo->info.InnerClasses.classes[i].inner_name_index, derreferencia);
                fprintf(file, "\t\tInner Class Access Flags:\t%d\n",
                        attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
            }
        }
        else if (!strcmp(tipoAtributo, "SourceFile"))
        {
            index = attributeInfo->info.Sourcefile.sourcefile_index - 1;
            derreferencia = dereferencia(index,classe);
            fprintf(file, "\t\tSource File Index: \tCP INFO #%d <%s>\n", attributeInfo->info.Sourcefile.sourcefile_index, derreferencia);
        }
        else if (!strcmp(tipoAtributo, "LineNumberTable"))
        {
            fprintf(file, "\t\tNumber of Lines:\t%d\n", attributeInfo->info.LineNumberTable.line_number_table_length);
            for (int i = 0; i < attributeInfo->info.LineNumberTable.line_number_table_length; i++)
            {
                fprintf(file, "\t\tLine Number: \t%d\n",
                        attributeInfo->info.LineNumberTable.line_number_table[i].line_number);
                fprintf(file, "\t\tStart PC:    \t%d\n",
                        attributeInfo->info.LineNumberTable.line_number_table[i].start_pc);
            }
        }
        else if (!strcmp(tipoAtributo, "LocalVariableTable"))
        {
            fprintf(file, "\t\tTable Length:    \t%d\n",
                    attributeInfo->info.LocalVariableTable.local_variable_table_length);
            for (int i = 0; i < attributeInfo->info.LocalVariableTable.local_variable_table_length; i++)
            {
                fprintf(file, "\t\tStart PC:        \t%d\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
                fprintf(file, "\t\tLength:          \t%d\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].length);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tName Index:      \tCP INFO #%d <%s>\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index, derreferencia);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index - 1;
                derreferencia = dereferencia(index,classe);
                fprintf(file, "\t\tDescriptor Index:\tCP INFO #%d <%s>\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index, derreferencia);
                fprintf(file, "\t\tIndex:           \t%d\n",
                        attributeInfo->info.LocalVariableTable.local_variable_table[i].index);
            }
        }
        else
        {
            fprintf(file, "\t\tDefault Data: \t");
            for (int i = 0; i < attributeInfo->attribute_length; i++)
            {
                fprintf(file, "%x", attributeInfo->info.Default.data[i]);
            }
            fprintf(file, "\n");
        }
    }
}

void imprime_methods_file(ClassFile *classe, FILE *file)
{
    char *derreferencia = NULL;
    int index = 0;
    fprintf(file, "\n");
    fprintf(file, ">>>Methods<<<\n");
    fprintf(file, "\n");
    fprintf(file, "Methods Count: \t%d\n", classe->methods_count);

    for (int i = 0; i < classe->methods_count; i++)
    {
        fprintf(file, "[%d]", i);
        for (int j = 0; j < classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.length; j++)
            fprintf(file, "%c", classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.bytes[j]);
        fprintf(file, "\n");
        fprintf(file, "\tAccess Flags:    \t%d\n", classe->methods[i].access_flags);
        index = classe->methods[i].name_index - 1;
        derreferencia = dereferencia(index,classe);
        fprintf(file, "\tName Index:      \tCP INFO #%d <%s>\n", classe->methods[i].name_index, derreferencia);
        index = classe->methods[i].descriptor_index - 1;
        derreferencia = dereferencia(index,classe);
        fprintf(file, "\tDescriptor Index:\tCP INFO #%d <%s>\n", classe->methods[i].descriptor_index, derreferencia);
        fprintf(file, "\tAttributes Count:\t%d\n", classe->methods[i].attributes_count);
        for (int j = 0; j < classe->methods[i].attributes_count; j++)
        {
            fprintf(file, "\t[%d]", j);
            imprime_attribute_file(&(classe->methods[i].attributes[j]), classe, file);
        }
    }
}

void imprime_attributes_file(ClassFile *classe, FILE *file)
{
    fprintf(file, "\n");
    fprintf(file, ">>>Attributes<<<\n");
    fprintf(file, "\n");
    fprintf(file, "Attributes Count: \t%d\n", classe->attributes_count);
    for (int i = 0; i < classe->attributes_count; i++)
    {
        fprintf(file, "\t[%d]", i);
        imprime_attribute_file(&(classe->attributes[i]), classe, file);
    }
}

void carrega_mnemonicos(Instrucao *mapa)
{
    strcpy(mapa[0x00].mnemonico, "nop");
    mapa[0x00].operandos = 0;
    mapa[0x00].req_cp = 0;
    strcpy(mapa[0x01].mnemonico, "aconst_null");
    mapa[0x01].operandos = 0;
    mapa[0x01].req_cp = 0;
    strcpy(mapa[0x02].mnemonico, "iconst_m1");
    mapa[0x02].operandos = 0;
    mapa[0x02].req_cp = 0;
    strcpy(mapa[0x03].mnemonico, "iconst_0");
    mapa[0x03].operandos = 0;
    mapa[0x03].req_cp = 0;
    strcpy(mapa[0x04].mnemonico, "iconst_1");
    mapa[0x04].operandos = 0;
    mapa[0x04].req_cp = 0;
    strcpy(mapa[0x05].mnemonico, "iconst_2");
    mapa[0x05].operandos = 0;
    mapa[0x05].req_cp = 0;
    strcpy(mapa[0x06].mnemonico, "iconst_3");
    mapa[0x06].operandos = 0;
    mapa[0x06].req_cp = 0;
    strcpy(mapa[0x07].mnemonico, "iconst_4");
    mapa[0x07].operandos = 0;
    mapa[0x07].req_cp = 0;
    strcpy(mapa[0x08].mnemonico, "iconst_5");
    mapa[0x08].operandos = 0;
    mapa[0x08].req_cp = 0;
    strcpy(mapa[0x09].mnemonico, "lconst_0");
    mapa[0x09].operandos = 0;
    mapa[0x09].req_cp = 0;
    strcpy(mapa[0x0A].mnemonico, "lconst_1");
    mapa[0x0A].operandos = 0;
    mapa[0x0A].req_cp = 0;
    strcpy(mapa[0x0B].mnemonico, "fconst_0");
    mapa[0x0B].operandos = 0;
    mapa[0x0B].req_cp = 0;
    strcpy(mapa[0x0C].mnemonico, "fconst_1");
    mapa[0x0C].operandos = 0;
    mapa[0x0C].req_cp = 0;
    strcpy(mapa[0x0D].mnemonico, "fconst_2");
    mapa[0x0D].operandos = 0;
    mapa[0x0D].req_cp = 0;
    strcpy(mapa[0x0E].mnemonico, "dconst_0");
    mapa[0x0E].operandos = 0;
    mapa[0x0E].req_cp = 0;
    strcpy(mapa[0x0F].mnemonico, "dconst_1");
    mapa[0x0F].operandos = 0;
    mapa[0x0F].req_cp = 0;
    strcpy(mapa[0x10].mnemonico, "bipush");
    mapa[0x10].operandos = 1;
    mapa[0x10].req_cp = 0;
    strcpy(mapa[0x11].mnemonico, "sipush");
    mapa[0x11].operandos = 2;
    mapa[0x11].req_cp = 0;
    strcpy(mapa[0x12].mnemonico, "ldc");
    mapa[0x12].operandos = 1;
    mapa[0x12].req_cp = REQ_LDCREF_1;
    strcpy(mapa[0x13].mnemonico, "ldc_w");
    mapa[0x13].operandos = 2;
    mapa[0x13].req_cp = REQ_LDCREF_1;
    strcpy(mapa[0x14].mnemonico, "ldc2_w");
    mapa[0x14].operandos = 2;
    mapa[0x14].req_cp = REQ_LDCREF_2;
    strcpy(mapa[0x15].mnemonico, "iload");
    mapa[0x15].operandos = 1;
    mapa[0x15].req_cp = 0;
    strcpy(mapa[0x16].mnemonico, "lload");
    mapa[0x16].operandos = 1;
    mapa[0x16].req_cp = 0;
    strcpy(mapa[0x17].mnemonico, "fload");
    mapa[0x17].operandos = 1;
    mapa[0x17].req_cp = 0;
    strcpy(mapa[0x18].mnemonico, "dload");
    mapa[0x18].operandos = 1;
    mapa[0x18].req_cp = 0;
    strcpy(mapa[0x19].mnemonico, "aload");
    mapa[0x19].operandos = 1;
    mapa[0x19].req_cp = 0;
    strcpy(mapa[0x1A].mnemonico, "iload_0");
    mapa[0x1A].operandos = 0;
    mapa[0x1A].req_cp = 0;
    strcpy(mapa[0x1B].mnemonico, "iload_1");
    mapa[0x1B].operandos = 0;
    mapa[0x1B].req_cp = 0;
    strcpy(mapa[0x1C].mnemonico, "iload_2");
    mapa[0x1C].operandos = 0;
    mapa[0x1C].req_cp = 0;
    strcpy(mapa[0x1D].mnemonico, "iload_3");
    mapa[0x1D].operandos = 0;
    mapa[0x1D].req_cp = 0;
    strcpy(mapa[0x1E].mnemonico, "lload_0");
    mapa[0x1E].operandos = 0;
    mapa[0x1E].req_cp = 0;
    strcpy(mapa[0x1F].mnemonico, "lload_1");
    mapa[0x1F].operandos = 0;
    mapa[0x1F].req_cp = 0;
    strcpy(mapa[0x20].mnemonico, "lload_2");
    mapa[0x20].operandos = 0;
    mapa[0x20].req_cp = 0;
    strcpy(mapa[0x21].mnemonico, "lload_3");
    mapa[0x21].operandos = 0;
    mapa[0x21].req_cp = 0;
    strcpy(mapa[0x22].mnemonico, "fload_0");
    mapa[0x22].operandos = 0;
    mapa[0x22].req_cp = 0;
    strcpy(mapa[0x23].mnemonico, "fload_1");
    mapa[0x23].operandos = 0;
    mapa[0x23].req_cp = 0;
    strcpy(mapa[0x24].mnemonico, "fload_2");
    mapa[0x24].operandos = 0;
    mapa[0x24].req_cp = 0;
    strcpy(mapa[0x25].mnemonico, "fload_3");
    mapa[0x25].operandos = 0;
    mapa[0x25].req_cp = 0;
    strcpy(mapa[0x26].mnemonico, "dload_0");
    mapa[0x26].operandos = 0;
    mapa[0x26].req_cp = 0;
    strcpy(mapa[0x27].mnemonico, "dload_1");
    mapa[0x27].operandos = 0;
    mapa[0x27].req_cp = 0;
    strcpy(mapa[0x28].mnemonico, "dload_2");
    mapa[0x28].operandos = 0;
    mapa[0x28].req_cp = 0;
    strcpy(mapa[0x29].mnemonico, "dload_3");
    mapa[0x29].operandos = 0;
    mapa[0x29].req_cp = 0;
    strcpy(mapa[0x2A].mnemonico, "aload_0");
    mapa[0x2A].operandos = 0;
    mapa[0x2A].req_cp = 0;
    strcpy(mapa[0x2B].mnemonico, "aload_1");
    mapa[0x2B].operandos = 0;
    mapa[0x2B].req_cp = 0;
    strcpy(mapa[0x2C].mnemonico, "aload_2");
    mapa[0x2C].operandos = 0;
    mapa[0x2C].req_cp = 0;
    strcpy(mapa[0x2D].mnemonico, "aload_3");
    mapa[0x2D].operandos = 0;
    mapa[0x2D].req_cp = 0;
    strcpy(mapa[0x2E].mnemonico, "iaload");
    mapa[0x2E].operandos = 0;
    mapa[0x2E].req_cp = 0;
    strcpy(mapa[0x2F].mnemonico, "laload");
    mapa[0x2F].operandos = 0;
    mapa[0x2F].req_cp = 0;
    strcpy(mapa[0x30].mnemonico, "faload");
    mapa[0x30].operandos = 0;
    mapa[0x30].req_cp = 0;
    strcpy(mapa[0x31].mnemonico, "daload");
    mapa[0x31].operandos = 0;
    mapa[0x31].req_cp = 0;
    strcpy(mapa[0x32].mnemonico, "aaload");
    mapa[0x32].operandos = 0;
    mapa[0x32].req_cp = 0;
    strcpy(mapa[0x33].mnemonico, "baload");
    mapa[0x33].operandos = 0;
    mapa[0x33].req_cp = 0;
    strcpy(mapa[0x34].mnemonico, "caload");
    mapa[0x34].operandos = 0;
    mapa[0x34].req_cp = 0;
    strcpy(mapa[0x35].mnemonico, "saload");
    mapa[0x35].operandos = 0;
    mapa[0x35].req_cp = 0;
    strcpy(mapa[0x36].mnemonico, "istore");
    mapa[0x36].operandos = 1;
    mapa[0x36].req_cp = 0;
    strcpy(mapa[0x37].mnemonico, "lstore");
    mapa[0x37].operandos = 1;
    mapa[0x37].req_cp = 0;
    strcpy(mapa[0x38].mnemonico, "fstore");
    mapa[0x38].operandos = 1;
    mapa[0x38].req_cp = 0;
    strcpy(mapa[0x39].mnemonico, "dstore");
    mapa[0x39].operandos = 1;
    mapa[0x39].req_cp = 0;
    strcpy(mapa[0x3A].mnemonico, "astore");
    mapa[0x3A].operandos = 1;
    mapa[0x3A].req_cp = 0;
    strcpy(mapa[0x3B].mnemonico, "istore_0");
    mapa[0x3B].operandos = 0;
    mapa[0x3B].req_cp = 0;
    strcpy(mapa[0x3C].mnemonico, "istore_1");
    mapa[0x3C].operandos = 0;
    mapa[0x3C].req_cp = 0;
    strcpy(mapa[0x3D].mnemonico, "istore_2");
    mapa[0x3D].operandos = 0;
    mapa[0x3D].req_cp = 0;
    strcpy(mapa[0x3E].mnemonico, "istore_3");
    mapa[0x3E].operandos = 0;
    mapa[0x3E].req_cp = 0;
    strcpy(mapa[0x3F].mnemonico, "lstore_0");
    mapa[0x3F].operandos = 0;
    mapa[0x3F].req_cp = 0;
    strcpy(mapa[0x40].mnemonico, "lstore_1");
    mapa[0x40].operandos = 0;
    mapa[0x40].req_cp = 0;
    strcpy(mapa[0x41].mnemonico, "lstore_2");
    mapa[0x41].operandos = 0;
    mapa[0x41].req_cp = 0;
    strcpy(mapa[0x42].mnemonico, "lstore_3");
    mapa[0x42].operandos = 0;
    mapa[0x42].req_cp = 0;
    strcpy(mapa[0x43].mnemonico, "fstore_0");
    mapa[0x43].operandos = 0;
    mapa[0x43].req_cp = 0;
    strcpy(mapa[0x44].mnemonico, "fstore_1");
    mapa[0x44].operandos = 0;
    mapa[0x44].req_cp = 0;
    strcpy(mapa[0x45].mnemonico, "fstore_2");
    mapa[0x45].operandos = 0;
    mapa[0x45].req_cp = 0;
    strcpy(mapa[0x46].mnemonico, "fstore_3");
    mapa[0x46].operandos = 0;
    mapa[0x46].req_cp = 0;
    strcpy(mapa[0x47].mnemonico, "dstore_0");
    mapa[0x47].operandos = 0;
    mapa[0x47].req_cp = 0;
    strcpy(mapa[0x48].mnemonico, "dstore_1");
    mapa[0x48].operandos = 0;
    mapa[0x48].req_cp = 0;
    strcpy(mapa[0x49].mnemonico, "dstore_2");
    mapa[0x49].operandos = 0;
    mapa[0x49].req_cp = 0;
    strcpy(mapa[0x4A].mnemonico, "dstore_3");
    mapa[0x4A].operandos = 0;
    mapa[0x4A].req_cp = 0;
    strcpy(mapa[0x4B].mnemonico, "astore_0");
    mapa[0x4B].operandos = 0;
    mapa[0x4B].req_cp = 0;
    strcpy(mapa[0x4C].mnemonico, "astore_1");
    mapa[0x4C].operandos = 0;
    mapa[0x4C].req_cp = 0;
    strcpy(mapa[0x4D].mnemonico, "astore_2");
    mapa[0x4D].operandos = 0;
    mapa[0x4D].req_cp = 0;
    strcpy(mapa[0x4E].mnemonico, "astore_3");
    mapa[0x4E].operandos = 0;
    mapa[0x4E].req_cp = 0;
    strcpy(mapa[0x4F].mnemonico, "iastore");
    mapa[0x4F].operandos = 0;
    mapa[0x4F].req_cp = 0;
    strcpy(mapa[0x50].mnemonico, "lastore");
    mapa[0x50].operandos = 0;
    mapa[0x50].req_cp = 0;
    strcpy(mapa[0x51].mnemonico, "fastore");
    mapa[0x51].operandos = 0;
    mapa[0x51].req_cp = 0;
    strcpy(mapa[0x52].mnemonico, "dastore");
    mapa[0x52].operandos = 0;
    mapa[0x52].req_cp = 0;
    strcpy(mapa[0x53].mnemonico, "aastore");
    mapa[0x53].operandos = 0;
    mapa[0x53].req_cp = 0;
    strcpy(mapa[0x54].mnemonico, "bastore");
    mapa[0x54].operandos = 0;
    mapa[0x54].req_cp = 0;
    strcpy(mapa[0x55].mnemonico, "castore");
    mapa[0x55].operandos = 0;
    mapa[0x55].req_cp = 0;
    strcpy(mapa[0x56].mnemonico, "sastore");
    mapa[0x56].operandos = 0;
    mapa[0x56].req_cp = 0;
    strcpy(mapa[0x57].mnemonico, "pop");
    mapa[0x57].operandos = 0;
    mapa[0x57].req_cp = 0;
    strcpy(mapa[0x58].mnemonico, "pop2");
    mapa[0x58].operandos = 0;
    mapa[0x58].req_cp = 0;
    strcpy(mapa[0x59].mnemonico, "dup");
    mapa[0x59].operandos = 0;
    mapa[0x59].req_cp = 0;
    strcpy(mapa[0x5A].mnemonico, "dup_x1");
    mapa[0x5A].operandos = 0;
    mapa[0x5A].req_cp = 0;
    strcpy(mapa[0x5B].mnemonico, "dup_x2");
    mapa[0x5B].operandos = 0;
    mapa[0x5B].req_cp = 0;
    strcpy(mapa[0x5C].mnemonico, "dup2");
    mapa[0x5C].operandos = 0;
    mapa[0x5C].req_cp = 0;
    strcpy(mapa[0x5D].mnemonico, "dup2_x1");
    mapa[0x5D].operandos = 0;
    mapa[0x5D].req_cp = 0;
    strcpy(mapa[0x5E].mnemonico, "dup2_x2");
    mapa[0x5E].operandos = 0;
    mapa[0x5E].req_cp = 0;
    strcpy(mapa[0x5F].mnemonico, "swap");
    mapa[0x5F].operandos = 0;
    mapa[0x5F].req_cp = 0;
    strcpy(mapa[0x60].mnemonico, "iadd");
    mapa[0x60].operandos = 0;
    mapa[0x60].req_cp = 0;
    strcpy(mapa[0x61].mnemonico, "ladd");
    mapa[0x61].operandos = 0;
    mapa[0x61].req_cp = 0;
    strcpy(mapa[0x62].mnemonico, "fadd");
    mapa[0x62].operandos = 0;
    mapa[0x62].req_cp = 0;
    strcpy(mapa[0x63].mnemonico, "dadd");
    mapa[0x63].operandos = 0;
    mapa[0x63].req_cp = 0;
    strcpy(mapa[0x64].mnemonico, "isub");
    mapa[0x64].operandos = 0;
    mapa[0x64].req_cp = 0;
    strcpy(mapa[0x65].mnemonico, "lsub");
    mapa[0x65].operandos = 0;
    mapa[0x65].req_cp = 0;
    strcpy(mapa[0x66].mnemonico, "fsub");
    mapa[0x66].operandos = 0;
    mapa[0x66].req_cp = 0;
    strcpy(mapa[0x67].mnemonico, "dsub");
    mapa[0x67].operandos = 0;
    mapa[0x67].req_cp = 0;
    strcpy(mapa[0x68].mnemonico, "imul");
    mapa[0x68].operandos = 0;
    mapa[0x68].req_cp = 0;
    strcpy(mapa[0x69].mnemonico, "lmul");
    mapa[0x69].operandos = 0;
    mapa[0x69].req_cp = 0;
    strcpy(mapa[0x6A].mnemonico, "fmul");
    mapa[0x6A].operandos = 0;
    mapa[0x6A].req_cp = 0;
    strcpy(mapa[0x6B].mnemonico, "dmul");
    mapa[0x6B].operandos = 0;
    mapa[0x6B].req_cp = 0;
    strcpy(mapa[0x6C].mnemonico, "idiv");
    mapa[0x6C].operandos = 0;
    mapa[0x6C].req_cp = 0;
    strcpy(mapa[0x6D].mnemonico, "ldiv");
    mapa[0x6D].operandos = 0;
    mapa[0x6D].req_cp = 0;
    strcpy(mapa[0x6E].mnemonico, "fdiv");
    mapa[0x6E].operandos = 0;
    mapa[0x6E].req_cp = 0;
    strcpy(mapa[0x6F].mnemonico, "ddiv");
    mapa[0x6F].operandos = 0;
    mapa[0x6F].req_cp = 0;
    strcpy(mapa[0x70].mnemonico, "irem");
    mapa[0x70].operandos = 0;
    mapa[0x70].req_cp = 0;
    strcpy(mapa[0x71].mnemonico, "lrem");
    mapa[0x71].operandos = 0;
    mapa[0x71].req_cp = 0;
    strcpy(mapa[0x72].mnemonico, "frem");
    mapa[0x72].operandos = 0;
    mapa[0x72].req_cp = 0;
    strcpy(mapa[0x73].mnemonico, "drem");
    mapa[0x73].operandos = 0;
    mapa[0x73].req_cp = 0;
    strcpy(mapa[0x74].mnemonico, "ineg");
    mapa[0x74].operandos = 0;
    mapa[0x74].req_cp = 0;
    strcpy(mapa[0x75].mnemonico, "lneg");
    mapa[0x75].operandos = 0;
    mapa[0x75].req_cp = 0;
    strcpy(mapa[0x76].mnemonico, "fneg");
    mapa[0x76].operandos = 0;
    mapa[0x76].req_cp = 0;
    strcpy(mapa[0x77].mnemonico, "dneg");
    mapa[0x77].operandos = 0;
    mapa[0x77].req_cp = 0;
    strcpy(mapa[0x78].mnemonico, "ishl");
    mapa[0x78].operandos = 0;
    mapa[0x78].req_cp = 0;
    strcpy(mapa[0x79].mnemonico, "lshl");
    mapa[0x79].operandos = 0;
    mapa[0x79].req_cp = 0;
    strcpy(mapa[0x7A].mnemonico, "ishr");
    mapa[0x7A].operandos = 0;
    mapa[0x7A].req_cp = 0;
    strcpy(mapa[0x7B].mnemonico, "lshr");
    mapa[0x7B].operandos = 0;
    mapa[0x7B].req_cp = 0;
    strcpy(mapa[0x7C].mnemonico, "iushr");
    mapa[0x7C].operandos = 0;
    mapa[0x7C].req_cp = 0;
    strcpy(mapa[0x7D].mnemonico, "lushr");
    mapa[0x7D].operandos = 0;
    mapa[0x7D].req_cp = 0;
    strcpy(mapa[0x7E].mnemonico, "iand");
    mapa[0x7E].operandos = 0;
    mapa[0x7E].req_cp = 0;
    strcpy(mapa[0x7F].mnemonico, "land");
    mapa[0x7F].operandos = 0;
    mapa[0x7F].req_cp = 0;
    strcpy(mapa[0x80].mnemonico, "ior");
    mapa[0x80].operandos = 0;
    mapa[0x80].req_cp = 0;
    strcpy(mapa[0x81].mnemonico, "lor");
    mapa[0x81].operandos = 0;
    mapa[0x81].req_cp = 0;
    strcpy(mapa[0x82].mnemonico, "ixor");
    mapa[0x82].operandos = 0;
    mapa[0x82].req_cp = 0;
    strcpy(mapa[0x83].mnemonico, "lxor");
    mapa[0x83].operandos = 0;
    mapa[0x83].req_cp = 0;
    strcpy(mapa[0x84].mnemonico, "iinc");
    mapa[0x84].operandos = 2;
    mapa[0x84].req_cp = REQ_IINCREF;
    strcpy(mapa[0x85].mnemonico, "i2l");
    mapa[0x85].operandos = 0;
    mapa[0x85].req_cp = 0;
    strcpy(mapa[0x86].mnemonico, "i2f");
    mapa[0x86].operandos = 0;
    mapa[0x86].req_cp = 0;
    strcpy(mapa[0x87].mnemonico, "i2d");
    mapa[0x87].operandos = 0;
    mapa[0x87].req_cp = 0;
    strcpy(mapa[0x88].mnemonico, "l2i");
    mapa[0x88].operandos = 0;
    mapa[0x88].req_cp = 0;
    strcpy(mapa[0x89].mnemonico, "l2f");
    mapa[0x89].operandos = 0;
    mapa[0x89].req_cp = 0;
    strcpy(mapa[0x8A].mnemonico, "l2d");
    mapa[0x8A].operandos = 0;
    mapa[0x8A].req_cp = 0;
    strcpy(mapa[0x8B].mnemonico, "f2i");
    mapa[0x8B].operandos = 0;
    mapa[0x8B].req_cp = 0;
    strcpy(mapa[0x8C].mnemonico, "f2l");
    mapa[0x8C].operandos = 0;
    mapa[0x8C].req_cp = 0;
    strcpy(mapa[0x8D].mnemonico, "f2d");
    mapa[0x8D].operandos = 0;
    mapa[0x8D].req_cp = 0;
    strcpy(mapa[0x8E].mnemonico, "d2i");
    mapa[0x8E].operandos = 0;
    mapa[0x8E].req_cp = 0;
    strcpy(mapa[0x8F].mnemonico, "d2l");
    mapa[0x8F].operandos = 0;
    mapa[0x8F].req_cp = 0;
    strcpy(mapa[0x90].mnemonico, "d2f");
    mapa[0x90].operandos = 0;
    mapa[0x90].req_cp = 0;
    strcpy(mapa[0x91].mnemonico, "i2b");
    mapa[0x91].operandos = 0;
    mapa[0x91].req_cp = 0;
    strcpy(mapa[0x92].mnemonico, "i2c");
    mapa[0x92].operandos = 0;
    mapa[0x92].req_cp = 0;
    strcpy(mapa[0x93].mnemonico, "i2s");
    mapa[0x93].operandos = 0;
    mapa[0x93].req_cp = 0;
    strcpy(mapa[0x94].mnemonico, "lcmp");
    mapa[0x94].operandos = 0;
    mapa[0x94].req_cp = 0;
    strcpy(mapa[0x95].mnemonico, "fcmpl");
    mapa[0x95].operandos = 0;
    mapa[0x95].req_cp = 0;
    strcpy(mapa[0x96].mnemonico, "fcmpg");
    mapa[0x96].operandos = 0;
    mapa[0x96].req_cp = 0;
    strcpy(mapa[0x97].mnemonico, "dcmpl");
    mapa[0x97].operandos = 0;
    mapa[0x97].req_cp = 0;
    strcpy(mapa[0x98].mnemonico, "dcmpg");
    mapa[0x98].operandos = 0;
    mapa[0x98].req_cp = 0;
    strcpy(mapa[0x99].mnemonico, "ifeq");
    mapa[0x99].operandos = 2;
    mapa[0x99].req_cp = REQ_JMPREF;
    strcpy(mapa[0x9A].mnemonico, "ifne");
    mapa[0x9A].operandos = 2;
    mapa[0x9A].req_cp = REQ_JMPREF;
    strcpy(mapa[0x9B].mnemonico, "iflt");
    mapa[0x9B].operandos = 2;
    mapa[0x9B].req_cp = REQ_JMPREF;
    strcpy(mapa[0x9C].mnemonico, "ifge");
    mapa[0x9C].operandos = 2;
    mapa[0x9C].req_cp = REQ_JMPREF;
    strcpy(mapa[0x9D].mnemonico, "ifgt");
    mapa[0x9D].operandos = 2;
    mapa[0x9D].req_cp = REQ_JMPREF;
    strcpy(mapa[0x9E].mnemonico, "ifle");
    mapa[0x9E].operandos = 2;
    mapa[0x9E].req_cp = REQ_JMPREF;
    strcpy(mapa[0x9F].mnemonico, "if_icmpeq");
    mapa[0x9F].operandos = 2;
    mapa[0x9F].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA0].mnemonico, "if_icmpne");
    mapa[0xA0].operandos = 2;
    mapa[0xA0].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA1].mnemonico, "if_icmplt");
    mapa[0xA1].operandos = 2;
    mapa[0xA1].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA2].mnemonico, "if_icmpge");
    mapa[0xA2].operandos = 2;
    mapa[0xA2].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA3].mnemonico, "if_icmpgt");
    mapa[0xA3].operandos = 2;
    mapa[0xA3].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA4].mnemonico, "if_icmple");
    mapa[0xA4].operandos = 2;
    mapa[0xA4].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA5].mnemonico, "if_acmpeq");
    mapa[0xA5].operandos = 2;
    mapa[0xA5].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA6].mnemonico, "if_acmpne");
    mapa[0xA6].operandos = 2;
    mapa[0xA6].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA7].mnemonico, "goto");
    mapa[0xA7].operandos = 2;
    mapa[0xA7].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA8].mnemonico, "jsr");
    mapa[0xA8].operandos = 2;
    mapa[0xA8].req_cp = REQ_JMPREF;
    strcpy(mapa[0xA9].mnemonico, "ret");
    mapa[0xA9].operandos = 1;
    mapa[0xA9].req_cp = 0;
    strcpy(mapa[0xAA].mnemonico, "tableswitch");
    mapa[0xAA].operandos = 14;
    mapa[0xAA].req_cp = 0;
    strcpy(mapa[0xAB].mnemonico, "lookupswitch");
    mapa[0xAB].operandos = 10;
    mapa[0xAB].req_cp = 0;
    strcpy(mapa[0xAC].mnemonico, "ireturn");
    mapa[0xAC].operandos = 0;
    mapa[0xAC].req_cp = 0;
    strcpy(mapa[0xAD].mnemonico, "lreturn");
    mapa[0xAD].operandos = 0;
    mapa[0xAD].req_cp = 0;
    strcpy(mapa[0xAE].mnemonico, "freturn");
    mapa[0xAE].operandos = 0;
    mapa[0xAE].req_cp = 0;
    strcpy(mapa[0xAF].mnemonico, "dreturn");
    mapa[0xAF].operandos = 0;
    mapa[0xAF].req_cp = 0;
    strcpy(mapa[0xB0].mnemonico, "areturn");
    mapa[0xB0].operandos = 0;
    mapa[0xB0].req_cp = 0;
    strcpy(mapa[0xB1].mnemonico, "return");
    mapa[0xB1].operandos = 0;
    mapa[0xB1].req_cp = 0;
    strcpy(mapa[0xB2].mnemonico, "getstatic");
    mapa[0xB2].operandos = 2;
    mapa[0xB2].req_cp = REQ_FIELDREF;
    strcpy(mapa[0xB3].mnemonico, "putstatic");
    mapa[0xB3].operandos = 2;
    mapa[0xB3].req_cp = REQ_FIELDREF;
    strcpy(mapa[0xB4].mnemonico, "getfield");
    mapa[0xB4].operandos = 2;
    mapa[0xB4].req_cp = REQ_FIELDREF;
    strcpy(mapa[0xB5].mnemonico, "putfield");
    mapa[0xB5].operandos = 2;
    mapa[0xB5].req_cp = REQ_FIELDREF;
    strcpy(mapa[0xB6].mnemonico, "invokevirtual");
    mapa[0xB6].operandos = 2;
    mapa[0xB6].req_cp = REQ_METHODREF_2;
    strcpy(mapa[0xB7].mnemonico, "invokespecial");
    mapa[0xB7].operandos = 2;
    mapa[0xB7].req_cp = REQ_METHODREF_2;
    strcpy(mapa[0xB8].mnemonico, "invokestatic");
    mapa[0xB8].operandos = 2;
    mapa[0xB8].req_cp = REQ_METHODREF_2;
    strcpy(mapa[0xB9].mnemonico, "invokeinterface");
    mapa[0xB9].operandos = 4;
    mapa[0xB9].req_cp = REQ_METHODREF_2;
    strcpy(mapa[0xBB].mnemonico, "new");
    mapa[0xBB].operandos = 2;
    mapa[0xBA].req_cp = 0;
    strcpy(mapa[0xBC].mnemonico, "newarray");
    mapa[0xBC].operandos = 1;
    mapa[0xBC].req_cp = REQ_ARRAYREF;
    strcpy(mapa[0xBD].mnemonico, "anewarray");
    mapa[0xBD].operandos = 2;
    mapa[0xBD].req_cp = 0;
    strcpy(mapa[0xBE].mnemonico, "arraylength");
    mapa[0xBE].operandos = 0;
    mapa[0xBE].req_cp = 0;
    strcpy(mapa[0xBF].mnemonico, "athrow");
    mapa[0xBF].operandos = 0;
    mapa[0xBF].req_cp = 0;
    strcpy(mapa[0xC0].mnemonico, "check_cast");
    mapa[0xC0].operandos = 0;
    mapa[0xC0].req_cp = 0;
    strcpy(mapa[0xC1].mnemonico, "instance_of");
    mapa[0xC1].operandos = 0;
    mapa[0xC1].req_cp = 0;
    strcpy(mapa[0xC2].mnemonico, "monitor_enter");
    mapa[0xC2].operandos = 0;
    mapa[0xC2].req_cp = 0;
    strcpy(mapa[0xC3].mnemonico, "monitor_exit");
    mapa[0xC3].operandos = 0;
    mapa[0xC3].req_cp = 0;
    strcpy(mapa[0xC4].mnemonico, "wide");
    mapa[0xC4].operandos = 7;
    mapa[0xC4].req_cp = 0;
    strcpy(mapa[0xC5].mnemonico, "multianewarray");
    mapa[0xC5].operandos = 3;
    mapa[0xC5].req_cp = 0;
    strcpy(mapa[0xC6].mnemonico, "ifnull");
    mapa[0xC6].operandos = 2;
    mapa[0xC6].req_cp = 0;
    strcpy(mapa[0xC7].mnemonico, "ifnonnull");
    mapa[0xC7].operandos = 2;
    mapa[0xC7].req_cp = 0;
    strcpy(mapa[0xC8].mnemonico, "goto_w");
    mapa[0xC8].operandos = 4;
    mapa[0xC8].req_cp = 0;
    strcpy(mapa[0xC9].mnemonico, "jsr_w");
    mapa[0xC9].operandos = 4;
    mapa[0xC9].req_cp = 0;
}

char* dereferencia(u2 index, ClassFile *classe)
{
    char *nome;
    int i;
    nome = (char *) malloc((classe->constant_pool[index].info.Utf8.length + 1) * sizeof(char));
    for (i = 0; i < classe->constant_pool[index].info.Utf8.length; i++)
    {
        nome[i] = classe->constant_pool[index].info.Utf8.bytes[i];
    }
    nome[i] = '\0';
    return nome;
}

char* dereferencia_methodinfo(u2 index, ClassFile *classe)
{
    char *class_name, *method_name, *nome;
    u2 class_index, name_and_type_index, method_index;

    class_index = classe->constant_pool[index].info.Methodref.class_index - 1;
    class_index = classe->constant_pool[class_index].info.Class.name_index - 1;
    name_and_type_index = classe->constant_pool[index].info.Methodref.name_and_type_index - 1;
    method_index = classe->constant_pool[name_and_type_index].info.NameAndType.name_index - 1;
    class_name = dereferencia(class_index, classe);
    method_name = dereferencia(method_index, classe);
    nome = (char *) malloc((strlen(class_name) + strlen(method_name) + 2) * sizeof(char));
    strcpy(nome, class_name);
    strcat(nome, ".");
    strcat(nome, method_name);
    return nome;
}

char* dereferencia_fieldrefinfo(u2 index, ClassFile *classe)
{
    char *class_name, *method_name, *nome;
    u2 class_index, name_and_type_index, method_index;

    class_index = classe->constant_pool[index].info.Fieldref.class_index - 1;
    class_index = classe->constant_pool[class_index].info.Class.name_index - 1;
    name_and_type_index = classe->constant_pool[index].info.Fieldref.name_and_type_index - 1;
    method_index = classe->constant_pool[name_and_type_index].info.NameAndType.name_index - 1;
    class_name = dereferencia(class_index, classe);
    method_name = dereferencia(method_index, classe);
    nome = (char *) malloc((strlen(class_name) + strlen(method_name) + 2) * sizeof(char));
    strcpy(nome, class_name);
    strcat(nome, ".");
    strcat(nome, method_name);
    return nome;
}

int verifica_match(ClassFile *classe, char *nome)
{
    char *temp, *nomeThisClass;
    char c = nome[0];
    int i = 0, index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;

    temp = (char *) malloc(strlen(nome) * sizeof(char));
    while(c != '.')
    {
        c = nome[i];
        temp[i] = nome[i];
        i++;
    }
    i+=1;
    temp[i] = '\0';
    nomeThisClass = dereferencia(index, classe);
    if(!strcmp(temp, nomeThisClass))
    {
        return ERRO_MATCHING;
    }
    return SUCESSO;
}
