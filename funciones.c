#include "funciones.h"


int  iniciar_juego()
{
    tJugador jugador;
    t_lista mazo, manoBot;
    t_pila descarte;
    tCola turnos;
    int puntosBot = 0,puntosBotAnterior = 0,turno = 1,quienTira,cartaTirada, carta, ultimaCarta;
    char dificulad;

    printf("%s\n",TITULO);
    printf("Cual es tu nombre?\n-->");
    fgets(jugador.nombre,sizeof(jugador.nombre),stdin);
    reemplazar_salto(jugador.nombre);///reemplaza el '\n' del enter con '\0'
    system("cls");

    printf("%s\n",TITULO);
    dificulad=menu(MSJ_DIFICULTAD,OPC_DIF);
    jugador.puntos=0;
    jugador.puntosAnterior = jugador.puntos;
    crearCola(&turnos);
    crear_lista(&mazo);
    crear_pila(&descarte);

    cargar_mazo(&mazo);///pone las cartas en el mazo
    mezclar_mazo(&mazo,MAXIMO_CARTAS);

    crear_lista(&jugador.mano);
    crear_lista(&manoBot);

    repartir_cartas(&mazo, &jugador, &manoBot);
    quienTira = rand() % 2;

    do
    {
        system("cls");
        printf("%s\n",TITULO);
        interfaz(puntosBot,jugador,&descarte,turno,quienTira);
        if( quienTira == TURNO_DEL_BOT)
        {
            cartaTirada = turno_bot(puntosBot,&manoBot,dificulad,jugador.puntos,&descarte);
            jugador.puntosAnterior = jugador.puntos;
            efectos_cartas(&puntosBot,&jugador.puntos,puntosBotAnterior,jugador.puntosAnterior,cartaTirada,&descarte);

            if(eliminar_de_lista(&mazo, &carta, sizeof(int)) == LISTA_VACIA)
            {
                desapilar(&descarte, &ultimaCarta, sizeof(int));///saco la ultima carta que tire
                nuevo_mazo(&mazo, &descarte);
                eliminar_de_lista(&mazo, &carta, sizeof(int));
                apilar(&descarte, &ultimaCarta, sizeof(int));///y la dejo de nuevo en el descarte
            }
            agregar_a_lista(&manoBot,&carta,sizeof(int));

            if(cartaTirada != REPETIR)
            {
                quienTira = TURNO_DEL_JUGADOR;
            }

            printf("Analizando la jugada....\n");
            printf("\n");
            system("pause");
            registrarTurno(&turnos, &jugador, puntosBot, turno, cartaTirada, TURNO_DEL_BOT);
        }
        else ///turno jugador
        {

            cartaTirada = turno_jugador(&jugador.mano);
            puntosBotAnterior = puntosBot;
            efectos_cartas(&jugador.puntos,&puntosBot,jugador.puntosAnterior,puntosBotAnterior,cartaTirada,&descarte);

            if(eliminar_de_lista(&mazo, &carta, sizeof(int)) == LISTA_VACIA)
            {
                desapilar(&descarte, &ultimaCarta, sizeof(int));///saco la ultima carta que tire
                nuevo_mazo(&mazo, &descarte);
                eliminar_de_lista(&mazo, &carta, sizeof(int));
                apilar(&descarte, &ultimaCarta, sizeof(int));///y la dejo de nuevo en el descarte
            }
            agregar_a_lista(&jugador.mano,&carta,sizeof(int));

            if(cartaTirada != REPETIR)
            {
                quienTira = TURNO_DEL_BOT;
            }
            registrarTurno(&turnos, &jugador, puntosBot, turno, cartaTirada, TURNO_DEL_JUGADOR);
        }
        turno++;
    }while(jugador.puntos < PUNTOS_MAX && puntosBot < PUNTOS_MAX);
    if(puntosBot >= PUNTOS_MAX)
    {
        system("cls");
        printf("%s\n",TITULO);
        printf("\tPERDISTE :(\n");
        printf("\tGANADOR BOT\n");
        enviar_resultado_api(jugador.nombre, 0);
    }
    else
    {
        system("cls");
        printf("%s\n",TITULO);
        printf("\tGANASTE :)\n");
        printf("\tGANADOR %s\n",jugador.nombre);
        enviar_resultado_api(jugador.nombre, 1);
    }
    generarInforme(&turnos);
    vaciarCola(&turnos);
    vaciar_lista(&mazo);
    vaciar_pila(&descarte);

    vaciar_lista(&jugador.mano);
    vaciar_lista(&manoBot);

    system("pause");
    system("cls");
    return TODO_OK;
}

int turno_jugador(t_lista* mano)
{
    int carta,pos,i=0;
    printf("\nSu mano actual:");
    map_lista(mano,mostrar_mano);
    printf("\n");
    printf("\nElija un carta 1 a 3: ");
    do
    {
        if(i!=0)
            printf("\nElija un carta 1 a 3: ");
        scanf("%d",&pos);
        fflush(stdin);
        i=1;
    }
    while(pos<1||pos>3);

    sacar_de_lista_posicion(mano,&carta,sizeof(int),pos-1);

    return carta;
}


