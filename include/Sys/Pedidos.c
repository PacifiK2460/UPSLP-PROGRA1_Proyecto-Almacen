#include "../sys.h"

struct Pedido{
    int numero;
    char estado;
    char nombre_de_cliente[51];
    char telefono_de_cliente[11];
    char correo[51];
    
    struct Carrito* Carrito;
    struct Pedido* next;
};

//Get struct info

struct Pedido* newPedido(){
    struct Pedido* temp = (struct Pedido*)calloc(1, sizeof(struct Pedido));
    if(temp == NULL) return NULL;
    temp->next = NULL;
    return temp;
}

int getPedidoNumero(struct Pedido* Src){
    return Src->numero;
}

char getPedidoEstado(struct Pedido* Src){
    return Src->estado;
}

char* getPedidoNombre(struct Pedido* Src){
    return Src->nombre_de_cliente;
}

char* getPedidoTelefono(struct Pedido* Src){
    return Src->telefono_de_cliente;
}

char* getPedidoCorreo(struct Pedido* Src){
    return Src->correo;
}

struct Carrito* getPedidoCarrito(struct Pedido* Src){
    return Src->Carrito;
}

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

struct Pedido* getPedidosHead(struct Pedidos* Src){
    return Src->Head;
}

int addPedido(struct Pedidos* Dest, char estado, char* nombre_del_cliente, char* telefono_del_cliente, char* correo, struct Carrito* Carrito, int id){
    struct Pedido* new = newPedido();
    if(new == NULL) return ERROR;
    new->estado = estado;
    cp(new->nombre_de_cliente,nombre_del_cliente);
    cp(new->telefono_de_cliente, telefono_del_cliente);
    cp(new->correo,correo);
    new->Carrito = Carrito;
    new->numero = id;

    return appendPedido(new,Dest);
}

int savePedidos(struct Pedidos* Src){
    if(Src == NULL) return ERROR;
    FILE* file = fopen("Pedidos", "wb");

    if(file == NULL) return ERROR;
    for(int i = 0; i < getPedidosSize(Src); i++){
        fwrite(getPedidoByIndex(Src,i), sizeof(struct Pedido),1,file);
    }

    fclose(file);
    return OK;
}

int loadPedidos(struct Pedidos* Dest){
    if(Dest == NULL) return ERROR;

    FILE* file = fopen("Pedidos", "rb");
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

struct Pedido* getPedidoByIndex(struct Pedidos* Src, int index){
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
