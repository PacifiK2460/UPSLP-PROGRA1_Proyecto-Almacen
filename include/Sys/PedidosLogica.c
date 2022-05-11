#include "../sys.h"

int listarPedidos(char* titulo, Pedido Almacen[], int productos){
    //Pedimos el producto
    NEW_SCREEN();
    MENU itemSeleccionado;
    char* nombres[productos];
    char** ids= (char**)malloc(productos * sizeof(char**));

    printf(CLEAR);

    for(int i=0; i < productos; i++){
        ids[i] = malloc(20);
        cp(ids[i], "ID: ");
        
        nombres[i] = Almacen[i].nombre_de_cliente;

        char temp[5] = {0};
        int2str(Almacen[i].numero, temp);

        cat(ids[i], temp);
    }

    setMenuData(&itemSeleccionado,STDOUTPUT,4,4,productos,nombres,ids);

    printf(HIDE_CURSOR);
    winprint(STDOUTPUT,4,2,titulo);
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-3,RESET FRGB(185, 251, 192)  "↓↑"     RESET DIM  " Arriba / Abajo ");
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "enter"  RESET DIM  " Seleccionar ");
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "←"  RESET DIM  " regresar ");
    focusMenu(&itemSeleccionado);

    for(int i=0; i < productos; i++) {
        //free(*nombres[i]);
        free(ids[i]);
    }
    
    CLOSE_SCREEN();
    return itemSeleccionado.selected;
}

int registrarPedido(){

    int productos = getAlmacenSize();
    Producto Almacen[productos];

    Pedido nuevoPedido;

    {//File Manager
        if(productos == -1 ||loadAlmacenFile(Almacen) == -1){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al leer el archivo" RESET);
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar ");
            getchar();
            return 1;
        }

        if(productos == 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No puedes pedir algo de un inventario inexistente" RESET);
            getchar();
            return 1;
        }

    }

    int numero = randrang(99999,00000);
    char numid[6] = {0};
    sprintf(numid,"%i",numero);
    char estado = 'A';
    char nombre_de_cliente[51] = {0};
    char telefono_de_cliente[12] = {0};
    char correo[51] = {0};

    char tituto[] = BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL " RESET "  " RESET BRGB(16,158,94) FRGB(255,255,255) " REGISTRAR PEDIDO ";
    printf(CLEAR);
    winprint(STDOUTPUT,4,2,tituto);
    
    if ( input(tituto,BOLD FRGB(185, 251, 192) "Nombre del Cliente", nombre_de_cliente,evaluarNombreDelCliente) == -1) return 0;
    if ( input(tituto,BOLD FRGB(185, 251, 192) "Telefono del cliente", telefono_de_cliente,evaluarNumero) == -1) return 0;
    if ( input(tituto,BOLD FRGB(185, 251, 192) "Correo del Cliente",correo,evaluarCorreo) == -1) return 0;

    int productosPedidos = 1;
    Detalle* Carrito = (Detalle*)malloc(sizeof(Detalle) * productosPedidos); //Almenos 1

    while(1){
        char pedidos[2] = {0};
        int ped = -1;
        char cantidad[11] = {0};
        int cant = -1;

        //Imprimimos tabla de productos
        ped = listarProductos(tituto, Almacen, productos);

        if(ped == -1) return 0;

        while(cant <= 0 || cant >= Almacen[ped].existentes){
            if( input(tituto,BOLD FRGB(185, 251, 192) "Cantidad",cantidad,evaluarNumero) == -1) return 0;;
            sscanf(cantidad,"%i",&cant);
            if(cant <= 0 || cant >= Almacen[ped].existentes){
                printf(CLEAR);
                printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2, "INGRESA UNA CANTIDAD POSIBLE A COMPRAR");
                winprint(STDOUTPUT,4,2,tituto);
                winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
                cleanInput();
                getchar();
                continue;
            }
            break;
        }

        printf(CLEAR);
        winprint(STDOUTPUT,4,2,tituto);

        //addDetalle(Carrito,Almacen[ped].nombre,cant);
        Carrito[productosPedidos-1].cantidad = cant;
        cp(Carrito[productosPedidos-1].nombre, Almacen[ped].nombre);
        Carrito = realloc(Carrito, productosPedidos);
        productosPedidos++;
        //TODO #8 #7 realloc crashes on allocating memory to new Carrito
        //Carrito = (Detalle*)realloc(, ++productosPedidos);


        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"ITEM AGREGADO CORRECTAMENTE");
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-3,RESET FRGB(185, 251, 192)  "enter"  RESET DIM  " agregar otro producto ");
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " continuar ");
        if(getchar() == 10) continue;
        break;
    }

    nuevoPedido.numero = numero;
    nuevoPedido.estado = estado;
    cp(nuevoPedido.nombre_de_cliente, nombre_de_cliente);
    cp(nuevoPedido.telefono_de_cliente, telefono_de_cliente);
    cp(nuevoPedido.correo, correo);

    nuevoPedido.productos = productosPedidos-1;
    nuevoPedido.Detalles = Carrito;

    if( appendPedido(nuevoPedido) == -1){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al leer el archivo, cambios perdidos" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar ");
        getchar();
        return 1;
    }


    printf(CLEAR);

    winprint(STDOUTPUT,4,2,tituto);

    imprimirPedido(nuevoPedido, 4, 4);

    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " continuar ");

    getchar();
}

