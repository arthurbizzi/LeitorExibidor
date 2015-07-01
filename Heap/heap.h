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

typedef struct heap
{
    struct listadearrays    *listaDeArrays;
    struct listastaticfield *listaStaticField;
    struct listadeobjetos   *listaDeObjetos;
    struct listadeclasses   *listaDeClasses;
    struct pilhadeframes    *pilhaDeFrames;
} Heap;

/**
*   @fn void InicializaListaDeArrays(ListaArrays **listadearrays)
*   @brief Funcao que inicializa a lista de arrays carregados na heap.
*   @param listadearrays Estrutura que contera a lista de arrays.
*/
void InicializaListaDeArrays(ListaArrays **listadearrays);

/**
*   @fn void InsereListaDeArrays(ListaArrays **listadearrays, tArray *dado)
*   @brief Funcao que insere um elemento na lista de arrays.
*   @param listadearrays Lista que recebera o elemento.
*   @param dado Dado a ser inserido.
*/
void InsereListaDeArrays(ListaArrays **listadearrays, tArray *dado);

/**
*   @fn void desalocaListaDeArrays(ListaArrays **listadearrays)
*   @brief Funcao que desaloca completamente uma lista de arrays.
*   @param listadearrays Lista a ser destruida.
*/
void desalocaListaDeArrays(ListaArrays **listadearrays);

/**
*   @fn void InicializaListaDeObjetos(ListaObjetos **listadeobjetos)
*   @brief Funcao que inicializa a lista de objetos carregados na heap.
*   @param listadeobjetos Estrutura que contera a lista de objetos.
*/
void InicializaListaDeObjetos(ListaObjetos **listadeobjetos);

/**
*   @fn void InsereListaDeObjetos(ListaObjetos **listadeobjetos, Objeto *dado)
*   @brief Funcao que insere um elemento na lista de objetos.
*   @param listadeobjetos Lista que recebera o elemento.
*   @param dado Dado a ser inserido.
*/
void InsereListaDeObjetos(ListaObjetos **listadeobjetos, Objeto *dado);

/**
*   @fn void desalocaListaDeObjetos(ListaObjetos **listadeobjetos)
*   @brief Funcao que desaloca completamente uma lista de objetos.
*   @param listadeobjetos Lista a ser destruida.
*/
void desalocaListaDeObjetos(ListaObjetos **listadeobjetos);

/**
*   @fn void InicializaListaDeClasses(ListaClasses **listadeclasses)
*   @brief Funcao que inicializa a lista de classes carregados na heap.
*   @param listadeclasses Estrutura que contera a lista de classes.
*/
void InicializaListaDeClasses(ListaClasses **listadeclasses);

/**
*   @fn void InsereListaDeClasses(ListaClasses **listadeclasses, ClassFile *dado)
*   @brief Funcao que insere um elemento na lista de classes.
*   @param listadeclasses Lista que recebera o elemento.
*   @param dado Dado a ser inserido.
*/
void InsereListaDeClasses(ListaClasses **listadeclasses, ClassFile *dado);

/**
*   @fn void desalocaListaDeClasses(ListaClasses **listadeclasses)
*   @brief Funcao que desaloca completamente uma lista de classes.
*   @param listadeclasses Lista a ser destruida.
*/
void desalocaListaDeClasses(ListaClasses *listadeclasses);

/**
*   @fn void InicializaListaDeFields(ListaStaticField **listadefields)
*   @brief Funcao que inicializa a lista de fields carregados na heap.
*   @param listadefields Estrutura que contera a lista de fields.
*/
void InicializaListaDeFields(ListaStaticField *listadefields);

/**
*   @fn void InsereListaDeFields(ListaStaticField **listadefields, staticField *dado)
*   @brief Funcao que insere um elemento na lista de fields.
*   @param listadefields Lista que recebera o elemento.
*   @param dado Dado a ser inserido.
*/
void InsereListaDeFields(ListaStaticField **listadefields, staticField *dado);

/**
*   @fn void desalocaListaDeFields(ListaStaticField **listadefields)
*   @brief Funcao que desaloca completamente uma lista de fields.
*   @param listadefields Lista a ser destruida.
*/
void desalocaListaDeFields(ListaStaticField *listadefields);

/**
*   @fn u1 ClasseCarregada(ListaClasses **listadeclasses, char *nomedaclasse)
*   @brief Funcao que verifica se uma classe esta carregada numa lista de classes.
*   @param listadeclasses Lista de classes carregadas.
*   @param nomedaclasse Classe a ser procurada.
*   @return 1, se estiver carregada, 0, caso contrario.
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
ClassFile *i_RecuperaClasse(char *nome, ListaClasses **listadeclasses);

void InicializaHeap(Heap *heap, ListaArrays *listaArrays, ListaStaticField *listaStaticField, ListaClasses *listaClasses, ListaObjetos *listaObjetos);

void desalocaHeap(Heap *heap);

#endif // HEAP_H
