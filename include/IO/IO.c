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

int getInt(char* Dest, int size){
    //getwchar();
    char c;
    int i = 0;
    while(i < size){
        c = getchar();
        if(esNumero(c) == 1){
            Dest[i++] = c;
            continue;
        } else if (c == 10) return 1;
        return 0;
    }
    while ((c = getchar()) != 10);
    return 0;
}

int getDouble(char* Dest, int size){
    //getwchar();
    char c;
    char p = 0;
    int i = 0;
    while(i < size){
        c = getchar();
        if(esNumero(c) == 1 || c == '.'){

            if(c == '.') p++;
            if(p > 1) return 0;

            Dest[i++] = c;
            continue;
        } else if (c == 10) return 1;
        return 0;
    }
    while ((c = getchar()) != 10);
    return 0;
}

int evaluarNombre(char* Src){
    if(getText(Src,size(Src) - 1) == 0) return 0;
    for(int i = 0; i < 3; i++) if(esLetra(Src[i]) == 0) return 0;
    for(int i = 3; i < 5; i++) if(esNumero(Src[i]) == 0) return 0;
    Src[size(Src)] = '\0'; 
    return 1;
}

int evaluarExistencia(char* Src){
    if(getInt(Src,size(Src) - 1)==0)return 0;
    Src[size(Src) - 1] = '\0';
    return 1;
}

int evaluarPrecio(char* Src){
    if(getDouble(Src,size(Src) - 1)==0)return 0;
    Src[size(Src)] = '\0';
    return 1;
}

int evaluarUbicacion(char* Src){
    if(getText(Src,1)==0)return 0;
    Src[2] = '\0';
    return 1;
}

int getNombre(char* Dest){
    //getwchar();
    char c;
    int i = 0;
    while(i < size(Dest)){
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

int getTel(char* Dest){
    //getwchar();
    char c;
    int i = 0;
    while(i < size(Dest)){
        c = getchar();
        if(esNumero(c) == 1){
            Dest[i++] = c;
            continue;
        } else if (c == 10) return 1;
        return 0;
    }
    while ((c = getchar()) != 10);
    return 0;
}

int getCorreo(char* Dest){
    //getwchar();
    char c;
    int i = 0;
    while(i < size(Dest)){
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

int evaluarCorreo(char* Dest){
    return getCorreo(Dest);
}