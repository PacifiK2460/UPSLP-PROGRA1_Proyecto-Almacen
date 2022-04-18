#ifndef WIN_H
#define WIN_H

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdarg.h>
#include "IO.h"


#ifdef _WIN32
  #include <windows.h>
#endif

#ifdef __linux__
  #include <sys/ioctl.h>
  #include <unistd.h>
  #include <termios.h>
#endif

#define VLINE  "│"
#define HLINE  "─"
#define TLLINE "╭"
#define TRLINE "╮"
#define BLLINE "╰"
#define BRLINE "╯"

#define MENUVLINE "▏"

#define STDOUTPUT NULL

#define RESET     "\e[0m"
#define NONE      ""

// Tipos
#define BOLD      "\e[1m"
#define DIM       "\e[2m"
#define ITALIC    "\e[3m"
#define INVERSE   "\e[7m"

// Colores
#define STR(X) #X
#define BRGB(R,G,B) "\e[48;2;" STR(R) STR(;) STR(G) STR(;) STR(B) STR(m)
#define FRGB(R,G,B) "\e[38;2;" STR(R) STR(;) STR(G) STR(;) STR(B) STR(m)

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
typedef struct TABLE TABLE;

typedef int (*Funciones)(void);

void innit();

WINDOW* newWin(int y, int x, int COLS, int ROWS, WINDOW* Parent);
void winprint(WINDOW* window,int X, int Y, char* text);
void printinthemiddle(WINDOW* Window, int Y, char* texto);
void printinthemiddlesize(WINDOW* Window, int Y, char* texto, int tam);
void box(WINDOW* Window);
void getcolsrows(WINDOW* Window, int* COLS, int* ROWS);
void getxy(WINDOW* Window, int* X, int* Y);
int getcols(WINDOW* Window);
int getrows(WINDOW* Window);
int getx(WINDOW* Window);
int gety(WINDOW* Window);

// Menu.h
MENU* newMenu(WINDOW* Parent, int x, int y, int COLS, int ROWS,char** opciones,char** descripciones, int cant);
int focusMenu(MENU* menu); 
void updateMenu(MENU* menu); 

// Table.h
TABLE* newTable(int columnas, int filas, char*** data);
char*** prepareTableData(int fila, int columna, char* headers[]);
void setTableData(int fila, int columna, char*** dest, char* src);
void printTable(TABLE* table, int x, int y);
int getTotal(TABLE* src);

#endif