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


typedef struct s_nodo
{
    void* dato;
    unsigned tam;
    struct s_nodo* sig;
}t_nodo;

typedef t_nodo* t_lista;

typedef t_nodo* t_pila;

typedef int(*tCMP)(const void* dato1, const void* dato2);
typedef int(*tACCION)(void* dato);

void crear_lista(t_lista* lista);
int lista_vacia(const t_lista* lista);
int lista_llena(const t_lista* lista);
int agregar_a_lista(t_lista* lista, void* dato, unsigned tam_dato);
int eliminar_de_lista(t_lista* lista, void* dato, unsigned tam_dato);
int sacar_de_lista_posicion(t_lista* lista, void* dato, unsigned tam_dato,int posicion);
int sacar_de_lista_clave(t_lista* lista,void* dato, unsigned tam_dato,const void* clave, tCMP cmp);
void vaciar_lista(t_lista* lista);

int map_lista(t_lista* lista, tACCION);
int insertar_ordenado(t_lista* lista, void* dato, unsigned tam_dato, int comp(const void*, const void*));
int insertar_ordenado_sin_dupli(t_lista* lista, void* dato, unsigned tam_dato, int comp(const void*, const void*));
//void ordenar_lista(t_lista* lista, int (comparar)(const void*, const void*, unsigned));
void ordenar_lista(t_lista* lista, int comp(const void*, const void*));

void crear_pila(t_pila *p);
int apilar(t_pila *p, const void *dato, unsigned tamDato);
int desapilar(t_pila *p, void *dato, unsigned tamDato);
void vaciar_pila(t_pila *p);
int ver_tope_pila(const t_pila *p, void *dato, unsigned tamDato);
int pila_llena(const t_pila *p, unsigned tamDato);
int pila_vacia(const t_pila *p);


#endif // LISTA_H_INCLUDED