void efectos_cartas(int* puntosTirador, int* puntosRival,int puntosAntTirador, int puntosAntRival, int carta, t_pila* descarte)
{
    int ultimaTirada=1;// = 1 por si no hay nada en el descarte
    switch(carta)
    {
    case ESPEJO:
        if(ver_tope_pila(descarte,&ultimaTirada,sizeof(int))==PILA_VACIA)///Se fija si la ultima carta es negativa, para aplicar el efecto
            break;

        if(ultimaTirada < 0)
        {
            *puntosRival += (*puntosTirador-puntosAntTirador);///le resta los puntos al rival
            *puntosTirador = puntosAntTirador;
        }
        break;

    case MAS1:
    case MAS2:
        *puntosTirador += carta;
        break;

    case MENOS1:
    case MENOS2:
        *puntosRival += carta;
        break;
    }
    if(*puntosRival < 0)
        *puntosRival = 0;

    ///si es REPETIR la tira y se fija en la funcion iniciar_juego

    apilar(descarte,&carta,sizeof(int));
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

/*
%d Es reemplazado por el día del mes como un número decimal (01-31)
%H Es reemplazado por la hora (reloj de 24 horas) como un número decimal (00-23)
%m Es reemplazado por el mes como un número decimal (01-12)
%M Es reemplazado por el minuto como un número decimal (00-59)
%Y Es reemplazado por el año con siglo como un número decimal
informe-juego_2025-02-01-12-20.txt
%Y-%m-%d-%H-%M
*/
void nombreInforme(char* nombre)
{
    time_t comienzo = time(NULL);
    struct tm *timepo = localtime(&comienzo);
    strftime(nombre, 40, "informe-juego_%Y-%m-%d-%H-%M.txt", timepo);
}

void registrarTurno(tCola* turnos, tJugador* jugador, unsigned puntosBot, unsigned numeroTurno, int carta, int quienTira)
{
    tTurno jugada;

    strcpy(jugada.nombreJugador, jugador->nombre);
    jugada.puntosBot = puntosBot;
    jugada.puntosJugador = jugador->puntos;
    jugada.turno = numeroTurno;
    jugada.quienTiro = quienTira;
    jugada.carta = carta;

    ponerEnCola(turnos, &jugada, sizeof(tTurno));
}

int generarInforme(tCola* turnos)
{
    char nombreArchivo[40];
    FILE* p;
    tTurno turno;
    nombreInforme(nombreArchivo);
    p = fopen(nombreArchivo, "wt");
    if(!p)
        return 0;
    while(sacarDeCola(turnos, &turno, sizeof(tTurno)))
    {
        switch(turno.carta)
        {
        case MAS1:
            if(turno.quienTiro == TURNO_DEL_JUGADOR)
                fprintf(p, "Turno %d: El jugador %s jugó la carta MAS 1. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            else
                fprintf(p, "Turno %d: El jugador Bot jugó la carta MAS 1. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            break;

        case MAS2:
            if(turno.quienTiro == TURNO_DEL_JUGADOR)
                fprintf(p, "Turno %d: El jugador %s jugó la carta MAS 2. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            else
                fprintf(p, "Turno %d: El jugador Bot jugó la carta MAS 2. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            break;

        case MENOS1:
            if(turno.quienTiro == TURNO_DEL_JUGADOR)
                fprintf(p, "Turno %d: El jugador %s jugó la carta MENOS 1. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            else
                fprintf(p, "Turno %d: El jugador Bot jugó la carta MENOS 1. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            break;

        case MENOS2:
            if(turno.quienTiro == TURNO_DEL_JUGADOR)
                fprintf(p, "Turno %d: El jugador %s jugó la carta MENOS 2. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            else
                fprintf(p, "Turno %d: El jugador Bot jugó la carta MENOS 2. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            break;

        case ESPEJO:
            if(turno.quienTiro == TURNO_DEL_JUGADOR)
                fprintf(p, "Turno %d: El jugador %s jugó la carta ESPEJO. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            else
                fprintf(p, "Turno %d: El jugador Bot jugó la carta ESPEJO. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            break;

        case REPETIR:
            if(turno.quienTiro == TURNO_DEL_JUGADOR)
                fprintf(p, "Turno %d: El jugador %s jugó la carta REPETIR TURNO. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            else
                fprintf(p, "Turno %d: El jugador Bot jugó la carta REPETIR TURNO. Puntos de %s: %d, puntos del Bot: %d\n", turno.turno, turno.nombreJugador, turno.puntosJugador, turno.puntosBot);
            break;
        }
    }
    if(turno.puntosJugador >= PUNTOS_MAX)
        fprintf(p, "El jugador %s ha ganado la partida logrando llegar a 12 puntos\n",turno.nombreJugador);
    else
        fprintf(p, "El jugador %s ha perdido la partida, el Bot logro llegar a los 12 puntos primero\n",turno.nombreJugador);
    fclose(p);
    return 1;
}
