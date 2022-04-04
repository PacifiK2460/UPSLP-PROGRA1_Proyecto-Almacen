#include "../sys.h"

// Estructuras de la interfaz
struct Producto{
    char nombre[7];
    int existentes;
    double precioUnitario;
    char estante;

    struct Producto* next;
};

struct Producto* newProducto(){
    struct Producto* temp = (struct Producto*)calloc(1,sizeof(struct Producto));
    if(temp == NULL) return NULL;
    temp->next = NULL;
    return temp;
}

struct Producto* getProductoByName(struct Productos* Src, char* name){
    for(int i = 0; i < getProductosSize(Src); i++){
        if( strcmp( getProductoName(getProductoByIndex(Src,i)),name ) == 0) return getProductoByIndex(Src,i);
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