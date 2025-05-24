#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y) (((x)<(y))?(x):(y))
#define SIN_ESPACIO -1
#define SIN_MEMORIA -1
#define LISTA_VACIA -2
#define PILA_VACIA -2
#define DUPLICADO -2
#define TODO_OK 1
#define ERROR 0


typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

typedef tNodo* tPila;

typedef int(*tCMP)(const void* dato1, const void* dato2);
typedef int(*tACCION)(void* dato);


//---------------------LISTA---------------------
void crearLista(tLista* lista);
int listaVacia(const tLista* lista);
int listaLlena(const tLista* lista);
int agregarALista(tLista* lista, void* dato, unsigned tamDato);
int eliminarDeLista(tLista* lista, void* dato, unsigned tamDato);
int sacarDeListaPosicion(tLista* lista, void* dato, unsigned tamDato,int posicion);
int sacarDeListaClave(tLista* lista,void* dato, unsigned tamDato,const void* clave, tCMP cmp);
void vaciarLista(tLista* lista);

int mapLista(tLista* lista, tACCION);
int insertarOrdenado(tLista* lista, void* dato, unsigned tamDato, int comp(const void*, const void*));
int insertarOrdenadoSinDupli(tLista* lista, void* dato, unsigned tamDato, int comp(const void*, const void*));
//void ordenarLista(tLista* lista, int (comparar)(const void*, const void*, unsigned));
void ordenarLista(tLista* lista, int comp(const void*, const void*));

//---------------------PILA---------------------
void crearPila(tPila *p);
int apilar(tPila *p, const void *dato, unsigned tamDato);
int desapilar(tPila *p, void *dato, unsigned tamDato);
void vaciarPila(tPila *p);
int verTopePila(const tPila *p, void *dato, unsigned tamDato);
int pilaLlena(const tPila *p, unsigned tamDato);
int pilaVacia(const tPila *p);


#endif // LISTA_H_INCLUDED
