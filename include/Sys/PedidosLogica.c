#include "../sys.h"

void input(char* bg_titulo, char* titulo, char* dest, int (*funcion)(char*)){
    printf(CLEAR);
    box(STDOUTPUT,DIM);
    printinthemiddle(STDOUTPUT,1,bg_titulo,DIM);

    WINDOW* wininput;
    wininput = newWin((getrows(STDOUTPUT) - 3)/2,2,getcols(STDOUTPUT)-3,2,STDOUTPUT);
    box(wininput,BOLD);
    
    winprint(wininput,1,0,titulo,BOLD);
    printf(SHOW_CURSOR);
    echo();

    winprint(wininput,1,1," ",NONE);

    delimitador result = funcion;
    //Leemos el nombre y evaluamos
    while(result(dest) == 0){
        printf(CLEAR);
        box(STDOUTPUT,DIM);
        printinthemiddle(STDOUTPUT,1,bg_titulo,DIM);
        box(wininput,BOLD);
        winprint(wininput,1,0,titulo,BOLD);
        winprint(wininput,1,1," ",NONE);
    }
    noEcho();
    printf(HIDE_CURSOR);
    printf(CLEAR);
}

int registrarPedido(){
    struct Productos* Almacen = newProductos();
    struct Producto* Producto;
    loadAlmacen(Almacen);

    int numero = randrang(99999,00000);
    char numid[6] = {0};
    sprintf(numid,"%i",numero);
    char estado = 'A';
    char nombre_de_cliente[51] = {0};
    char telefono_de_cliente[11] = {0};
    char correo[51] = {0};

    struct Pedidos* Pedidos = newPedidos();

    input("Registrar Pedido","Nombre del Cliente", nombre_de_cliente,evaluarNombre);
    input("Registrar Pedido","Telefono del cliente", telefono_de_cliente,evaluarNumero);
    input("Registrar Pedido","Correo del Cliente",correo,evaluarCorreo);

    struct Carrito* Carrito = newCarrito();
    struct Detalle* Detalle = newDetalle();

    char pedidos[2] = {0};
    int ped = -1;
    char cantidad[11] = {0};
    int cant;
    while(1){
        box(STDOUTPUT,DIM);
        printinthemiddle(STDOUTPUT,1,"MODELOS DISPONIBLES",BOLD);
        for(int i = 0; i < getProductosSize(Almacen); i++){
            Producto = getProductoByIndex(Almacen,i);
            char *tit;
            sprintf(tit,"%-2i %s", i, getProductoName(Producto));
            printinthemiddle(STDOUTPUT, 2 + i,tit, NONE);
        }
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona cualquier tecla para continuar >",DIM);
        getchar();

        input("Registrar Pedido","ID del Producto",pedidos,evaluarNumero);
        sscanf(pedidos,"%i",ped);
        if(ped > getPedidosSize(Pedidos) || ped < 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"ID INVALIDO", BOLD);
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona cualquier tecla para continuar >",DIM);
            continue;
        }

        input("Registrar Pedido", "Cantidad",cantidad,evaluarNumero);
        sscanf(cantidad,"%i",cant);
        if(cant <= 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2, "INGRESA UNA CANTIDAD MAYOR A 0",BOLD);
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presiona cualquier tecla para continuar >",DIM);
            continue;
        }

        Producto = getProductoByIndex(Almacen,ped);
        addDetalle(Carrito,getProductoName(Producto),cant);

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
    winprint(STDOUTPUT,17,2,numid,BOLD);

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

