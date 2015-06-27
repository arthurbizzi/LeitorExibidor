#include "others.h"

void i_nop()
{
    return;
};

void i_bipush(Frame* frame,u4* n)
{
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),n);
}

void i_sipush(Frame* frame,u2* n)
{
	u4 dado = *n;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&dado);
}

void i_ldc(Frame* frame,u1 index, cp_info* constantPool)
{
    u1 tag = constantPool[index-1].tag;
    u4 dado;
    switch (tag)
    {
    case CONSTANT_Integer:  //Integer
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Integer.bytes);
        break;
    case CONSTANT_Float: //Float
    	dado =  constantPool[index-1].info.Float.bytes;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&dado);
        //EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Float.bytes);
        break;
    case CONSTANT_String: //String, Need to see the correct reference to save it.
		dado =  constantPool[index-1].info.String.string_index;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&dado);
        //EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.String.string_index);
        break;
    }
}

void i_ldc_w(Frame* frame,u1 index,u1 index2, cp_info* constantPool)
{
	u4 dado=0;
    u2 indexConcat = (index<<8) | index2;
    u1 tag = constantPool[index-1].tag;
    switch (tag)
    {
    case CONSTANT_Integer: //Integer
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Integer.bytes);
        break;
    case CONSTANT_Float: //Float
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Float.bytes);
        break;
    case CONSTANT_String: //String, Need to see the correct reference to save it.
		dado = constantPool[index-1].info.String.string_index;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&dado);
        //EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.String.string_index);
        break;
    }
}

void i_ldc2_w(Frame* frame,u1 index,u1 index2, cp_info* constantPool)
{
    u2 indexConcat = (index<<8) | index2;
    u1 tag = constantPool[indexConcat-1].tag;

    switch(tag)
    {
    case CONSTANT_Long:
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[indexConcat-1].info.Long.high_bytes);
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[indexConcat-1].info.Long.low_bytes);
        break;
    case CONSTANT_Double:
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[indexConcat-1].info.Double.high_bytes);
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[indexConcat-1].info.Double.low_bytes);
        break;
    }
}

void i_goto(Frame* frame, u1 index1, u1 index2){
	frame->pc += (u2)((index1<<8)+index2);
}

#warning alinhar como incremento do ponteiro de PC é feito
void i_jsr(Frame* frame, u1 index, u1 index2){
	u4 pc = frame->pc;
	pc++;
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &(pc));
}

#warning precis ser olhado com mais cuidado
void i_ret(Frame* frame, u1 index){
	frame->pc = frame->VetorVariaveisLocais[index];
}



#pragma mark - SMURF PART
void i_putfield()
{

    return;
}

