#include "funciones.h"

int turno_bot(int puntosBot, t_lista* mano, char dif, int puntosJugador, t_pila* descarte)
{
    int cartaTirada;
   // printf("\nMano bot actual:");
   // map_lista(mano,mostrar_mano);
    printf("\n");
    switch(tolower(dif))
    {
    case 'f':
        cartaTirada = dificultad_facil(mano);
        break;
    case 'm':
        cartaTirada = dificultad_media(puntosBot,mano,puntosJugador);
        break;
    case 'd':
        cartaTirada = dificultad_dificil(puntosBot,mano,puntosJugador,descarte);
        break;
    }
    return cartaTirada;
}


int dificultad_facil(t_lista* mano)
{
    int carta;

    sacar_de_lista_posicion(mano,&carta,sizeof(int),(rand() % 3));

    return carta;
}

int dificultad_media(int puntosBot, t_lista* mano, int puntosJugador)
{
    int carta,elegir;

    if(puntosBot >= CERCA_GANAR)///SI ESTA CON MAS DE X PUNTOS PRIORIZA SUMAR
    {
        elegir=MAS2;///PRIORIZA EL MAS 2
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
        elegir=MAS1;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
    }
    if(puntosJugador == 0)///SI EL JUGADOR TIENE CERO PUNTOS NO TIRA NEGATIVAS
    {
        elegir=REPETIR;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
        elegir=MAS2;///PRIORIZA EL MAS 2
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
        elegir=MAS1;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
        elegir=ESPEJO;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
    }

    //carta = dificultad_facil(mano);///SI NO PUEDE HACER LO  ANTERIOR TIRA UNA AL AZAR
    sacar_de_lista_posicion(mano,&carta,sizeof(int),(rand() % 3));

    return carta;
}

int dificultad_dificil(int puntosBot, t_lista* mano, int puntosJugador, t_pila* descarte)
{
    int carta,elegir,ultimaCarta,buenas;

    buenas = contar_cartas_buenas(mano);

    ver_tope_pila(descarte,&ultimaCarta,sizeof(int));

    if( buenas > CARTAS_BUENAS )
    {
        elegir=REPETIR;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
    }

    if(ultimaCarta < 0)///SI TIRARON UN EFECTO NEGATIVO
    {
        elegir=ESPEJO;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
    }

    if(puntosJugador >= CERCA_GANAR)///SI EL JUGADOR ESTA CERCA DE GANAR
    {
        elegir=REPETIR;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;

        elegir=MENOS2;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;

        elegir=MENOS1;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
    }

    elegir=MAS2;
    if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
        return carta;
    elegir=MAS1;
    if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
        return carta;

    ///si no se da ninguna de las otras condiciones tira al azar

    //carta = dificultad_facil(mano);
    sacar_de_lista_posicion(mano,&carta,sizeof(int),(rand() % 3));

    return carta;

}

int contar_cartas_buenas(t_lista* mano)
{
    int buenas = 0;
    while(*mano != NULL)
    {
        if( *(int*)((*mano)->dato) == MAS1 || *(int*)((*mano)->dato) == MAS2 )
            buenas++;
        mano = &(*mano)->sig;

    }
    return buenas;
}
