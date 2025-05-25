#include "funciones.h"
void cargar_mazo(t_lista* mazo)
{
    poner_cartas_mazo(mazo,MAS2,6);
    poner_cartas_mazo(mazo,MAS1,10);
    poner_cartas_mazo(mazo,MENOS2,6);
    poner_cartas_mazo(mazo,MENOS1,8);
    poner_cartas_mazo(mazo,REPETIR,6);
    poner_cartas_mazo(mazo,ESPEJO,4);
    return;
}

void poner_cartas_mazo(t_lista* mazo,int  carta,int cantidad)
{
    for(int c=0; c<cantidad; c++)
        agregar_a_lista(mazo,&carta,sizeof(carta));
}

int rand_num(const void* a, const void* b)
{
    srand(time(NULL));
    int i=(rand() % 3) - 1;
    return i;
}

void mezclar_mazo(t_lista* lista)
{
    // Primero, contar la cantidad de elementos en la lista
    int cantidad = 0, i, j;
    t_nodo* actual = *lista, **arreglo;

    while(actual != NULL)
    {
        cantidad++;
        actual = actual->sig;
    }

    // Inicializar semilla para números aleatorios
    srand(time(NULL));

    // Convertir la lista en un arreglo temporal de punteros a nodos
    arreglo = malloc(cantidad * sizeof(t_nodo*));
    actual = *lista;

    for(i=0;i<cantidad;i++)
    {
        arreglo[i] = actual;
        actual = actual->sig;
    }

    // Aplicar el algoritmo Fisher-Yates
    for(i=cantidad-1;i>0;i--)
    {
        j = rand() % (i + 1); // Índice aleatorio entre 0 e i

        // Intercambiar los elementos i y j
        t_nodo* temp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = temp;
    }

    // Reconstruir la lista con el nuevo orden
    *lista = arreglo[0];
    actual = *lista;

    for(i=1;i<cantidad;i++)
    {
        actual->sig = arreglo[i];
        actual = actual->sig;
    }
    actual->sig = NULL;

    free(arreglo);
}
int repartir_cartas(t_lista* mazo, tJugador* jugador, t_lista* manoBot){
    int i, carta;
    for(i=0; i<3; i++)
    {
        sacar_de_lista_posicion(mazo, &carta, sizeof(int), 1);
        agregar_a_lista(&(jugador->mano),&carta,sizeof(int));
        sacar_de_lista_posicion(mazo, &carta, sizeof(int), 1);
        agregar_a_lista(manoBot,&carta,sizeof(int));
    }
    return TODO_OK;
}
void nuevo_mazo(t_lista* mazo, t_pila* descarte){
    int carta;
    while(desapilar(descarte, &carta, sizeof(int)) == TODO_OK){
        agregar_a_lista(mazo, &carta, sizeof(int));
    }
    mezclar_mazo(mazo);
}
