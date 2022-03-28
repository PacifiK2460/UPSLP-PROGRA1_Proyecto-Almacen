#ifndef WIN_H
#define WIN_H

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

#ifdef _WIN32
  #include <windows.h>
#endif

#ifdef __linux__
  #include <sys/ioctl.h>
  #include <unistd.h>
  #include <termios.h>
#endif

#define STDOUTPUT NULL

#define RESET     "\e[0m"
#define NONE      ""

// Tipos
#define BOLD      "\e[1m"
#define DIM       "\e[2m"
#define ITALIC    "\e[3m"
#define INVERSE   "\e[7m"

// Color de fuente

// Color de fondo

// MISC
#define HIDE_CURSOR "\e[?25l"
#define SHOW_CURSOR "\e[?25h"
#define CLEAR "\e[2J"

// Posición del Cursor
void noEcho();
void echo();

// Window.h
typedef struct WINDOW WINDOW;
typedef struct MENU MENU;

typedef void (*Funciones)(void);

void innit();

WINDOW* newWin(int y, int x, int COLS, int ROWS, WINDOW* Parent);
void winprint(WINDOW* window,int X, int Y, char* text, char* mode);
void printinthemiddle(WINDOW* Window, int Y, char* texto, char* mode);
void printinthemiddlesize(WINDOW* Window, int Y, char* texto,char* mode, int tam);
void box(WINDOW* Window, char* mode);
void getcolsrows(WINDOW* Window, int* COLS, int* ROWS);
void getxy(WINDOW* Window, int* X, int* Y);
int getcols(WINDOW* Window);
int getrows(WINDOW* Window);
int getx(WINDOW* Window);
int gety(WINDOW* Window);


// Menu.h
MENU* newMenu(WINDOW* Parent, int x, int y, int COLS, int ROWS,char** opciones, int cant,Funciones* funciones);
void printmenu();
void focusMenu(MENU* menu); 
void updateMenu(MENU* menu); 

#endif