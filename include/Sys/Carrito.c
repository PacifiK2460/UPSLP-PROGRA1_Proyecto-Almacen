#include "../sys.h"

struct Carrito{
    struct Detalle* Head;
    struct Detalle* temp;
    int size;
};

struct Carrito* newCarrito(){
    struct Carrito* temp = (struct Carrito*)calloc(1,sizeof(struct Carrito));
    if(temp == NULL) return NULL;
    temp->Head = NULL;
    temp->temp = NULL;
    temp->size = 0;

    return temp;
}

int getCarritoSize(struct Carrito* Src){
    if(Src == NULL) return -1;
    return Src->size;
}

struct Detalle{
    char nombre[7];
    int cantidad;

    struct Detalle* next;
};

struct Detalle* newDetalle(){
    struct Detalle* temp = (struct Detalle*)calloc(1, sizeof(struct Detalle));
    if(temp == NULL) return NULL;
    temp->next = NULL;
    temp->cantidad = 0;
}

struct Detalle* getDetalleByIndex(struct Carrito* Src, int index){
    if(Src == NULL) return NULL;
    if(index > getCarritoSize(Src) || index < 0) return NULL;

    Src->temp = Src->Head;
    while(index >= 1){
        Src->temp = Src->temp->next;
        index -= 1;
    }

    return Src->temp;
}

char* getDetalleNombre(struct Detalle* Src){
    return Src->nombre;
}

int getDetalleCantidad(struct Detalle* Src){
    return Src->cantidad;
}

int appendDetalle(struct Detalle* Src, struct Carrito* Dest){
    if(Dest == NULL) return ERROR;

    if(getCarritoSize(Dest) == 0){
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

int addDetalle(struct Carrito* Dest, char* nombre, int cantidad){
    struct Detalle* new = newDetalle();
    if(new == NULL) return ERROR;
    cp(new->nombre,nombre);
    new->cantidad = cantidad;

    return appendDetalle(new,Dest);
}