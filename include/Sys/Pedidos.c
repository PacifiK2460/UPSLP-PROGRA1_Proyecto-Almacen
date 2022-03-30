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

struct Carrito* getCarrito(struct Pedido* Src){
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

void regresar(){
    return;
}

void mostrarPedidosPor(char tipo){
    struct Pedidos* Pedidos = newPedidos();
    struct Pedido* Pedido;
    
    struct Carrito* Carrito;
    struct Detalle* Detalle;
    
    struct Productos* Productos;
    struct Producto* Producto;
    loadPedidos(Pedidos);
    loadAlmacen(Productos);
    int i = 0;
    int c;
    char color[5];
    char estado[10];
    char temp[20];
    double total;

    switch (tipo)
    {
    case 'A':
        strcpy(color,"\e[1;91m");
        strcpy(estado,"Activo");
        break;
    
    case 'E':
        strcpy(color,"\e[1;92m");
        strcpy(estado,"Entregado");
        break;
    case 'C':
        strcpy(color,"\e[1;91m");
        strcpy(estado,"Cancelado");
        break;
    }

    noEcho();


    while(1){
        printf(CLEAR);
        Pedido = getPedido(Pedidos,i);
        Carrito = getCarrito(Pedido);

        if(Pedido == NULL) break;
        if(Pedido->estado != tipo){
            i++;
            continue;
        }

        total = 0;
        //Imprimirmos la Info General
        box(STDOUTPUT,DIM);
        printinthemiddle(STDOUTPUT,1," PEDIDOS ", INVERSE);

        char informacion_del_cliente[300];
        sprintf(informacion_del_cliente,NONE BOLD "Pedido N°: " NONE "%i" BOLD "ESTADO: " "%s%s" BOLD "Nombre del Cliente: " NONE "%s" BOLD "Télefono: " NONE "%s" BOLD "Correo electrónico: " NONE  "%s", Pedido->numero,color,estado,getNamePedido(Pedido),getTelPedido(Pedido), getCorreoPedido(Pedido));
        
        printinthemiddle(STDOUTPUT,3,informacion_del_cliente,NONE);

        //Imprimirmos el carrito
            //Obtenemos la cantida de caracteres a alinear
        int mayor_cantidad = 0, mayor_precio = 0, mayor_total = 0;
        for(int j = 0; j < getCarritoSize(Carrito); j++){
            Detalle = getDetalle(Carrito,j);
            if( Detalle->cantidad > mayor_cantidad ) mayor_cantidad = Detalle->cantidad;
            Producto = getProductoByName(Producto,Detalle->nombre);
            if( getPrice(Producto) > mayor_precio ) mayor_precio = getPrice(Producto);
            if( ( getPrice(Producto) * mayor_cantidad ) > mayor_total ) mayor_total = ( getPrice(Producto) * mayor_cantidad ); 
        }
        mayor_cantidad = 8 > digitos(mayor_cantidad) ? 8 : digitos(mayor_cantidad);
        mayor_precio = 15 > digitos(mayor_precio) ? 15 : digitos(mayor_precio);
        mayor_total = 9 > digitos(mayor_total) ? 9 : digitos(mayor_total);        

            //Imprimimos Encabezados
        int ancho = 6 + 1 + mayor_cantidad + 1 + mayor_precio + 1 + mayor_total;
        ancho = (getcols(STDOUTPUT)-ancho)/2;
        winprint(STDOUTPUT,ancho, 4, "MODELO", BOLD);
        ancho += 7;
        winprint(STDOUTPUT,ancho,4,"CANTIDAD",BOLD);
        ancho += mayor_cantidad + 1;
        winprint(STDOUTPUT,ancho,4,"PRECIO UNITARIO",BOLD);
        ancho += mayor_precio + 1;
        winprint(STDOUTPUT,ancho,4, "SubTotal",BOLD);
            //Imprimimos Contenido
        for(int j = 0; j < getCarritoSize(Carrito);){
            Detalle = getDetalle(Carrito,j);
            ancho = 6 + 1 + mayor_cantidad + 1 + mayor_precio + 1 + mayor_total;

            ancho = (getcols(STDOUTPUT)-ancho)/2;
            
            winprint(STDOUTPUT,ancho,5+j,Detalle->nombre,NONE);

            ancho += 7;

            sprintf(temp, "%i", Detalle->cantidad);
            winprint(STDOUTPUT,ancho,5+j,temp,NONE);

            ancho += mayor_cantidad + 1;

            sprintf(temp,"%.2f",getPrice(getItem(Productos,i)));
            winprint(STDOUTPUT,ancho,5+j,temp,BOLD);
            
            ancho += mayor_precio + 1;
            
            total += getPrice(getItem(Productos,i)) * Detalle->cantidad;

            sprintf(temp,"%.2f",getPrice(getItem(Productos,i)) * Detalle->cantidad);
            winprint(STDOUTPUT,ancho,5+j, temp,BOLD);
        }

        sprintf(temp,BOLD "TOTAL: " NONE "%.2f",total);
        printinthemiddle(STDOUTPUT,getCarrito(Carrito),temp,NONE);

        //Imprimimos pie de pagina
        if(i != 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-3,"< Presiona «A» para ver el pedido anterior >", DIM);
        }
        if(i < getPedidosSize(Pedidos)){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona «S» para ver el pedido siguiente >", DIM);
        }
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-1,"< Presiona cualquier tecla para salir >", DIM);

