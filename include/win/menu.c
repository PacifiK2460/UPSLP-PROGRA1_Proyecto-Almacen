#include "../win.h"

struct MENU{
    WINDOW* Parent;
    int X;
    int Y;
    int COLS;
    int ROWS;
    wchar_t** opciones;

    int numeroDeOpciones;
    int opcionMasLarga;

    int selected;

    Funciones* funciones;
};

MENU* newMenu(WINDOW* Parent, int x, int y, int COLS, int ROWS,wchar_t** opciones, int cantOps,Funciones* funciones){
    MENU* menu = (MENU*)malloc(sizeof(MENU));
    menu->opciones = opciones;
    menu->numeroDeOpciones = cantOps;
    menu->opcionMasLarga = 0;
    for(int i = 0; i < menu->numeroDeOpciones; i++){
        if( wcslen(opciones[i]) > menu->opcionMasLarga)
            menu->opcionMasLarga = wcslen(opciones[i]);
    }
    menu->opcionMasLarga+=1;
    menu->X = getx(Parent);
    menu->X += x;
    menu->Y = gety(Parent);
    menu->Y += y;
    menu->COLS = COLS;
    menu->ROWS = ROWS;
    menu->selected = 0;

    menu->funciones = funciones;
    return menu;
}

void focusMenu(MENU* menu){
    updateMenu(menu);
    register int c;
    //Leemos el teclado non-canonical mode
    #ifdef _WIN32
        DWORD mode;
        HANDLE console = GetStdHandle(STD_INPUT_HANDLE);

        GetConsoleMode(console, &mode);
        SetConsoleMode(console, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
    #endif

    #ifdef __linux__
        struct termios mode;
        tcgetattr(0, &mode);
        mode.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(0, TCSANOW, &mode);
    #endif

    while(1){
        c = getchar();
        if(c == '\033'){ //ESC
            getchar(); //Omitimos el 2do [
            switch ( (c = getchar()) )
            {
                case 'A':
                    if(menu->selected != 0) menu->selected -= 1;
                    break;
                
                case 'B':
                    if(menu->selected != menu->numeroDeOpciones - 1) menu->selected += 1;
                    break;
            }
            fflush(stdout);
            updateMenu(menu);
            fflush(stdout);
        }
        if(c == 10){
            break;
        }
    }
    menu->funciones[menu->selected]();
}

void updateMenu(MENU* menu){
    for(int i = 0; i < menu->numeroDeOpciones; i++){
        printf("\x1B[%i;%iH%s %ls%-*ls%ls\n",menu->X + i,menu->Y,( (menu->selected == i) ? ">" : " " ), ( (menu->selected == i) ? INVERSE : NONE ), menu->opcionMasLarga, menu->opciones[i], RESET);
    }
}

