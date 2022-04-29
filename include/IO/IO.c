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

int evaluarNombreDeProducto(char* Src){
    int size = MAX_TEXT_LENGTH;
    if( scanf("%6s", Src) == 0 ) return 0;
    //if(getText(Src,size - 1) == 0) return 0;
    Src[size] = '\0'; 

    //REGLAS ESPECIFICADAS EN EL DOCUMENTO
    for(int i = 0; i < 3; i++) if(esLetra(Src[i]) == 0) return 0;
    for(int i = 3; i < 6; i++) if(esNumero(Src[i]) == 0) return 0;
    return 1;
}

int evaluarNombreDelCliente(char* Src){
    int size = MAX_TEXT_LENGTH;
    if(scanf("%51s", Src) == 0) return 0;
    Src[size] = '\0'; 

    //EL NOMBRE SOLO PUEDE SER TEXTO
    for(int i = 0; Src[i] != '\0'; i++) if(esLetra(Src[i]) == 0) return 0;
    return 1;
}

int evaluarExistencia(char* Src){
    int size = 11;
    int temp;
    if( scanf("%ui", &temp) == 0 ) return 0;
    snprintf(Src, size-1, "%i", temp);
    Src[size] = '\0';
    return 1;
}

int evaluarPrecio(char* Src){
    int size = 11;
    int temp;
    if(scanf("%ui", &temp)==0)return 0;
    snprintf(Src, size-1, "%i", temp);
    Src[size] = '\0';
    return 1;
}

int evaluarUbicacion(char* Src){
    if(scanf("%1s", Src)==0) return 0;
    for(int i = 0; i < 2-1; i++) if(esLetra(Src[i]) == 0) return 0;
    Src[1] = '\0';
    return 1;
}

int evaluarNumero(char* Src){
    int temp;
    if(scanf("%ui",&temp)==0)return 0;
    snprintf(Src, 10,"%i", temp);
    Src[10] = '\0';
    return 1;
}

int evaluarCorreo(char* Dest){
    char c = scanf("%s", Dest);
    return c;
}