int mostrarPedidosPor(char tipo){
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
    char color[10] = {0};
    char estado[10] = {0};
    char temp[20] = {0};
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
        Pedido = getPedidoByIndex(Pedidos,i);
        Carrito = getPedidoCarrito(Pedido);

        if(Pedido == NULL) break;
        if(getPedidoEstado(Pedido) != tipo){
            i++;
            continue;
        }

        total = 0;
        //Imprimirmos la Info General
        box(STDOUTPUT,DIM);
        printinthemiddle(STDOUTPUT,1," PEDIDOS ", INVERSE);

        char informacion_del_cliente[300] = {0};
        sprintf(informacion_del_cliente,NONE BOLD "Pedido N°: " NONE "%i" BOLD "ESTADO: " "%s%s" BOLD "Nombre del Cliente: " NONE "%s" BOLD "Télefono: " NONE "%s" BOLD "Correo electrónico: " NONE  "%s", getPedidoNumero(Pedido),color,estado,getPedidoNombre(Pedido),getPedidoTelefono(Pedido), getPedidoCorreo(Pedido));
        
        printinthemiddle(STDOUTPUT,3,informacion_del_cliente,NONE);

        //Imprimirmos el carrito
            //Obtenemos la cantida de caracteres a alinear
        int mayor_cantidad = 0, mayor_precio = 0, mayor_total = 0;
        for(int j = 0; j < getCarritoSize(Carrito); j++){
            Detalle = getDetalleByIndex(Carrito,j);
            if( getDetalleCantidad(Detalle) > mayor_cantidad ) mayor_cantidad = getDetalleCantidad(Detalle);
            Producto = getProductoByName(Productos,getDetalleNombre(Detalle));
            if( getProductoPrecio(Producto) > mayor_precio ) mayor_precio = getProductoPrecio(Producto);
            if( ( getProductoPrecio(Producto) * mayor_cantidad ) > mayor_total ) mayor_total = ( getProductoPrecio(Producto) * mayor_cantidad ); 
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
            Detalle = getDetalleByIndex(Carrito,j);
            ancho = 6 + 1 + mayor_cantidad + 1 + mayor_precio + 1 + mayor_total;

            ancho = (getcols(STDOUTPUT)-ancho)/2;
            
            winprint(STDOUTPUT,ancho,5+j,getDetalleNombre(Detalle),NONE);

            ancho += 7;

            sprintf(temp, "%i", getDetalleCantidad(Detalle));
            winprint(STDOUTPUT,ancho,5+j,temp,NONE);

            ancho += mayor_cantidad + 1;

            sprintf(temp,"%.2f",getProductoPrecio(getProductoByIndex(Productos,i)));
            winprint(STDOUTPUT,ancho,5+j,temp,BOLD);
            
            ancho += mayor_precio + 1;
            
            total += getProductoPrecio(getProductoByIndex(Productos,i)) * getDetalleCantidad(Detalle);

            sprintf(temp,"%.2f",getProductoPrecio(getProductoByIndex(Productos,i)) * getDetalleCantidad(Detalle));
            winprint(STDOUTPUT,ancho,5+j, temp,BOLD);
        }

        sprintf(temp,BOLD "TOTAL: " NONE "%.2f",total);
        printinthemiddle(STDOUTPUT,getCarritoSize(Carrito),temp,NONE);

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

int pedidosActivos(){
    mostrarPedidosPor('A');
}

int pedidosEntregados(){
    mostrarPedidosPor('E');
}

int pedidosCancelados(){
    mostrarPedidosPor('C');
}

int buscarID(char* ID){
    int Id;
    sscanf(ID,"%i",&Id);

    struct Pedidos* Pedidos = newPedidos();
    struct Pedido* Pedido;
    loadPedidos(Pedidos);

    struct Carrito* Carrito;
    struct Detalle* Detalle;
    
    struct Productos* Productos;
    struct Producto* Producto;

    char color[10] = {0};
    char estado[10] = {0};
    char temp[20] = {0};
    double total = {0};

    for(int i = 0; i <  getPedidosSize(Pedidos); i++){
        if(getPedidoNumero(getPedidoByIndex(Pedidos,i)) == Id){
            Carrito = getPedidoCarrito(getPedidoByIndex(Pedidos,i));
            switch (getPedidoEstado(getPedidoByIndex(Pedidos,i)))
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

            char informacion_del_cliente[300] = {0};
            sprintf(informacion_del_cliente,NONE BOLD "Pedido N°: " NONE "%i" BOLD "ESTADO: " "%s%s" BOLD "Nombre del Cliente: " NONE "%s" BOLD "Télefono: " NONE "%s" BOLD "Correo electrónico: " NONE  "%s", getPedidoNumero(getPedidoByIndex(Pedidos,i)),color,estado,getPedidoNombre(getPedidoByIndex(Pedidos,i)),getPedidoTelefono(getPedidoByIndex(Pedidos,i)), getPedidoCorreo(getPedidoByIndex(Pedidos,i)));

            printinthemiddle(STDOUTPUT,3,informacion_del_cliente,NONE);

            //Imprimirmos el carrito
                //Obtenemos la cantida de caracteres a alinear
            int mayor_cantidad = 0, mayor_precio = 0, mayor_total = 0;
            for(int j = 0; j < getCarritoSize(Carrito); j++){
                Detalle = getDetalleByIndex(Carrito,j);
                if( getDetalleCantidad(Detalle) > mayor_cantidad ) mayor_cantidad = getDetalleCantidad(Detalle);
                Producto = getProductoByName(Productos,getDetalleNombre(Detalle));
                if( getProductoPrecio(Producto) > mayor_precio ) mayor_precio = getProductoPrecio(Producto);
                if( ( getProductoPrecio(Producto) * mayor_cantidad ) > mayor_total ) mayor_total = ( getProductoPrecio(Producto) * mayor_cantidad ); 
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
                Detalle = getDetalleByIndex(Carrito,j);
                ancho = 6 + 1 + mayor_cantidad + 1 + mayor_precio + 1 + mayor_total;

                ancho = (getcols(STDOUTPUT)-ancho)/2;
                
                winprint(STDOUTPUT,ancho,5+j,getDetalleNombre(Detalle),NONE);

                ancho += 7;

                sprintf(temp, "%i", getDetalleCantidad(Detalle));
                winprint(STDOUTPUT,ancho,5+j,temp,NONE);

                ancho += mayor_cantidad + 1;

                sprintf(temp,"%.2f",getProductoPrecio(getProductoByIndex(Productos,i)));
                winprint(STDOUTPUT,ancho,5+j,temp,BOLD);
                
                ancho += mayor_precio + 1;
                
                total += getProductoPrecio(getProductoByIndex(Productos,i)) * getDetalleCantidad(Detalle);

                sprintf(temp,"%.2f", getProductoPrecio(getProductoByIndex(Productos,i)) * getDetalleCantidad(Detalle));
                winprint(STDOUTPUT,ancho,5+j, temp,BOLD);
            }

            sprintf(temp,BOLD "TOTAL: " NONE "%.2f",total);
            printinthemiddle(STDOUTPUT,getCarritoSize(Carrito),temp,NONE);
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-1,"< Presiona cualquier tecla para salir >", DIM);
            getchar();
            break;
        }
    }

}

int numeroDePedido(){
    char ID[6] = {0};
    input("BUSCAR POR ID", "INTRODUCE EL ID",ID,&buscarID);
}

int consultarPedido(){
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
int registrarEntrega(){}
int modificarPedido(){}

int regresar(){
    return 1;
}