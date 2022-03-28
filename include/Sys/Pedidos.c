#include "../sys.h"

struct Detalle{
    char nombre[7];
    int cantidad;  

    struct Detalle* next;
};

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

struct Detalle* newDetalle(){
    struct Detalle* temp = (struct Detalle*)calloc(1, sizeof(struct Detalle));
    if(temp == NULL) return NULL;
    temp->next = NULL;
    temp->cantidad = 0;
}

int getCarritoSize(struct Carrito* Src){
    if(Src == NULL) return -1;
    return Src->size;
}

struct Detalle* getDetalle(struct Carrito* Src, int index){
    if(Src == NULL) return NULL;
    if(index > getCarritoSize(Src) || index < 0) return NULL;

    Src->temp = Src->Head;
    while(index >= 1){
        Src->temp = Src->temp->next;
        index -= 1;
    }

    return Src->temp;
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
    strcpy(new->nombre,nombre);
    new->cantidad = cantidad;

    return appendDetalle(new,Dest);
}

struct Pedido{
    int numero;
    char estado;
    char* nombre_de_cliente;
    char* telefono_de_cliente;
    char* correo;
    
    struct Carrito* Carrito;

    struct Pedido* next;
};

struct Pedidos{
    struct Pedido* Head;
    struct Pedido* temp;
    int size;
};

struct Pedidos* newPedidos(){
    struct Pedidos* temp = (struct Pedidos*)calloc(1,sizeof(struct Pedidos));
    if(temp == NULL) return NULL;
    temp->Head = NULL;
    temp->size = 0;
    temp->temp = NULL;
}

struct Pedido* newPedido(){
    struct Pedido* temp = (struct Pedido*)calloc(1, sizeof(struct Pedido));
    if(temp == NULL) return NULL;
    temp->next = NULL;
    return temp;
}

int getPedidosSize(struct Pedidos* Src){
    if(Src == NULL) return -1;
    return Src->size;
}

struct Pedido* getPedido(struct Pedidos* Src, int index){
    if(Src == NULL) return NULL;
    if(index > getPedidosSize(Src) || index < 0) return NULL;

    Src->temp = Src->Head;
    while(index >= 1){
        Src->temp = Src->temp->next;
        index -= 1;
    }

    return Src->temp;
}

int appendPedido(struct Pedido* Src, struct Pedidos* Dest){
    if(Dest == NULL) return ERROR;

    if(getPedidosSize(Dest) == 0){
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

int savePedidos(struct Pedidos* Src){
    if(Src == NULL) return ERROR;
    FILE* file = fopen("Pedidos", "wb");

    if(file == NULL) return ERROR;
    for(int i = 0; i < getPedidosSize(Src); i++){
        fwrite(getPedido(Src,i), sizeof(struct Pedido),1,file);
    }

    fclose(file);
    return OK;
}

int loadPedidos(struct Pedidos* Dest){
    if(Dest == NULL) return ERROR;

    FILE* file = fopen("Almacen", "rb");
    if(file == NULL) return ERROR;

    struct Pedido* buffer;
    buffer = newPedido();

    while(fread(buffer, sizeof(struct Pedido),1,file) == 1){
        buffer->next = NULL;
        appendPedido(buffer,Dest);
        buffer = newPedido();
    }

    fclose(file);
    return OK;
}

int addPedido(struct Pedidos* Dest, char estado, char* nombre_del_cliente, char* telefono_del_cliente, char* correo, struct Carrito* Carrito){
    struct Pedido* new = newPedido();
    if(new == NULL) return ERROR;
    new->estado = estado;
    strcpy(new->nombre_de_cliente,nombre_del_cliente);
    strcpy(new->telefono_de_cliente, telefono_del_cliente);
    strcpy(new->correo,correo);
    new->Carrito = Carrito;

    return appendPedido(new,Dest);
}

void registrarPedido(){}
void consultarPedido(){}