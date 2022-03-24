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
};

MENU* newMenu(WINDOW* Parent, int y, int x, int COLS, int ROWS, wchar_t* opciones[], int cantOps){
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
        mode.c_lflag &= ~(ECHO | ICANON | ICRNL);
        tcsetattr(0, TCSANOW, &mode);
    #endif

    while(1){
        if(getchar() == '\033'){ //ESC
            getchar(); //Omitimos el 2do [
            switch (getchar())
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
    }
}

void updateMenu(MENU* menu){
    printf("\x1B[%i;%iH" ,menu->X,menu->Y);
    for(int i = 0; i < menu->numeroDeOpciones; i++){
        printf("\x1B[%i;%iH" " %c " "%s" "%-*ls" reset "\n",menu->Y + i,menu->X,( (menu->selected == i) ? '>' : ' ' ),( (menu->selected == i) ? INVERSE : NONE ), menu->COLS,menu->opciones[i]);
    }
}

