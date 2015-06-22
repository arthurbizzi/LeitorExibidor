/**
* @file lista_arrays_objetos_classes.h
* @author Guilherme
* @brief
*/

#ifndef LISTA_ARRAYS_OBJETOS_CLASSES_H
#define LISTA_ARRAYS_OBJETOS_CLASSES_H

#include "ClassLoader/classloader.h"
#include "ClassLoader/carregamento.h"

typedef struct tipoarray
{
    u1 tag;
    u4 tamanho;
    union
    {
        u1 *tipoBoolean;
        u1 *tipoByte;
        u2 *tipoChar;
        u2 *tipoShort;
        u4 *tipoReferencia;
        u4 *tipoInt;
        u4 *tipoFloat;
        u8 *tipoLong;
        u8 *tipoDouble;
    } info;
} tArray;

typedef struct listadearrays
{
    tArray                  *dado;
    struct listadearrays    *prox;
} ListaArrays;

typedef struct tipofield
{
    u1 tag;
    union
    {
        u1 tipoBoolean;
        u1 tipoByte;
        u2 tipoShort;
        u4 tipoInt;
        u4 tipoFloat;
        u8 tipoLong;
        u8 tipoDouble;
    } info;
    field_info *field;
    ClassFile  *classe;
} Field;

typedef struct tipoobjeto
{
    ClassFile   *classe;
    u2          tamanhotipoField;
    Field       *tipofield;
    u2          tamanhotipoArray;
    tArray      *tipoarray;
} Objeto;

typedef struct listadeobjetos
{
    Objeto                  *dado;
    struct listadeobjetos   *prox;
} ListaObjetos;

typedef struct listadeclasses
{
    ClassFile               *dado;
    struct listadeclasses   *prox;
} ListaClasses;

/**
*   @fn void InicializaListaDeArrays(ListaArrays **listadearrays)
*   @brief
*   @param listadearrays
*/
void InicializaListaDeArrays(ListaArrays **listadearrays);

/**
*   @fn void InsereListaDeArrays(ListaArrays **listadearrays, tArray *dado)
*   @brief
*   @param listadearrays
*   @param dado
*/
void InsereListaDeArrays(ListaArrays **listadearrays, tArray *dado);

/**
*   @fn void desalocaListaDeArrays(ListaArrays **listadearrays)
*   @brief
*   @param listadearrays
*/
void desalocaListaDeArrays(ListaArrays **listadearrays);

/**
*   @fn void InicializaListaDeObjetos(ListaObjetos **listadeobjetos)
*   @brief
*   @param listadeobjetos
*/
void InicializaListaDeObjetos(ListaObjetos **listadeobjetos);

/**
*   @fn void InsereListaDeObjetos(ListaObjetos **listadeobjetos, Objeto *dado)
*   @brief
*   @param listadeobjetos
*   @param dado
*/
void InsereListaDeObjetos(ListaObjetos **listadeobjetos, Objeto *dado);

/**
*   @fn void desalocaListaDeObjetos(ListaObjetos **listadeobjetos)
*   @brief
*   @param listadeobjetos
*/
void desalocaListaDeObjetos(ListaObjetos **listadeobjetos);

/**
*   @fn void InicializaListaDeClasses(ListaClasses **listadeclasses)
*   @brief
*   @param listadeclasses
*/
void InicializaListaDeClasses(ListaClasses **listadeclasses);

/**
*   @fn void InsereListaDeClasses(ListaClasses **listadeclasses, ClassFile *dado)
*   @brief
*   @param listadeclasses
*   @param dado
*/
void InsereListaDeClasses(ListaClasses **listadeclasses, ClassFile *dado);

/**
*   @fn void desalocaListaDeClasses(ListaClasses **listadeclasses)
*   @brief
*   @param listadeclasses
*/
void desalocaListaDeClasses(ListaClasses **listadeclasses);

/**
*   @fn u1 ClasseCarregada(ListaClasses **listadeclasses, char *nomedaclasse)
*   @brief
*   @param listadeclasses
*   @param nomedaclasse
*   @return
*/
u1 ClasseCarregada(ListaClasses **listadeclasses, char *nomedaclasse);

/**
*   @fn u1 ClasseCarregada(ListaClasses **listadeclasses, char *nomedaclasse)
*   @brief Funcao que recebe um indice e procura na lista de classes a classe correspondente a esse indice.
*   @param index Indice da lista a ser recuperado.
*   @param listadeclasses Lista que contem as classes carregadas.
*   @return Retorna a i-esima classe da lista.
*/
ClassFile *RecuperaIesimaClasse(int index, ListaClasses **listadeclasses);

#endif // LISTA_ARRAYS_OBJETOS_CLASSES_H