void i_invokevirtual(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
{
    tArray *array1;
    Frame *frame1;
    ClassFile *classe;
    float valorf;
    char *nomeclasse, *nomemetodo, *metododesc, *nome;
    u8 valoru8;
    u4 numparam, i, j, valoru4, *argumentos;
    u2 index, classindex, descriptorindex, metodoindex, length;
    u1 *bytes;
    index = (u4)indexbyte1 << 8 | (u4)indexbyte2;
    classindex = frame->constant_pool[index - 1].info.Methodref.class_index - 1;
    classindex = frame->constant_pool[classindex].info.Class.name_index - 1;
    nomeclasse = i_dereferencia_instrucoes(classindex, frame->constant_pool);
    descriptorindex = frame->constant_pool[index - 1].info.Methodref.name_and_type_index - 1;
    metodoindex = frame->constant_pool[descriptorindex].info.NameAndType.name_index - 1;
    descriptorindex = frame->constant_pool[descriptorindex].info.NameAndType.descriptor_index - 1;
    nomemetodo = i_dereferencia_instrucoes(metodoindex, frame->constant_pool);
    metododesc = i_dereferencia_instrucoes(descriptorindex, frame->constant_pool);

    if (!strcmp(nomeclasse, "java/io/PrintStream") && (!strcmp(nomemetodo, "print") || !strcmp(nomemetodo, "println")))
    {
        //Long
        if (strstr(metododesc, "J") != NULL)
        {
            valoru8 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
            printf("%l", (int64_t)valoru8);

        }//Double
        else if (strstr(metododesc, "D") != NULL)
        {
            valoru8 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
            printf("%.15f", (int64_t)valoru8);

        }//Boolean
        else if (strstr(metododesc, "Z") != NULL)
        {
            if (DesempilhaOperando32bits(&(frame->pilhaDeOperandos)))
                printf("TRUE");
            else
                printf("FALSE");

        }//Char
        else if (strstr(metododesc, "C") != NULL)
        {
            //Array
            if (strstr(metododesc, "[C") != NULL)
            {
                array1 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
                for (i = 0; i < array1->tamanho1; i++)
                {
                    printf("%c", (int16_t)array1->info.tipoChar[i]);
                }

            }//Char
            else
            {
                printf("%c", (int16_t)DesempilhaOperando32bits(&(frame->pilhaDeOperandos)));
            }

        }//Inteiro
        else if (strstr(metododesc, "I") != NULL)
        {
            printf("%d", (int32_t)DesempilhaOperando32bits(&(frame->pilhaDeOperandos)));

        }//Float
        else if (strstr(metododesc, "F") != NULL)
        {
            valoru4 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            memcpy(&valorf, &valoru4, sizeof(u4));
            printf("%f", valorf);

        }//String
        else if (strstr(metododesc, "Ljava/lang/String") != NULL)
        {
            valoru4 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            printf("%s", (char *)valoru4);

        }//Object
        else if (strstr(metododesc, "Ljava/lang/Object") != NULL)
        {
            printf("%p", (void *)DesempilhaOperando32bits(&(frame->pilhaDeOperandos)));
        }

        if (strstr(nomemetodo, "println") != NULL)
            printf("\n");
    }
    else
    {
        classe = i_RecuperaClasse(nomeclasse, &listadeclasses);
        if (classe == NULL)
        {
            char *nomearquivo;
            classe = (ClassFile *)malloc(sizeof(ClassFile));
            nomearquivo = (char *)malloc(sizeof(char) * (strlen(nomeclasse) + 7));
            strcpy(nomearquivo, nomeclasse);
            strcat(nomearquivo, ".class");
            carrega_classe(nomearquivo, classe);
            InsereListaDeClasses(&listadeclasses, classe);
        }

        bytes = frame->constant_pool[descriptorindex].info.Utf8.bytes;
        length = frame->constant_pool[descriptorindex].info.Utf8.length;

        for (i = 0; i < length && bytes[i] != ')'; i++)
        {
            if(bytes[i] == 'L')
            {
                while(bytes[i] != ';')
                {
                    i++;
                }
                numparam++;
            }
            else if((bytes[i] == 'B')||(bytes[i] == 'C')||(bytes[i] == 'F')|| (bytes[i] == 'I')||(bytes[i] == 'S')||(bytes[i] == 'Z') )
            {
                numparam++;
            }
            else if((bytes[i] == 'D')||(bytes[i] == 'J'))
            {
                numparam+=2;
            }
        }

        argumentos = (u4 *)malloc(sizeof(u4) * (numparam + 1));

        for (i = numparam; i >= 0; i--)
        {
            argumentos[i] = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
        }

        nomemetodo = i_dereferencia_instrucoes(metodoindex, frame->constant_pool);

        for(i = 0; i < classe->methods_count; i++) {
            index = classe->methods[i].name_index - 1;
            nome = i_dereferencia_instrucoes(index, classe->constant_pool);
            if(!strcmp(nomemetodo, nome))
                break;
        }
        if (i != classe->methods_count)
        {
            if (classe->methods[i].access_flags & AFNative)
            {
                u4 zero = 0;
                bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.bytes;
                length = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.length;
                if(bytes[length - 1] == 'D' || bytes[length - 1] == 'J') {
                    EmpilhaOperando64bits(&frame->pilhaDeOperandos, &zero);
                }
                else if(bytes[length-1] != 'V')
                {
                    EmpilhaOperando32bits(&frame->pilhaDeOperandos, &zero);
                }
            }
            else
            {
                prepara_metodo(&classe->methods[i], classe, pilhadeframes);
                frame1 = DesempilhaFrame(&pilhadeframes);
                for (j = numparam; j >= 0; j--)
                {
                    frame1->VetorVariaveisLocais[j] = argumentos[j];
                }
                EmpilhaFrame(&pilhadeframes, frame1);
                executa_metodo(&classe->methods[i], classe, pilhadeframes);
            }
        }
        else
        {
            printf("metodo não encontrado");
        }
    }

    return;
}

void i_invokespecial(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
{
    Frame *frame1;
    ClassFile *classe;
    char *nomeclasse, *nomemetodo;
    u4 numparam, i, j, *argumentos;
    u2 index, classindex, descriptorindex, metodoindex, length;
    u1 *bytes;
    index = (u4)indexbyte1 << 8 | (u4)indexbyte2;
    classindex = frame->constant_pool[index - 1].info.Methodref.class_index - 1;
    classindex = frame->constant_pool[classindex].info.Class.name_index - 1;
    nomeclasse = i_dereferencia_instrucoes(classindex, frame->constant_pool);
    classe = i_RecuperaClasse(nomeclasse, &listadeclasses);
    if (classe == NULL)
    {
        char *nomearquivo;
        classe = (ClassFile *)malloc(sizeof(ClassFile));
        nomearquivo = (char *)malloc(sizeof(char) * (strlen(nomeclasse) + 7));
        strcpy(nomearquivo, nomeclasse);
        strcat(nomearquivo, ".class");
        carrega_classe(nomearquivo, classe);
        InsereListaDeClasses(&listadeclasses, classe);
    }
    descriptorindex = frame->constant_pool[index - 1].info.Methodref.name_and_type_index - 1;
    metodoindex = frame->constant_pool[descriptorindex].info.NameAndType.name_index - 1;
    descriptorindex = frame->constant_pool[descriptorindex].info.NameAndType.descriptor_index - 1;
    bytes = frame->constant_pool[descriptorindex].info.Utf8.bytes;
    length = frame->constant_pool[descriptorindex].info.Utf8.length;

    for (i = 0; i < length && bytes[i] != ')'; i++)
    {
		if(bytes[i] == 'L')
		{
			while(bytes[i] != ';')
			{
				i++;
			}
			numparam++;
		} else if((bytes[i] == 'B')||(bytes[i] == 'C')||(bytes[i] == 'F')|| (bytes[i] == 'I')||(bytes[i] == 'S')||(bytes[i] == 'Z') )
		{
			numparam++;
		} else if((bytes[i] == 'D')||(bytes[i] == 'J'))
		{
			numparam+=2;
		}
	}

	argumentos = (u4 *)malloc(sizeof(u4) * numparam);

	for (i = numparam; i >= 0; i--)
    {
        argumentos[i] = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    }

    nomemetodo = i_dereferencia_instrucoes(metodoindex, frame->constant_pool);

    if (classe->methods[0].access_flags & AFNative)
    {
        u4 zerou4 = 0;
        u8 zerou8 = zerou4;
        bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.bytes;
        length = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.length;
        if(bytes[length - 1] == 'D' || bytes[length - 1] == 'J') {
            EmpilhaOperando64bits(&frame->pilhaDeOperandos, &zerou8);
        } else if(bytes[length-1] != 'V') {
            EmpilhaOperando32bits(&frame->pilhaDeOperandos, &zerou4);
        }
    }
    else
    {
        prepara_metodo(&classe->methods[0], classe, pilhadeframes);
        frame1 = DesempilhaFrame(&pilhadeframes);
        for (j = numparam; j >= 0; j--)
        {
            frame1->VetorVariaveisLocais[j] = argumentos[j];
        }
        EmpilhaFrame(&pilhadeframes, frame1);
        executa_metodo(&classe->methods[0], classe, pilhadeframes);
    }

    return;
}

void i_invokestatic(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
{
    Frame *frame1;
    ClassFile *classe;
    char *nomeclasse, *nomemetodo, *nome;
    u4 numparam, i, j, *argumentos;
    u2 index, classindex, descriptorindex, metodoindex, length;
    u1 *bytes;
    index = (u4)indexbyte1 << 8 | (u4)indexbyte2;
    classindex = frame->constant_pool[index - 1].info.Methodref.class_index - 1;
    classindex = frame->constant_pool[classindex].info.Class.name_index - 1;
    nomeclasse = i_dereferencia_instrucoes(classindex, frame->constant_pool);
    classe = i_RecuperaClasse(nomeclasse, &listadeclasses);
    if (classe == NULL)
    {
        char *nomearquivo;
        classe = (ClassFile *)malloc(sizeof(ClassFile));
        nomearquivo = (char *)malloc(sizeof(char) * (strlen(nomeclasse) + 7));
        strcpy(nomearquivo, nomeclasse);
        strcat(nomearquivo, ".class");
        carrega_classe(nomearquivo, classe);
        InsereListaDeClasses(&listadeclasses, classe);
    }
    descriptorindex = frame->constant_pool[index - 1].info.Methodref.name_and_type_index - 1;
    metodoindex = frame->constant_pool[descriptorindex].info.NameAndType.name_index - 1;
    descriptorindex = frame->constant_pool[descriptorindex].info.NameAndType.descriptor_index - 1;
    bytes = frame->constant_pool[descriptorindex].info.Utf8.bytes;
    length = frame->constant_pool[descriptorindex].info.Utf8.length;

    for (i = 0; i < length && bytes[i] != ')'; i++)
    {
		if(bytes[i] == 'L')
		{
			while(bytes[i] != ';')
			{
				i++;
			}
			numparam++;
		} else if((bytes[i] == 'B')||(bytes[i] == 'C')||(bytes[i] == 'F')|| (bytes[i] == 'I')||(bytes[i] == 'S')||(bytes[i] == 'Z') )
		{
			numparam++;
		} else if((bytes[i] == 'D')||(bytes[i] == 'J'))
		{
			numparam+=2;
		}
	}

	argumentos = (u4 *)malloc(sizeof(u4) * numparam);

	for (i = (numparam - 1); i >= 0; i--)
    {
        argumentos[i] = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    }

    nomemetodo = i_dereferencia_instrucoes(metodoindex, frame->constant_pool);

    for(i = 0; i < classe->methods_count; i++) {
        index = classe->methods[i].name_index - 1;
        nome = i_dereferencia_instrucoes(index, classe->constant_pool);
        if(!strcmp(nomemetodo, nome))
            break;
    }
    if (i != classe->methods_count)
    {
        if (classe->methods[i].access_flags & AFNative)
        {
            u4 zero = 0;
            bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.bytes;
            length = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.length;
            if(bytes[length - 1] == 'D' || bytes[length - 1] == 'J') {
                EmpilhaOperando64bits(&frame->pilhaDeOperandos, &zero);
            } else if(bytes[length-1] != 'V') {
                EmpilhaOperando32bits(&frame->pilhaDeOperandos, &zero);
            }
        }
        else
        {
            prepara_metodo(&classe->methods[i], classe, pilhadeframes);
            frame1 = DesempilhaFrame(&pilhadeframes);
            for (j = (numparam - 1); j >= 0; j--)
            {
                frame1->VetorVariaveisLocais[j] = argumentos[j];
            }
            EmpilhaFrame(&pilhadeframes, frame1);
            executa_metodo(&classe->methods[i], classe, pilhadeframes);
        }
    }
    else
    {
        printf("metodo não encontrado");
    }

    return;
}

void i_invokeinterface(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, u1 contagem, u1 zero)
{
    ClassFile *classe;
    Frame *frame1;
    char *nome, *nomemetodo, *nomeclasse;
    u2 index, classeindex;
    u4 *argumentos, i, j;
    Objeto *obj;
    argumentos = (u4 *)malloc(sizeof(u4) * (contagem + 1));
    index = (u4)indexbyte1 << 8 | (u4)indexbyte2;
    classeindex = index;
    for (i = contagem; i >= 0; i--)
    {
        argumentos[i] = DesempilhaOperando32bits(&frame->pilhaDeOperandos);
    }
    index = frame->constant_pool[index - 1].info.InterfaceMethodref.name_and_type_index - 1;
    index = frame->constant_pool[index].info.NameAndType.name_index - 1;
    classeindex = frame->constant_pool[classeindex - 1].info.InterfaceMethodref.class_index - 1;
    classeindex = frame->constant_pool[classeindex].info.Class.name_index - 1;
    nomeclasse = i_dereferencia_instrucoes(classeindex, frame->constant_pool);
    classe = i_RecuperaClasse(nomeclasse, &listadeclasses);
    if (classe == NULL)
    {
        char *nomearquivo;
        classe = (ClassFile *)malloc(sizeof(ClassFile));
        nomearquivo = (char *)malloc(sizeof(char) * (strlen(nomeclasse) + 7));
        strcpy(nomearquivo, nomeclasse);
        strcat(nomearquivo, ".class");
        carrega_classe(nomearquivo, classe);
        InsereListaDeClasses(&listadeclasses, classe);
    }
    nomemetodo = i_dereferencia_instrucoes(index,frame->constant_pool);
    for(i = 0; i < classe->methods_count; i++) {
        index = classe->methods[i].name_index - 1;
        nome = i_dereferencia_instrucoes(index, classe->constant_pool);
        if(!strcmp(nomemetodo, nome))
            break;
    }
    if (i != obj->classe->methods_count)
    {
        prepara_metodo(&obj->classe->methods[i], obj->classe, pilhadeframes);
        frame1 = DesempilhaFrame(&pilhadeframes);
        for (j = contagem; j >= 0; j--)
        {
            frame1->VetorVariaveisLocais[j] = argumentos[j];
        }
        EmpilhaFrame(&pilhadeframes, frame1);
        executa_metodo(&obj->classe->methods[i], obj->classe, pilhadeframes);
    }
    else
    {
        printf("metodo não encontrado");
    }

    return;
}

void i_new(Frame *frame, u1 indexbyte1, u1 indexbyte2, ListaClasses *listadeclasses)
{
    Objeto *obj;
    char *nomeclasse;
    u2 index;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    nomeclasse = i_dereferencia_instrucoes(index, frame->constant_pool);
    obj = (Objeto *)malloc(sizeof(Objeto));
    obj->classe = i_RecuperaClasse(nomeclasse,&listadeclasses);
    if (obj->classe == NULL)
    {
        ClassFile *classe;
        char *nomearquivo;
        classe = (ClassFile *)malloc(sizeof(ClassFile));
        nomearquivo = (char *)malloc(sizeof(char) * (strlen(nomeclasse) + 7));
        strcpy(nomearquivo, nomeclasse);
        strcat(nomearquivo, ".class");
        carrega_classe(nomearquivo, classe);
        obj->classe = classe;
        InsereListaDeClasses(&listadeclasses, classe);
    }
    obj->tamanhotipoField = 0;
    obj->tipofield = NULL;
    obj->tamanhotipoArray = 0;
    obj->tipoarray = NULL;
    return;
}

void i_newarray(Frame *frame, u1 atype)
{
    u4 valor, referencia;
    tArray *a;
    a = (tArray *)malloc(sizeof(tArray));
    valor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    switch (atype)
    {
    case TipoByte:
        a->tag = TipoByte;
        a->info.tipoByte = (u1 *)malloc(sizeof(u1) * valor);
        break;
    case TipoChar:
        a->tag = TipoChar;
        a->info.tipoChar = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case TipoDouble:
        a->tag = TipoDouble;
        a->info.tipoDouble = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case TipoFloat:
        a->tag = TipoFloat;
        a->info.tipoFloat = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case TipoInt:
        a->tag = TipoInt;
        a->info.tipoInt = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case TipoLong:
        a->tag = TipoLong;
        a->info.tipoLong = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case TipoReferencia:
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case TipoShort:
        a->tag = TipoShort;
        a->info.tipoShort = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case TipoBoolean:
        a->tag = TipoBoolean;
        a->info.tipoBoolean = (u1 *)malloc(sizeof(u1) * valor);
        break;
    default:
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    }
#warning SMURF: ou está usando a funçao errada da pilha ou  passando o valor errado pra ser guardado
    referencia = a;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &referencia);
    return;
}

void i_anewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    char *tipo;
    u2 index;
    u4 i, valor, referencia;
    tArray *a;
    a = (tArray *)malloc(sizeof(tArray));
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    tipo = i_dereferencia_instrucoes(index, frame->constant_pool);
    valor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    i = 0;
    while (tipo[i] == '[')
    {
        i++;
    }
    switch (tipo[i])
    {
    case 'B':
        a->tag = TipoByte;
        a->info.tipoByte = (u1 *)malloc(sizeof(u1) * valor);
        break;
    case 'C':
        a->tag = TipoChar;
        a->info.tipoChar = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case 'D':
        a->tag = TipoDouble;
        a->info.tipoDouble = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case 'F':
        a->tag = TipoFloat;
        a->info.tipoFloat = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'I':
        a->tag = TipoInt;
        a->info.tipoInt = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'J':
        a->tag = TipoLong;
        a->info.tipoLong = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case 'L':
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'S':
        a->tag = TipoShort;
        a->info.tipoShort = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case 'Z':
        a->tag = TipoBoolean;
        a->info.tipoBoolean = (u1 *)malloc(sizeof(u1) * valor);
        break;
    default:
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    }
    #warning SMURF: ou está usando a funçao errada da pilha ou  passando o valor errado pra ser guardado
    referencia = a;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &referencia);
    return;
}

