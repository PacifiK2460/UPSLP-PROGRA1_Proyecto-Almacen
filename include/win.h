#ifndef WIN_H
#define WIN_H

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
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

#define RESET     L"\e[0m"
#define NONE      L""

// Tipos
#define BOLD      L"\e[1m"
#define DIM       L"\e[2m"
#define ITALIC    L"\e[3m"
#define INVERSE   L"\e[7m"

// Color de fuente

// Color de fondo

// MISC
#define HIDE_CURSOR "\e[?25l"
#define SHOW_CURSOR "\e[?25h"
#define CLEAR "\e[2J"

// Posición del Cursor
void moveUP(int i);

// Window.h
typedef struct WINDOW WINDOW;
typedef struct MENU MENU;

typedef void (*Funciones)(void);

void innit();

void newWin(WINDOW* Window, int x, int y, int COLS, int ROWS, WINDOW* Parent);
void winprint(int X, int Y, wchar_t* text, wchar_t* mode);
void printinthemiddle(WINDOW* Window, int Y, wchar_t* texto, wchar_t* mode);
void box(WINDOW* Window, wchar_t* mode);
void getcolsrows(WINDOW* Window, int* COLS, int* ROWS);
void getxy(WINDOW* Window, int* X, int* Y);
int getcols(WINDOW* Window);
int getrows(WINDOW* Window);
int getx(WINDOW* Window);
int gety(WINDOW* Window);


// Menu.h
MENU* newMenu(WINDOW* Parent, int x, int y, int COLS, int ROWS,wchar_t** opciones, int cant,Funciones* funciones);
    
void focusMenu(MENU* menu); 
void updateMenu(MENU* menu); 

#endif