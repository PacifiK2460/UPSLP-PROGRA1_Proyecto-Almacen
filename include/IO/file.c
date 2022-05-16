#include "../IO.h"

int getFileLines(char* filename){
    int rows = 0;
    FILE* file;
    file = fopen(filename,"r+");
    if(file == NULL){
        return -1;
    }

    for(char temp; fscanf(file,"%c",&temp) == 1;  ){
        if(temp == '\n') rows++;
    }

    fclose(file);
    return rows;
}