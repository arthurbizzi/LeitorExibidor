/**
* @file area_metodos.c
* @author Bruno
* @brief Arquivo que implementa a area de metodos da JVM.
*/

#include "area_metodos.h"
#include "../Instrucoes/bridge_arquivosinstrucoes.h"

void (*instrucao[0xFF])(Frame *frame);

method_info* recupera_main(ClassFile *classe) {
    for(int i = 0; i < classe->methods_count; i++) { // Para cada metodo dentro da classe
        u1 *nome;
        int index_nome = classe->methods[i].name_index - 1;
        index_nome ;
        nome = dereferencia(index_nome, classe);
        if(!strcmp("main", (char *) nome)) { // Se o nome do metodo for main
            return &classe->methods[i];
        }
    }
    return NULL;
}

int executa_metodo(method_info *metodo, ClassFile *classe, PilhaDeFrames *pilha_de_frames) {
    int fim = 0;
    Frame *frame = ConstruirFrame(classe, metodo);

    EmpilhaFrame(&pilha_de_frames, frame);
    DestruirFrame(frame);
    while(!fim) {
        Frame *atual = DesempilhaFrame(&pilha_de_frames); // Recupera frame atual
        fim = executa_instrucoes(metodo, atual);
        if(fim == ERRO_INSTRUCAO) {
            printf("ERRO: instrucao nao pode ser executada.\n");
            DestruirFrame(atual);
            return ERRO_INSTRUCAO;
        }
        if(!fim) {
            EmpilhaFrame(&pilha_de_frames, frame);
        }
        else {
            DestruirFrame(atual);
            fim = 1;
        }
    }

    return SUCESSO;
}

