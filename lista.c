#include "lista.h"


void crear_lista(t_lista* lista)
{
    *lista = NULL;
}

int lista_vacia(const t_lista* lista)
{
    return *lista == NULL;
}

int lista_llena(const t_lista* lista)
{
    return 0;
}
int agregar_a_lista(t_lista* lista, void* dato, unsigned tam_dato)
{
    t_nodo* nuevo_nodo;

    nuevo_nodo = malloc(sizeof(t_nodo));
    if(!nuevo_nodo)
        return SIN_ESPACIO;

    nuevo_nodo->dato = malloc(tam_dato);
    if(!nuevo_nodo->dato)
    {
        free(nuevo_nodo);
        return SIN_ESPACIO;
    }

    memcpy(nuevo_nodo->dato, dato, tam_dato);
    nuevo_nodo->tam = tam_dato;
    nuevo_nodo->sig = *lista;
    *lista = nuevo_nodo;

    return TODO_OK;
}

int eliminar_de_lista(t_lista* lista, void* dato, unsigned tam_dato)
{
    t_nodo* elim = *lista;

    if(elim == NULL)
        return LISTA_VACIA;

    memcpy(dato, elim->dato, MIN(tam_dato, elim->tam));
    *lista = elim->sig;
    free(elim->dato);
    free(elim);
    return TODO_OK;
}


int sacar_de_lista_posicion(t_lista* lista, void* dato, unsigned tam_dato,int posicion)
{
    int i;

    if(*lista == NULL)
        return LISTA_VACIA;

    for(i=0; i < posicion; i++)
        lista = &(*lista)->sig;

    t_nodo* sacar = *lista;

    memcpy(dato, sacar->dato, MIN(tam_dato, sacar->tam));
    *lista = sacar->sig;
    free(sacar->dato);
    free(sacar);
    return TODO_OK;
}

int sacar_de_lista_clave(t_lista* pLista,void* dato, unsigned tam_dato,const void* clave, tCMP cmp)
{

    t_nodo* elim;
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
    memcpy(dato,elim->dato,tam_dato);

    free(elim->dato);
    free(elim);


    return TODO_OK;
}


void vaciar_lista(t_lista* lista)
{
    t_nodo* elim;
    while(*lista != NULL)
    {
        elim = *lista;
        *lista = elim->sig;
        free(elim->dato);
        free(elim);
    }
    return;
}

int map_lista(t_lista* lista, tACCION accion)
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

int insertar_ordenado(t_lista* lista, void* dato, unsigned tam_dato, int comp(const void*, const void*))
{
    t_nodo* nuevo_nodo;


    while(*lista != NULL && comp((*lista)->dato, dato) < 0)
        lista = &(*lista)->sig;


    nuevo_nodo = malloc(sizeof(t_nodo));
    if(!nuevo_nodo)
        return SIN_ESPACIO;

    nuevo_nodo->dato = malloc(tam_dato);
    if(!nuevo_nodo->dato)
    {
        free(nuevo_nodo);
        return SIN_ESPACIO;
    }

    memcpy(nuevo_nodo->dato, dato, tam_dato);
    nuevo_nodo->tam = tam_dato;
    nuevo_nodo->sig = *lista;
    *lista = nuevo_nodo;

    return TODO_OK;
}

int insertar_ordenado_sin_dupli(t_lista* lista, void* dato, unsigned tam_dato, int comp(const void*, const void*))
{
    t_nodo* nuevo_nodo;
    int cmp = 0;


    while(*lista != NULL && (cmp = comp((*lista)->dato, dato)) < 0)
        lista = &(*lista)->sig;

    if(cmp == 0)
        return DUPLICADO;


    nuevo_nodo = malloc(sizeof(t_nodo));
    if(!nuevo_nodo)
        return SIN_ESPACIO;

    nuevo_nodo->dato = malloc(tam_dato);
    if(!nuevo_nodo->dato)
    {
        free(nuevo_nodo);
        return SIN_ESPACIO;
    }

    memcpy(nuevo_nodo->dato, dato, tam_dato);
    nuevo_nodo->tam = tam_dato;
    nuevo_nodo->sig = *lista;
    *lista = nuevo_nodo;

    return TODO_OK;
}

//void ordenar_lista(t_lista* lista, int (comparar)(const void*, const void*, unsigned))
//{
//
//    t_lista nuevaLista = NULL;
//    t_nodo actual = *lista;
//
//    while (actual != NULL)
//    {
//        t_nodo* menorNodo = actual;
//        t_nodo* nodoAnteriorMenor = NULL;
//        t_nodo* temp = actual->sig;
//        t_nodo* nodoAnteriorTemp = actual;
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

void ordenar_lista(t_lista* lista, int comp(const void*, const void*))
{
    int ordenado;
    t_nodo** nodo;
    t_nodo* aux;

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



