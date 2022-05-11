#include "../IO.h"

#define MAX_TEXT_LENGTH 51

// int volatile CONTINUE_RUNNING = 1;

void cleanInput(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { };
}

//TODO #6 change inputh method to work in min-max ranges

int esNumero(char numero){
    return (numero >= '0' && numero <= '9');
}

int esLetra(char letra){
    return ( (letra >= 'a' && letra <= 'z') || (letra >= 'A' && letra <= 'Z') );
}

int evaluarNombreDeProducto(char* Src){
    int size = MAX_TEXT_LENGTH;
    int res = scanf("%6s", Src);
    if(res == EOF || res == 0) return res;
    //if( scanf("%6s", Src) == 0 ) return 0;
    //if(getText(Src,size - 1) == 0) return 0;
    Src[size] = '\0'; 

    //REGLAS ESPECIFICADAS EN EL DOCUMENTO
    for(int i = 0; i < 3; i++) if(esLetra(Src[i]) == 0) return 0;
    for(int i = 3; i < 6; i++) if(esNumero(Src[i]) == 0) return 0;
    return 1;
}

int evaluarNombreDelCliente(char* Src){
    int size = MAX_TEXT_LENGTH;
    int res = scanf("%51s", Src);
    if(res == EOF || res == 0) return res;
    // if(scanf("%51s", Src) == 0) return 0;
    Src[size] = '\0'; 

    //EL NOMBRE SOLO PUEDE SER TEXTO
    for(int i = 0; Src[i] != '\0'; i++) if(esLetra(Src[i]) == 0) return 0;
    return 1;
}

int evaluarExistencia(char* Src){
    int size = 11;
    int temp;
    int res = scanf("%ui", &temp); 
    if(res == EOF || res == 0) return res;
    //if( scanf("%ui", &temp) == 0 ) return 0;
    snprintf(Src, size-1, "%i", temp);
    Src[size] = '\0';
    return 1;
}

int evaluarPrecio(char* Src){
    int size = 11;
    int temp;
    int res = scanf("%ui", &temp);
    if(res == EOF  || res == 0) return res; 
    // if(scanf("%ui", &temp)==0)return 0;
    snprintf(Src, size-1, "%i", temp);
    Src[size] = '\0';
    return 1;
}

int evaluarUbicacion(char* Src){
    int res = scanf("%1s", Src);
    if(res == EOF || res == 0) return res; 
    // if(scanf("%1s", Src)==0) return 0;
    for(int i = 0; i < 2-1; i++) if(esLetra(Src[i]) == 0) return 0;
    Src[1] = '\0';
    return 1;
}

int evaluarNumero(char* Src){
    int temp;
    int res = scanf("%ui",&temp);
    if(res == EOF || res == 0) return res;
    // if(scanf("%ui",&temp)==0)return 0;
    snprintf(Src, 11,"%i", temp);
    //Src[11] = '\0';
    return 1;
}

int evaluarCorreo(char* Dest){
    int c = scanf("%s", Dest);
    return c;
}

// void intHandler(int dummy) {
//     signal(SIGINT, intHandler);
//     CONTINUE_RUNNING = 0;
// }

int input(char* bg_titulo, char* titulo, char* dest, int (*funcion)(char*)){
    // signal(SIGINT, intHandler);
    NEW_SCREEN();
    delimitador result = funcion;
    int res;
    do{
        {
            printf(CLEAR);
            echo();
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "ctrl + d"  RESET DIM  " regresar ");
            winprint(STDOUTPUT,4,2, bg_titulo);
            winprint(STDOUTPUT,5, (getrows(STDOUTPUT)/2)-1,titulo);
            winprint(STDOUTPUT,4, (getrows(STDOUTPUT)/2)-1,MENUVLINE);
            winprint(STDOUTPUT,5, (getrows(STDOUTPUT)/2)," ");
            winprint(STDOUTPUT,4, (getrows(STDOUTPUT)/2),MENUVLINE);
        }

    }while((res = result(dest)) == 0);
    cleanInput();
    noEcho();
    clearerr(stdin);
    CLOSE_SCREEN();
    return res;

    //return ( CONTINUE_RUNNING == 0 ? !(CONTINUE_RUNNING = 1) : (CONTINUE_RUNNING) );
    // if(CONTINUE_RUNNING == 0) return (CONTINUE_RUNNING = 1);
    // return CONTINUE_RUNNING;
    // //Leemos el nombre y evaluamos
    // while(result(dest) == 0){
    //     cleanInput();
    //     printf(CLEAR);
    //     winprint(STDOUTPUT,4,2, bg_titulo);
    //     winprint(STDOUTPUT,5, (getrows(STDOUTPUT)/2)-1,titulo);
    //     winprint(STDOUTPUT,4, (getrows(STDOUTPUT)/2)-1,MENUVLINE);
    //     winprint(STDOUTPUT,5, (getrows(STDOUTPUT)/2)," ");
    //     winprint(STDOUTPUT,4, (getrows(STDOUTPUT)/2),MENUVLINE);
    // }
    // cleanInput();
    // noEcho();
    // printf(HIDE_CURSOR);
    // printf(CLEAR);
    // CLOSE_SCREEN();
}