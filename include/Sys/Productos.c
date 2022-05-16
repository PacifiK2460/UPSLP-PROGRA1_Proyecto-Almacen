#include "../sys.h"

int getAlmacenSize(){
    return getFileLines("Almacen");
}

int loadAlmacenFile(Producto Destination[]){
    FILE* file;
    int fila = 0;
    file = fopen("Almacen", "r+");
    if(file == NULL) return -1;

    for(Producto Temp; fscanf(file,"%6s %i %lf %c", Temp.nombre, &Temp.existentes,&Temp.precioUnitario, &Temp.estante) == 4; ){
        Destination[fila].existentes = Temp.existentes;
        Destination[fila].precioUnitario = Temp.precioUnitario;
        Destination[fila].estante = Temp.estante;
        strcpy(Destination[fila].nombre, Temp.nombre);
        fila++;
    }

    fclose(file);
    return 1;
}

int saveAlmacenFile(Producto Source[], int filas){
    remove("Almacen");
    FILE* file;
    file = fopen("Almacen", "w+");
    if(file == NULL) return -1;
    for(int fila = 0; fila < filas; fila++){
        fprintf(file,"%6s %i %lf %c\n", Source[fila].nombre, Source[fila].existentes,
        Source[fila].precioUnitario, Source[fila].estante);
    }
    fclose(file);
    return 1;
}

int appendAlmacenProduct(char* nombre, int existentes, double precio, char estante){
    FILE* file;
    int fila = 0;
    file = fopen("Almacen", "a");
    if(file == NULL) return -1;

    fprintf(
        file,"%6s %i %lf %c\n",nombre,existentes,precio,estante);

    fclose(file);
    return 1;
}

Producto getProductoByName(char* name){
    Producto ProductoBuffer[getAlmacenSize()];
    //Por ahora no checamos ni regresamos en caso de error
    loadAlmacenFile(ProductoBuffer);

    for(int i = 0; i < getAlmacenSize(); i++){
        if(strcmp(ProductoBuffer[i].nombre, name) == 0){
            return ProductoBuffer[i];
        }
    }
    Producto nul;
    nul.existentes = -1;
    return nul;
}