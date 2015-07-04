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
    float f;
    switch (tag)
    {
    case CONSTANT_Integer:  //Integer
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Integer.bytes);
        break;
    case CONSTANT_Float: //Float
    	dado =  constantPool[index-1].info.Float.bytes;
    	memcpy(&f, &dado, sizeof(u4));
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&dado);
        break;
    case CONSTANT_String: //String, Need to see the correct reference to save it.
		dado =  constantPool[index-1].info.String.string_index;
		EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&dado);
        break;
    }
}

void i_ldc_w(Frame* frame,u1 index,u1 index2, cp_info* constantPool)
{
	u4 dado=0;
    u1 tag = constantPool[index-1].tag;
    float f=0;
    switch (tag)
    {
    case CONSTANT_Integer: //Integer
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&constantPool[index-1].info.Integer.bytes);
        break;
    case CONSTANT_Float: //Float
        	dado = (constantPool[index-1].info.Float.bytes);
        	memcpy(&f, &dado, sizeof(u4));
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&(constantPool[index-1].info.Float.bytes));
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
    u8 dado;
    switch(tag)
    {
    case CONSTANT_Long:
		dado = ((u8)constantPool[indexConcat-1].info.Long.high_bytes <<32) | constantPool[indexConcat-1].info.Long.low_bytes;
		EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&dado);
        break;
    case CONSTANT_Double:
       dado = ((u8)constantPool[indexConcat-1].info.Long.high_bytes <<32) | constantPool[indexConcat-1].info.Long.low_bytes;
       EmpilhaOperando64bits(&(frame->pilhaDeOperandos),&dado);
        break;
    }
}

void i_goto(Frame* frame, u1 index1, u1 index2){
	int16_t offset = (((u2)index1)<<8)+index2;
	frame->pc += offset - 3;
}

void i_jsr(Frame* frame, u1 index, u1 index2){
	EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &(frame->pc));
	int16_t offset = (((u2)index)<<8)+index2;
		frame->pc += offset - 3;
}

void i_ret(Frame* frame, u1 index){
	frame->pc = frame->VetorVariaveisLocais[index];
}

void i_tableswitch(Frame *frame)
{
    int32_t defaultbyte, high, low, index;
	int32_t *tableswitch;
	u4 byte1, byte2, byte3, byte4;
	u4 enderecotable;
	u4 target, tableSize;
	u4 i;

	index = (int32_t)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	enderecotable = frame->pc;

	while((frame->pc + 1) % 4 != 0) {
		frame->pc++;
	}
	frame->pc++;

	byte1 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte2 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte3 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte4 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	defaultbyte = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

	byte1 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte2 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte3 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte4 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	low = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

	byte1 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte2 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte3 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte4 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	high = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

	tableSize = high - low + 1;
	tableswitch = calloc(sizeof(u4), tableSize);

	for(i = 0; i < tableSize; i++) 	{
		byte1 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		byte2 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		byte3 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		byte4 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		tableswitch[i] = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));
	}

	if(index < low || index > high) {
		target = enderecotable + defaultbyte;
	} else {
		u4 offset = tableswitch[index - low];
		target = enderecotable + offset;
	}
	frame->pc = target;
	free(tableswitch);
    return;
}

void i_lookupswitch(Frame *frame)
{
    int32_t defaultbyte, npairs, key;
	int32_t *match, *offset;
	u4 byte1, byte2, byte3, byte4;
	u4 target, enderecolookup;
	u4 i;
	u1 encontrado;

	key = (int32_t)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
	enderecolookup = frame->pc;

	while((frame->pc + 1) % 4 != 0) {
		frame->pc++;
	}
	frame->pc++;

	byte1 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte2 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte3 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte4 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	defaultbyte = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

	byte1 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte2 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte3 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	byte4 = frame->codigo->info.CodeAttribute.code[frame->pc++];
	npairs = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

	match = calloc(sizeof(int32_t), npairs);
	offset = calloc(sizeof(int32_t), npairs);
	for(i = 0; i < npairs; i++) {
		byte1 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		byte2 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		byte3 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		byte4 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		match[i] = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));
		byte1 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		byte2 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		byte3 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		byte4 = frame->codigo->info.CodeAttribute.code[frame->pc++];
		offset[i] = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));
	}

	i = 0;
	encontrado = 0;
	while((i < npairs) &&(!encontrado)) {
		if(match[i] == key)
			encontrado = 1;
		i++;
	}
	i--;

	if(encontrado) {
		target = offset[i] + enderecolookup;
	} else {
		target = defaultbyte + enderecolookup;
	}
	frame->pc = target;
	free(match);
	free(offset);
    return;
}

