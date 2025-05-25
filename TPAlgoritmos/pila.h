#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include "funciones.h"

void crear_pila(t_pila *p);
int apilar(t_pila *p, const void *dato, unsigned tamDato);
int desapilar(t_pila *p, void *dato, unsigned tamDato);
void vaciar_pila(t_pila *p);
int ver_tope_pila(const t_pila *p, void *dato, unsigned tamDato);
int pila_llena(const t_pila *p, unsigned tamDato);
int pila_vacia(const t_pila *p);

#endif // PILA_H_INCLUDED
