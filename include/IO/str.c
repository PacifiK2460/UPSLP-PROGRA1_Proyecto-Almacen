#include "../IO.h"

void int2str(int src, char* dest){
    snprintf(dest,29,"%i",src);
}

void double2str(double src, char* dest){
    snprintf(dest,29,"%.2f",src);
}