void i_ireturn(Frame *frame)
{
    Frame *frame1;
    u4 valor;
    valor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame1 = frame;
    if (frame->pilhaDeFrames != NULL)
    {
        frame = DesempilhaFrame(&frame->pilhaDeFrames);
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &valor);
        frame->pilhaDeFrames = EmpilhaFrame(frame->pilhaDeFrames, frame);
        DestruirFrame(frame1);
    }
    else
    {
        frame->pc = frame->codigo->info.CodeAttribute.code_length;
    }

    return;
}

void i_lreturn(Frame *frame)
{
    Frame *frame1;
    u8 valor;
    valor = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame1 = frame;
    if (frame->pilhaDeFrames != NULL)
    {
        frame = DesempilhaFrame(&frame->pilhaDeFrames);
        EmpilhaOperando64bits(&(frame->pilhaDeOperandos), &valor);
        frame->pilhaDeFrames = EmpilhaFrame(frame->pilhaDeFrames, frame);
        DestruirFrame(frame1);
    }
    else
    {
        frame->pc = frame->codigo->info.CodeAttribute.code_length;
    }

    return;
}

void i_freturn(Frame *frame)
{
    Frame *frame1;
    u4 valor;
    valor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame1 = frame;
    if (frame->pilhaDeFrames != NULL)
    {
        frame = DesempilhaFrame(&frame->pilhaDeFrames);
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &valor);
        frame->pilhaDeFrames = EmpilhaFrame(frame->pilhaDeFrames, frame);
        DestruirFrame(frame1);
    }
    else
    {
        frame->pc = frame->codigo->info.CodeAttribute.code_length;
    }

    return;
}

void i_dreturn(Frame* frame)
{
    Frame *frame1;
    u8 valor;
    valor = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    frame1 = frame;
    if (frame->pilhaDeFrames != NULL)
    {
        frame = DesempilhaFrame(&frame->pilhaDeFrames);
        EmpilhaOperando64bits(&(frame->pilhaDeOperandos), &valor);
        frame->pilhaDeFrames = EmpilhaFrame(frame->pilhaDeFrames, frame);
        DestruirFrame(frame1);
    }
    else
    {
        frame->pc = frame->codigo->info.CodeAttribute.code_length;
    }

    return;
}

void i_areturn(Frame* frame)
{
    Frame *frame1;
    u4 valor;
    valor = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    frame1 = frame;
    if (frame->pilhaDeFrames != NULL)
    {
        frame = DesempilhaFrame(&frame->pilhaDeFrames);
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &valor);
        frame->pilhaDeFrames = EmpilhaFrame(frame->pilhaDeFrames, frame);
        DestruirFrame(frame1);
    }
    else
    {
        frame->pc = frame->codigo->info.CodeAttribute.code_length;
    }

    return;
}

void i_return(Frame* frame)
{
	frame->pc = frame->codigo->info.CodeAttribute.code_length;
    return;
}

void i_getstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
{
    ClassFile *classe = NULL;
    staticField *field = NULL;
    char *tipo = NULL, *name = NULL, *nomeclasse = NULL, *nome = NULL;
    u8 valoru8 = 0;
    u4 valoru4 = 0;
    u2 index = 0, tipoindex = 0, nameindex = 0, fieldindex = 0, nomeclasseindex = 0;
    index = (u2) indexbyte1 << 8 | (u2)indexbyte2;
    nomeclasseindex = frame->constant_pool[index - 1].info.Fieldref.class_index - 1;
    nomeclasseindex = frame->constant_pool[nomeclasseindex].info.Class.name_index - 1;
    tipoindex = frame->constant_pool[index - 1].info.Fieldref.name_and_type_index - 1;
    nameindex = frame->constant_pool[tipoindex].info.NameAndType.name_index - 1;
    tipoindex = frame->constant_pool[tipoindex].info.NameAndType.descriptor_index - 1;
    tipo = dereferencia_instrucao(tipoindex, frame->constant_pool);
    name = dereferencia_instrucao(nameindex, frame->constant_pool);
    nomeclasse = dereferencia_instrucao(nomeclasseindex, frame->constant_pool);
    classe = RecuperaClassePorNome(nomeclasse, &listadeclasses);
    if(!classe) {
        if(!strcmp(nomeclasse, "java/lang/System")) {
            if (tipo[0] == 'J' || tipo[0] == 'D')
            {
                valoru8 = 0;
                EmpilhaOperando64bits(&(frame->pilhaDeOperandos), &valoru8);
            }
            else
            {
                valoru4 = 0;
                EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &valoru4);
            }
            free(tipo);
            free(name);
            free(nome);
            return;
        }
        else {
            exit(-1);
        }
    }
    field = recupera_field(nomeclasse, &listadefields);
    if(!field) {
        if (tipo[0] == 'J' || tipo[0] == 'D')
        {
            valoru8 = 0;
            EmpilhaOperando64bits(&(frame->pilhaDeOperandos), &valoru8);
        }
        else
        {
            valoru4 = 0;
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &valoru4);
        }
        free(tipo);
        free(name);
        free(nome);
        return;
    }
    for (fieldindex = 0; fieldindex < classe->fields_count; fieldindex++)
    {
        u2 nomeindex = classe->fields[fieldindex].name_index - 1;
        nome = dereferencia_instrucao(nomeindex, classe->constant_pool);
        if (!strcmp(name, nome))
            break;
    }

    if (tipo[0] == 'J' || tipo[0] == 'D')
    {
        valoru8 = field->valor[fieldindex];
        EmpilhaOperando64bits(&(frame->pilhaDeOperandos), &valoru8);
    }
    else
    {
        valoru4 = (u4) field->valor[fieldindex];
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &valoru4);
    }
    free(tipo);
    free(name);
    free(nome);
    return;
}

