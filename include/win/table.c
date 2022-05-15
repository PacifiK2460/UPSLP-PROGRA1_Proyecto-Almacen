#include "../win.h"

typedef struct FILA{
    char** columna;
}FILA;

int getTotal(TABLE* src){
    return src->total;
}

int getTotalToerico(TABLE* src){
    return src->toalTeorico;
}

// TABLE* newTable(int columnas, int filas){
//     TABLE* table = malloc(sizeof(TABLE));
//     table->columas = columnas;
//     table->filas = filas;
//     table->total = 0;
//     table->toalTeorico = 0;
//     table->currentFilledRow = 0;
//     table->textoMasLargo = malloc(columnas * sizeof(int));
//     for(int i = 0; i < table->columas; i++) table->textoMasLargo[i] = 0;
//     //table->data = allocRows(filas);
//     table->data = malloc(filas * sizeof(FILA));
    
//     for(int fil = 0; fil < filas; fil++){
//         table->data[fil].columna = malloc(table->columas * sizeof(char*));
//         for(int col = 0; col < columnas; col++){
//             table->data[fil].columna[col] = malloc(51);
//         }
//     }
//     return table;
// }

void tableSetHeaders(TABLE *src,char** headers){
    //free(src->headers);
    for(int col = 0; col < src->columas; col++){
        strcpy(src->headers[col], headers[col]);
    }
}

void tableAppendRow(TABLE *src, ...){
    //si nos pasamos, no hacemos nada
    if(src->currentFilledRow > src->filas) return;
    
    va_list column;
    va_start(column,src);

    //src->data = malloc(src->filas * sizeof(src->data));
    //Obtenemos memoria para almacenar la fila
    //currentRow->columna = malloc(src->columas * sizeof(char**));
    
    for(int col=0; col < src->columas; col++){
        //Obtenemos memoria para guardar la string de la columna y fila actual
        //currentRow->columna[col] = malloc(sizeof(char*));
        //Guardamos cada str en la columna
        //char* watch = va_arg(column,char*);
        strcpy(src->data[src->currentFilledRow].columna[col], va_arg(column, char*));
        //src->data[src->currentFilledRow].columna[col] = watch;
        //watch =  src->data[src->currentFilledRow].columna[col];
    }

    //Aumentamos el index fila vacia
    src->currentFilledRow++;
    va_end(column);
}

void tablePrepareDataAling(TABLE *src){
    //Headers
    for(int col = 0; col < src->columas; col++){
        int tam = strlen(src->headers[col]);
        if(tam > src->textoMasLargo[col])
            src->textoMasLargo[col] = tam;
    }
    
    for(int fila = 0; fila < src->filas; fila++){
        //Obtengo la fila
        FILA _fila = src->data[fila];
        for(int col = 0; col < src->columas; col++){
            int coltotal = 0;
            //De cada fila, voy columna por columna
            char* temp = _fila.columna[col];
            int tam = strlen(_fila.columna[col]);
            //Saco el largo de cada columna
            if(tam > src->textoMasLargo[col])
                src->textoMasLargo[col] = tam;

            //Información que nos ayudará a alinear la tabla
            
            coltotal += strlen(BOLD FRGB(185, 251, 192));
            coltotal += src->textoMasLargo[col];
            coltotal += strlen(RESET);
            coltotal += strlen(" " VLINE " ");

            src->total += strlen(BOLD FRGB(185, 251, 192));
            src->total += src->textoMasLargo[col];
            src->total += strlen(RESET);
            src->total += strlen(" " VLINE " ");

            if(coltotal > src->toalTeorico) src->toalTeorico = coltotal;
            //src->toalTeorico += src->textoMasLargo[col];
        }
    }
}

void prepareTableData(TABLE* table, int columnas, int filas){
    table->columas = columnas;
    table->filas = filas;
    table->total = 0;
    table->toalTeorico = 0;
    table->currentFilledRow = 0;

    table->textoMasLargo = malloc(columnas * sizeof(int));
    for(int i = 0; i < columnas; i++) table->textoMasLargo[i] = 0;
    
    table->headers = malloc(columnas * sizeof(char*));
    for(int col = 0; col < table->columas; col++){
        table->headers[col] = malloc(30);
    }

    table->data = malloc(filas * sizeof(FILA));
    
    for(int fil = 0; fil < filas; fil++){
        table->data[fil].columna = malloc(table->columas * sizeof(char*));
        for(int col = 0; col < columnas; col++){
            table->data[fil].columna[col] = malloc(51);
        }
    }
}

void setTableData(char* dest, char* src){
    //dest[fila][columna] = malloc(len(src) * sizeof(char));
    dest = src;
    //strcpy(dest[fila][columna], src);
}

void printTable(TABLE* table, int x, int y){

    tablePrepareDataAling(table);
    
    if(x == -1) x = (getcols(STDOUTPUT) - table->toalTeorico)/2;
    
    //Headers
    {
        char* rowbuffer = malloc(table->total * sizeof(char));
        for(int i = 0; i < table->total; i++) rowbuffer[i] = '\0';

        for(int col = 0; col < table->columas; col++){

            char* colbuffer = malloc(table->total * sizeof(char));
            for(int i = 0; i < table->total; i++) colbuffer[i] = '\0';
            
            snprintf(colbuffer,
                table->total-1,
                BOLD FRGB(185, 251, 192) "%*s" RESET,
                table->textoMasLargo[col],
                table->headers[col]
            );

            strcat(rowbuffer,colbuffer);
            if(col+1 < table->columas)
                strcat(rowbuffer, " " VLINE " ");
            
            free(colbuffer);
        }
        winprint(STDOUTPUT,x,y++,rowbuffer);
        free(rowbuffer);
    }

    //Rows
    {
        for(int row = 0; row < table->filas; row++){
            char* rowbuffer = malloc(table->total * sizeof(char));
            for(int i = 0; i < table->total; i++) rowbuffer[i] = '\0';
            
            for(int col = 0; col < table->columas; col++){

                char* colbuffer = malloc(table->total * sizeof(char));
                for(int i=0; i < table->total; i++) colbuffer[i] = '\0';

                //char* watch= table->data[row].columna[col];
             
                snprintf(colbuffer,
                    table->total-1,
                    DIM FRGB(185, 251, 192) "%*s" RESET,
                    table->textoMasLargo[col],
                    table->data[row].columna[col]
                );

                strcat(rowbuffer,colbuffer);
                if(col+1 < table->columas){
                    strcat(rowbuffer, " " VLINE " ");
                }

                free(colbuffer);
            }
            winprint(STDOUTPUT,x,y++,rowbuffer);
            free(rowbuffer);
        }
    }

}

void freeTable(TABLE *src){
    //free(src->headers);
    free(src->textoMasLargo);

    for(int i=0; i < src->columas; i++){
        free(src->headers[i]);
    }
    free(src->headers);

    for(int i=0; i < src->filas; i++){
        for(int j=0; j < src->columas; j++){
            free(src->data[i].columna[j]);
        }
        free(src->data[i].columna);
        //free(src->data[i]);
    }
    free(src->data);

}