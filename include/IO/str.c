#include "../IO.h"

int len(char* text){
    int i = 0;
    while(*text++ != '\0') i++;
    return i;
}
char * cp(char* dest, char* src){
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
int _int2str(int src, char* dest){
    if((src/10) != 0) dest += _int2str(src/10,dest);
    *dest = (src%10) + '0';
    return 1;
}
char* int2str(int src){
    char* dest = (char*)malloc(30 * sizeof(char));
    for(int i=0; i< 30; i++) dest[i] = '\0';
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

char * strcat(char *dest, char *src){
    int i = 0,j = 0;
    for (i = 0; dest[i] != '\0'; i++);
    for (j = 0; src[j] != '\0'; j++)
        dest[i+j] = src[j];
    dest[i+j] = '\0';
    return dest;
}