void i_putstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2)
{
    ClassFile *classe;
    staticField *field;
    char *tipo, *name, *nomeclasse, *nome;
    u8 valor;
    u2 index, tipoindex, nameindex, fieldindex, nomeclasseindex;
    index = (u2)indexbyte1 << 8 | (u2)indexbyte2;
    nomeclasseindex = frame->constant_pool[index - 1].info.Fieldref.class_index - 1;
    nomeclasseindex = frame->constant_pool[nomeclasseindex].info.Class.name_index - 1;
    tipoindex = frame->constant_pool[index - 1].info.Fieldref.name_and_type_index - 1;
    nameindex = frame->constant_pool[tipoindex].info.NameAndType.name_index - 1;
    tipoindex = frame->constant_pool[tipoindex].info.NameAndType.descriptor_index - 1;
    tipo = dereferencia_instrucao(tipoindex, frame->constant_pool);
    name = dereferencia_instrucao(nameindex, frame->constant_pool);
    nomeclasse = dereferencia_instrucao(nomeclasseindex, frame->constant_pool);
    classe = RecuperaClassePorNome(nomeclasse, &listadeclasses);
    if (tipo[0] == 'J' || tipo[0] == 'D')
        valor = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    else
        valor = (u8) DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    for (fieldindex = 0; fieldindex < classe->fields_count; fieldindex++)
    {
        u2 nomeindex = classe->fields[fieldindex].name_index - 1;
        nome = dereferencia_instrucao(nomeindex, classe->constant_pool);
        if (!strcmp(name, nome))
            break;
    }

    field = recupera_field(nomeclasse, &listadefields);
    if (field == NULL)
    {
        field = (staticField *)malloc(sizeof(staticField));
        field->NomeClasse = (char *)malloc(sizeof(char) * (strlen(nomeclasse) + 1));
        strcpy(field->NomeClasse, nomeclasse);
        field->fieldCount = classe->fields_count;
        field->valor = (u8 *)malloc(sizeof(u8) * field->fieldCount);
        field->valor[fieldindex] = valor;
        InsereListaDeFields(&listadefields, field);
    }

    field->valor[fieldindex] = valor;
    free(tipo);
    free(name);
    free(nome);
    return;
}

void i_getfield(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    Objeto *obj;
    char *tipo, *name, *nome;
    u8 valoru8;
    u4 valoru4;
    u2 index, tipoindex, nameindex, fieldindex;
    index = (u2)indexbyte1 << 8 | (u2)indexbyte2;
    tipoindex = frame->constant_pool[index - 1].info.Fieldref.name_and_type_index - 1;
    nameindex = frame->constant_pool[tipoindex].info.NameAndType.name_index - 1;
    tipoindex = frame->constant_pool[tipoindex].info.NameAndType.descriptor_index - 1;
    tipo = dereferencia_instrucao(tipoindex, frame->constant_pool);
    name = dereferencia_instrucao(nameindex, frame->constant_pool);

    obj = (void*)(long)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    for (fieldindex = 0; fieldindex < obj->tamanhotipoField; fieldindex++)
    {
        u2 nomeindex = obj->classe->fields[fieldindex].name_index - 1;
        nome = dereferencia_instrucao(nomeindex, obj->classe->constant_pool);
        if (!strcmp(name, nome))
            break;
    }

    if (tipo[0] == 'J' || tipo[0] == 'D')
    {
        valoru8 = obj->tipofield[fieldindex];
        EmpilhaOperando64bits(&(frame->pilhaDeOperandos), &valoru8);
    }
    else
    {
        valoru4 = (u4)obj->tipofield[fieldindex];
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &valoru4);
    }
    free(tipo);
    free(name);
    free(nome);
    return;
}