        c = getchar();
        if(i != 0){
            i--;
            continue;
        }
        if(i < getPedidosSize(Pedidos)){
            i++;

            continue;
        }
        break;
    }
    echo();
}

void pedidosActivos(){
    mostrarPedidosPor('A');
}

void pedidosEntregados(){
    mostrarPedidosPor('E');
}

void pedidosCancelados(){
    mostrarPedidosPor('C');
}

void buscarID(char* ID){
    int Id;
    sscanf(ID,"%i",&Id);

    struct Pedidos* Pedidos = newPedidos();
    struct Pedido* Pedido;
    loadPedidos(Pedidos);

    struct Carrito* Carrito;
    struct Detalle* Detalle;
    
    struct Productos* Productos;
    struct Producto* Producto;

    char color[5];
    char estado[10];
    char temp[20];
    double total;

    for(int i = 0; i <  getPedidosSize(Pedidos); i++){
        if(getPedido(Pedidos,i)->numero == Id){
            Carrito = getCarrito(getPedido(Pedidos,i));
            switch (getPedido(Pedidos,i)->estado)
            {
            case 'A':
                strcpy(color,"\e[1;91m");
                strcpy(estado,"Activo");
                break;
            
            case 'E':
                strcpy(color,"\e[1;92m");
                strcpy(estado,"Entregado");
                break;
            case 'C':
                strcpy(color,"\e[1;91m");
                strcpy(estado,"Cancelado");
                break;
            }

            printf(CLEAR);

            box(STDOUTPUT,DIM);
            printinthemiddle(STDOUTPUT,1," PEDIDOS ", INVERSE);

            char informacion_del_cliente[300];
            sprintf(informacion_del_cliente,NONE BOLD "Pedido N°: " NONE "%i" BOLD "ESTADO: " "%s%s" BOLD "Nombre del Cliente: " NONE "%s" BOLD "Télefono: " NONE "%s" BOLD "Correo electrónico: " NONE  "%s", getPedido(Pedidos,i)->numero,color,estado,getPedido(Pedidos,i)->nombre_de_cliente,getPedido(Pedidos,i)->telefono_de_cliente, getPedido(Pedidos,i)->correo);

            printinthemiddle(STDOUTPUT,3,informacion_del_cliente,NONE);

            //Imprimirmos el carrito
                //Obtenemos la cantida de caracteres a alinear
            int mayor_cantidad = 0, mayor_precio = 0, mayor_total = 0;
            for(int j = 0; j < getCarritoSize(Carrito); j++){
                Detalle = getDetalle(Carrito,j);
                if( Detalle->cantidad > mayor_cantidad ) mayor_cantidad = Detalle->cantidad;
                Producto = getProductoByName(Producto,Detalle->nombre);
                if( getPrice(Producto) > mayor_precio ) mayor_precio = getPrice(Producto);
                if( ( getPrice(Producto) * mayor_cantidad ) > mayor_total ) mayor_total = ( getPrice(Producto) * mayor_cantidad ); 
            }
            mayor_cantidad = 8 > digitos(mayor_cantidad) ? 8 : digitos(mayor_cantidad);
            mayor_precio = 15 > digitos(mayor_precio) ? 15 : digitos(mayor_precio);
            mayor_total = 9 > digitos(mayor_total) ? 9 : digitos(mayor_total);        

                //Imprimimos Encabezados
            int ancho = 6 + 1 + mayor_cantidad + 1 + mayor_precio + 1 + mayor_total;
            ancho = (getcols(STDOUTPUT)-ancho)/2;
            winprint(STDOUTPUT,ancho, 4, "MODELO", BOLD);
            ancho += 7;
            winprint(STDOUTPUT,ancho,4,"CANTIDAD",BOLD);
            ancho += mayor_cantidad + 1;
            winprint(STDOUTPUT,ancho,4,"PRECIO UNITARIO",BOLD);
            ancho += mayor_precio + 1;
            winprint(STDOUTPUT,ancho,4, "SubTotal",BOLD);
                //Imprimimos Contenido
            for(int j = 0; j < getCarritoSize(Carrito);){
                Detalle = getDetalle(Carrito,j);
                ancho = 6 + 1 + mayor_cantidad + 1 + mayor_precio + 1 + mayor_total;

                ancho = (getcols(STDOUTPUT)-ancho)/2;
                
                winprint(STDOUTPUT,ancho,5+j,Detalle->nombre,NONE);

                ancho += 7;

                sprintf(temp, "%i", Detalle->cantidad);
                winprint(STDOUTPUT,ancho,5+j,temp,NONE);

                ancho += mayor_cantidad + 1;

                sprintf(temp,"%.2f",getPrice(getItem(Productos,i)));
                winprint(STDOUTPUT,ancho,5+j,temp,BOLD);
                
                ancho += mayor_precio + 1;
                
                total += getPrice(getItem(Productos,i)) * Detalle->cantidad;

                sprintf(temp,"%.2f",getPrice(getItem(Productos,i)) * Detalle->cantidad);
                winprint(STDOUTPUT,ancho,5+j, temp,BOLD);
            }

            sprintf(temp,BOLD "TOTAL: " NONE "%.2f",total);
            printinthemiddle(STDOUTPUT,getCarrito(Carrito),temp,NONE);
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-1,"< Presiona cualquier tecla para salir >", DIM);
            getchar();
            break;
        }
    }

}

void numeroDePedido(){
    char ID[6];
    input("BUSCAR POR ID", "INTRODUCE EL ID",ID,buscarID);
}

void consultarPedido(){
    MENU* menu;
    char* opciones[] = {
        "Pedidos Activos",
        "Pedidos Entregados",
        "Pedidos Cancelados",
        "Numero de Pedido",
        "Cancelar"
    };

    Funciones Funciones[] = {
        pedidosActivos,
        pedidosEntregados,
        pedidosCancelados,
        numeroDePedido,
        regresar
    };
    menu = newMenu(STDOUTPUT,(getrows(STDOUTPUT) - 7)/2, (getcols(STDOUTPUT) - 30) / 2 ,30,5, opciones,5, Funciones);

    printmenu();
    focusMenu(menu);
}
void registrarEntrega(){}
void modificarPedido(){}