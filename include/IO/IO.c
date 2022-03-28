#include "../IO.h"

int esNumero(char numero){
    return (numero >= '0' && numero <= '9');
}

int esLetra(char letra){
    return ( (letra >= 'a' && letra <= 'z') || (letra >= 'A' && letra <= 'Z') );
}

int getText(char* Dest, int size){
    //getwchar();
    char c;
    int i = 0;
    while(i < size){
        c = getchar();
        if(esLetra(c) == 1 || esNumero(c) == 1){
            Dest[i++] = c;
            continue;
        } else if (c == 10) return 1;
        return 0;
    }
    while ((c = getchar()) != 10);
    return 0;
}

int evaluarNombre(char* Src){
    getText(Src,6);
    for(int i = 0; i < 3; i++) if(esLetra(Src[i]) == 0) return 0;
    for(int i = 3; i < 5; i++) if(esNumero(Src[i]) == 0) return 0;
    Src[7] = '\0'; 
    return 1;
}

int evaluarExistencia(char* Src){

}

int evaluarPrecio(char* Src){

}

int evaluarUbicacion(char* Src){
    
}