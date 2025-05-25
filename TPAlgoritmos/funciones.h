#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <time.h>
#include <ctype.h>
#include "lista.h"
#include "cola.h"
#include "pila.h"

#define TITULO  "========================================\n"\
                "=            ---- DoCe ----            =\n"\
                "========================================\n"

#define MSJ_MENU    "------MENU------\n"\
                    "[A] Jugar\n"\
                    "[B] Ver ranking\n"\
                    "[C] Salir\n"\
                    "---> "

#define OPC_MENU "ABCabc"

#define MSJ_DIFICULTAD  "---DIFICULTAD---\n"\
                        "[F] Facil\n"\
                        "[M] Medio\n"\
                        "[D] Dificil\n"\
                        "---> "
#define OPC_DIF "FMDfmd"

#define TURNO_DEL_BOT 0
#define TURNO_DEL_JUGADOR 1
#define MAS2 2
#define MAS1 1
#define MENOS1 -1
#define MENOS2 -2
#define REPETIR 3
#define ESPEJO 0
#define PUNTOS_MAX 12
#define CERCA_GANAR 8
#define CARTAS_BUENAS 1

typedef struct{
    char nombreJugador[36];
    unsigned puntosBot;
    unsigned puntosJugador;
    unsigned turno;
    unsigned quienTiro;
    int carta;
}tTurno;

typedef struct
{
    char nombre[36];
    int puntos;
    t_lista mano;
    int cantCartasEnMano;

} tJugador;

///funciones.c
int  iniciar_juego();
int turno_jugador(t_lista* mano);
void efectos_cartas(int* puntosTirador, int* puntosRival, int carta, t_pila* descarte);
void reemplazar_salto(char* s);
int comparar_cartas(const void* a,const void* b);
void nombreInforme(char* nombre);
void registrarTurno(tCola* turnos, tJugador* jugador, unsigned puntosBot, unsigned numeroTurno, int carta, int quienTira);
int generarInforme(tCola* turnos);

///funcionesBot.c
int turno_bot(int puntosBot, t_lista* mano, char dif, int puntosJugador, t_pila* descarte);
int dificultad_facil(t_lista* mano);
int dificultad_media(int puntosBot, t_lista* mano, int puntosJugador);
int dificultad_dificil(int puntosBot, t_lista* mano, int puntosJugador, t_pila* descarte);
int contar_cartas_buenas(t_lista* mano);

///funcionesMazo.c
void cargar_mazo(t_lista* mazo);
void poner_cartas_mazo(t_lista* mazo,int  carta,int cantidad);
void mezclar_mazo(t_lista* lista);
int rand_num(const void* a, const void* b);
int repartir_cartas(t_lista* mazo, tJugador* jugador, t_lista* manoBot);
void nuevo_mazo(t_lista* mazo, t_pila* descarte);

///funcionesInterfaz.c
void interfaz(int puntosBot, tJugador jugador, t_pila* descarte,int turno_actual,int quien_tira);
void imprimir_carta(int carta);
char menu(const char* msj,const char* opciones);
int mostrar_mano(void* mano);

#endif // FUNCIONES_H_INCLUDED
