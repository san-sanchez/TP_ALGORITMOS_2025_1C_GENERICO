#include "lista.h"


void crearLista(tLista* lista)
{
    *lista = NULL;
}

int listaVacia(const tLista* lista)
{
    return *lista == NULL;
}

int listaLlena(const tLista* lista)
{
    return 0;
}
int agregarALista(tLista* lista, void* dato, unsigned tamDato)
{
    tNodo* nuevoNodo;

    nuevoNodo = malloc(sizeof(tNodo));
    if(!nuevoNodo)
        return SIN_ESPACIO;

    nuevoNodo->dato = malloc(tamDato);
    if(!nuevoNodo->dato)
    {
        free(nuevoNodo);
        return SIN_ESPACIO;
    }

    memcpy(nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tam = tamDato;
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;

    return TODO_OK;
}

int eliminarDeLista(tLista* lista, void* dato, unsigned tamDato)
{
    tNodo* elim = *lista;

    if(elim == NULL)
        return LISTA_VACIA;

    memcpy(dato, elim->dato, MIN(tamDato, elim->tam));
    *lista = elim->sig;
    free(elim->dato);
    free(elim);
    return TODO_OK;
}


int sacarDeListaPosicion(tLista* lista, void* dato, unsigned tamDato,int posicion)
{
    int i;

    if(*lista == NULL)
        return LISTA_VACIA;

    for(i=0; i < posicion; i++)
        lista = &(*lista)->sig;

    tNodo* sacar = *lista;

    memcpy(dato, sacar->dato, MIN(tamDato, sacar->tam));
    *lista = sacar->sig;
    free(sacar->dato);
    free(sacar);
    return TODO_OK;
}

int sacarDeListaClave(tLista* pLista,void* dato, unsigned tamDato,const void* clave, tCMP cmp)
{

    tNodo* elim;
    if(! *pLista)
        return LISTA_VACIA;

    while(*pLista != NULL &&  cmp(clave,(*pLista)->dato) != 0)
    {
        pLista = &(*pLista)->sig;
    }
    if(*pLista == NULL)
        return LISTA_VACIA;

    elim = *pLista;
    *pLista = elim->sig;
    memcpy(dato,elim->dato,tamDato);

    free(elim->dato);
    free(elim);


    return TODO_OK;
}


void vaciarLista(tLista* lista)
{
    tNodo* elim;
    while(*lista != NULL)
    {
        elim = *lista;
        *lista = elim->sig;
        free(elim->dato);
        free(elim);
    }
    return;
}

int mapLista(tLista* lista, tACCION accion)
{
    int cont = 0;
    while(*lista != NULL)
    {
        accion((*lista)->dato);
        lista = &(*lista)->sig;
        cont++;
    }
    return cont;
}

int insertarOrdenado(tLista* lista, void* dato, unsigned tamDato, int comp(const void*, const void*))
{
    tNodo* nuevoNodo;


    while(*lista != NULL && comp((*lista)->dato, dato) < 0)
        lista = &(*lista)->sig;


    nuevoNodo = malloc(sizeof(tNodo));
    if(!nuevoNodo)
        return SIN_ESPACIO;

    nuevoNodo->dato = malloc(tamDato);
    if(!nuevoNodo->dato)
    {
        free(nuevoNodo);
        return SIN_ESPACIO;
    }

    memcpy(nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tam = tamDato;
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;

    return TODO_OK;
}

int insertarOrdenadoSinDupli(tLista* lista, void* dato, unsigned tamDato, int comp(const void*, const void*))
{
    tNodo* nuevoNodo;
    int cmp = 0;


    while(*lista != NULL && (cmp = comp((*lista)->dato, dato)) < 0)
        lista = &(*lista)->sig;

    if(cmp == 0)
        return DUPLICADO;


    nuevoNodo = malloc(sizeof(tNodo));
    if(!nuevoNodo)
        return SIN_ESPACIO;

    nuevoNodo->dato = malloc(tamDato);
    if(!nuevoNodo->dato)
    {
        free(nuevoNodo);
        return SIN_ESPACIO;
    }

    memcpy(nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tam = tamDato;
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;

    return TODO_OK;
}

//void ordenarLista(tLista* lista, int (comparar)(const void*, const void*, unsigned))
//{
//
//    tLista nuevaLista = NULL;
//    tNodo actual = *lista;
//
//    while (actual != NULL)
//    {
//        tNodo* menorNodo = actual;
//        tNodo* nodoAnteriorMenor = NULL;
//        tNodo* temp = actual->sig;
//        tNodo* nodoAnteriorTemp = actual;
//
//        // Buscar el nodo con el menor dato en la parte no ordenada de la lista
//        while (temp != NULL)
//        {
//            if (comparar(temp->dato, menorNodo->dato, menorNodo->tam) < 0)
//            {
//                menorNodo = temp;
//                nodoAnteriorMenor = nodoAnteriorTemp;
//            }
//            nodoAnteriorTemp = temp;
//            temp = temp->sig;
//        }
//
//        // Desconectar el nodo menor de su posición actual
//        if (nodoAnteriorMenor == NULL)
//        {
//            // El menor nodo es el primero de la parte no ordenada
//            actual = menorNodo->sig;
//        }
//        else
//        {
//            nodoAnteriorMenor->sig = menorNodo->sig;
//        }
//
//        // Insertar el nodo menor al principio de la nueva lista ordenada
//        menorNodo->sig = nuevaLista;
//        nuevaLista = menorNodo;
//    }
//
//    // Actualizar la lista original para que apunte a la nueva lista ordenada
//    *lista = nuevaLista;
//}

void ordenarLista(tLista* lista, int comp(const void*, const void*))
{
    int ordenado;
    tNodo** nodo;
    tNodo* aux;

    do
    {
        ordenado = 0;
        nodo = lista;

        while(*nodo && (*nodo)->sig)
        {
            if(comp((*nodo)->dato, (*nodo)->sig->dato) > 0)
            {
                // NODO -> B -> A -> C
                aux = (*nodo)->sig; // AUX = A
                (*nodo)->sig = aux->sig; // B -> C
                aux->sig = *nodo; // A -> B
                *nodo = aux; // NODO -> A
                // NODO -> A -> B -> C

                ordenado = 1;
            }
            nodo = &(*nodo)->sig;
        }
    }
    while(ordenado);
}




void crearPila(tPila* p)
{
    *p  = NULL;
}

int pilaVacia(const tPila *p)
{
    return *p == NULL;
}

int pilaLlena(const tPila *p, unsigned tamDato)
{
    return 0;
}


int apilar(tPila *p, const void *dato, unsigned tamDato)
{
    tNodo* nuevoNodo;

    nuevoNodo = malloc(sizeof(tNodo));
    if(!nuevoNodo)
        return SIN_MEMORIA;

    nuevoNodo->dato = malloc(sizeof(tamDato));
    if(!nuevoNodo->dato)
    {
        free(nuevoNodo);
        return SIN_MEMORIA;
    }

    memcpy(nuevoNodo->dato, dato, tamDato);
    nuevoNodo->tam = tamDato;

    nuevoNodo->sig = *p;
    *p = nuevoNodo;

    return TODO_OK;
}

int desapilar(tPila *p, void *dato, unsigned tamDato)
{
    tNodo* elim = *p;

    if(elim == NULL)
        return PILA_VACIA;

    memcpy(dato, elim->dato, MIN(elim->tam,tamDato));

    *p = elim->sig;
    free(elim->dato);
    free(elim);

    return TODO_OK;
}

int verTopePila(const tPila *p, void *dato, unsigned tamDato)
{
    tNodo* nodo = *p;

    if(nodo == NULL)
        return PILA_VACIA;

    memcpy(dato, nodo->dato, MIN(nodo->tam,tamDato));
    return TODO_OK;

}

void vaciarPila(tPila *p)
{
    tNodo* elim;

    while(*p != NULL)
    {
        elim = *p;
        *p = elim->sig;

        free(elim->dato);
        free(elim);
    }

}



