#include "../win.h"

// Estructura que nos permite habilitar y deshabilitar el eco
#ifdef _WIN32
    DWORD mode;
#endif

#ifdef __linux__
    struct termios mode;
#endif

struct MENU{
    WINDOW* Parent;
    int X;
    int Y;
    int COLS;
    int ROWS;
    char** opciones;
    char** descripcion;

    int numeroDeOpciones;
    int opcionMasLarga;

    int selected;
};

void noEcho(){
    #ifdef _WIN32
        HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(console, &mode);
        SetConsoleMode(console, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
    #endif

    #ifdef __linux__
        tcgetattr(0, &mode);
        mode.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(0, TCSANOW, &mode);
    #endif
}

void echo(){
    #ifdef _WIN32
        HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(console, &mode);
        SetConsoleMode(console, mode | (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
    #endif

    #ifdef __linux__
        tcgetattr(0, &mode);
        mode.c_lflag |= (ICANON | ECHO);
        tcsetattr(0, TCSANOW, &mode);
    #endif
}


MENU* newMenu(WINDOW* Parent, int x, int y, int COLS, int ROWS,char** opciones,char** descripciones, int cantOps){
    MENU* menu = (MENU*)malloc(sizeof(MENU));
    menu->opciones = opciones;
    menu->numeroDeOpciones = cantOps;
    menu->opcionMasLarga = 0;
    for(int i = 0; i < menu->numeroDeOpciones; i++){
        if( len(opciones[i]) > menu->opcionMasLarga)
            menu->opcionMasLarga = len(opciones[i]);
    }
    menu->opcionMasLarga+=1;
    menu->X = getx(Parent);
    menu->X += x;
    menu->Y = gety(Parent);
    menu->Y += y;
    menu->COLS = COLS;
    menu->ROWS = ROWS;
    menu->selected = 0;
    menu->descripcion = descripciones;

    return menu;
}

int focusMenu(MENU* menu){
    updateMenu(menu);
    register int c;
    //Leemos el teclado non-canonical mode
    noEcho();

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
            //En caso de update, actualizamos visualmente el manu
            updateMenu(menu);
        }
        //Enter
        if(c == 10){
            break;
        }
    }
    //Regresamos index seleccionado
    return menu->selected;
}

void updateMenu(MENU* menu){
    for(int i = 0, x = 0; i < menu->numeroDeOpciones; i++){
        printf( "\e[%i;%iH"
                "%s" "%s " "%s" RESET,
                menu->X + i + x++,menu->Y, //Posicion
                menu->selected == i ? BOLD FRGB(185, 251, 192) : NONE, //Color
                menu->selected == i ? MENUVLINE : " ", //Caracter de seleccion
                menu->opciones[i]);
        printf( "\e[%i;%iH"
                "%s" "%s " "%s" RESET,
                menu->X + i + x++,menu->Y,
                menu->selected == i ? DIM FRGB(185, 251, 192) : NONE,
                menu->selected == i ? MENUVLINE : " ",
                menu->descripcion[i]); //Cantidad de caracteres, texto
    }
}