/**
* @file area_metodos.c
* @author Bruno
* @brief Arquivo que implementa a area de metodos da JVM.
*/

#include "area_metodos.h"
#include "../Instrucoes/bridge_arquivosinstrucoes.h"

void (*instrucao[0xCA])(Frame *frame);
u1 opcode;

method_info* recupera_main(ClassFile *classe) {
    for(int i = 0; i < classe->methods_count; i++) { // Para cada metodo dentro da classe
        u1 *nome;
        int index_nome = classe->methods[i].name_index - 1;
        nome = (u1*) dereferencia(index_nome, classe);
        if(!strcmp("main", (char *) nome)) { // Se o nome do metodo for main
            return &classe->methods[i];
        }
    }
    return NULL;
}

void prepara_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames) {
    for(int i = 0; i < metodo->attributes_count; i++) {
        if(metodo->attributes[i].tag == ATTRTAG_Code) {
            if(metodo->attributes_count > 0) {
                Frame *frame = ConstruirFrame(classe, metodo);
                EmpilhaFrame(&pilha_de_frames, frame);
                DestruirFrame(frame);
                return;
            }
            else {
                metodo->attributes_count++;
                metodo->attributes = (attribute_info *) malloc(sizeof(attribute_info));
                metodo->attributes[0].info.CodeAttribute.code_length = 0;
                Frame *frame = ConstruirFrame(classe, metodo);
                EmpilhaFrame(&pilha_de_frames, frame);
                DestruirFrame(frame);
                return;
            }
        }
    }
    printf("ERRO: Metodo sem ATTRIBUTE CODE.\n");
    return;
}

int executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames) {
    int fim = 0;
    while(!fim) {
        Frame *atual = DesempilhaFrame(&pilha_de_frames); // Recupera frame atual
        fim = executa_instrucoes(metodo, atual);
        if(fim == ERRO_INSTRUCAO) {
            printf("ERRO: instrucao nao pode ser executada.\n");
            DestruirFrame(atual);
            return ERRO_INSTRUCAO;
        }
        if(!fim) {
            EmpilhaFrame(&pilha_de_frames, atual);
        }
        else {
            DestruirFrame(atual);
        }
    }

    return SUCESSO;
}

int executa_instrucoes(method_info *metodo, Frame *frame) {
    for(int i = 0; i < metodo->attributes_count; i++) {
        if(metodo->attributes[i].tag == ATTRTAG_Code) {
            attribute_info *codigo = &(metodo->attributes[i]);
            for(int j = 0; j < codigo->info.CodeAttribute.code_length; j++) {
                opcode = codigo->info.CodeAttribute.code[j];
                instrucao[opcode](frame);
            }
            return 1;
        }
    }
    return ERRO_INSTRUCAO;
}