int executa_instrucoes(method_info *metodo, Frame *frame) {
    for(int i = 0; i < metodo->attributes_count; i++) {
        if(metodo->attributes[i].tag == ATTRTAG_Code) {
            attribute_info *codigo = &(metodo->attributes[i]);
            for(int j = 0; j < codigo->info.CodeAttribute.code_length; j++) {
                instrucao[codigo->info.CodeAttribute.code[i]](frame);
            }
            return SUCESSO;
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
	instrucao[0x0a] = i_lconst_1;
	instrucao[0x0b] = i_fconst_0;
	instrucao[0x0c] = i_fconst_1;
	instrucao[0x0d] = i_fconst_2;
	instrucao[0x0e] = i_dconst_0;
	instrucao[0x0f] = i_dconst_1;
	instrucao[0x10] = i_bipush;
	instrucao[0x11] = i_sipush;
	instrucao[0x12] = i_ldc;
	instrucao[0x13] = i_ldc_w;
	instrucao[0x14] = i_ldc2_w;
	instrucao[0x15] = i_iload;
	instrucao[0x16] = i_lload;
	instrucao[0x17] = i_fload;
	instrucao[0x18] = i_dload;
	instrucao[0x19] = i_aload;
	instrucao[0x1a] = i_iload_0;
	instrucao[0x1b] = i_iload_1;
	instrucao[0x1c] = i_iload_2;
	instrucao[0x1d] = i_iload_3;
	instrucao[0x1e] = i_lload_0;
	instrucao[0x1f] = i_lload_1;
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
	instrucao[0x2a] = i_aload_0;
	instrucao[0x2b] = i_aload_1;
	instrucao[0x2c] = i_aload_2;
	instrucao[0x2d] = i_aload_3;
	instrucao[0x2e] = i_iaload;
	instrucao[0x2f] = i_laload;
	instrucao[0x30] = i_faload;
	instrucao[0x31] = i_daload;
	instrucao[0x32] = i_aaload;
	instrucao[0x33] = i_baload;
	instrucao[0x34] = i_caload;
	instrucao[0x35] = i_saload;
	instrucao[0x36] = i_istore;
	instrucao[0x37] = i_lstore;
	instrucao[0x38] = i_fstore;
	instrucao[0x39] = i_dstore;
	instrucao[0x3a] = i_astore;
	instrucao[0x3b] = i_istore_0;
	instrucao[0x3c] = i_istore_1;
	instrucao[0x3d] = i_istore_2;
	instrucao[0x3e] = i_istore_3;
	instrucao[0x3f] = i_lstore_0;
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
	instrucao[0x4a] = i_dstore_3;
	instrucao[0x4b] = i_astore_0;
	instrucao[0x4c] = i_astore_1;
	instrucao[0x4d] = i_astore_2;
	instrucao[0x4e] = i_astore_3;
	instrucao[0x4f] = i_iastore;
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
	instrucao[0x5a] = i_dup2_x1;
	instrucao[0x5b] = i_dup2_x2;
	instrucao[0x5c] = i_dup2;
	instrucao[0x5d] = i_dup2_x1;
	instrucao[0x5e] = i_dup2_x2;
//	instrucao[0x5f] = i_swap;
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
	instrucao[0x6a] = i_fmul;
	instrucao[0x6b] = i_dmul;
	instrucao[0x6c] = i_idiv;
	instrucao[0x6d] = i_ldiv;
	instrucao[0x6e] = i_fdiv;
	instrucao[0x6f] = i_ddiv;
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
	instrucao[0x7a] = i_ishr;
	instrucao[0x7b] = i_lshr;
	instrucao[0x7c] = i_iushr;
	instrucao[0x7d] = i_lushr;
	instrucao[0x7e] = i_iand;
	instrucao[0x7f] = i_land;
	instrucao[0x80] = i_ior;
	instrucao[0x81] = i_lor;
	instrucao[0x82] = i_ixor;
	instrucao[0x83] = i_lxor;
	instrucao[0x84] = i_iinc;
	instrucao[0x85] = i_i2l;
	instrucao[0x86] = i_i2f;
	instrucao[0x87] = i_i2d;
	instrucao[0x88] = i_l2i;
	instrucao[0x89] = i_l2f;
	instrucao[0x8a] = i_l2d;
	instrucao[0x8b] = i_f2i;
	instrucao[0x8c] = i_f2l;
	instrucao[0x8d] = i_f2d;
	instrucao[0x8e] = i_d2i;
	instrucao[0x8f] = i_d2l;
	instrucao[0x90] = i_d2f;
	instrucao[0x91] = i_i2b;
	instrucao[0x92] = i_i2c;
	instrucao[0x93] = i_i2s;
	instrucao[0x94] = i_lcmp;
	instrucao[0x95] = i_fcmpl;
	instrucao[0x96] = i_fcmpg;
	instrucao[0x97] = i_dcmpl;
	instrucao[0x98] = i_dcmpg;
	instrucao[0x99] = i_ifeq;
	instrucao[0x9a] = i_ifne;
	instrucao[0x9b] = i_iflt;
	instrucao[0x9c] = i_ifge;
	instrucao[0x9d] = i_ifgt;
	instrucao[0x9e] = i_ifle;
	instrucao[0x9f] = i_if_icmpeq;
	instrucao[0xa0] = i_if_icmpne;
	instrucao[0xa1] = i_if_icmplt;
	instrucao[0xa2] = i_if_icmpge;
	instrucao[0xa3] = i_if_icmpgt;
	instrucao[0xa4] = i_if_icmple;
	instrucao[0xa5] = i_if_acmpeq;
	instrucao[0xa6] = i_if_acmpne;
	instrucao[0xa7] = i_goto;
	instrucao[0xa8] = i_jsr;
	instrucao[0xa9] = i_ret;
//	instrucao[0xaa] = i_tableswitch;
//	instrucao[0xab] = i_lookupswitch;
//	instrucao[0xac] = i_ireturn;
//	instrucao[0xad] = i_lreturn;
//	instrucao[0xae] = i_freturn;
//	instrucao[0xaf] = i_dreturn;
//	instrucao[0xb0] = i_areturn;
//	instrucao[0xb1] = i_return;
//	instrucao[0xb2] = i_getstatic;
//	instrucao[0xb3] = i_putstatic;
//	instrucao[0xb4] = i_getfield;
//	instrucao[0xb5] = i_putfield;
//	instrucao[0xb6] = i_invokevirtual;
//	instrucao[0xb7] = i_invokespecial;
//	instrucao[0xb8] = i_invokestatic;
	instrucao[0xb9] = i_invokeinterface;
	instrucao[0xbb] = i_new;
	instrucao[0xbc] = i_newarray;
	instrucao[0xbd] = i_anewarray;
//	instrucao[0xbf] = i_athrow;
	instrucao[0xc0] = i_checkcast;
	instrucao[0xc1] = i_instanceof;
	instrucao[0xc2] = i_monitorenter;
	instrucao[0xc3] = i_monitorexit;
	instrucao[0xc4] = i_wide;
	instrucao[0xc5] = i_multianewarray;
	instrucao[0xc6] = i_ifnull;
	instrucao[0xc7] = i_ifnonnull;
	instrucao[0xc8] = i_goto_w;
	instrucao[0xc9] = i_jsr_w;
}
