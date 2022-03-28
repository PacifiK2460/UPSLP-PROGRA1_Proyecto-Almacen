#include "include/win.h"
#include "include/sys.h"
#include "include/IO.h"
#include <stdio.h>

void splashScreen();
void menu();
void printmenu();

int main(){
    splashScreen();
    menu();
}

void menu(){
    // Preparamos el menu
    MENU* menu;
    char* opciones[] = {
        "Consulta de almacén",
        "Actualizar almacén",
        "Registrar Pedido",
        "Consultar Pedido",
        "Registrar entrega",
        "Modificar estado de pedido",
        "Salir del sistema"
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

    while(1){
        printmenu();
        focusMenu(menu);
    }
    printf(SHOW_CURSOR);
}

/*
    Una pelta de gold de .45 kg adquiere una rapides de 25 m/s al ser golpeada.
    Si el tiempo de contacto es de 2 ms, que fuerza media actua sobre la pelota

    F = mv/t = 6525N
*/

/*
    Un vagon abierto de 24,000 KG, viaja sin friccion sobre una via horizontal.
    Esta lloviendo muy fuerte, y la lluvia cae de forma vertical. El vagon originalmente esta vacio y tiene una rapidez de 4m/s.

        A) ¿Que rapidez tiene el vagon despues de acumular 3,000 KG de agua de lluvia?

            Tren   + Awa   = TOTAL
        m = 24k KG + 3k KG = 27k KG
        
        Velocidad del Tren
        v = 4 m/s

        Movimiento del Tren + Awa
        P = m2v2 = 108k kg m/s

        Movimiento del Tren
        P = m1v1 = 96k kg m/s

        m1v1 = m1v2

        m1v1 / m2 = v2
        v2 = 3.5 m/s

        B) Puesto que la lluvia cae verticalmente, ¿Como afecta esto al movimiento horizontal del vagon? 
*/

void splashScreen(){
    innit();

    box(STDOUTPUT, BOLD);
    noEcho();
    printf(HIDE_CURSOR);
    printinthemiddle(STDOUTPUT,1,"BY:",NONE);
    printinthemiddle(STDOUTPUT,2,"Sistemas Plus S.A. DE C.V.",BOLD);
    int x = 3;
    printinthemiddlesize(STDOUTPUT,x++,"                      ▗▄▄▄▄                       ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"                   ▗▄████████▄▖                   ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"                ▗▄██████████████▄▖                ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"             ▄▄████████▛▀▀█████████▄▖             ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"          ▗▄█████████▀▘     ▀█████████▄           ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"       ▗▄██████████▙          ▝▀█████████▄        ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"     ▄███████████████▙▄          ▝▀████████▙▄     ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"  ▗▟████████▀▘▝▀████████▙▄          ▝▀████████▙▖  ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++," ▟███████▀▘      ▀▀████████▙▖          ▝▀███████▙ ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"▐███████▄           ▀▜████████▙▖        ▗▄███████▙",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"██████████▙▄           ▀▜████████▄▖   ▄▟██████████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████████████▙▖           ▀▜████████▟█████████████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████ ▀▜████████▙▖           ▀████████████▀▘ █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████    ▀▜████████▄▖        ▗▄████████▛▀    █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████       ▀▜████████▄▖  ▗▄█████████▀       █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████          ▀████████▙████████▛▀          █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████            ▝▀████████████▀             █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████               ▝▀██████▀▘               █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"█████▖                ▐████▌                ▗█████",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"▐█████▙▖              ▐████▌              ▄▟█████▌",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++," ▜███████▄▖           ▐████▌           ▄▟███████▛ ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"  ▝▜████████▄▖        ▐████▌        ▗▟████████▛▘  ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"     ▀▜████████▄▖     ▐████▌     ▗▄████████▛▀     ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"       ▝▀█████████▄   ▐████▌  ▗▄████████▛▀        ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"          ▝▀█████████▄▐████▌▄████████▛▀           ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"             ▝▀████████████████████▀▘             ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"                ▝▀██████████████▀                 ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"                   ▝▀████████▀▘                   ",BOLD,50);
    printinthemiddlesize(STDOUTPUT,x++,"                      ▝▀▀▀▀                       ",BOLD,50);

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT) - 2,"< Presiona cualquier tecla para continuar >",DIM);
    getchar();
    printf(SHOW_CURSOR);
    echo();
}