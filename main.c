#include "lista.h"
#include "funciones.h"

int main()
{
    char op;
    do{
        printf("%s\n",TITULO);
        op=menu(MSJ_MENU,OPC_MENU);
        switch(tolower(op)){
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
    }while(tolower(op) != 'c');
    system("cls");
    return 0;
}