int mostrarPedidosPor(char tipo){
    char tituto[] = BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL " RESET "  " RESET BRGB(16,158,94) FRGB(255,255,255) " MOSTRAR PEDIDO ";
    printf(CLEAR);
    winprint(STDOUTPUT,4,2,tituto);
    int pedidos = getPedidosSize();
    if(pedidos == 0){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No hay pedidos por mostrar" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar "); 
        getchar();
        return 1;   
    }

    Pedido Pedidos[pedidos];
    if( loadPedidoFile(Pedidos) == -1){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al cargar el archivo" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar "); 
        getchar();
        return 1;   
    }

    int cantidadDePedidosDelTipoSolicitado = 0;
    int index[pedidos];
    for(int i = 0; i < pedidos; i++) index[i] = -1;
    for(int i = 0; i < pedidos; i++){
        if( Pedidos[i].estado == tipo ){
            cantidadDePedidosDelTipoSolicitado++;
            index[i] = i;
        }
    }

    if(cantidadDePedidosDelTipoSolicitado == 0){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No hay pedidos por mostrar" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar "); 
        getchar();
        return 1;   
    }

    Pedido PedidosDelTipo[cantidadDePedidosDelTipoSolicitado];
    for(int i = 0, j = 0; i < pedidos; i++){
        if(index[i] != -1){
            PedidosDelTipo[j++] = Pedidos[index[i]];
        }
    }
    int i = 0;

    int c;

    noEcho();

    while(1){
        printf(CLEAR);
        winprint(STDOUTPUT,4,2,tituto);

        //Imprimirmos la Info General
        imprimirPedido(PedidosDelTipo[i], 4, 4);

        //Imprimimos pie de pagina
        if(i > 0 && i < cantidadDePedidosDelTipoSolicitado-1){
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-4,RESET FRGB(185, 251, 192)  "↑"  RESET DIM  " siguiente pedido "); 
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-3,RESET FRGB(185, 251, 192)  "↓"  RESET DIM  " anterior pedido "); 
        } else if(i > 0){
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-3,RESET FRGB(185, 251, 192)  "↑"  RESET DIM  " siguiente pedido "); 
        } else if(i < cantidadDePedidosDelTipoSolicitado-1){
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-3,RESET FRGB(185, 251, 192)  "↓"  RESET DIM  " anterior pedido "); 
        }
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "enter"  RESET DIM  " salir "); 

        c = getchar();
        if(c == '\033'){ //ESC
            getchar(); //Omitimos el 2do [
            switch ( (c = getchar()) )
            {
                case 'A':
                    if(i > 0) i--;
                    break;
                
                case 'B':
                    if(i < cantidadDePedidosDelTipoSolicitado-1) i++;
                    break;
            }
        }
        //Enter
        if(c == 10){
            break;
        }
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

