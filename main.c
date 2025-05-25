
#include "lista.h"
#include "funciones.h"


void mostrarCarta(tNodo* nodo)
{
    printf("%d ",*(int*)(nodo->dato));
}

int main()
{
//    tLista mazo;
//    crearLista(&mazo);
//    tPila descarte;
//    crearPila(&descarte);
//
//    cargarMazo(&mazo);
//    mapLista(&mazo,mostrarCarta);
//    puts("\n---------");

//    mezclarMazo(&mazo);
//    mapLista(&mazo,mostrarCarta);

    char op;
    printf("%s\n",TITULO);
    op=menu(MSJ_MENU,OPC_MENU);
    switch(tolower(op))
    {
    case 'a':
        system("cls");
        iniciarJuego();
        break;
    case 'b':
        system("cls");
        break;
    case 'c':
        break;

    }

}
