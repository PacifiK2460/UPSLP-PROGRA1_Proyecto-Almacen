#include "../win.h"

// Estructura que nos permite habilitar y deshabilitar el eco
#ifdef _WIN32
    DWORD mode;
#endif

#ifdef __linux__
    struct termios mode;
#endif

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

void setMenuData(MENU* Destination, WINDOW* Parent, int x, int y, int rows,char* opciones[], char* descripciones[]){
    Destination->opciones = opciones;
    Destination->descripcion = descripciones;

    Destination->X = getx(Parent) + x;
    Destination->Y = gety(Parent) + y;
    Destination->ROWS = rows;
    Destination->selected = 0;
}

void focusMenu(MENU* menu){
    updateMenu(menu);
    //Leemos el teclado non-canonical mode

    while(1){
        updateMenu(menu);
        //echo();
        char c = 0;
        noEcho();
        if((c = getchar()) == '\033'){ //ESC
            getchar(); //Omitimos el 2do [
            switch ( (c = getchar()) )
            {
                case 'A':
                    if(menu->selected != 0) menu->selected -= 1;
                    break;
                
                case 'B':
                    if(menu->selected != menu->ROWS - 1) menu->selected += 1;
                    break;
                case 'D':
                    menu->selected = -1;
                    echo();
                    updateMenu(menu);
                    return;
            }
            //En caso de update, actualizamos visualmente el manu
            echo();
            updateMenu(menu);
        } else if (c == 10){
            updateMenu(menu);
            echo();
            return;
        }
    }
    updateMenu(menu);
    echo();
    //Regresamos index seleccionado
}

void updateMenu(MENU* menu){
    for(int i = 0, x = 0; i < menu->ROWS; i++){
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