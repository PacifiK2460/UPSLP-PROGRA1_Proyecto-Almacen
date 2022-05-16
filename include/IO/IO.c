#include "../IO.h"

#define MAX_TEXT_LENGTH 51

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

int evaluarText(char* Dest, int lenght){
    if(!fgets(Dest, lenght, stdin)){
        return -1;
    }
    Dest[lenght] = '\0';
    Dest[strcspn(Dest, "\r\n")] = 0;

    return 1;
}

int evaluarNombreDelCliente(char* Src){
    if( evaluarText(Src, MAX_TEXT_LENGTH) == -1) return -1;
    for(int i = 0; Src[i] != '\0' && Src[i] != '\n'; i++) if(esLetra(Src[i]) == 0) return 0;
    return 1;
}

int evaluarInt(int* Dest){
    char buff[1024];
    if(!fgets(buff,1024,stdin)){
        return -1;
    }

    char *endptr;
    errno = 0;
    *Dest = strtol(buff, &endptr, 10);

    if(errno == ERANGE || endptr == buff || (*endptr && *endptr != '\n')){
        *Dest = 0;
    }

    return 1;
}

int evaluarDouble(double* Dest){
    char buff[1024];
    if(!fgets(buff,1024,stdin)){
        return -1;
    }

    char *endptr;
    errno = 0;
    *Dest = strtof(buff, &endptr);

    if(errno == ERANGE || endptr == buff || (*endptr && *endptr != '\n')){
        *Dest = 0;
    }

    return 1;
}

int evaluarNumeroTelefonico(char* Src){
    if( evaluarText(Src, 12) == -1) return -1;
    for(int i = 0; Src[i] != '\0' && Src[i] != '\n'; i++) if(esNumero(Src[i]) == 0) return 0;
    if(strlen(Src) < 10 ) return 0;
    return 1;
}


int evaluarUbicacion(char* Src){
    if( evaluarText(Src, 2) == -1) return -1;
    for(int i = 0; Src[i] != '\0'; i++) if(esLetra(Src[i]) == 0) return 0;
    return 1;

}


int evaluarCorreo(char* Dest){
    return evaluarText(Dest, MAX_TEXT_LENGTH);
}



int input(char* bg_titulo, char* titulo, void* dest, int (*funcion)(void*)){
    delimitador result = funcion;
    int res;
    do{
        {
            clearerr(stdin);
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
    noEcho();
    clearerr(stdin);
    return res;
}