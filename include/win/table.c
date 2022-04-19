#include "../win.h"

struct TABLE{
    int columas, filas;
    //Bidimencional: texto mas largo por columna
    int* textoMasLargo;
    //Tridimencional: columna, fila y texto
    int total;
    int toalTeorico;
};

int getTotal(TABLE* src){
    return src->total;
}

int getTotalToerico(TABLE* src){
    return src->toalTeorico;
}

TABLE* newTable(int columnas, int filas, char* data[filas][columnas]){
    TABLE* table = malloc(sizeof(struct TABLE*));
    table->columas = columnas;
    table->filas = filas;
    table->total = 0;
    table->toalTeorico = 0;

    table->textoMasLargo = malloc(columnas * sizeof(int*));
    for(int i = 0; i<columnas;i++) table->textoMasLargo[i] = 0;
    for(int i = 0; i < filas+1; i++){
        for(int j = 0; j < columnas; j++){
            int tam = len(data[i][j]); 
            if(tam > table->textoMasLargo[j]) table->textoMasLargo[j] = tam;
        }
    }

    for(int i = 0; i < columnas; i++){
        table->total += len(BOLD FRGB(185, 251, 192));
        table->total += table->textoMasLargo[i];
        table->total += len(RESET);
        table->total += len(" " VLINE " ");

        table->toalTeorico += table->textoMasLargo[i];
    }

    return table;
}

void prepareTableData(int fila, int columna, char* headers[],char* dest[fila][columna]){
    for(int i = 0; i < fila; i++){
        for(int j = 0; j < columna; j++){
            dest[i][j] = headers[j];
        }
    }
}

void setTableData(char* dest, char* src){
    //dest[fila][columna] = malloc(len(src) * sizeof(char));
    dest = src;
    //cp(dest[fila][columna], src);
}

void printTable(TABLE* table, int x, int y,int fil, int cols, char* data[fil][cols]){
    for(int j = 0; j < table->filas+1; j++){
        char* headerbuff = (char*)malloc(table->total * sizeof(char));
        //for(int _ = 0; _ < table->total; _++ ) headerbuff[_] = '\0';
        for(int i = 0; i < table->columas; i++){
            char* colbuff = (char*)malloc(table->total * sizeof(char));
            //for(int _ = 0; _ < table->total; _++ ) colbuff[_] = '\0';
            if(j == 0)
                snprintf(colbuff,table->total,BOLD FRGB(185, 251, 192) "%*s" RESET, table->textoMasLargo[i], data[j][i]);
            else
                snprintf(colbuff,table->total,DIM  FRGB(185, 251, 192) "%*s" RESET, table->textoMasLargo[i], data[j][i]);
            strcat(headerbuff,colbuff);
            if(i+1 < table->columas) strcat(headerbuff," " VLINE " ");
            free(colbuff);
        }
        winprint(STDOUTPUT,x,y + j,headerbuff);
        free(headerbuff);
    }
}

void freeTable(TABLE *src){
    free(src->textoMasLargo);
    //free(src);
}