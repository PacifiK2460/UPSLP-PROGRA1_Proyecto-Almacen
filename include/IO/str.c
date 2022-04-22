#include "../IO.h"

int stringlen(char* text){
    int i = 0;
    while(*text++ != '\0') i++;
    return i;
}

char* cp(char* dest, char* src){
    char *temp = dest;
    while((*temp++=*src++) != '\0');
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

void int2str(int src, char* dest){
    snprintf(dest,29,"%i",src);
}

void double2str(double src, char* dest){
    // Me encontre con el problema de que los double
    // se convierten en notación cientifica, no voy
    // a reinventar la rueda para este.
    snprintf(dest,29,"%.2f",src);
}

char* cat(char* dest, char* src){
    int i = 0,j = 0;
    for (i = 0; dest[i] != '\0'; i++);
    for (j = 0; src[j] != '\0'; j++)
        dest[i+j] = src[j];
    dest[i+j] = '\0';
    return dest;
}