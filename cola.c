#include "cola.h"

void crearCola(tCola* cola){
    cola->pri = NULL;
    cola->ult = NULL;
}
void vaciarCola(tCola* cola){
    tNodo* elim = cola->pri;
    while(elim){
        cola->pri = elim->sig;
        free(elim->dato);
        free(elim);
        elim = cola->pri;
    }
    cola->ult = NULL;
}
int colaVacia(const tCola* cola){
    return cola->pri == NULL;
}
int colaLlena(const tCola* cola, const void* dato, unsigned tam){
    return 0;
}
int ponerEnCola(tCola* cola, const void* dato, unsigned tam){
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0;
    nue->dato = malloc(tam);
    if(!(nue->dato)){
        free(nue);
        return 0;
    }
    memcpy(nue->dato, dato, tam);
    nue->tam = tam;
    nue->sig = NULL;
    if(cola->ult)
        cola->ult->sig = nue;
    else
        cola->pri = nue;
    cola->ult = nue;

    return 1;
}
int sacarDeCola(tCola* cola, void* dato, unsigned tam){
    tNodo* elim = cola->pri;
    if(!elim)
        return 0;
    memcpy(dato, elim->dato, MIN(tam, elim->tam));
    cola->pri = elim->sig;
    free(elim->dato);
    free(elim);
    if(!cola->pri)
        cola->ult = NULL;
    return 1;
}
int verPrimero(const tCola* cola, void* dato, unsigned tam){
    if(!cola->pri)
        return 0;
    memcpy(dato, cola->pri->dato, MIN(tam, cola->pri->tam));
    return 1;
}