int numeroDePedido(){
    char ID[6] = {0};
    char tituto[] = BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL " RESET "  " RESET BRGB(16,158,94) FRGB(255,255,255) " BUSCAR PEDIDO ";
    if( input(tituto,BOLD FRGB(185, 251, 192) "INTRODUCE EL ID",ID,&evaluarNumero) == -1) return 0;
    int id;
    sscanf(ID,"%5i", &id);

    printf(CLEAR);
    winprint(STDOUTPUT,4,2,tituto);
    int pedidos = getPedidosSize();
    if(pedidos == 0){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No hay pedidos por mostrar" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar "); 
        getchar();
        return 1;   
    }

    Pedido Pedidos[pedidos];
    if( loadPedidoFile(Pedidos) == -1){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al cargar el archivo" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar "); 
        getchar();
        return 1;   
    }

    printf(CLEAR);
    winprint(STDOUTPUT,4,2,tituto);
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar "); 
    for(int i = 0; i < pedidos; i++){
        if( Pedidos[i].numero == id ){
            imprimirPedido(Pedidos[i], 4, 4);
            getchar();
            return 1;
        }
    }

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No hay pedidos por mostrar" RESET);
    getchar();
    return 1;   
}

int consultarPedido(){
    MENU menu;
    setMenuData(&menu, NULL, 4,4,5,(char*[]){
            "Pedidos Activos",
            "Pedidos Entregados",
            "Pedidos Cancelados",
            "Numero de Pedido",
            "Regresar"
            },
        (char*[]){
            "Enlista los pedidos Activos",
            "Enlista los pedidos Entregados",
            "Enlista los pedidos Cancelados",
            "Busca el pedido por el ID ingresado",
            "Regresa al menu anterior"
    });
    Funciones Funciones[] = {
        pedidosActivos,
        pedidosEntregados,
        pedidosCancelados,
        numeroDePedido,
        regresar
    };

    while(1){
        printf(CLEAR);
        winprint(STDOUTPUT,4,2,BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL " RESET "  " RESET BRGB(16,158,94) FRGB(255,255,255) " CONSULTAR PEDIDO ");
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-3,RESET FRGB(185, 251, 192)  "↓↑"     RESET DIM  " Arriba / Abajo ");
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "enter"  RESET DIM  " Seleccionar ");
        
        
        //menu = newMenu(STDOUTPUT,4, 4 ,30,5, opciones,descripciones,5);
        focusMenu(&menu);
        if(menu.selected == 4 || menu.selected == -1) break;
        Funciones[menu.selected]();
    }
}

