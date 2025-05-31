#include "funciones.h"

void interfaz(int puntosBot, tJugador jugador, t_pila* descarte,int turno_actual,int quien_tira)
{
    int cartaEnMesa;
    printf("Turno Actual:%d \t\t Tira: %s\n ",turno_actual, (quien_tira==0?"Bot":jugador.nombre));
    printf("Puntos %s: %d \t Puntos Bot: %d",jugador.nombre,jugador.puntos,puntosBot);
    printf("\n\n");
    if(ver_tope_pila(descarte,&cartaEnMesa,sizeof(int))!=PILA_VACIA)
        imprimir_carta(cartaEnMesa);
}

void imprimir_carta(int carta)
{
    printf("\t---------\n");
    if(carta == ESPEJO)
        printf("\t|ESPEJO|\n");

    else if(carta == REPETIR)
        printf("\t|REPETIR|\n");
    else
        printf("\t| %5d |\n",carta);
    printf("\t---------\n");
}

char menu(const char* msj,const char* opciones)
{
    char op;
    int priVez=0;
    do
    {
        if(priVez!=0)
            printf("\nOPCION NO VALIDA\n");
        priVez=1;
        printf("%s",msj);
        scanf("%c",&op);
        fflush(stdin);

    }
    while(strchr(opciones,op) == NULL);

    return op;
}
int mostrar_mano(void* mano)
{
    int carta = *(int*)mano;

    if(carta == ESPEJO)
        printf("\t|ESPEJO|");

    else if(carta == REPETIR)
        printf("\t|REPETIR|");
    else
        printf("\t|%d|",carta);

    return TODO_OK;
}
