#include "../win.h"

struct TABLE{
    int x, y;
    int columas, filas;
    //Bidimencional: texto mas largo por columna
    int* textoMasLargo;
    //Tridimencional: columna, fila y texto
    char*** data;
};

TABLE* newTable(int x, int y, int columnas, int filas, char*** data){
    TABLE* table = (struct TABLE*)calloc(1,sizeof(struct TABLE));
    table->columas = columnas;
    table->filas = filas;
    table->data = data;
    table->x = x;
    table->y = y;

    table->textoMasLargo = malloc(columnas * filas * sizeof(int));
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(len(data[i][j]) > table->textoMasLargo[j]) table->textoMasLargo[j] = len(data[i][j]);
        }
    }

    return table;
}