#include "../IO.h"

int len(char* text){
    int i = 0;
    while(*text++ != '\0') i++;
    return i;
}
char * cp(char* dest, char* src){
    if(dest == NULL || src == NULL) return NULL;
    char *temp = dest;
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

char* _int2str(int src, char* dest){
    /*
    El unico bug encontrado es cuando el numero empieza en 0
        750:
        i = 0
            750/10:         75 > 0
                75/10:      07 > 0
                    7/10:   0 == 0
                    dest[i++] = (7)%10  (7)
                dest[i++] = (75)%10     (5)
            dest[i++] = (750)%10        (0)
        dest = "750"
    */
    if((src/10) != 0) dest = _int2str(src/10,dest);
    *dest = (src%10) + '0';
    return ++dest;
}

char* int2str(int src){
    //30 caracteres es lo maximo de una maquina de 64bits + margen de error
    char* dest = (char*)malloc(30 * sizeof(char));
    _int2str(src,dest);
    return dest; 
}

char* double2str(double src){
    // Me encontre con el problema de que los double
    // se convierten en notación cientifica, no voy
    // a reinventar la rueda para este.
    char* dest = (char*)malloc(30 * sizeof(char));
    snprintf(dest,29,"%f",src);
    return dest; 
}