void i_putfield(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    Objeto *obj;
    char *tipo, *name, *nome;
    u8 valor;
    u2 index, tipoindex, nameindex, fieldindex;
    index = (u2)indexbyte1 << 8 | (u2)indexbyte2;
    tipoindex = frame->constant_pool[index - 1].info.Fieldref.name_and_type_index - 1;
    nameindex = frame->constant_pool[tipoindex].info.NameAndType.name_index - 1;
    tipoindex = frame->constant_pool[tipoindex].info.NameAndType.descriptor_index - 1;
    tipo = dereferencia_instrucao(tipoindex, frame->constant_pool);
    name = dereferencia_instrucao(nameindex, frame->constant_pool);

    if (tipo[0] == 'J' || tipo[0] == 'D')
        valor = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
    else
        valor = (u8)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    obj = (void*)(long)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    for (fieldindex = 0; fieldindex < obj->classe->fields_count; fieldindex++)
    {
        u2 nomeindex = obj->classe->fields[fieldindex].name_index - 1;
        nome = dereferencia_instrucao(nomeindex, obj->classe->constant_pool);
        if (!strcmp(name, nome))
            break;
    }

    obj->tipofield[fieldindex] = valor;
    free(tipo);
    free(name);
    free(nome);
    return;
}

void i_invokevirtual(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, Heap *heap)
{
    int i = 0;
    ClassFile *classe = NULL;
    float valorf = 0;
    char *nomeclasse = NULL, *nomemetodo = NULL, *metododesc = NULL, *nome = NULL, *nomedesc = NULL;
    u8 valoru8 = 0;
    u4 valoru4 = 0, *argumentos = NULL;
    u2 index = 0, classindex = 0, descriptorindex = 0, metodoindex = 0;
    index = (u2)indexbyte1 << 8 | (u2)indexbyte2;
    classindex = frame->constant_pool[index - 1].info.Methodref.class_index - 1;
    classindex = frame->constant_pool[classindex].info.Class.name_index - 1;
    nomeclasse = dereferencia_instrucao(classindex, frame->constant_pool);
    descriptorindex = frame->constant_pool[index - 1].info.Methodref.name_and_type_index - 1;
    metodoindex = frame->constant_pool[descriptorindex].info.NameAndType.name_index - 1;
    descriptorindex = frame->constant_pool[descriptorindex].info.NameAndType.descriptor_index - 1;
    nomemetodo = dereferencia_instrucao(metodoindex, frame->constant_pool);
    metododesc = dereferencia_instrucao(descriptorindex, frame->constant_pool);

    if (!strcmp(nomeclasse, "java/io/PrintStream") && (!strcmp(nomemetodo, "print") || !strcmp(nomemetodo, "println")))
    {
        //Long
        if (strstr(metododesc, "J") != NULL)
        {
            valoru8 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
            int64_t value = valoru8;
            printf("%ld", value);

        }//Double
        else if (strstr(metododesc, "D") != NULL)
        {
            valoru8 = DesempilhaOperando64bits(&(frame->pilhaDeOperandos));
            double value;
            memcpy(&value,&valoru8,sizeof(u8));
            printf("%f", value);

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
                tArray *array1 = (void*)(long)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
                for (i = 0; i < array1->tamanho1; i++)
                {
                    printf("%c", array1->info.tipoChar[i]);
                }

            }//Char
            else
            {
                printf("%c", DesempilhaOperando32bits(&(frame->pilhaDeOperandos)));
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
            if (valoru4 != 0)
            {
                char *cpointer = dereferencia((u2) valoru4 - 1, frame->classe);
                printf("%s", cpointer);
            }
            else
            {
                printf("%s", (char *)valoru4);
            }

        }//Object
        else if (strstr(metododesc, "Ljava/lang/Object") != NULL)
        {
			valoru4 = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            void *ppointer = (void*)(long)valoru4;
            printf("%p",ppointer);
        }

        if (strstr(nomemetodo, "println") != NULL)
            printf("\n");
    }
    else
    {
        u4 numparam = 0;
        classe = RecuperaClassePorNome(nomeclasse, &listadeclasses);
        if (classe == NULL)
        {
            char *nomearquivo;
            classe = (ClassFile *)malloc(sizeof(ClassFile));
            nomearquivo = (char *)malloc(sizeof(char) * (strlen(nomeclasse) + 7));
            strcpy(nomearquivo, nomeclasse);
            strcat(nomearquivo, ".class");
            carrega_classe(nomearquivo, classe);
            listadeclasses = InsereListaDeClasses(&listadeclasses, classe);
            frame->heap->listaDeClasses = listadeclasses;
        }

        u1 *bytes = frame->constant_pool[descriptorindex].info.Utf8.bytes;
        u2 length = frame->constant_pool[descriptorindex].info.Utf8.length;

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

        nomemetodo = dereferencia_instrucao(metodoindex, frame->constant_pool);

        for(i = 0; i < classe->methods_count; i++) {
            index = classe->methods[i].name_index - 1;
            nome = dereferencia_instrucao(index, classe->constant_pool);
            u2 index1 = classe->methods[i].descriptor_index - 1;
            nomedesc = dereferencia_instrucao(index1, classe->constant_pool);
            if(!strcmp(nomemetodo, nome) && !strcmp(metododesc, nomedesc))
                break;
        }
        if (i != classe->methods_count)
        {
            if (classe->methods[i].access_flags & ACC_NATIVE)
            {
                u8 zero64 = 0;
                u4 zero32 = 0;

                bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.bytes;
                length = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.length;
                if(bytes[length - 1] == 'D' || bytes[length - 1] == 'J') {
                    EmpilhaOperando64bits(&frame->pilhaDeOperandos, &zero64);
                }
                else if(bytes[length-1] != 'V')
                {
                    EmpilhaOperando32bits(&frame->pilhaDeOperandos, &zero32);
                }
            }
            else
            {
                prepara_metodo(&classe->methods[i], classe,&pilhadeframes, &heap);
                Frame *frame1 = DesempilhaFrame(&pilhadeframes);
                for (int j = numparam; j >= 0; j--)
                {
                    frame1->VetorVariaveisLocais[j] = argumentos[j];
                }
                pilhadeframes = EmpilhaFrame(pilhadeframes, frame1);
                executa_metodo(&classe->methods[i], classe, pilhadeframes);
            }
        }
        else
        {
            printf("metodo não encontrado");
        }
    }
    free(nomemetodo);
    free(metododesc);
    free(nome);
    free(nomedesc);
    free(argumentos);
    return;
}

