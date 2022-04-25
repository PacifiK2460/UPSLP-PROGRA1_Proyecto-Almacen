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

    MENU menu;
    setMenuData(&menu,STDOUTPUT,4,4,7,
        (char*[]){
            "Consulta de almacén",
            "Actualizar almacén",
            "Registrar Pedido",
            "Consultar Pedido",
            "Registrar entrega",
            "Modificar estado de pedido",
            "Salir del sistema"
        },
        (char*[]){
            "Enlista los productos disponibles",
            "Sumar / Modificar inventario, agregar productos",
            "Registrar información del pedido y del cliente",
            "Enlista los pedidos por Activos, Entregados, Cancelados e ID",
            "Registra la entrega de un pedido y actualiza el inventario",
            "Modifica el estado del pedido del cliente",
            "Cierra la sesión actual"
        }
    );

    Funciones Funciones[] = {
        consultarAlmacen,
        actualizarAlmacen,
        registrarPedido,
        consultarPedido,
        registrarEntrega,
        modificarPedido,
        salir
    };

    //menu = newMenu(STDOUTPUT,4, 4 ,30,7, opciones,descropciones,7);

    printf(HIDE_CURSOR);
    while(1){
        printf(CLEAR);
        winprint(STDOUTPUT,4,2,BRGB(16,158,94) FRGB(255,255,255) " MENU PRINCIPAL ");
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-3,RESET FRGB(185, 251, 192)  "↓↑"     RESET DIM  " Arriba / Abajo ");
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "enter"  RESET DIM  " Seleccionar ");
        focusMenu(&menu);
        if(menu.selected == 6){
            //free(menu.selected); //limpio memoria y salgoe
            salir();
        } else {
            Funciones[menu.selected]();
        }
        //Funciones[focusMenu(menu)]();
        
    }
    printf(SHOW_CURSOR);
}



void splashScreen(){
    innit();

    box(STDOUTPUT);
    noEcho();
    printf(HIDE_CURSOR);
    printinthemiddle(STDOUTPUT,1,"BY:");
    printinthemiddle(STDOUTPUT,2,"Sistemas Plus S.A. DE C.V.");
    int x = 3;
    printinthemiddlesize(STDOUTPUT,x++,"                      ▗▄▄▄▄                       ",50);
    printinthemiddlesize(STDOUTPUT,x++,"                   ▗▄████████▄▖                   ",50);
    printinthemiddlesize(STDOUTPUT,x++,"                ▗▄██████████████▄▖                ",50);
    printinthemiddlesize(STDOUTPUT,x++,"             ▄▄████████▛▀▀█████████▄▖             ",50);
    printinthemiddlesize(STDOUTPUT,x++,"          ▗▄█████████▀▘     ▀█████████▄           ",50);
    printinthemiddlesize(STDOUTPUT,x++,"       ▗▄██████████▙          ▝▀█████████▄        ",50);
    printinthemiddlesize(STDOUTPUT,x++,"     ▄███████████████▙▄          ▝▀████████▙▄     ",50);
    printinthemiddlesize(STDOUTPUT,x++,"  ▗▟████████▀▘▝▀████████▙▄          ▝▀████████▙▖  ",50);
    printinthemiddlesize(STDOUTPUT,x++," ▟███████▀▘      ▀▀████████▙▖          ▝▀███████▙ ",50);
    printinthemiddlesize(STDOUTPUT,x++,"▐███████▄           ▀▜████████▙▖        ▗▄███████▙",50);
    printinthemiddlesize(STDOUTPUT,x++,"██████████▙▄           ▀▜████████▄▖   ▄▟██████████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████████████▙▖           ▀▜████████▟█████████████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████ ▀▜████████▙▖           ▀████████████▀▘ █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████    ▀▜████████▄▖        ▗▄████████▛▀    █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████       ▀▜████████▄▖  ▗▄█████████▀       █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████          ▀████████▙████████▛▀          █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████            ▝▀████████████▀             █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████               ▝▀██████▀▘               █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████                 ▐████▌                 █████",50);
    printinthemiddlesize(STDOUTPUT,x++,"█████▖                ▐████▌                ▗█████",50);
    printinthemiddlesize(STDOUTPUT,x++,"▐█████▙▖              ▐████▌              ▄▟█████▌",50);
    printinthemiddlesize(STDOUTPUT,x++," ▜███████▄▖           ▐████▌           ▄▟███████▛ ",50);
    printinthemiddlesize(STDOUTPUT,x++,"  ▝▜████████▄▖        ▐████▌        ▗▟████████▛▘  ",50);
    printinthemiddlesize(STDOUTPUT,x++,"     ▀▜████████▄▖     ▐████▌     ▗▄████████▛▀     ",50);
    printinthemiddlesize(STDOUTPUT,x++,"       ▝▀█████████▄   ▐████▌  ▗▄████████▛▀        ",50);
    printinthemiddlesize(STDOUTPUT,x++,"          ▝▀█████████▄▐████▌▄████████▛▀           ",50);
    printinthemiddlesize(STDOUTPUT,x++,"             ▝▀████████████████████▀▘             ",50);
    printinthemiddlesize(STDOUTPUT,x++,"                ▝▀██████████████▀                 ",50);
    printinthemiddlesize(STDOUTPUT,x++,"                   ▝▀████████▀▘                   ",50);
    printinthemiddlesize(STDOUTPUT,x++,"                      ▝▀▀▀▀                       ",50);

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT) - 2,"< Presiona cualquier tecla para continuar >");
    getchar();
    printf(SHOW_CURSOR);
    echo();
}