void carrega_instrucoes() {
	instrucao[0x00] = i_nop;
	instrucao[0x01] = i_aconst_null;
	instrucao[0x02] = i_iconst_m1;
	instrucao[0x03] = i_iconst_0;
	instrucao[0x04] = i_iconst_1;
	instrucao[0x05] = i_iconst_2;
	instrucao[0x06] = i_iconst_3;
	instrucao[0x07] = i_iconst_4;
	instrucao[0x08] = i_iconst_5;
	instrucao[0x09] = i_lconst_0;
	instrucao[0x0A] = i_lconst_1;
	instrucao[0x0B] = i_fconst_0;
	instrucao[0x0C] = i_fconst_1;
	instrucao[0x0D] = i_fconst_2;
	instrucao[0x0E] = i_dconst_0;
	instrucao[0x0F] = i_dconst_1;
	instrucao[0x10] = decodifica_geral;
	instrucao[0x11] = decodifica_geral;
	instrucao[0x12] = decodifica_geral;
	instrucao[0x13] = decodifica_geral;
	instrucao[0x14] = decodifica_geral;
	instrucao[0x15] = decodifica_load;
	instrucao[0x16] = decodifica_load;
	instrucao[0x17] = decodifica_load;
	instrucao[0x18] = decodifica_load;
	instrucao[0x19] = decodifica_load;
	instrucao[0x1A] = i_iload_0;
	instrucao[0x1B] = i_iload_1;
	instrucao[0x1C] = i_iload_2;
	instrucao[0x1D] = i_iload_3;
	instrucao[0x1E] = i_lload_0;
	instrucao[0x1F] = i_lload_1;
	instrucao[0x20] = i_lload_2;
	instrucao[0x21] = i_lload_3;
	instrucao[0x22] = i_fload_0;
	instrucao[0x23] = i_fload_1;
	instrucao[0x24] = i_fload_2;
	instrucao[0x25] = i_fload_3;
	instrucao[0x26] = i_dload_0;
	instrucao[0x27] = i_dload_1;
	instrucao[0x28] = i_dload_2;
	instrucao[0x29] = i_dload_3;
	instrucao[0x2A] = i_aload_0;
	instrucao[0x2B] = i_aload_1;
	instrucao[0x2C] = i_aload_2;
	instrucao[0x2D] = i_aload_3;
	instrucao[0x2E] = i_iaload;
	instrucao[0x2F] = i_laload;
	instrucao[0x30] = i_faload;
	instrucao[0x31] = i_daload;
	instrucao[0x32] = i_aaload;
	instrucao[0x33] = i_baload;
	instrucao[0x34] = i_caload;
	instrucao[0x35] = i_saload;
	instrucao[0x36] = decodifica_store;
	instrucao[0x37] = decodifica_store;
	instrucao[0x38] = decodifica_store;
	instrucao[0x39] = decodifica_store;
	instrucao[0x3A] = decodifica_store;
	instrucao[0x3B] = i_istore_0;
	instrucao[0x3C] = i_istore_1;
	instrucao[0x3D] = i_istore_2;
	instrucao[0x3E] = i_istore_3;
	instrucao[0x3F] = i_lstore_0;
	instrucao[0x40] = i_lstore_1;
	instrucao[0x41] = i_lstore_2;
	instrucao[0x42] = i_lstore_3;
	instrucao[0x43] = i_fstore_0;
	instrucao[0x44] = i_fstore_1;
	instrucao[0x45] = i_fstore_2;
	instrucao[0x46] = i_fstore_3;
	instrucao[0x47] = i_dstore_0;
	instrucao[0x48] = i_dstore_1;
	instrucao[0x49] = i_dstore_2;
	instrucao[0x4A] = i_dstore_3;
	instrucao[0x4B] = i_astore_0;
	instrucao[0x4C] = i_astore_1;
	instrucao[0x4D] = i_astore_2;
	instrucao[0x4E] = i_astore_3;
	instrucao[0x4F] = i_iastore;
	instrucao[0x50] = i_lastore;
	instrucao[0x51] = i_fastore;
	instrucao[0x52] = i_dastore;
	instrucao[0x53] = i_aastore;
	instrucao[0x54] = i_bastore;
	instrucao[0x55] = i_castore;
	instrucao[0x56] = i_sastore;
	instrucao[0x57] = i_pop;
	instrucao[0x58] = i_pop2;
	instrucao[0x59] = i_dup;
	instrucao[0x5A] = i_dup_x1;
	instrucao[0x5B] = i_dup_x2;
//	instrucao[0x5C] = i_dup2; // NAO IMPLEMENTADO
//	instrucao[0x5D] = i_dup2_x1; // NAO IMPLEMENTADO
//	instrucao[0x5E] = i_dup2_x2; // NAO IMPLEMENTADO
	instrucao[0x5F] = i_swap;
	instrucao[0x60] = i_iadd;
	instrucao[0x61] = i_ladd;
	instrucao[0x62] = i_fadd;
	instrucao[0x63] = i_dadd;
	instrucao[0x64] = i_isub;
	instrucao[0x65] = i_lsub;
	instrucao[0x66] = i_fsub;
	instrucao[0x67] = i_dsub;
	instrucao[0x68] = i_imul;
	instrucao[0x69] = i_lmul;
	instrucao[0x6A] = i_fmul;
	instrucao[0x6B] = i_dmul;
	instrucao[0x6C] = i_idiv;
	instrucao[0x6D] = i_ldiv;
	instrucao[0x6E] = i_fdiv;
	instrucao[0x6F] = i_ddiv;
	instrucao[0x70] = i_irem;
	instrucao[0x71] = i_lrem;
	instrucao[0x72] = i_frem;
	instrucao[0x73] = i_drem;
	instrucao[0x74] = i_ineg;
	instrucao[0x75] = i_lneg;
	instrucao[0x76] = i_fneg;
	instrucao[0x77] = i_dneg;
	instrucao[0x78] = i_ishl;
	instrucao[0x79] = i_lshl;
	instrucao[0x7A] = i_ishr;
	instrucao[0x7B] = i_lshr;
	instrucao[0x7C] = i_iushr;
	instrucao[0x7D] = i_lushr;
	instrucao[0x7E] = i_iand;
	instrucao[0x7F] = i_land;
	instrucao[0x80] = i_ior;
	instrucao[0x81] = i_lor;
	instrucao[0x82] = i_ixor;
	instrucao[0x83] = i_lxor;
	instrucao[0x84] = decodifica_geral;
	instrucao[0x85] = i_i2l;
	instrucao[0x86] = i_i2f;
	instrucao[0x87] = i_i2d;
	instrucao[0x88] = i_l2i;
	instrucao[0x89] = i_l2f;
	instrucao[0x8A] = i_l2d;
	instrucao[0x8B] = i_f2i;
	instrucao[0x8C] = i_f2l;
	instrucao[0x8D] = i_f2d;
	instrucao[0x8E] = i_d2i;
	instrucao[0x8F] = i_d2l;
	instrucao[0x90] = i_d2f;
	instrucao[0x91] = i_i2b;
	instrucao[0x92] = i_i2c;
	instrucao[0x93] = i_i2s;
	instrucao[0x94] = i_lcmp;
	instrucao[0x95] = i_fcmpl;
	instrucao[0x96] = i_fcmpg;
	instrucao[0x97] = i_dcmpl;
	instrucao[0x98] = i_dcmpg;
	instrucao[0x99] = decodifica_if;
	instrucao[0x9A] = decodifica_if;
	instrucao[0x9B] = decodifica_if;
	instrucao[0x9C] = decodifica_if;
	instrucao[0x9D] = decodifica_if;
	instrucao[0x9E] = decodifica_if;
	instrucao[0x9F] = decodifica_if;
	instrucao[0xA0] = decodifica_if;
	instrucao[0xA1] = decodifica_if;
	instrucao[0xA2] = decodifica_if;
	instrucao[0xA3] = decodifica_if;
	instrucao[0xA4] = decodifica_if;
	instrucao[0xA5] = decodifica_if;
	instrucao[0xA6] = decodifica_if;
	instrucao[0xA7] = decodifica_geral;
	instrucao[0xA8] = decodifica_geral;
	instrucao[0xA9] = decodifica_geral;
//	instrucao[0xAA] = i_tableswitch; // NAO IMPLEMENTADO
//	instrucao[0xAB] = i_lookupswitch; // NAO IMPLEMENTADO
//	instrucao[0xAC] = i_ireturn; // NAO IMPLEMENTADO
//	instrucao[0xAD] = i_lreturn; // NAO IMPLEMENTADO
//	instrucao[0xAE] = i_freturn; // NAO IMPLEMENTADO
//	instrucao[0xAF] = i_dreturn; // NAO IMPLEMENTADO
//	instrucao[0xB0] = i_areturn; // NAO IMPLEMENTADO
//	instrucao[0xB1] = i_return; // NAO IMPLEMENTADO
//	instrucao[0xB2] = i_getstatic; // NAO IMPLEMENTADO
//	instrucao[0xB3] = i_putstatic; // NAO IMPLEMENTADO
//	instrucao[0xB4] = i_getfield; // NAO IMPLEMENTADO
//	instrucao[0xB5] = i_putfield; // NAO IMPLEMENTADO
//	instrucao[0xB6] = i_invokevirtual; // NAO IMPLEMENTADO
//	instrucao[0xB7] = i_invokespecial; // NAO IMPLEMENTADO
//	instrucao[0xB8] = i_invokestatic; // NAO IMPLEMENTADO
	instrucao[0xB9] = decodifica_geral;
	instrucao[0xBB] = decodifica_geral;
	instrucao[0xBC] = decodifica_geral;
	instrucao[0xBD] = decodifica_geral;
	instrucao[0xBE] = i_arraylength;
	instrucao[0xBF] = i_atrhow;
	instrucao[0xC0] = decodifica_geral;
	instrucao[0xC1] = decodifica_geral;
	instrucao[0xC2] = i_monitorenter;
	instrucao[0xC3] = i_monitorexit;
	instrucao[0xC4] = decodifica_geral;
	instrucao[0xC5] = decodifica_geral;
	instrucao[0xC6] = decodifica_geral;
	instrucao[0xC7] = decodifica_geral;
	instrucao[0xC8] = decodifica_geral;
	instrucao[0xC9] = decodifica_geral;
}

