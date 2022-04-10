#include "../IO.h"

int len(char* text){
    int i = 0;
    while(*text++ != '\0') i++;
    return i;
}
char * cp(char* dest, char* src){
    if(dest == NULL || src == NULL) return NULL;
    while((*dest++=*src++) != '\0');
    return dest;
}
int cmp(char* dest, char* src){
    while(*dest && (*dest == *src))
    {
        dest++;
        src++;
    }
    return *(char*)dest - *(char*)src;
}

char* int2str(int src){
    //30 caracteres es lo maximo de una maquina de 64bits + margen de error
    char* dest = (char*)malloc(30 * sizeof(char));


    return dest; 
}

char* double2str(double src){
    char* dest = (char*)malloc(30 * sizeof(char));

    

    return dest; 
}