int registrarEntrega(){
    printf(CLEAR);
    int pedidos = getPedidosSize();
    Pedido Pedidos[pedidos];

    char titulo[] = BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
                    RESET "  " RESET
                    BRGB(16,158,94) FRGB(255,255,255) " MODIFICAR PEDIDO ";

    { //UI & File Managin
        winprint(STDOUTPUT,4,2, titulo);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " continuar ");

        if(pedidos == -1 ||loadPedidoFile(Pedidos) == -1){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al leer el archivo" RESET);
            getchar();
            return 1;
        }

        if(pedidos == 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No hay productos por listar" RESET);
            getchar();
            return 1;
        }
    }

    int index;
    do
    {
        printf(CLEAR);
        winprint(STDOUTPUT,4,2, titulo);
        index = listarPedidos(titulo, Pedidos, pedidos);
        if(index == -1) return 0;

        if(Pedidos[index].estado == 'E'){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Por ahora no sabemos viajar al pasado, no puedes modificar un pedido entregado");
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
            getchar();
            continue;
        } else if(Pedidos[index].estado == 'C'){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "¿Estas haciendo fraude?, no puedes entregar un pedido cancelado");
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
            getchar();
            continue;
        }
        break;
    } while (1);

    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " finalizar ");


    int productos = getAlmacenSize();
    Producto Almacen[productos];
    {// Actualizar almacen
        if(productos == -1 ||loadAlmacenFile(Almacen) == -1){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al actulizar el almacen" RESET);
            getchar();
            return 1;
        }

        if(productos == 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "El almacen ah desaparecido, nada que actualizar" RESET);
            getchar();
            return 1;
        }

        for(int CarritoPedido = 0; CarritoPedido < pedidos; CarritoPedido++){
            for(int producto = 0; producto < productos; producto++){
                if( cmp(Pedidos[index].Detalles[CarritoPedido].nombre, Almacen[producto].nombre) == 0 ){
                    if( (Almacen[producto].existentes - Pedidos[index].Detalles[CarritoPedido].cantidad) < 0 ){
                        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No hay suficientes productos para completar la entrega. No se ah actualizado el Almacen" RESET);
                        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " finalizar ");
                        getchar();
                        return 0;
                    }
                }
            }
        }

        for(int CarritoPedido = 0; CarritoPedido < Pedidos[index].productos; CarritoPedido++){
            for(int producto = 0; producto < productos; producto++){
                if( cmp(Pedidos[index].Detalles[CarritoPedido].nombre, Almacen[producto].nombre) == 0 ){
                    Almacen[producto].existentes -= Pedidos[index].Detalles[CarritoPedido].cantidad;
                    break;
                }
            }
        }
    }

    Pedidos[index].estado = 'E';
    if(savePedidoFile(Pedidos, pedidos) == -1 || saveAlmacenFile(Almacen,productos) == -1){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM  "Hubo un error al guardar el archivo, el progreso se perdio" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " finalizar ");
        getchar();
        return 0;
    }

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM  "Cambios guardados correctamente" RESET);
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " finalizar ");
    getchar();

    return registrarEntrega();
}

int modificarPedido(){
    printf(CLEAR);
    int productos = getPedidosSize();
    Pedido Almacen[productos];
    MENU itemSeleccionado;

    char titulo[] = BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
                    RESET "  " RESET
                    BRGB(16,158,94) FRGB(255,255,255) " MODIFICAR PEDIDO ";

    { //UI & File management
        winprint(STDOUTPUT,4,2, titulo);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " continuar ");

        if(productos == -1 ||loadPedidoFile(Almacen) == -1){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al leer el archivo" RESET);
            getchar();
            return 1;
        }

        if(productos == 0){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No hay productos por listar" RESET);
            getchar();
            return 1;
        }
    }
    
    int idx;
    int index;
    char cont = 0;
    do{
        //Pedimos el producto
        {
            printf(CLEAR);
            winprint(STDOUTPUT,4,2, titulo);
            index = listarPedidos(titulo, Almacen, productos);
            if(index == -1) return 0;
        }

        if(Almacen[index].estado == 'E'){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Por ahora no sabemos viajar al pasado, no puedes modificar un pedido entregado");
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
            getchar();
            continue;
        }
        break;
    }while(1);


    if(Almacen[index].estado == 'A'){
        Almacen[index].estado = 'C';        
    } else if(Almacen[index].estado == 'C'){
        Almacen[index].estado = 'A';
    } else {
        return 1;
    }

    if(savePedidoFile(Almacen, productos) == -1){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM  "Hubo un error al guardar el archivo, el progreso se perdio" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " finalizar ");
        getchar();
        return 0;
    }

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM  "Cambios guardados correctamente" RESET);
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " finalizar ");
    getchar();
}

int regresar(){
    return 1;
}