#include "include/win.h"
#include "include/sys.h"
#include <stdio.h>

void splashScreen();
void menu();

int main(){
    splashScreen();
    menu();
}

void menu(){
    printf(CLEAR);
    box(STDOUTPUT, DIM);
    printf(HIDE_CURSOR);
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
    };
    Funciones Funciones[] = {
        consultarAlmacen,
        actualizarAlmacen,
        registrarPedido,
        consultarPedido,
        registrarEntrega,
        modificarPedido,
        salir
    };

    menu = newMenu(STDOUTPUT,(getrows(STDOUTPUT) - 7)/2, (getcols(STDOUTPUT) - 30) / 2 ,30,7, opciones,7, Funciones);

    printinthemiddle(STDOUTPUT,1,L"SELECCIONA LA OPCIOÓN",BOLD);
    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT) - 2,L"Usa ↓↑ para seleccionar la opción y <ENTER> para realizar la opción",DIM);
    
    focusMenu(menu);

    printf(SHOW_CURSOR);
}


void splashScreen(){
    innit();

    box(STDOUTPUT, BOLD);
    printf(HIDE_CURSOR);
    printinthemiddle(STDOUTPUT,(getrows(STDOUTPUT)/2) - 1,L"BY:",NONE);
    printinthemiddle(STDOUTPUT,(getrows(STDOUTPUT)/2),L"Sistemas Plus S.A. DE C.V.",BOLD);
    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT) - 2,L"< Presiona cualquier tecla para continuar >",DIM);
    getchar();
    printf(SHOW_CURSOR);
}