void decodifica_geral(Frame *frame) {
    u4 *nu4 = NULL;
    u2 *nu2 = NULL;
    u1 index = 0, index2 = 0, inc = 0, type = 0, constbyte1 = 0, constbyte2 = 0;
    u1 branch1 = 0, branch2 = 0, branch3 = 0, branch4 = 0, dimensions = 0;
    cp_info *constant_pool = frame->constant_pool;

    switch(opcode) {
        case 0x10:
            i_bipush(frame, nu4);
            break;
        case 0x11:
            i_sipush(frame, nu2);
            break;
        case 0x12:
            i_ldc(frame, index, constant_pool);
            break;
        case 0x13:
            i_ldc_w(frame, index, index2, constant_pool);
            break;
        case 0x14:
            i_ldc2_w(frame, index, index2, constant_pool);
            break;
        case 0x84:
            i_iinc(frame, index, inc);
            break;
        case 0xA7:
            i_goto(frame, index, index2);
            break;
        case 0xA8:
            i_jsr(frame, index, index2);
            break;
        case 0xA9:
            i_ret(frame, index);
            break;
        /*case 0xAA:
            break;
        case 0xAB:
            break;
        case 0xAC:
            break;
        case 0xAD:
            break;
        case 0xAE:
            break;
        case 0xAF:
            break;
        case 0xB0:
            break;
        case 0xB1:
            break;
        case 0xB2:
            break;
        case 0xB3:
            break;
        case 0xB4:
            break;
        case 0xB5:
            break;
        case 0xB6:
            break;
        case 0xB7:
            break;
        case 0xB8:
            break;
        case 0xB9:
            i_invokeinterface(frame, pilha);
            break;
        case 0xBB:
            i_new(frame, index, index2);
            break;*/
        case 0xBC:
            i_newarray(frame, type);
            break;
        case 0xBD:
            i_anewarray(frame, index, index2);
            break;
        case 0xC0:
            i_checkcast(frame, index, index2);
            break;
        case 0xC1:
            i_instanceof(frame, index, index2);
            break;
        case 0xC4:
            i_wide(frame, opcode, index, index2, constbyte1, constbyte2);
            break;
        case 0xC5:
            i_multianewarray(frame, index, index2, dimensions);
            break;
        case 0xC6:
            i_ifnull(frame, branch1, branch2);
            break;
        case 0xC7:
            i_ifnonnull(frame, branch1, branch2);
            break;
        case 0xC8:
            i_goto_w(frame, branch1, branch2, branch3, branch4);
            break;
        case 0xC9:
            i_jsr_w(frame, branch1, branch2, branch3, branch4);
            break;
        default:
            break;
    }
    return;
}

void decodifica_load(Frame *frame) {

}

void decodifica_store(Frame *frame) {

}

void decodifica_if(Frame *frame) {

}
