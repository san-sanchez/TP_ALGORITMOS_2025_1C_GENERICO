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

void mezclar_mazo(t_lista* mazo, int cantidad)
{

    t_lista mazoMezclado;
    int carta, posicion;

    // inicializar la semilla para numeros aleatorios
    srand(time(NULL));

    // crear nueva lista vacia para el mazo mezclado
    crear_lista(&mazoMezclado);

    // mientras haya cartas en el mazo
    while (cantidad > 0)
    {
        posicion = rand() % cantidad;

        // sacar una carta de una posicion aleatoria
        if (sacar_de_lista_posicion(mazo, &carta, sizeof(carta), posicion) == TODO_OK)
        {
            // agregarla a la nueva lista
            agregar_a_lista(&mazoMezclado, &carta, sizeof(carta));
        }

        cantidad--;
    }

    // actualizar la lista original con la nueva
    *mazo = mazoMezclado;
}
int repartir_cartas(t_lista* mazo, tJugador* jugador, t_lista* manoBot)
{
    int i, carta;
    for(i=0; i<3; i++)
    {
        eliminar_de_lista(mazo, &carta, sizeof(int));
        agregar_a_lista(&(jugador->mano),&carta, sizeof(int));
        eliminar_de_lista(mazo, &carta, sizeof(int));
        agregar_a_lista(manoBot,&carta,sizeof(int));
    }
    return TODO_OK;
}
void nuevo_mazo(t_lista* mazo, t_pila* descarte)
{
    int carta;
    while(desapilar(descarte, &carta, sizeof(int)) == TODO_OK)
    {
        agregar_a_lista(mazo, &carta, sizeof(int));
    }
    mezclar_mazo(mazo,CARTAS_DESCARTE);
}
