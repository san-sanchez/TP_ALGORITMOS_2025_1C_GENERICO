#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include <curl/curl.h>

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
#define MAXIMO_CARTAS 40
#define CARTAS_DESCARTE 33
#define MAX_LINEA 100

typedef struct{
    char *data;
    size_t size;
}Buffer;

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
    int puntosAnterior;
    t_lista mano;


} tJugador;

///funciones.c
int  iniciar_juego();
int turno_jugador(t_lista* mano);
void efectos_cartas(int* puntosTirador, int* puntosRival,int puntosAntTirador, int puntosAntRival, int carta, t_pila* descarte);
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
void mezclar_mazo(t_lista* mazo, int cantidad);
int rand_num(const void* a, const void* b);
int repartir_cartas(t_lista* mazo, tJugador* jugador, t_lista* manoBot);
void nuevo_mazo(t_lista* mazo, t_pila* descarte);

///funcionesInterfaz.c
void interfaz(int puntosBot, tJugador jugador, t_pila* descarte,int turno_actual,int quien_tira);
void imprimir_carta(int carta);
char menu(const char* msj,const char* opciones);
int mostrar_mano(void* mano);

///funcionesApi.c
cJSON* cuerpo_post(const char* nom, int vencedor);
int peticion_post(const char* str_cuerpo, const char* api);
int enviar_resultado_api(const char* nombre_jugador, int vencedor);
size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata);
cJSON* peticion_get(const char* url_api, const char* codigo_grupo);
void mostrar_ranking(cJSON* ranking);
int leer_configuracion_api(const char* nombre_archivo, char* url_api, char* codigo_grupo);
void obtener_ranking();

#endif // FUNCIONES_H_INCLUDED