void i_arraylength(Frame *frame)
{
    tArray *a;
    a = (tArray *)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &(a->tamanho1));
    return;
}

void i_atrhow(Frame *frame)
{

    return;
}

void i_checkcast(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    char *nomeclasse, *nomeclasseobjeto;
    Objeto *obj;
    u2 index;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    obj = (Objeto *)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    nomeclasse = i_dereferencia_instrucoes(index, frame->constant_pool);
    nomeclasseobjeto = i_dereferencia_instrucoes(obj->classe->constant_pool[obj->classe->this_class - 1].info.Class.name_index - 1, obj->classe->constant_pool);
    if (obj == NULL)
    {
        printf("Erro: Referencia nula\n");
    } else if (!strcmp(nomeclasse,nomeclasseobjeto))
    {
        printf(" Erro: Objeto do tipo errado\n");
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), (u4 *)obj);
    return;
}

void i_instanceof(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    char *nomeclasse, *nomeclasseobjeto;
    Objeto *obj;
    u2 index;
    u4 valor = 0;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    obj = (Objeto *)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    nomeclasse = i_dereferencia_instrucoes(index, frame->constant_pool);
    nomeclasseobjeto = i_dereferencia_instrucoes(obj->classe->constant_pool[obj->classe->this_class - 1].info.Class.name_index - 1, obj->classe->constant_pool);
    if (obj == NULL)
    {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
    } else if (!strcmp(nomeclasse,nomeclasseobjeto))
    {
        valor = 1;
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
    } else
    {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
    }
    return;
}

