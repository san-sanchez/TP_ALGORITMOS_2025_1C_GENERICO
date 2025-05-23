#include "lista.h"
#include "funciones.h"


int  iniciar_juego()
{
    tJugador jugador;
    t_lista mazo, manoBot;
    t_pila descarte;
    int prueba,i;///sacar despues
    int puntosBot=0,turno=1,quienTira,ultimaCarta,cartaTirada;
    char dificulad;

    printf("Cual es tu nombre?\n-->");
    fgets(jugador.nombre,sizeof(jugador.nombre),stdin);
    reemplazar_salto(jugador.nombre);///reemplaza el '\n' del enter con '\0'

    dificulad=menu(MSJ_DIFICULTAD,OPC_DIF);
    jugador.puntos=0;

    crear_lista(&mazo);
    crear_pila(&descarte);

    cargar_mazo(&mazo);///pone las cartas en el mazo
    mezclar_mazo(&mazo);

    crear_lista(&jugador.mano);
    crear_lista(&manoBot);

    ///SACAR DESPUES, reemplazar con REPARTIR LAS CARTAS
    for(i=0; i<3; i++)
    {
        prueba =(rand() % 5) - 1;///numero entre -1 y 3 que son las cartas
        agregar_a_lista(&jugador.mano,&prueba,sizeof(int));
        prueba =(rand() % 5) - 1;
        agregar_a_lista(&manoBot,&prueba,sizeof(int));
    }
    ///

    quienTira = rand() % 2;

    while(jugador.puntos < PUNTOS_MAX && puntosBot < PUNTOS_MAX)
    {
        system("cls");
        interfaz(puntosBot,jugador,&descarte,turno,quienTira);
        if( quienTira == 0) ///Va el bot
        {
            cartaTirada = turno_bot(puntosBot,&manoBot,dificulad,jugador.puntos,&descarte);
            efectos_cartas(&puntosBot,&jugador.puntos,cartaTirada,&descarte);

            prueba =(rand() % 5) - 1;
            agregar_a_lista(&manoBot,&prueba,sizeof(int));///Para probar SACAR despues

            ver_tope_pila(&descarte,&ultimaCarta,sizeof(int));///Para ver si repite el turno
            if(ultimaCarta != REPETIR)
            {
                quienTira = 1;
            }

            printf("Analizando la jugada....\n");
            printf("\n");
            system("pause");
        }
        else ///turno jugador
        {

            cartaTirada = turno_jugador(&jugador.mano);
            efectos_cartas(&jugador.puntos,&puntosBot,cartaTirada,&descarte);

            prueba =(rand() % 5) - 1;
            agregar_a_lista(&jugador.mano,&prueba,sizeof(int));///Para probar SACAR despues

            ver_tope_pila(&descarte,&ultimaCarta,sizeof(int));
            if(ultimaCarta != REPETIR)
            {
                quienTira = 0;
            }
        }
        ///AGREGAR EL INFORME POR TURNO
        turno++;
    }
    if(puntosBot >= PUNTOS_MAX)
    {
        system("cls");
        printf("\tPERDISTE :(\n");
        printf("\tGANADOR BOT\n");
    }
    else
    {
        system("cls");
        printf("\tGANASTE :)\n");
        printf("\tGANADOR %s\n",jugador.nombre);
    }


    return TODO_OK;
}

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
        printf("\t|ESPEJO |\n");

    else if(carta == REPETIR)
        printf("\t|REPETIR|\n");
    else
        printf("\t| %5d |\n",carta);
    printf("\t---------\n");
}

int turno_jugador(t_lista* mano)
{
    int carta,pos,i=0;
    printf("\nSu mano actual:");
    map_lista(mano,mostrar_mano);
    printf("\n");
    printf("\nElija un carta 1 a 3: ");
    do  ///Se rompe al poner una letra
    {
        if(i!=0)
            printf("\nElija un carta 1 a 3: ");
        scanf("%d",&pos);
        fflush(stdin);
        i=1;
    }
    while(pos<1||pos>3);

    sacar_de_lista_posicion(mano,&carta,sizeof(int),pos-1);

    ///FALTA DARLE LA OTRA CARTA
    return carta;
}

int turno_bot(int puntosBot, t_lista* mano, char dif, int puntosJugador, t_pila* descarte)
{
    int cartaTirada;
    printf("\nMano bot actual:");
    map_lista(mano,mostrar_mano);
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
    ///FALTA DARLE LA OTRA CARTA
    return cartaTirada;
}


int dificultad_facil(t_lista* mano)
{
    int tirar,carta;

    tirar = rand() % 3;

    sacar_de_lista_posicion(mano,&carta,sizeof(int),tirar);

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
    if(puntosJugador > 0)///SI EL JUGADOR TIENE PUNTOS SE LOS RESTA
    {
        elegir=MENOS2;///PRIORIZA EL MENOS 2
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
        elegir=MENOS1;
        if(sacar_de_lista_clave(mano,&carta,sizeof(int),&elegir,comparar_cartas)==TODO_OK)
            return carta;
    }

    carta = dificultad_facil(mano);///SI NO PUEDE HACER LO  ANTERIOR TIRA UNA AL AZAR

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

    carta = dificultad_facil(mano);

    return carta;

}

void efectos_cartas(int* puntosTirador, int* puntosRival, int carta, t_pila* descarte)
{
    int ultimaTirada;
    if( carta == ESPEJO )
    {
        ver_tope_pila(descarte,&ultimaTirada,sizeof(int));///Se fija si la ultima carta es negativa, para aplicar el efecto

        if(ultimaTirada < 0)///Tiene una falla
        {
            *puntosRival += ultimaTirada;///le resta los puntos al rival
            *puntosTirador -= ultimaTirada;///se los "suma" al tirador de la carta espejo
        }
    }

    if( carta == MAS1 || carta == MAS2)
    {
        *puntosTirador += carta;
    }

    if( carta == MENOS1 || carta == MENOS2)
    {
        *puntosRival += carta;
    }

    if(*puntosRival < 0)
        *puntosRival = 0;

    ///si es REPETIR la tira y se fija en la funcion iniciar_juego

    apilar(descarte,&carta,sizeof(int));

}



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
    int cantidad = 0;
    t_nodo* actual = *lista;

    while (actual != NULL)
    {
        cantidad++;
        actual = actual->sig;
    }

    // Inicializar semilla para números aleatorios
    srand(time(NULL));

    // Convertir la lista en un arreglo temporal de punteros a nodos
    t_nodo** arreglo = malloc(cantidad * sizeof(t_nodo*));
    actual = *lista;

    for (int i = 0; i < cantidad; i++)
    {
        arreglo[i] = actual;
        actual = actual->sig;
    }

    // Aplicar el algoritmo Fisher-Yates
    for (int i = cantidad - 1; i > 0; i--)
    {
        int j = rand() % (i + 1); // Índice aleatorio entre 0 e i

        // Intercambiar los elementos i y j
        t_nodo* temp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = temp;
    }

    // Reconstruir la lista con el nuevo orden
    *lista = arreglo[0];
    actual = *lista;

    for (int i = 1; i < cantidad; i++)
    {
        actual->sig = arreglo[i];
        actual = actual->sig;
    }
    actual->sig = NULL;

    free(arreglo);
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

void reemplazar_salto(char* s)
{
    char* aux=strchr(s,'\n');
    *aux='\0';
}

int comparar_cartas(const void* a,const void* b)
{
    return *(int*)a - *(int*)b;
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
