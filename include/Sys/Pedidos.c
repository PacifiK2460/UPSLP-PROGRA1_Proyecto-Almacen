#include "../sys.h"

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

int getPedidosSize(struct Pedidos* Src){
    if(Src == NULL) return -1;
    return Src->size;
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

int addPedido(struct Pedidos* Dest, char estado, char* nombre_del_cliente, char* telefono_del_cliente, char* correo, struct Carrito* Carrito, int id){
    struct Pedido* new = newPedido();
    if(new == NULL) return ERROR;
    new->estado = estado;
    strcpy(new->nombre_de_cliente,nombre_del_cliente);
    strcpy(new->telefono_de_cliente, telefono_del_cliente);
    strcpy(new->correo,correo);
    new->Carrito = Carrito;
    new->numero = id;

    return appendPedido(new,Dest);
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