void i_monitorenter(Frame *frame)
{
    return;
}

void i_monitorexit(Frame *frame)
{
    return;
}

void i_wide(Frame *frame, u1 opcode, u1 index, u1 index2, u1 constbyte1, u1 constbyte2)
{
	int16_t valor;
	u4 value = 0;
    u2 indexConcat = 0;
    indexConcat = (u2)(index<<8) | (u2)(index2);
    switch (opcode)
    {
        case 0x15:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x16:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat + 1]));
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x17:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x18:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat + 1]));
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x19:
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(frame->VetorVariaveisLocais[indexConcat]));
        break;
        case 0x36:
			value=0;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
        break;
        case 0x37:
			value=0;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat + 1] = value;
        break;
        case 0x38:
			value=0;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
        break;
        case 0x39:
			value=0;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat + 1] = value;
        break;
        case 0x3a:
			value=0;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
        break;
        case 0x84:

            valor = (int16_t)(constbyte1<<8) | (int16_t)(constbyte2);
            frame->VetorVariaveisLocais[indexConcat] += valor;
        break;
    }
    return;
}

void i_multianewarray(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 dimensions)
{
    u4 valor;
    int i;
    char *tipo;
    u2 index;
    tArray *a;
    a = (tArray *)malloc(sizeof(tArray));
    index = (u2)(indexbyte1 << 8 | indexbyte2);
    index = ((frame->constant_pool[index - 1].info.Class.name_index) - 1);
    tipo = i_dereferencia_instrucoes(index, frame->constant_pool);
    valor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    a->tamanho1 = valor;
    for (i = 1; i < dimensions; i++)
    {
        valor *= DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    }
    i = 0;
    while (tipo[i] == '[')
    {
        i++;
    }
    a->tamanho = valor;
    switch (tipo[i])
    {
    case 'B':
        a->tag = TipoByte;
        a->info.tipoByte = (u1 *)malloc(sizeof(u1) * valor);
        break;
    case 'C':
        a->tag = TipoChar;
        a->info.tipoChar = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case 'D':
        a->tag = TipoDouble;
        a->info.tipoDouble = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case 'F':
        a->tag = TipoFloat;
        a->info.tipoFloat = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'I':
        a->tag = TipoInt;
        a->info.tipoInt = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'J':
        a->tag = TipoLong;
        a->info.tipoLong = (u8 *)malloc(sizeof(u8) * valor);
        break;
    case 'L':
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    case 'S':
        a->tag = TipoShort;
        a->info.tipoShort = (u2 *)malloc(sizeof(u2) * valor);
        break;
    case 'Z':
        a->tag = TipoBoolean;
        a->info.tipoBoolean = (u1 *)malloc(sizeof(u1) * valor);
        break;
    default:
        a->tag = TipoReferencia;
        a->info.tipoReferencia = (u4 *)malloc(sizeof(u4) * valor);
        break;
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &a);
    return;
}

