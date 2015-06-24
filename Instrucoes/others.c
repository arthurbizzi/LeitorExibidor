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

void i_invokeinterface(Frame *frame, u1 indexbyte1, u1 indexbyte2, u1 contagem, u1 zero)
{

    return;
}

void i_new(Frame *frame, u1 indexbyte1, u1 indexbyte2, ListaClasses *listadeclasses)
{
    Objeto *obj;
    char *tipo;
    u2 index;
    index = (u2)(indexbyte1 << 8) | (u2)(indexbyte2);
    index = frame->constant_pool[index - 1].info.Class.name_index - 1;
    tipo = i_dereferencia_instrucoes(index, frame->constant_pool);
    obj = (Objeto *)malloc(sizeof(Objeto));
    obj->classe = i_RecuperaClasse(tipo,&listadeclasses);
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
    EmpilhaOperando32bits(&(frame->pilhaDeOperandos), &(a->tamanho));
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
    u4 valor = 1;
    int i;
    char *tipo;
    u2 index;
    tArray *a;
    a = (tArray *)malloc(sizeof(tArray));
    index = (u2)(indexbyte1 << 8 | indexbyte2);
    index = ((frame->constant_pool[index - 1].info.Class.name_index) - 1);
    tipo = i_dereferencia_instrucoes(index, frame->constant_pool);
    for (i = 0; i < dimensions; i++)
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
    int i;
    nome = (char *) malloc((cp[index].info.Utf8.length + 1) * sizeof(char));
    for (i = 0; i < cp[index].info.Utf8.length; i++)
    {
        nome[i] = cp[index].info.Utf8.bytes[i];
    }
    nome[i] = '\0';
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
