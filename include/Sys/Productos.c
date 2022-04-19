#include "../sys.h"

// Estructuras de la interfaz
struct Producto{
    char nombre[7];
    int existentes;
    double precioUnitario;
    char estante;

    struct Producto* next;
};

struct Producto* getProductoByName(struct Productos* Src, char* name){
    for(int i = 0; i < getProductosSize(Src); i++){
        if( cmp( getProductoName(getProductoByIndex(Src,i)),name ) == 0) return getProductoByIndex(Src,i);
    }
    return NULL;
}

char* getProductoName(struct Producto* Src){
    return Src->nombre;
}

int getProductoExistentes(struct Producto* Src){
    return Src->existentes;
}

double getProductoPrecio(struct Producto* Src){
    return Src->precioUnitario;
}

char getProductoEstante(struct Producto* Src){
    return Src->estante;
}

struct Productos{
    struct Producto* Head;
    struct Producto* temp;
    int size;
};

int getProductosSize(struct Productos* Src){
    if(Src == NULL) return ERROR;
    return Src->size;
}

int modExistencia(struct Productos* Src, int index,int cant,char op){
    if(Src == NULL) return ERROR;
    if(index > getProductosSize(Src) || index < 0) return ERROR;

    Src->temp = Src->Head;
    while(index > 0){
        Src->temp = Src->temp->next;
        index -= 1;
    }

    if(op == 'A') Src->temp->existentes += cant;
    else if(op == 'S') Src->temp->existentes = cant;
    else return ERROR;

    return OK;
}

int addProduct(struct Productos* Dest,char* nombre, int existentes, double precio, char estante){
    struct Producto* new = newProducto();
    if(new == NULL) return ERROR;
    cp(new->nombre, nombre);
    new->existentes = existentes;
    new->precioUnitario = precio;
    new->estante = estante;
    return appendProduct(new,Dest);
}

int loadAlmacen(struct Productos* Dest){
    if(Dest == NULL) return ERROR;

    FILE* file = fopen("Almacen", "r");
    if(file == NULL){
        return ERROR;
    }

    struct Producto* buffer;
    buffer = newProducto();

    while(file != EOF){
        fscanf(file,"%.7s %i %d %c", &buffer->nombre, &buffer->existentes, &buffer->precioUnitario, &buffer->estante);
        buffer->next = NULL;
        appendProduct(buffer,Dest);
        free(buffer);
        buffer = newProducto();
    }

    // while(fread(buffer,sizeof(struct Producto),1,file) == 1){
    //     buffer->next = NULL;
    //     appendProduct(buffer,Dest);
    //     free(buffer);
    //     buffer = newProducto();
    // }

    free(buffer);
    fclose(file);
    return OK;
}

int saveAlmacen(struct Productos* Dest){
    if(Dest == NULL) return ERROR;
    FILE* file = fopen("Almacen","w");

    if(file == NULL) return ERROR;
    struct Producto* buffer;
    for(int i = 0; i < getProductosSize(Dest); i++){
        getProductoByIndex(buffer,i);
        fprintf(file,"%.7s %i %d %c",buffer->nombre, buffer->existentes, buffer->precioUnitario, buffer->estante);
        //fwrite(getProductoByIndex(Dest,i),sizeof(struct Producto),1,file);
    }

    fclose(file);
    return OK;
}

struct Producto* getProductoByIndex(struct Productos* Src, int index){
    if(Src == NULL) return NULL;
    if(index > getProductosSize(Src) || index < 0) return NULL;
    if(index == 0) return Src->Head;

    Src->temp = Src->Head;
    while (index >= 1){
        Src->temp = Src->temp->next;
        index -= 1;
    }

    return Src->temp;
}

int appendProduct(struct Producto* Src, struct Productos* Dest){
    if(Dest == NULL) return ERROR;

    if(getProductosSize(Dest) == 0){
        Dest->Head = Src;
        Dest->size += 1;
        return OK;
    }

    Dest->temp = Dest->Head;
    while(Dest->temp->next != NULL) Dest->temp = Dest->temp->next;

    Dest->temp->next = Src;
    Dest->size += 1;

    return OK;
}