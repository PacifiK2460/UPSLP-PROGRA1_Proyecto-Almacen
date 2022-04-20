#include "../win.h"

typedef struct FILA{
    char** columna;
}FILA;


struct TABLE{
    int columas, filas;
    int currentFilledRow;
    //Bidimencional: texto mas largo por columna
    int* textoMasLargo;
    //Tridimencional: columna, fila y texto
    int total;
    int toalTeorico;
    char** headers;
    FILA data[];
};

int getTotal(TABLE* src){
    return src->total;
}

int getTotalToerico(TABLE* src){
    return src->toalTeorico;
}

TABLE* newTable(int columnas, int filas){
    TABLE* table = malloc(sizeof(*table) + filas*sizeof(*table->data));
    table->columas = columnas;
    table->filas = filas;

    table->total = 0;
    table->toalTeorico = 0;

    table->currentFilledRow = 0;

    // table->textoMasLargo = malloc(columnas * sizeof(int*));
    // for(int i = 0; i<columnas;i++) table->textoMasLargo[i] = 0;
    // for(int i = 0; i < filas+1; i++){
    //     for(int j = 0; j < columnas; j++){
    //         int tam = len(data[i][j]); 
    //         if(tam > table->textoMasLargo[j]) table->textoMasLargo[j] = tam;
    //     }
    // }

    // for(int i = 0; i < columnas; i++){
    //     table->total += len(BOLD FRGB(185, 251, 192));
    //     table->total += table->textoMasLargo[i];
    //     table->total += len(RESET);
    //     table->total += len(" " VLINE " ");

    //     table->toalTeorico += table->textoMasLargo[i];
    // }

    return table;
}

void tableSetHeaders(TABLE *src,char** headers){
    free(src->headers);
    src->headers = malloc(src->columas*sizeof(char*));
    for(int col = 0; col < src->columas; col++){
        free(src->headers[col]); //borramos por si acaso
        src->headers[col] = malloc(sizeof(char*));
        src->headers[col] = headers[col];
    }
}

void tableAppendRow(TABLE *src, ...){
    //si nos pasamos, no hacemos nada
    if(src->currentFilledRow > src->filas) return;
    
    va_list column;
    va_start(column,src->columas);

    //obtenemos la fila actual que deberia de estar vacia
    FILA* currentRow = &(src->data[src->currentFilledRow]);
    //Despejamos memoria, por si acaso
    free(currentRow);
    //Obtenemos memoria para almacenar la fila
    currentRow = malloc(src->columas * sizeof(char*));
    
    for(int col=0; col < src->columas; col++){
        //Liberamos memoria de la columna actual col de la fila seleccionada
        free(currentRow->columna[col]);
        //Obtenemos memoria para guardar la string de la columna y fila actual
        currentRow->columna[col] = malloc(sizeof(char*));
        //Guardamos cada str en la columna
        currentRow->columna[col] = va_arg(column,char*); 
    }

    //Aumentamos el index fila vacia
    src->currentFilledRow++;
    va_end(column);
}

void tablePrepareDataAling(TABLE *src){
    src->textoMasLargo = malloc(src->columas * sizeof(int*));
    for(int i = 0; i < src->columas; i++) src->textoMasLargo[i] = 0;
    
    //Headers
    for(int col = 0; col < src->columas; col++){
        int tam = len(src->headers[col]);
        if(tam > src->textoMasLargo[col])
            src->textoMasLargo[col] = tam;
    }
    
    for(int fila = 0; fila < src->filas; fila++){
        //Obtengo la fila
        FILA _fila = src->data[fila];
        for(int col = 0; col < src->columas; col++){
            //De cada fila, voy columna por columna
            int tam = len(_fila.columna[col]);
            //Saco el largo de cada columna
            if(tam > src->textoMasLargo[col])
                src->textoMasLargo[col] = tam;

            //Información que nos ayudará a alinear la tabla
            src->total += len(BOLD FRGB(185, 251, 192));
            src->total += src->textoMasLargo[col];
            src->total += len(RESET);
            src->total += len(" " VLINE " ");

            src->toalTeorico += src->textoMasLargo[col];
        }
    }
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

void printTable(TABLE* table, int x, int y){
    tablePrepareDataAling(table);
    //Headers
    {
        char* rowbuffer = malloc(table->total * sizeof(char));
        for(int col = 0; col < table->columas; col++){
            char* colbuffer = malloc(table->total * sizeof(char));
            
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
    }

    //Rows
    {
        for(int row = 0; row < table->filas; row++){
            char* rowbuffer = malloc(table->total * sizeof(char));
            FILA currentRow = table->data[row];
            for(int col = 0; col < table->columas; col++){
                char* colbuffer = malloc(table->total * sizeof(char));
                
                snprintf(colbuffer,
                    table->total-1,
                    DIM FRGB(185, 251, 192) "%*s" RESET,
                    table->textoMasLargo[col],
                    currentRow.columna[col]
                );

                strcat(rowbuffer,colbuffer);
                if(col+1 < table->columas)
                    strcat(rowbuffer, " " VLINE " ");

                free(colbuffer);
            }
            winprint(STDOUTPUT,x,y++,rowbuffer);
            free(rowbuffer);
        }
    }

    // for(int j = 0; j < table->filas+1; j++){
    //     char* headerbuff = (char*)malloc(table->total * sizeof(char));
    //     //for(int _ = 0; _ < table->total; _++ ) headerbuff[_] = '\0';
    //     for(int i = 0; i < table->columas; i++){
    //         char* colbuff = (char*)malloc(table->total * sizeof(char));
    //         //for(int _ = 0; _ < table->total; _++ ) colbuff[_] = '\0';
    //         if(j == 0)
    //             snprintf(colbuff,table->total,BOLD FRGB(185, 251, 192) "%*s" RESET, table->textoMasLargo[i], data[j][i]);
    //         else
    //             snprintf(colbuff,table->total,DIM  FRGB(185, 251, 192) "%*s" RESET, table->textoMasLargo[i], data[j][i]);
    //         strcat(headerbuff,colbuff);
    //         if(i+1 < table->columas) strcat(headerbuff," " VLINE " ");
    //         free(colbuff);
    //     }
    //     winprint(STDOUTPUT,x,y + j,headerbuff);
    //     free(headerbuff);
    // }
}

void freeTable(TABLE *src){
    free(src->textoMasLargo);
    for(int i = 0; i < src->columas; i++) free(src->headers[i]);
    free(src->headers);

    for(int i=0; i<src->filas;i++){
        FILA* cR = &(src->data[i]);
        for(int j = 0; j < src->columas; j++){
            free(cR->columna[j]);
        }
        free(cR);
    }
    free(src->data);
    free(src);
}