void i_invokespecial(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, Heap *heap)
{
    int i = 0;
    ClassFile *classe = NULL;
    char *nomeclasse = NULL, *nomemetodo = NULL, *nome, *nomedesc, *metododesc;
    u4 numparam = 0, *argumentos = NULL;
    u2 index = 0, classindex = 0, descriptorindex = 0, metodoindex = 0, length = 0;
    u1 *bytes = NULL;
    index = (u2)indexbyte1 << 8 | (u2)indexbyte2;
    classindex = frame->constant_pool[index - 1].info.Methodref.class_index - 1;
    classindex = frame->constant_pool[classindex].info.Class.name_index - 1;
    nomeclasse = dereferencia_instrucao(classindex, frame->constant_pool);
    classe = RecuperaClassePorNome(nomeclasse, &listadeclasses);
    if (classe == NULL)
    {
        char *nomearquivo;
        classe = (ClassFile *)malloc(sizeof(ClassFile));
        nomearquivo = (char *)malloc(sizeof(char) * (strlen(nomeclasse) + 7));
        strcpy(nomearquivo, nomeclasse);
        strcat(nomearquivo, ".class");
        carrega_classe(nomearquivo, classe);
        listadeclasses = InsereListaDeClasses(&listadeclasses, classe);
        frame->heap->listaDeClasses = listadeclasses;
    }
    descriptorindex = frame->constant_pool[index - 1].info.Methodref.name_and_type_index - 1;
    metodoindex = frame->constant_pool[descriptorindex].info.NameAndType.name_index - 1;
    descriptorindex = frame->constant_pool[descriptorindex].info.NameAndType.descriptor_index - 1;
    nomemetodo = dereferencia_instrucao(metodoindex, frame->constant_pool);
    metododesc = dereferencia_instrucao(descriptorindex, frame->constant_pool);
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

	argumentos = (u4 *)malloc(sizeof(u4) * (numparam + 1));

	for (i = numparam; i >= 0; i--)
    {
        argumentos[i] = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    }

    for(i = 0; i < classe->methods_count; i++) {
        index = classe->methods[i].name_index - 1;
        nome = dereferencia_instrucao(index, classe->constant_pool);
        u2 index1 = classe->methods[i].descriptor_index - 1;
        nomedesc = dereferencia_instrucao(index1, classe->constant_pool);
        if(!strcmp(nomemetodo, nome) && !strcmp(metododesc, nomedesc))
            break;
    }

    if (classe->methods[i].access_flags & ACC_NATIVE)
    {
        u4 zerou4 = 0;
        u8 zerou8 = 0;
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
        prepara_metodo(&classe->methods[i], classe,&pilhadeframes, &heap);
        Frame *frame1 = DesempilhaFrame(&pilhadeframes);
        for (int j = numparam; j >= 0; j--)
        {
            frame1->VetorVariaveisLocais[j] = argumentos[j];
        }
        pilhadeframes = EmpilhaFrame(pilhadeframes, frame1);
        executa_metodo(&classe->methods[i], classe, pilhadeframes);
    }
    free(argumentos);
    return;
}

