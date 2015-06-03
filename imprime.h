/**
* @file imprime.h
* @author Bruno, Guilherme, Kelvin
* @brief Arquivo com as definicoes de funcoes relacionadas a impressao do conteudo da classe em tela e em arquivo.
*/

#ifndef LEITOREXIBIDOR_IMPRIME_H
#define LEITOREXIBIDOR_IMPRIME_H

#include "main.h"

/* Protótipos */
// Imprime Stdout
/**
*   @fn void imprime_general_information(ClassFile *classe)
*   @brief Funcao que imprime informacao geral (Versao, CP Count, entre outros) na tela.
*   @param classe Estrutura que contem a informacao da classe.
*/
void imprime_general_information(ClassFile *classe);

/**
*   @fn void imprime_constant_pool(ClassFile *classe)
*   @brief Funcao que imprime o pool de constantes na tela.
*   @param classe Estrutura que contem a informacao da classe.
*/
void imprime_constant_pool(ClassFile *classe);

/**
*   @fn void imprime_attributes(ClassFile *classe)
*   @brief Funcao que imprime os atributos na tela.
*   @param classe Estrutura que contem a informacao da classe.
*/
void imprime_attributes(ClassFile *classe);

/**
*   @fn void imprime_methods(ClassFile *classe)
*   @brief Funcao que imprime os metodos na tela.
*   @param classe Estrutura que contem a informacao da classe.
*/
void imprime_methods(ClassFile *classe);

/**
*   @fn void imprime_attribute(ClassFile *classe)
*   @brief Funcao que imprime um unico atributo na tela.
*   @param attributeInfo Estrutura que contem O atributo a ser impresso.
*   @param classe Estrutura que contem a informacao da classe.
*/
void imprime_attribute(attribute_info *attributeInfo, ClassFile *classe);

/**
*   @fn void imprime_fields(ClassFile *classe)
*   @brief Funcao que imprime os campos na tela.
*   @param classe Estrutura que contem a informacao da classe.
*/
void imprime_fields(ClassFile *classe);

// Imprime para arquivo
/**
*   @fn void imprime_general_information_file(ClassFile *classe, FILE *file)
*   @brief Funcao que imprime informacao geral (Versao, CP Count, entre outros) no arquivo.
*   @param classe Estrutura que contem a informacao da classe.
*   @param file Arquivo de destino da impressao.
*/
void imprime_general_information_file(ClassFile *classe, FILE *file);

/**
*   @fn void imprime_constant_pool_file(ClassFile *classe, FILE *file)
*   @brief Funcao que imprime o pool de constantes no arquivo.
*   @param classe Estrutura que contem a informacao da classe.
*   @param file Arquivo de destino da impressao.
*/
void imprime_constant_pool_file(ClassFile *classe, FILE *file);

/**
*   @fn void imprime_attributes_file(ClassFile *classe, FILE *file)
*   @brief Funcao que imprime os atributos no arquivo.
*   @param classe Estrutura que contem a informacao da classe.
*   @param file Arquivo de destino da impressao.
*/
void imprime_attributes_file(ClassFile *classe, FILE *file);

/**
*   @fn void imprime_methods_file(ClassFile *classe, FILE *file)
*   @brief Funcao que imprime os metodos no arquivo.
*   @param classe Estrutura que contem a informacao da classe.
*   @param file Arquivo de destino da impressao.
*/
void imprime_methods_file(ClassFile *classe, FILE *file);

/**
*   @fn void imprime_attribute_file(ClassFile *classe)
*   @brief Funcao que imprime um unico atributo no arquivo.
*   @param attributeInfo Estrutura que contem O atributo a ser impresso.
*   @param classe Estrutura que contem a informacao da classe.
*   @param file Arquivo de destino da impressao.
*/
void imprime_attribute_file(attribute_info *attributeInfo, ClassFile *classe, FILE *file);

/**
*   @fn void imprime_fields_file(ClassFile *classe, FILE *file)
*   @brief Funcao que imprime os campos no arquivo.
*   @param classe Estrutura que contem a informacao da classe.
*   @param file Arquivo de destino da impressao.
*/
void imprime_fields_file(ClassFile *classe, FILE *file);

// Outros
/**
*   @fn void carrega_instrucoes(Instrucao *mapa)
*   @brief Funcao que organiza um mapa com mnemonicos e argumentos de instrucoes.
*   @param mapa Referencia do mapa que sera preenchido.
*/
void carrega_instrucoes(Instrucao *mapa);

#endif // LEITOREXIBIDOR_IMPRIME_H