void i_ifnull(Frame *frame, u1 branchbyte1, u1 branchbyte2)
{
    u4 objref;
    u2 branchoffset;
    branchoffset = (branchbyte1 << 8 | branchbyte2);
    objref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if (objref == NULL)
        frame->pc = frame->pc + branchoffset;

    return;
}

void i_ifnonnull(Frame *frame, u1 branchbyte1, u1 branchbyte2)
{
    u4 objref;
    u2 branchoffset;
    branchoffset = (branchbyte1 << 8 | branchbyte2);
    objref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if (objref != NULL)
        frame->pc = frame->pc + branchoffset;

    return;
}

void i_goto_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4)
{
    u4 branchoffset;
    branchoffset = (branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4);
    frame->pc = frame->pc + branchoffset;
    return;
}

void i_jsr_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4)
{
    u4 branchoffset, pc;
    branchoffset = (branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4);
    pc = frame->pc + 5;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &pc);
    frame->pc = frame->pc + branchoffset;
    return;
}

char* i_dereferencia_instrucoes(u2 index, cp_info *cp)
{
    char *nome;
    int i, j;

    for (i = 0; i < cp[index].info.Utf8.length; i++)
    {
        if ((char)cp[index].info.Utf8.bytes[i] == '$')
            break;
    }

    if (i == cp[index].info.Utf8.length)
    {
        nome = (char *) malloc((cp[index].info.Utf8.length + 1) * sizeof(char));
        for (i = 0; i < cp[index].info.Utf8.length; i++)
        {
            nome[i] = cp[index].info.Utf8.bytes[i];
        }
        nome[i] = '\0';
        return nome;
    }
    else
    {
        nome = (char *) malloc((cp[index].info.Utf8.length - i) * sizeof(char));
        for (j = 0; i < cp[index].info.Utf8.length; i++, j++)
        {
            nome[j] = cp[index].info.Utf8.bytes[i];
        }
    }
    nome[j] = '\0';
    return nome;
}

ClassFile *i_RecuperaClasse(char *nome, ListaClasses **listadeclasses)
{
    ListaClasses *lc1;
    int index;
    char *nomeThisClass;
    lc1 = *listadeclasses;
    while (lc1 != NULL)
    {
        index = lc1->dado->constant_pool[lc1->dado->this_class - 1].info.Class.name_index - 1;
        nomeThisClass = dereferencia(index, lc1->dado);
        if (!strcmp(nome,nomeThisClass))
            return lc1->dado;
        lc1 = lc1->prox;
    }
    return NULL;
}