void i_invokestatic(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, Heap *heap)
{
    int i = 0;
    ClassFile *classe = NULL;
    char *nomeclasse = NULL, *nomemetodo = NULL, *metododesc = NULL, *nome = NULL, *nomedesc = NULL;
    u4 numparam = 0, *argumentos = NULL;
    u2 index = 0, classindex = 0, descriptorindex = 0, metodoindex = 0, length = 0;
    u1 *bytes = NULL;
    index = (u4)indexbyte1 << 8 | (u4)indexbyte2;
    classindex = frame->constant_pool[index - 1].info.Methodref.class_index - 1;
    classindex = frame->constant_pool[classindex].info.Class.name_index - 1;
    nomeclasse = dereferencia_instrucao(classindex, frame->constant_pool);
    classe = RecuperaClassePorNome(nomeclasse, &listadeclasses);
    descriptorindex = frame->constant_pool[index - 1].info.Methodref.name_and_type_index - 1;
    metodoindex = frame->constant_pool[descriptorindex].info.NameAndType.name_index - 1;
    descriptorindex = frame->constant_pool[descriptorindex].info.NameAndType.descriptor_index - 1;
    metododesc = dereferencia_instrucao(descriptorindex, frame->constant_pool);
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

    nomemetodo = dereferencia_instrucao(metodoindex, frame->constant_pool);

    for(i = 0; i < classe->methods_count; i++) {
        index = classe->methods[i].name_index - 1;
        nome = dereferencia_instrucao(index, classe->constant_pool);
        u2 index1 = classe->methods[i].descriptor_index - 1;
        nomedesc = dereferencia_instrucao(index1, classe->constant_pool);
        if(!strcmp(nomemetodo, nome) && !strcmp(metododesc, nomedesc))
            break;
    }

    if (i != classe->methods_count)
    {
        if (classe->methods[i].access_flags & ACC_NATIVE)
        {
            u4 zero32 = 0;
            u8 zero64 = 0;
            bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.bytes;
            length = classe->constant_pool[classe->methods[i].descriptor_index - 1].info.Utf8.length;
            if(bytes[length - 1] == 'D' || bytes[length - 1] == 'J') {
                EmpilhaOperando64bits(&frame->pilhaDeOperandos, &zero64);
            } else if(bytes[length-1] != 'V') {
                EmpilhaOperando32bits(&frame->pilhaDeOperandos, &zero32);
            }
        }
        else
        {
            prepara_metodo(&classe->methods[i], classe, &pilhadeframes, &heap);
            Frame *frame1 = DesempilhaFrame(&pilhadeframes);
            for (int j = (numparam - 1); j >= 0; j--)
            {
                frame1->VetorVariaveisLocais[j] = argumentos[j];
            }
            pilhadeframes = EmpilhaFrame(pilhadeframes, frame1);
            executa_metodo(&classe->methods[i], classe, pilhadeframes);
        }
    }
    else
    {
        printf("metodo não encontrado");
    }
    free(nomemetodo);
    free(metododesc);
    free(nome);
    free(nomedesc);
    free(argumentos);
    return;
}

