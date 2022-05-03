#include "../IO.h"

int getFileLines(char* filename){
    int rows = 0;
    FILE* file;
    //Si el archivo no existe, crea uno
    //Con w+ podemos leer escribir
    file = fopen(filename,"r+");

    //Como intenta crear un archivo, le hecho de que falle
    //significa que ocurrio algo peor
    if(file == NULL){
        return -1;
    }

    for(char temp; fscanf(file,"%c",&temp) == 1;  ){
        if(temp == '\n') rows++;
    }

    fclose(file);
    return rows;
}