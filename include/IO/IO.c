#include "../IO.h"

#define MAX_TEXT_LENGTH 51

//TODO #6 change inputh method to work in min-max ranges

int esNumero(char numero){
    return (numero >= '0' && numero <= '9');
}

int esLetra(char letra){
    return ( (letra >= 'a' && letra <= 'z') || (letra >= 'A' && letra <= 'Z') );
}

//Caracteres de la tabla ASCII que podrian usarse en texto.
int getText(char* Dest, int size){
    //getwchar();
    char c;
    int longitudActual = 0;
    while(longitudActual < size){
        c = getchar();
        if(c >= '!' && c <= '~'){
            Dest[longitudActual++] = c;
            continue;
        } else if (c == 10) return longitudActual;
        return -1;
    }
    while ((c = getchar()) != 10);
    return -1;

}

// int getOnlyText(char* Dest, int size){
//     //getwchar();
//     char c;
//     int i = 0;
//     while(i < size){
//         c = getchar();
//         if(esLetra(c) == 1){
//             Dest[i++] = c;
//             continue;
//         } else if (c == 10) return 1;
//         return 0;
//     }
//     while ((c = getchar()) != 10);
//     return 0;
// }

// int getAll(char* Dest, int size){
//     //getwchar();
//     char c;
//     int i = 0;
//     while(i < size){
//         c = getchar();
//         if(c != 10){
//             Dest[i++] = c;
//             continue;
//         }
//         return 1;
//     }
//     while ((c = getchar()) != 10);
//     return 0;
// }

// int getInt(char* Dest, int size){
//     //getwchar();
//     char c;
//     int i = 0;
//     while(i < size){
//         c = getchar();
//         if(esNumero(c) == 1){
//             Dest[i++] = c;
//             continue;
//         } else if (c == 10) return 1;
//         return 0;
//     }
//     while ((c = getchar()) != 10);
//     return 0;
// }

// int getDouble(char* Dest, int size){
//     //getwchar();
//     char c;
//     char p = 0;
//     int i = 0;
//     while(i < size){
//         c = getchar();
//         if(esNumero(c) == 1 || c == '.'){

//             if(c == '.') p++;
//             if(p > 1) return 0;

//             Dest[i++] = c;
//             continue;
//         } else if (c == 10) {
//             Dest[i] = '\0';
//             return 1;
//         }
//         return 0;
//     }
//     while ((c = getchar()) != 10);
//     return 0;
// }

int evaluarNombreDeProducto(char* Src){
    int size = MAX_TEXT_LENGTH;
    if(getText(Src,size - 1) == 0) return 0;
    Src[size] = '\0'; 

    //REGLAS ESPECIFICADAS EN EL DOCUMENTO
    for(int i = 0; i < 3; i++) if(esLetra(Src[i]) == 0) return 0;
    for(int i = 3; i < 6; i++) if(esNumero(Src[i]) == 0) return 0;
    return 1;
}

int evaluarNombreDelCliente(char* Src){
    int size = MAX_TEXT_LENGTH;
    if(getText(Src,size - 1) == 0) return 0;
    Src[size] = '\0'; 

    //EL NOMBRE SOLO PUEDE SER TEXTO
    for(int i = 0; i < MAX_TEXT_LENGTH-1; i++) if(esLetra(Src[i]) == 0) return 0;
    return 1;
}

int evaluarExistencia(char* Src){
    int size = 11;
    if(getText(Src,size - 1)==0)return 0;
    for(int i = 0; i < 11-1; i++) if(esNumero(Src[i]) == 0) return 0;
    Src[size] = '\0';
    return 1;
}

int evaluarPrecio(char* Src){
    int size = 11;
    if(getText(Src,size - 1)==0)return 0;
    for(int i = 0; i < 11-1; i++) if(esNumero(Src[i]) == 0 || Src[i] != '.') return 0;
    Src[size] = '\0';
    return 1;
}

int evaluarUbicacion(char* Src){
    if(getText(Src,2)==0)return 0;
    for(int i = 0; i < 2-1; i++) if(esLetra(Src[i]) == 0) return 0;
    Src[1] = '\0';
    return 1;
}

int evaluarNumero(char* Src){
    if(getText(Src,11 - 1)==0)return 0;
    for(int i = 0; i < 11-1; i++) if(esNumero(Src[i]) == 0) return 0;
    Src[11] = '\0';
    return 1;
}

int evaluarCorreo(char* Dest){
    return getText(Dest, 51);
}