void i_invokeinterface(Frame *frame, PilhaDeFrames *pilhadeframes, ListaClasses *listadeclasses, u1 indexbyte1, u1 indexbyte2, u1 contagem, u1 zero, Heap *heap)
{
    int i = 0;
    ClassFile *classe;
    char *nome = NULL, *nomemetodo = NULL, *nomeclasse = NULL, *nomedesc = NULL, *metododesc = NULL;
    u2 index = 0, classeindex = 0, descriptorindex = 0;
    u4 *argumentos;
    Objeto *obj = (Objeto *) malloc(sizeof(Objeto));
    argumentos = (u4 *) malloc(sizeof(u4) * (contagem + 1));
    index = (u2)indexbyte1 << 8 | (u2)indexbyte2;
    classeindex = index;
    nomeclasse = dereferencia_instrucao(classeindex, frame->constant_pool);
    obj->classe = RecuperaClassePorNome(nomeclasse, &listadeclasses);
    for (i = contagem; i >= 0; i--)
    {
        argumentos[i] = DesempilhaOperando32bits(&frame->pilhaDeOperandos);
    }
    index = frame->constant_pool[index - 1].info.InterfaceMethodref.name_and_type_index - 1;
    descriptorindex = frame->constant_pool[index].info.NameAndType.descriptor_index - 1;
    index = frame->constant_pool[index].info.NameAndType.name_index - 1;
    classeindex = frame->constant_pool[classeindex - 1].info.InterfaceMethodref.class_index - 1;
    classeindex = frame->constant_pool[classeindex].info.Class.name_index - 1;
    nomeclasse = dereferencia_instrucao(classeindex, frame->constant_pool);
    classe = RecuperaClassePorNome(nomeclasse, &listadeclasses);
    metododesc = dereferencia_instrucao(descriptorindex, frame->constant_pool);
    nomemetodo = dereferencia_instrucao(index,frame->constant_pool);
    for(i = 0; i < classe->methods_count; i++) {
        index = classe->methods[i].name_index - 1;
        nome = dereferencia_instrucao(index, classe->constant_pool);
        u2 index1 = classe->methods[i].descriptor_index - 1;
        nomedesc = dereferencia_instrucao(index1, classe->constant_pool);
        if(!strcmp(nomemetodo, nome) && !strcmp(metododesc, nomedesc))
            break;
    }
    if (i != obj->classe->methods_count)
    {
        prepara_metodo(&obj->classe->methods[i], obj->classe, &pilhadeframes, &heap);
        Frame *frame1 = DesempilhaFrame(&pilhadeframes);
        for (int j = contagem; j >= 0; j--)
        {
            frame1->VetorVariaveisLocais[j] = argumentos[j];
        }
        pilhadeframes = EmpilhaFrame(pilhadeframes, frame1);
        executa_metodo(&obj->classe->methods[i], obj->classe, pilhadeframes);
    }
    else
    {
        printf("Metodo não encontrado");
    }
    free(nome);
    free(nomemetodo);
    free(nomedesc);
    free(metododesc);
    free(argumentos);
    return;
}

void i_new(Frame *frame, u1 indexbyte1, u1 indexbyte2, ListaClasses *listadeclasses)
{
    u4 valor;
    Objeto *obj;
    char *nomeclasse;
    u2 index;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    nomeclasse = dereferencia_instrucao(index, frame->constant_pool);
    obj = (Objeto *)malloc(sizeof(Objeto));
    obj->classe = RecuperaClassePorNome(nomeclasse,&listadeclasses);
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
        listadeclasses = InsereListaDeClasses(&listadeclasses, classe);
        frame->heap->listaDeClasses = listadeclasses;
    }
    obj->tamanhotipoField = obj->classe->fields_count;
    obj->tipofield = (u8 *)malloc(sizeof(u8) * obj->tamanhotipoField);
    valor = (u4)(long)obj;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &valor);

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
    referencia = (int)(long)a;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &(referencia));
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
    tipo = dereferencia_instrucao(index, frame->constant_pool);
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
    referencia = (int)(long)a;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &referencia);
    free(tipo);
    return;
}

void i_arraylength(Frame *frame)
{
    tArray *a;
    a = (void*)(long)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &(a->tamanho1));
    return;
}

void i_atrhow(Frame *frame)
{
    return;
}

