#include "../IO.h"

int len(char* text){
    int i = 0;
    while(*text++ != '\0') i++;
    return i;
}