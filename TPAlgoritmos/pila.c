#include "pila.h"

void crear_pila(t_pila* p)
{
    *p  = NULL;
}

int pila_vacia(const t_pila *p)
{
    return *p == NULL;
}

int pila_llena(const t_pila *p, unsigned tamDato)
{
    return 0;
}


int apilar(t_pila *p, const void *dato, unsigned tamDato)
{
    t_nodo* nuevo_nodo;

    nuevo_nodo = malloc(sizeof(t_nodo));
    if(!nuevo_nodo)
        return SIN_MEMORIA;

    nuevo_nodo->dato = malloc(sizeof(tamDato));
    if(!nuevo_nodo->dato)
    {
        free(nuevo_nodo);
        return SIN_MEMORIA;
    }

    memcpy(nuevo_nodo->dato, dato, tamDato);
    nuevo_nodo->tam = tamDato;

    nuevo_nodo->sig = *p;
    *p = nuevo_nodo;

    return TODO_OK;
}

int desapilar(t_pila *p, void *dato, unsigned tamDato)
{
    t_nodo* elim = *p;

    if(elim == NULL)
        return PILA_VACIA;

    memcpy(dato, elim->dato, MIN(elim->tam,tamDato));

    *p = elim->sig;
    free(elim->dato);
    free(elim);

    return TODO_OK;
}

int ver_tope_pila(const t_pila *p, void *dato, unsigned tamDato)
{
    t_nodo* nodo = *p;

    if(nodo == NULL)
        return PILA_VACIA;

    memcpy(dato, nodo->dato, MIN(nodo->tam,tamDato));
    return TODO_OK;

}

void vaciar_pila(t_pila *p)
{
    t_nodo* elim;

    while(*p != NULL)
    {
        elim = *p;
        *p = elim->sig;

        free(elim->dato);
        free(elim);
    }

}
