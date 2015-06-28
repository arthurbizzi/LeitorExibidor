/**
* @file heap.c
* @author Bruno, Guilherme
* @brief
*/

#include "heap.h"

void InicializaListaDeArrays(ListaArrays **listadearrays)
{
    *listadearrays = NULL;
    return;
}

void InsereListaDeArrays(ListaArrays **listadearrays, tArray *dado)
{
    ListaArrays *la1;
    la1 = (ListaArrays *)malloc(sizeof(ListaArrays));
    la1->dado = dado;
    la1->prox = *listadearrays;
    *listadearrays = la1;
    return;
}

void desalocaListaDeArrays(ListaArrays **listadearrays)
{
    ListaArrays *la1;
    while (*listadearrays != NULL)
    {
        free((*listadearrays)->dado);
        la1 = *listadearrays;
        *listadearrays = la1->prox;
        free(la1);
    }
    return;
}

void InicializaListaDeObjetos(ListaObjetos **listadeobjetos)
{
    *listadeobjetos = NULL;
    return;
}

void InsereListaDeObjetos(ListaObjetos **listadeobjetos, Objeto *dado)
{
    ListaObjetos *lo1;
    lo1 = (ListaObjetos *)malloc(sizeof(ListaObjetos));
    lo1->dado = dado;
    lo1->prox = *listadeobjetos;
    *listadeobjetos = lo1;
    return;
}

void desalocaListaDeObjetos(ListaObjetos **listadeobjetos)
{
    ListaObjetos *lo1;
    while (*listadeobjetos != NULL)
    {
        free((*listadeobjetos)->dado);
        lo1 = *listadeobjetos;
        *listadeobjetos = lo1->prox;
        free(lo1);
    }
    return;
}

void InicializaListaDeClasses(ListaClasses **listadeclasses)
{
    *listadeclasses = NULL;
    return;
}

void InsereListaDeClasses(ListaClasses **listadeclasses, ClassFile *dado)
{
    ListaClasses *lc1;
    lc1 = (ListaClasses *)malloc(sizeof(ListaClasses));
    lc1->dado = dado;
    lc1->prox = *listadeclasses;
    *listadeclasses = lc1;
    return;
}

void desalocaListaDeClasses(ListaClasses **listadeclasses)
{
    ListaClasses *lc1;
    while (*listadeclasses != NULL)
    {
        free((*listadeclasses)->dado);
        lc1 = *listadeclasses;
        *listadeclasses = lc1->prox;
        free(lc1);
    }
    return;
}

void InicializaListaDeFields(ListaStaticField **listadefields)
{
    *listadefields = NULL;
    return;
}

void InsereListaDeFields(ListaStaticField **listadefields, staticField *dado)
{
    ListaStaticField *lsf1;
    lsf1 = (ListaStaticField *)malloc(sizeof(ListaStaticField));
    lsf1->dado = dado;
    lsf1->prox = *listadefields;
    *listadefields = lsf1;
    return;
}

void desalocaListaDeFields(ListaStaticField **listadefields)
{
    ListaStaticField *lsf1;
    while (*listadefields != NULL)
    {
        free((*listadefields)->dado);
        lsf1 = *listadefields;
        *listadefields = lsf1->prox;
        free(lsf1);
    }
    return;
}

u1 ClasseCarregada(ListaClasses **listadeclasses, char *nomedaclasse)
{
    ListaClasses *lc1;
    int index;
    char *nomeThisClass;
    lc1 = *listadeclasses;
    while (lc1 != NULL)
    {
        index = lc1->dado->constant_pool[lc1->dado->this_class - 1].info.Class.name_index - 1;
        nomeThisClass = dereferencia(index, lc1->dado);
        if (!strcmp(nomedaclasse,nomeThisClass))
            return 1;
        lc1 = lc1->prox;
    }
    return 0;
}

ClassFile *RecuperaIesimaClasse(int index, ListaClasses **listadeclasses)
{
    ListaClasses *lc1;

    lc1 = *listadeclasses;
    for(int i = 0; i < index + 1; i++)
    {
        if(i == index)
        {
            return lc1->dado;
        }
        lc1 = lc1->prox;
    }
    return NULL;
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
