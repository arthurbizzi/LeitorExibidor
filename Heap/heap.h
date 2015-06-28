/**
* @file heap.h
* @author Bruno, Guilherme
* @brief
*/

#include "../ClassLoader/classloader.h"
#include "../ClassLoader/carregamento.h"

#ifndef HEAP_H
#define HEAP_H


typedef struct tipoarray
{
    u1 tag;
    u4 tamanho;
    u4 tamanho1;
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

typedef struct tipoobjeto
{
    ClassFile   *classe;
    u2          tamanhotipoField;
    u8          *tipofield;
} Objeto;

typedef struct
{
	char    *NomeClasse;
	u2      fieldCount;
	u8      *valor;
} staticField;

typedef struct listastaticfield
{
	staticField             *dado;
	struct listastaticfield *prox;
} ListaStaticField;

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

void InicializaListaDeFields(ListaStaticField **listadefields);
void InsereListaDeFields(ListaStaticField **listadefields, staticField *dado);
void desalocaListaDeFields(ListaStaticField **listadefields);

/**
*   @fn u1 ClasseCarregada(ListaClasses **listadeclasses, char *nomedaclasse)
*   @brief
*   @param listadeclasses
*   @param nomedaclasse
*   @return
*/
u1 ClasseCarregada(ListaClasses **listadeclasses, char *nomedaclasse);

/**
*   @fn ClassFile *RecuperaIesimaClasse(int index, ListaClasses **listadeclasses)
*   @brief Funcao que recebe um indice e procura na lista de classes a classe correspondente a esse indice.
*   @param index Indice da lista a ser recuperado.
*   @param listadeclasses Lista que contem as classes carregadas.
*   @return I-esima classe da lista.
*/
ClassFile *RecuperaIesimaClasse(int index, ListaClasses **listadeclasses);

/**
*   @fn ClassFile *RecuperaClassePorNome(char *nome, ListaClasses **listadeclasses)
*   @brief Funcao que recebe um indice e procura na lista de classes a classe correspondente a esse indice.
*   @param nome Nome da classe a ser recuperada.
*   @param listadeclasses Lista que contem as classes carregadas.
*   @return Classe com o nome correspondente.
*/
ClassFile *RecuperaClassePorNome(char *nome, ListaClasses **listadeclasses);

#endif // HEAP_H
