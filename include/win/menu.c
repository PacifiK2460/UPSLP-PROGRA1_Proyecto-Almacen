#include "../win.h"

// Estructura que nos permite habilitar y deshabilitar el eco
#ifdef _WIN32
    DWORD mode;
#endif

#ifdef __linux__
    static int fd = STDIN_FILENO;
    static struct termios old;
#endif

void reset_tty(void){
    #ifdef __linux__
        tcsetattr(fd, TCSANOW, &old);
    #endif

    #ifdef _WIN32
        //TODO
    #endif
}


void noEcho(){
    #ifdef _WIN32
        HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(console, &mode);
        SetConsoleMode(console, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
    #endif

    #ifdef __linux__
        struct termios new;
        tcgetattr(fd, &old);
        new = old;
        new.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(fd, TCSANOW, &new);

    #endif
}

void echo(){
    #ifdef _WIN32
        HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(console, &mode);
        SetConsoleMode(console, mode | (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
    #endif

    #ifdef __linux__
        tcsetattr(fd, TCSANOW, &old);
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
        char c;
        noEcho();
        // read(STDIN_FILENO, &c, 1);
        // switch (c){
        //     case 27:
        //     {
        //         fd_set set;
        //         struct timeval timeout;
        //         FD_ZERO(&set);
        //         FD_SET(STDIN_FILENO, &set);
        //         timeout.tv_sec = 0;
        //         timeout.tv_usec = 0;
        //         int selret = select(1, &set, NULL, NULL, &timeout);

        //         if (selret == 1){
        //             read(STDIN_FILENO, &c, 1);
        //             read(STDIN_FILENO, &c, 1);
        //             switch (c)
        //             {
        //                 case 'A':
        //                     if(menu->selected > 0) menu->selected -= 1;
        //                     break;
        //                 case 'B':
        //                     if(menu->selected < menu->ROWS - 1) menu->selected += 1;
        //                     break;
        //             }
        //         }
        //         else {
        //             updateMenu(menu);
        //             echo();
        //             menu->selected = -1;
        //             return;
        //         }
        //     updateMenu(menu);
        //     echo();
        //     }
        //         break;
        //     case 10:
        //         echo();
        //         return updateMenu(menu);
        // }
        // updateMenu(menu);
        // echo();

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
                    return;
            }
            //En caso de update, actualizamos visualmente el manu
            updateMenu(menu);
        } else if (c == 10){
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