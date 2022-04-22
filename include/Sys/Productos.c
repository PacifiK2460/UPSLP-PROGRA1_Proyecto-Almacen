#include "../sys.h"

int getAlmacenSize(){
    return getFileLines("Almacen");
}

int loadAlmacenFile(Producto Destination[]){
    FILE* file;
    int fila = 0;
    file = fopen("Almacen", "w+");
    if(file == NULL) return -1;

    for(Producto Temp; fscanf(file,"%6s %i %lf %c", Temp.nombre, &(Temp.existentes),&(Temp.precioUnitario), &(Temp.estante)) == 4; ){
        Destination[fila].existentes = Temp.existentes;
        Destination[fila].precioUnitario = Temp.precioUnitario;
        Destination[fila].estante = Temp.estante;
        cp(Destination[fila].nombre, Temp.nombre);
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
        if(cmp(ProductoBuffer[i].nombre, name) == 0){
            return ProductoBuffer[i];
        }
    }
}

// Estructuras de la interfaz DEPRECATED 
// struct Producto getProductoByName(struct Productos* Src, char* name){
//     for(int i = 0; i < getProductosSize(Src); i++){
//         if( cmp( getProductoName(getProductoByIndex(Src,i)),name ) == 0) return getProductoByIndex(Src,i);
//     }
//     return NULL;
// }

// char* getProductoName(struct Producto* Src){
//     return Src->nombre;
// }

// int getProductoExistentes(struct Producto* Src){
//     return Src->existentes;
// }

// double getProductoPrecio(struct Producto* Src){
//     return Src->precioUnitario;
// }

// char getProductoEstante(struct Producto* Src){
//     return Src->estante;
// }

// int getProductosSize(struct Productos* Src){
//     if(Src == NULL) return ERROR;
//     return Src->size;
// }

// int modExistencia(struct Productos* Src, int index,int cant,char op){
//     if(Src == NULL) return ERROR;
//     if(index > getProductosSize(Src) || index < 0) return ERROR;

//     Src->temp = Src->Head;
//     while(index > 0){
//         Src->temp = Src->temp->next;
//         index -= 1;
//     }

//     if(op == 'A') Src->temp->existentes += cant;
//     else if(op == 'S') Src->temp->existentes = cant;
//     else return ERROR;

//     return OK;
// }

// int addProduct(struct Productos* Dest,char* nombre, int existentes, double precio, char estante){
//     struct Producto* new = newProducto();
//     if(new == NULL) return ERROR;
//     cp(new->nombre, nombre);
//     new->existentes = existentes;
//     new->precioUnitario = precio;
//     new->estante = estante;
//     return appendProduct(new,Dest);
// }

// int loadAlmacen(struct Productos* Dest){
//     if(Dest == NULL) return ERROR;

//     FILE* file = fopen("Almacen", "r");
//     if(file == NULL){
//         file = fopen("Almacen", "w");
//         if(file == NULL) return ERROR;
//         fclose(file);
//         file = fopen("Almacen", "r");
//         if(file == NULL) return ERROR;
//     }

//     struct Producto* buffer;
//     buffer = (struct Producto*)malloc(sizeof(struct Producto));

//     while(fscanf(file,"%6s %i %lf %c", &(buffer->nombre), &(buffer->existentes), &(buffer->precioUnitario), &(buffer->estante)) == 4){
//         buffer->next = NULL;
//         appendProduct(buffer,Dest);
//         //free(buffer);
//         buffer = (struct Producto*)malloc(sizeof(struct Producto));

//     }

//     free(buffer);
//     fclose(file);
//     return OK;
// }

// int saveAlmacen(struct Productos* Dest){
//     if(Dest == NULL) return ERROR;
//     FILE* file = fopen("Almacen","w");

//     if(file == NULL) return ERROR;
//     struct Producto* buffer;
//     for(int i = 0; i < getProductosSize(Dest); i++){
//         buffer = getProductoByIndex(Dest,i);
//         fprintf(file,"%.7s %i %d %c",buffer->nombre, buffer->existentes, buffer->precioUnitario, buffer->estante);
//         //fwrite(getProductoByIndex(Dest,i),sizeof(struct Producto),1,file);
//     }

//     fclose(file);
//     return OK;
// }

// Producto getProductoByIndex(Productos Src, int index){
//     if(index == 0) return Src.Head;

//     Src.temp = Src.Head;
//     while (index >= 1){
//         Src->temp = Src->temp->next;
//         index -= 1;
//     }

//     return Src->temp;
// }

// int appendProduct(struct Producto* Src, struct Productos* Dest){
//     if(Dest == NULL) return ERROR;

//     if(getProductosSize(Dest) == 0){
//         Dest->Head = Src;
//         Dest->size += 1;
//         return OK;
//     }

//     Dest->temp = Dest->Head;
//     while(Dest->temp->next != NULL) Dest->temp = Dest->temp->next;

//     Dest->temp->next = Src;
//     Dest->size += 1;

//     return OK;
// }