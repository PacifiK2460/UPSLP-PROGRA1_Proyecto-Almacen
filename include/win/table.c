#include "../win.h"

struct TABLE{
    int columas, filas;
    //Bidimencional: texto mas largo por columna
    int* textoMasLargo;
    //Tridimencional: columna, fila y texto
    char*** data;
    int total;
    int toalTeorico;
};

int getTotal(TABLE* src){
    return src->total;
}

int getTotalToerico(TABLE* src){
    return src->toalTeorico;
}

TABLE* newTable(int columnas, int filas, char*** data){
    TABLE* table = (struct TABLE*)calloc(1,sizeof(struct TABLE));
    table->columas = columnas;
    table->filas = filas;
    table->data = data;
    table->total = 0;
    table->toalTeorico = 0;

    table->textoMasLargo = malloc(columnas * sizeof(int));
    for(int i = 0; i<columnas;i++) table->textoMasLargo[i] = 0;
    for(int i = 0; i < filas+1; i++){
        for(int j = 0; j < columnas; j++){
            if(len(data[i][j]) > table->textoMasLargo[j]) table->textoMasLargo[j] = len(data[i][j]);
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

char* ** prepareTableData(int fila, int columna, char* headers[]){
    char*** data = malloc(fila * sizeof(char));
    for(int i = 0; i < fila; i++){
        data[i] = malloc(columna * sizeof(char));
    }
    for(int j = 0; j < columna; j++){
        data[0][j] = headers[j];
    }
    return data;
}

void setTableData(int fila, int columna, char*** dest, char* src){
    //dest[fila][columna] = malloc(len(src) * sizeof(char));
    dest[fila][columna] = src;
    //cp(dest[fila][columna], src);
}

void printTable(TABLE* table, int x, int y){
    for(int j = 0; j < table->filas+1; j++){
        char* headerbuff = (char*)malloc(table->total * sizeof(char));
        for(int _ = 0; _ < table->total; _++ ) headerbuff[_] = '\0';
        for(int i = 0; i < table->columas; i++){
            char* colbuff = (char*)malloc(table->total * sizeof(char));
            for(int _ = 0; _ < table->total; _++ ) colbuff[_] = '\0';
            if(j == 0)
                snprintf(colbuff,table->total,BOLD FRGB(185, 251, 192) "%*s" RESET, table->textoMasLargo[i], table->data[j][i]);
            else
                snprintf(colbuff,table->total,DIM  FRGB(185, 251, 192) "%*s" RESET, table->textoMasLargo[i], table->data[j][i]);
            strcat(headerbuff,colbuff);
            if(i+1 < table->columas) strcat(headerbuff," " VLINE " ");
            
        }
        winprint(STDOUTPUT,x,y + j,headerbuff);
    }
}