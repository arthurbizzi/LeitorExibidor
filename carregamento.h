/**
* @file carregamento.h
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo com as definicoes de funcoes relacionadas ao carregamento do conteudo da classe de um arquivo.
*/

#ifndef LEITOREXIBIDOR_CARREGAMENTO_H
#define LEITOREXIBIDOR_CARREGAMENTO_H

#include <stdio.h>
#include "main.h"

/* Protótipos */
/**
*   @fn u1 le_u1(FILE *arquivo)
*   @brief Funcao que le um u1 de um arquivo. u1 e um tipo definido como uint8_t, com 8 bits.
*   @param arquivo Ponteiro para arquivo de onde deve ser lido.
*   @return Retorna o u1 lido.
*/
u1 le_u1(FILE *arquivo);

/**
*   @fn u2 le_u2(FILE *arquivo)
*   @brief Funcao que le um u2 de um arquivo. u2 e um tipo definido como uint16_t, com 16 bits.
*   @param arquivo Ponteiro para arquivo de onde deve ser lido.
*   @return Retorna o u1 lido.
*/
u2 le_u2(FILE *arquivo);

/**
*   @fn u4 le_u4(FILE *arquivo)
*   @brief Funcao que le um u4 de um arquivo. u4 e um tipo definido como uint32_t, com 32 bits.
*   @param arquivo Ponteiro para arquivo de onde deve ser lido.
*   @return Retorna o u4 lido.
*/
u4 le_u4(FILE *arquivo);

/**
*   @fn int carrega_header(FILE *arquivo, ClassFile *classe)
*   @brief Funcao que carrega magic number e versao de uma classe.
*   @param arquivo Ponteiro para arquivo onde a classe esta.
*   @param classe Estrutura que contera a informacao da classe.
*   @return Retorna o status de execucao: SUCESSO, ERRO_MAGIC ou ERRO_VERSION.
*/
int carrega_header(FILE *arquivo, ClassFile *classe);

/**
*   @fn int carrega_constantpool(FILE *arquivo, ClassFile *classe)
*   @brief Funcao que carrega o pool de constantes de uma classe.
*   @param arquivo Ponteiro para arquivo onde a classe esta.
*   @param classe Estrutura que contera a informacao da classe.
*/
void carrega_constantpool(FILE *arquivo, ClassFile *classe);

/**
*   @fn int carrega_flagseclasses(FILE *arquivo, ClassFile *classe)
*   @brief Funcao que carrega flags e classes de uma classe.
*   @param arquivo Ponteiro para arquivo onde a classe esta.
*   @param classe Estrutura que contera a informacao da classe.
*/
void carrega_flagseclasses(FILE *arquivo, ClassFile *classe);

/**
*   @fn int carrega_interfaces(FILE *arquivo, ClassFile *classe)
*   @brief Funcao que carrega as interfaces de uma classe.
*   @param arquivo Ponteiro para arquivo onde a classe esta.
*   @param classe Estrutura que contera a informacao da classe.
*/
void carrega_interfaces(FILE *arquivo, ClassFile *classe);

/**
*   @fn int carrega_fields(FILE *arquivo, ClassFile *classe)
*   @brief Funcao que carrega os fields de uma classe.
*   @param arquivo Ponteiro para arquivo onde a classe esta.
*   @param classe Estrutura que contera a informacao da classe.
*/
void carrega_fields(FILE *arquivo, ClassFile *classe);

/**
*   @fn int carrega_methods(FILE *arquivo, ClassFile *classe)
*   @brief Funcao que carrega os metodos de uma classe.
*   @param arquivo Ponteiro para arquivo onde a classe esta.
*   @param classe Estrutura que contera a informacao da classe.
*/
void carrega_methods(FILE *arquivo, ClassFile *classe);

/**
*   @fn int carrega_attributes(FILE *arquivo, ClassFile *classe)
*   @brief Funcao que carrega os atributos de uma classe.
*   @param arquivo Ponteiro para arquivo onde a classe esta.
*   @param classe Estrutura que contera a informacao da classe.
*/
void carrega_attributes(FILE *arquivo, ClassFile *classe);

/**
*   @fn int carrega_attribute(FILE *arquivo, ClassFile *classe, attribute_info *atributo)
*   @brief Funcao que carrega um unico atributo de uma classe.
*   @param arquivo Ponteiro para arquivo onde a classe esta.
*   @param classe Estrutura que contera a informacao da classe.
*   @param atributo Estrutura que contem um atributo a ser carregado.
*/
void carrega_attribute(FILE *arquivo, ClassFile *classe, attribute_info *atributo);

#endif // LEITOREXIBIDOR_CARREGAMENTO_H
