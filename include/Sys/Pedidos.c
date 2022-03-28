#include "../sys.h"

void input(char* bg_titulo, char* titulo, char* dest, int delimitar ( int (*f)(char*) )){
    printf(CLEAR);
    box(STDOUTPUT,DIM);
    printinthemiddle(STDOUTPUT,1,bg_titulo,DIM);

    WINDOW* input;
    input = newWin((getrows(STDOUTPUT) - 3)/2,2,getcols(STDOUTPUT)-3,2,STDOUTPUT);
    box(input,BOLD);
    
    winprint(input,1,0,titulo,BOLD);
    printf(SHOW_CURSOR);
    echo();

    winprint(input,1,1," ",NONE);

    //Leemos el nombre y evaluamos
    while(delimitar(dest) == 0){
        printf(CLEAR);
        box(STDOUTPUT,DIM);
        printinthemiddle(STDOUTPUT,1,bg_titulo,DIM);
        box(input,BOLD);
        winprint(input,1,0,titulo,BOLD);
        winprint(input,1,1," ",NONE);
    }
    noEcho();
    printf(HIDE_CURSOR);
    printf(CLEAR);
}

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
    char nombre_de_cliente[51];
    char telefono_de_cliente[11];
    char correo[51];
    
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

void verPedido(){

}

void registrarPedido(){
    struct Productos* Almacen = newProductos();
    struct Producto* Producto;
    loadAlmacen(Almacen);

    int numero = randrang(99999,00000);
    char estado = 'A';
    char nombre_de_cliente[51];
    char telefono_de_cliente[11];
    char correo[51];

    struct Pedidos* Pedidos = newPedidos();
    input("Registrar Pedido","Nombre del Cliente", nombre_de_cliente,getNombre);
    input("Registrar Pedido","Telefono del cliente", telefono_de_cliente,getTel);
    input("Registrar Pedido","Correo del Cliente",correo,evaluarCorreo);

    struct Carrito* Carrito = newCarrito();
    struct Detalle* Detalle = newDetalle();

    char pedidos[2];
    int ped = -1;
    char cantidad[11];
    int cant;
    while(1){
        box(STDOUTPUT,DIM);
        printinthemiddle(STDOUTPUT,1,"MODELOS DISPONIBLES",BOLD);
        for(int i = 0; i < getSize(Almacen); i++){
            Producto = getItem(Pedidos,i);
            char *tit;
            sprintf(tit,"%-2i %s", i, getName(Producto));
            printinthemiddle(STDOUTPUT, 2 + i,tit, NONE);
        }
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona cualquier tecla para continuar >",DIM);
        getchar();

        input("Registrar Pedido","ID del Producto",pedidos,getTel);
        sscanf(pedidos,"%i",ped);
        if(ped > getSize(Producto) || ped < 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"ID INVALIDO", BOLD);
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona cualquier tecla para continuar >",DIM);
            continue;
        }

        input("Registrar Pedido", "Cantidad",cantidad,getTel);
        sscanf(cantidad,"%i",cant);
        if(cant <= 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2, "INGRESA UNA CANTIDAD MAYOR A 0",BOLD);
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona cualquier tecla para continuar >",DIM);
            continue;
        }

        Producto = getItem(Almacen,ped);
        addDetalle(Carrito,getName(Producto),cant);

        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"ITEM AGREGADO CORRECTAMENTE", BOLD);
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona cualquier tecla para continuar >",DIM);
        getchar();
        break;
    }

    addPedido(Pedidos,estado,nombre_de_cliente,telefono_de_cliente,correo,Carrito,numero);

    printf(CLEAR);
    winprint(STDOUTPUT,1,2,"Pedido: ", NONE);
    winprint(STDOUTPUT,8,2,"ACTIVO",BOLD);

    winprint(STDOUTPUT,13,2,"ID: ", NONE);
    winprint(STDOUTPUT,17,2,numero,BOLD);

    winprint(STDOUTPUT,1, 3,"NOMBRE DEL CLIENTE: ", NONE);
    winprint(STDOUTPUT,20,3,nombre_de_cliente,BOLD);

    winprint(STDOUTPUT,1,4,"TÉLEFONO: ",NONE);
    winprint(STDOUTPUT,10,4,telefono_de_cliente,BOLD);

    winprint(STDOUTPUT,1,5,"CORREO: ", NONE);
    winprint(STDOUTPUT,8,5,correo,BOLD);

    int i = 0;
    for(i; i < getCarritoSize(Carrito); i++){
        
    }

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona cualquier tecla para visualizarlo >",DIM);

    remove("Pedidos");
    savePedidos(Pedidos);

}
void consultarPedido(){}
void registrarEntrega(){}
void modificarPedido(){}