void i_checkcast(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    char *nomeclasse = NULL, *nomeclasseobjeto = NULL;
    Objeto *obj;
    u2 index;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    obj = (void*)(long)DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if(obj != NULL) {
        index = frame->constant_pool[index - 1].info.Class.name_index - 1;
        nomeclasse = dereferencia_instrucao(index, frame->constant_pool);
        nomeclasseobjeto = dereferencia_instrucao(obj->classe->constant_pool[obj->classe->this_class - 1].info.Class.name_index - 1, obj->classe->constant_pool);
        if(!strcmp(nomeclasse,nomeclasseobjeto)) {
            printf("Erro: Objeto do tipo errado\n");
        }
    }
    else {
        printf("Erro: Referencia nula\n");
    }
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), (u4 *)obj);
    free(nomeclasse);
    free(nomeclasseobjeto);
    return;
}

void i_instanceof(Frame *frame, u1 indexbyte1, u1 indexbyte2)
{
    char *nomeclasse, *nomeclasseobjeto;
    Objeto *obj;
    u2 index;
    u4 valor = 0;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    obj = (void*)(long) DesempilhaOperando32bits(&(frame->pilhaDeOperandos));

    if(obj != NULL) {
        index = frame->constant_pool[index - 1].info.Class.name_index - 1;
        nomeclasse = dereferencia_instrucao(index, frame->constant_pool);
        nomeclasseobjeto = dereferencia_instrucao(obj->classe->constant_pool[obj->classe->this_class - 1].info.Class.name_index - 1, obj->classe->constant_pool);
        if(!strcmp(nomeclasse, nomeclasseobjeto)) {
            valor = 1;
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
        }
        else {
            EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
        }
    }
    else {
        EmpilhaOperando32bits(&(frame->pilhaDeOperandos),&valor);
    }

    free(nomeclasse);
    free(nomeclasseobjeto);
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
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
            break;
        case 0x37:
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat + 1] = value;
            break;
        case 0x38:
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
            break;
        case 0x39:
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat] = value;
            value = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
            frame->VetorVariaveisLocais[indexConcat + 1] = value;
            break;
        case 0x3a:
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
    u4 valor,referencia;
    int i;
    char *tipo;
    u2 index;
    tArray *a;
    a = (tArray *)malloc(sizeof(tArray));
    index = (u2)(indexbyte1 << 8 | indexbyte2);
    index = ((frame->constant_pool[index - 1].info.Class.name_index) - 1);
    tipo = dereferencia_instrucao(index, frame->constant_pool);
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
    referencia = (int)(long)a;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &referencia);
    free(tipo);
    return;
}

void i_ifnull(Frame *frame, u1 branchbyte1, u1 branchbyte2)
{
    u4 objref = 0;
    objref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if (objref == 0x0){
        int16_t offset = (((u2)branchbyte1)<<8)+branchbyte2;
		frame->pc += offset;
	}

    return;
}

void i_ifnonnull(Frame *frame, u1 branchbyte1, u1 branchbyte2)
{
    u4 objref;
    objref = DesempilhaOperando32bits(&(frame->pilhaDeOperandos));
    if (objref != 0x0){
        int16_t offset = (((u2)branchbyte1)<<8)+branchbyte2;
		frame->pc += offset;
	}

    return;
}

void i_goto_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4)
{
    u4 branchoffset;
    branchoffset = ((u4)branchbyte1 << 24) | ((u4)branchbyte2 << 16) | ((u4)branchbyte3 << 8) | ((u4)branchbyte4);
    frame->pc = frame->pc + branchoffset - 3;
    return;
}

void i_jsr_w(Frame *frame, u1 branchbyte1, u1 branchbyte2, u1 branchbyte3, u1 branchbyte4)
{
    u4 branchoffset, pc;
    branchoffset = ((u4)branchbyte1 << 24) | ((u4)branchbyte2 << 16) | ((u4)branchbyte3 << 8) | ((u4)branchbyte4);
    pc = frame->pc + 5;
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &pc);
    frame->pc = frame->pc + branchoffset - 3;
    return;
}

char* dereferencia_instrucao(u2 index, cp_info *cp)
{
    char *nome;
    int i;

    nome = (char *) malloc((cp[index].info.Utf8.length + 1) * sizeof(char));
    for (i = 0; i < cp[index].info.Utf8.length; i++)
    {
        nome[i] = cp[index].info.Utf8.bytes[i];
    }
    nome[i] = '\0';
    return nome;
}

staticField *recupera_field(char *nome, ListaStaticField **listadefields)
{
    ListaStaticField *lsf1;
    lsf1 = *listadefields;
    while (lsf1 != NULL)
    {
        if (!strcmp(nome, lsf1->dado->NomeClasse))
            return lsf1->dado;
        lsf1 = lsf1->prox;
    }
    return NULL;
}
