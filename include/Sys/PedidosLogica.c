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

    input("Registrar Pedido","Nombre del Cliente", nombre_de_cliente,Nombre(nombre_de_cliente));
    input("Registrar Pedido","Telefono del cliente", telefono_de_cliente,Numero(telefono_de_cliente));
    input("Registrar Pedido","Correo del Cliente",correo,Correo(correo));

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

        input("Registrar Pedido","ID del Producto",pedidos,Numero(pedidos));
        sscanf(pedidos,"%i",ped);
        if(ped > getSize(Producto) || ped < 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"ID INVALIDO", BOLD);
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona cualquier tecla para continuar >",DIM);
            continue;
        }

        input("Registrar Pedido", "Cantidad",cantidad,Numero(pedidos));
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

void regresar(){
    return;
}