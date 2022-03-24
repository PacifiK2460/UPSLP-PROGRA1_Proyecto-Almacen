#include "include/win.h"
#include <stdio.h>

void splashScreen();
void menu();

int main(){
    splashScreen();
    menu();
    printf(reset);
}

void menu(){
    printf(CLEAR);
    box(STDOUTPUT, DIM);
    printf(HIDE_CURSOR);
    int rows = getrows(STDOUTPUT);
    int cols = getcols(STDOUTPUT);
    printinthemiddle(STDOUTPUT,1,L"SELECCIONA LA OPCIOÓN",BOLD);

    // Preparamos el menu
    MENU* menu;
    wchar_t* opciones[] = {
        L"Consulta de almacén",
        L"Actualizar almacén",
        L"Registrar Pedido",
        L"Registrar Pedido",
        L"Registrar entrega",
        L"Modificar estado de pedido",
        L"Salir del sistema"
    }; //(temp - 7) / 2
    menu = newMenu(STDOUTPUT,(rows - 7)/2, (cols - 30) / 2 ,30,7, &opciones,7);

    printinthemiddle(STDOUTPUT,1,L"SELECCIONA LA OPCIOÓN",BOLD);
    printinthemiddle(STDOUTPUT,rows - 2,L"Usa ↓↑ para seleccionar la opción y <ENTER> para realizar la opción",DIM);
    
    focusMenu(menu);

    printf(SHOW_CURSOR);
}

void splashScreen(){
    innit();
    box(STDOUTPUT, DIM);
    printf(HIDE_CURSOR);
    int temp = getrows(STDOUTPUT);
    printinthemiddle(STDOUTPUT,(temp/2) - 1,L"BY:",NONE);
    printinthemiddle(STDOUTPUT,(temp/2),L"Sistemas Plus S.A. DE C.V.",BOLD);
    printinthemiddle(STDOUTPUT,temp - 2,L"< Presiona cualquier tecla para continuar >",DIM);
    getchar();
    printf(SHOW_CURSOR);
}