
#include "lista.h"
#include "funciones.h"


void mostrarCarta(t_nodo* nodo)
{
    printf("%d ",*(int*)(nodo->dato));
}

int main()
{
//    t_lista mazo;
//    crear_lista(&mazo);
//    t_pila descarte;
//    crear_pila(&descarte);
//
//    cargar_mazo(&mazo);
//    map_lista(&mazo,mostrarCarta);
//    puts("\n---------");

//    ordenar_lista(&mazo,rand_num);
//    mezclar_mazo(&mazo);
//    map_lista(&mazo,mostrarCarta);

    char op;
    printf("%s\n",TITULO);
    op=menu(MSJ_MENU,OPC_MENU);
    switch(tolower(op))
    {
    case 'a':
        system("cls");
        iniciar_juego();
        break;
    case 'b':
        system("cls");
        break;
    case 'c':
        break;

    }
    return 0;
}
