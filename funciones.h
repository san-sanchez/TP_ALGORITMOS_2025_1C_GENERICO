#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <time.h>
#include <ctype.h>

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


#define MAS2 2
#define MAS1 1
#define MENOS1 -1
#define MENOS2 -2
#define REPETIR 3
#define ESPEJO 0
#define PUNTOS_MAX 12
#define CERCA_GANAR 8
#define CARTAS_BUENAS 1


typedef struct
{
    char nombre[36];
    int puntos;
    tLista mano;
    int cantCartasEnMano;

} tJugador;

int  iniciarJuego();
void cargarMazo(tLista* mazo);
void ponerCartasMazo(tLista* mazo,int  carta,int cantidad);
void mezclarMazo(tLista* lista);

void interfaz(int puntosBot, tJugador jugador, tPila* descarte,int turnoActual,int quienTira);
void imprimirCarta(int carta);

int turnoJugador(tLista* mano);

int turnoBot(int puntosBot, tLista* mano, char dif, int puntosJugador, tPila* descarte);
int dificultadFacil(tLista* mano);
int dificultadMedia(int puntosBot, tLista* mano, int puntosJugador);
int dificultadDificil(int puntosBot, tLista* mano, int puntosJugador, tPila* descarte);

void efectosCartas(int* puntosTirador, int* puntosRival, int carta, tPila* descarte);


char menu(const char* msj,const char* opciones);
void reemplazarSalto(char* s);
int compararCartas(const void* a,const void* b);
int mostrarMano(void* mano);
int contarCartasBuenas(tLista* mano);
#endif // FUNCIONES_H_INCLUDED
