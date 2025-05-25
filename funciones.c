#include "lista.h"
#include "funciones.h"


int  iniciarJuego()
{
    tJugador jugador;
    tLista mazo, manoBot;
    tPila descarte;
    int prueba,i;///sacar despues
    int puntosBot=0,turno=1,quienTira,ultimaCarta,cartaTirada;
    char dificulad;

    printf("Cual es tu nombre?\n-->");
    fgets(jugador.nombre,sizeof(jugador.nombre),stdin);
    reemplazarSalto(jugador.nombre);///reemplaza el '\n' del enter con '\0'

    dificulad=menu(MSJ_DIFICULTAD,OPC_DIF);
    jugador.puntos=0;

    crearLista(&mazo);
    crearPila(&descarte);

    cargarMazo(&mazo);///pone las cartas en el mazo
    mezclarMazo(&mazo);

    crearLista(&jugador.mano);
    crearLista(&manoBot);

    ///SACAR DESPUES, reemplazar con REPARTIR LAS CARTAS
    for(i=0; i<3; i++)
    {
        prueba =(rand() % 5) - 1;///numero entre -1 y 3 que son las cartas
        agregarALista(&jugador.mano,&prueba,sizeof(int));
        prueba =(rand() % 5) - 1;
        agregarALista(&manoBot,&prueba,sizeof(int));
    }
    ///

    quienTira = rand() % 2;

    while(jugador.puntos < PUNTOS_MAX && puntosBot < PUNTOS_MAX)
    {
        system("cls");
        interfaz(puntosBot,jugador,&descarte,turno,quienTira);
        if( quienTira == 0) ///Va el bot
        {
            cartaTirada = turnoBot(puntosBot,&manoBot,dificulad,jugador.puntos,&descarte);
            efectosCartas(&puntosBot,&jugador.puntos,cartaTirada,&descarte);

            prueba =(rand() % 5) - 1;
            agregarALista(&manoBot,&prueba,sizeof(int));///Para probar SACAR despues

            verTopePila(&descarte,&ultimaCarta,sizeof(int));///Para ver si repite el turno
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

            cartaTirada = turnoJugador(&jugador.mano);
            efectosCartas(&jugador.puntos,&puntosBot,cartaTirada,&descarte);

            prueba =(rand() % 5) - 1;
            agregarALista(&jugador.mano,&prueba,sizeof(int));///Para probar SACAR despues

            verTopePila(&descarte,&ultimaCarta,sizeof(int));
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

void interfaz(int puntosBot, tJugador jugador, tPila* descarte,int turnoActual,int quienTira)
{
    int cartaEnMesa;
    printf("Turno Actual:%d \t\t Tira: %s\n ",turnoActual, (quienTira==0?"Bot":jugador.nombre));
    printf("Puntos %s: %d \t Puntos Bot: %d",jugador.nombre,jugador.puntos,puntosBot);
    printf("\n\n");
    if(verTopePila(descarte,&cartaEnMesa,sizeof(int))!=pilaVacia)
        imprimirCarta(cartaEnMesa);
}

void imprimirCarta(int carta)
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

int turnoJugador(tLista* mano)
{
    int carta,pos,i=0;
    printf("\nSu mano actual:");
    mapLista(mano,mostrarMano);
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

    sacarDeListaPosicion(mano,&carta,sizeof(int),pos-1);

    ///FALTA DARLE LA OTRA CARTA
    return carta;
}

int turnoBot(int puntosBot, tLista* mano, char dif, int puntosJugador, tPila* descarte)
{
    int cartaTirada;
    printf("\nMano bot actual:");
    mapLista(mano,mostrarMano);
    printf("\n");
    switch(tolower(dif))
    {
    case 'f':
        cartaTirada = dificultadFacil(mano);
        break;
    case 'm':
        cartaTirada = dificultadMedia(puntosBot,mano,puntosJugador);
        break;
    case 'd':
        cartaTirada = dificultadDificil(puntosBot,mano,puntosJugador,descarte);
        break;
    }
    ///FALTA DARLE LA OTRA CARTA
    return cartaTirada;
}


int dificultadFacil(tLista* mano)
{
    int tirar,carta;

    tirar = rand() % 3;

    sacarDeListaPosicion(mano,&carta,sizeof(int),tirar);

    return carta;
}

int dificultadMedia(int puntosBot, tLista* mano, int puntosJugador)
{
    int carta,elegir;

    if(puntosBot >= CERCA_GANAR)///SI ESTA CON MAS DE X PUNTOS PRIORIZA SUMAR
    {
        elegir=MAS2;///PRIORIZA EL MAS 2
        if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
            return carta;
        elegir=MAS1;
        if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
            return carta;
    }
    if(puntosJugador > 0)///SI EL JUGADOR TIENE PUNTOS SE LOS RESTA
    {
        elegir=MENOS2;///PRIORIZA EL MENOS 2
        if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
            return carta;
        elegir=MENOS1;
        if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
            return carta;
    }

    carta = dificultadFacil(mano);///SI NO PUEDE HACER LO  ANTERIOR TIRA UNA AL AZAR

    return carta;
}

int dificultadDificil(int puntosBot, tLista* mano, int puntosJugador, tPila* descarte)
{
    int carta,elegir,ultimaCarta,buenas;

    buenas = contarCartasBuenas(mano);

    verTopePila(descarte,&ultimaCarta,sizeof(int));

    if( buenas > CARTAS_BUENAS )
    {
        elegir=REPETIR;
        if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
            return carta;
    }

    if(ultimaCarta < 0)///SI TIRARON UN EFECTO NEGATIVO
    {
        elegir=ESPEJO;
        if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
            return carta;
    }

    if(puntosJugador >= CERCA_GANAR)///SI EL JUGADOR ESTA CERCA DE GANAR
    {
        elegir=REPETIR;
        if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
            return carta;

        elegir=MENOS2;
        if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
            return carta;

        elegir=MENOS1;
        if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
            return carta;
    }

    elegir=MAS2;
    if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
        return carta;
    elegir=MAS1;
    if(sacarDeListaClave(mano,&carta,sizeof(int),&elegir,compararCartas)==TODO_OK)
        return carta;

    ///si no se da ninguna de las otras condiciones tira al azar

    carta = dificultadFacil(mano);

    return carta;

}

void efectosCartas(int* puntosTirador, int* puntosRival, int carta, tPila* descarte)
{
    int ultimaTirada;
    if( carta == ESPEJO )
    {
        verTopePila(descarte,&ultimaTirada,sizeof(int));///Se fija si la ultima carta es negativa, para aplicar el efecto

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

    ///si es REPETIR la tira y se fija en la funcion iniciarJuego

    apilar(descarte,&carta,sizeof(int));

}



void cargarMazo(tLista* mazo)
{
    ponerCartasMazo(mazo,MAS2,6);
    ponerCartasMazo(mazo,MAS1,10);
    ponerCartasMazo(mazo,MENOS2,6);
    ponerCartasMazo(mazo,MENOS1,8);
    ponerCartasMazo(mazo,REPETIR,6);
    ponerCartasMazo(mazo,ESPEJO,4);
    return;
}

void ponerCartasMazo(tLista* mazo,int  carta,int cantidad)
{
    for(int c=0; c<cantidad; c++)
        agregarALista(mazo,&carta,sizeof(carta));
}






void mezclarMazo(tLista* lista)
{
    // Primero, contar la cantidad de elementos en la lista
    int cantidad = 0;
    tNodo* actual = *lista;

    while (actual != NULL)
    {
        cantidad++;
        actual = actual->sig;
    }

    // Inicializar semilla para números aleatorios
    srand(time(NULL));

    // Convertir la lista en un arreglo temporal de punteros a nodos
    tNodo** arreglo = malloc(cantidad * sizeof(tNodo*));
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
        tNodo* temp = arreglo[i];
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

void reemplazarSalto(char* s)
{
    char* aux=strchr(s,'\n');
    *aux='\0';
}

int compararCartas(const void* a,const void* b)
{
    return *(int*)a - *(int*)b;
}

int mostrarMano(void* mano)
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

int contarCartasBuenas(tLista* mano)
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
