#ifndef WIN_H
#define WIN_H

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdarg.h>
#include <time.h>
#include "IO.h"


#ifdef _WIN32
  #include <windows.h>
#endif

#ifdef __linux__
  #include <sys/ioctl.h>
  #include <unistd.h>
  #include <termios.h>

  #include <string.h>
  #include <sys/select.h>
  #include <sys/time.h>
#endif

#define NEW_SCREEN() printf("\e[?1049h")
#define CLOSE_SCREEN() printf("\e[?1049l")

#define VLINE  "│"
#define HLINE  "─"
#define TLLINE "╭"
#define TRLINE "╮"
#define BLLINE "╰"
#define BRLINE "╯"

#define MENUVLINE "▏"

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

#define STDOUTPUT NULL

// Posición del Cursor
void noEcho();
void echo();

// Window.h
typedef struct _WINDOW
{
  int X;
  int Y;
  int COLS;
  int ROWS;

  struct WINDOW* Parent;
}WINDOW;


typedef struct _MENU{
    WINDOW* Parent;
    int X;
    int Y;
    int ROWS;
    char** opciones;
    char** descripcion;
    int selected;
} MENU;

typedef struct _TABLE{
    int columas, filas;
    int currentFilledRow;
    //Bidimencional: texto mas largo por columna
    int* textoMasLargo;
    //Tridimencional: columna, fila y texto
    int total;
    int toalTeorico;
    char** headers;
    struct FILA* data;
} TABLE;

typedef int (*Funciones)(void);

void setMenuData(MENU* Destination,WINDOW* Parent, int x, int y, int rows,char* opciones[], char* descripciones[]);

void innit();

WINDOW* newWin(int y, int x, int COLS, int ROWS, WINDOW* Parent);
void winprint(WINDOW* window,int X, int Y, char* text);
void printinthemiddle(WINDOW* Window, int Y,const char* texto);
void printinthemiddlesize(WINDOW* Window, int Y, char* texto, int tam);
void box(WINDOW* Window);
void getcolsrows(WINDOW* Window, int* COLS, int* ROWS);
void getxy(WINDOW* Window, int* X, int* Y);
int getcols(WINDOW* Window);
int getrows(WINDOW* Window);
int getx(WINDOW* Window);
int gety(WINDOW* Window);

void printMessage(char* text);

// Menu.h
//MENU* newMenu(WINDOW* Parent, int x, int y, int COLS, int ROWS,char** opciones,char** descripciones, int cant);
void focusMenu(MENU* menu); 
void updateMenu(MENU* menu); 

// Table.h
// TABLE* newTable(int columnas, int filas);
void tableSetHeaders(TABLE *src,char** headers);
void tableAppendRow(TABLE *src, ...);
void tablePrepareDataAling(TABLE *src);
void printTable(TABLE* table, int x, int y);

void prepareTableData(TABLE* src, int columnas, int filas);
void setTableData(char* dest, char* src);
int getTotal(TABLE* src);
int getTotalToerico(TABLE* src);
void freeTable(TABLE *src);

#endif