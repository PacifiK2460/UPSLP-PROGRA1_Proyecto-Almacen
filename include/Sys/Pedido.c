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