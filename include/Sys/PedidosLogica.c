#include "../sys.h"

void input(char* bg_titulo, char* titulo, char* dest, int (*funcion)(char*)){
    printf(CLEAR);
    winprint(STDOUTPUT,4,2, bg_titulo);
    printf(SHOW_CURSOR);
    echo();
    
    winprint(STDOUTPUT,5, (getrows(STDOUTPUT)/2)-1,titulo);
    winprint(STDOUTPUT,4, (getrows(STDOUTPUT)/2)-1,MENUVLINE);
    winprint(STDOUTPUT,5, (getrows(STDOUTPUT)/2)," ");
    winprint(STDOUTPUT,4, (getrows(STDOUTPUT)/2),MENUVLINE);


    delimitador result = funcion;
    //Leemos el nombre y evaluamos
    while(result(dest) == 0){
        cleanInput();
        printf(CLEAR);
        winprint(STDOUTPUT,4,2, bg_titulo);
        winprint(STDOUTPUT,5, (getrows(STDOUTPUT)/2)-1,titulo);
        winprint(STDOUTPUT,4, (getrows(STDOUTPUT)/2)-1,MENUVLINE);
        winprint(STDOUTPUT,5, (getrows(STDOUTPUT)/2)," ");
        winprint(STDOUTPUT,4, (getrows(STDOUTPUT)/2),MENUVLINE);
    }
    cleanInput();
    noEcho();
    printf(HIDE_CURSOR);
    printf(CLEAR);
}

int registrarPedido(){

    int productos = getAlmacenSize();
    Producto Almacen[productos];

    Pedido nuevoPedido;

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
    

    input(tituto,BOLD FRGB(185, 251, 192) "Nombre del Cliente", nombre_de_cliente,evaluarNombreDelCliente);
    input(tituto,BOLD FRGB(185, 251, 192) "Telefono del cliente", telefono_de_cliente,evaluarNumero);
    input(tituto,BOLD FRGB(185, 251, 192) "Correo del Cliente",correo,evaluarCorreo);

    int productosPedidos = 0;
    Detalle* Carrito = malloc(sizeof(Detalle)); //Almenos 1

    while(1){
        char pedidos[2] = {0};
        int ped = -1;
        char cantidad[11] = {0};
        int cant = -1;

        //Imprimimos tabla de productos
        { 
            printf(CLEAR);
            winprint(STDOUTPUT,4,2,tituto);
            TABLE* dataTable = newTable(2,getAlmacenSize());
            tableSetHeaders(dataTable,(char*[]){
                "ID",
                "Nombre"
            });
            char* temp;
            for(int fila = 0; fila < productos; fila++){
                //Producto Tmp = Almacen[fila]; 
                temp = malloc(30);
                int2str(fila, temp);
                tableAppendRow(dataTable,
                    temp,
                    Almacen[fila].nombre//getProductoName(Tmp)
                );
            };
            printTable(dataTable, -1, 4);

            winprint(STDOUTPUT,4,2,tituto);
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " continuar ");
            getchar();
        }
        printf(CLEAR);
        winprint(STDOUTPUT,4,2,tituto);

        while(ped > productos || ped < 0){
            input(tituto, BOLD FRGB(185, 251, 192) "ID del Producto",pedidos,evaluarNumero);
            sscanf(pedidos,"%i",&ped);
            if(ped > productos || ped < 0){
                printf(CLEAR);
                printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"ID INVALIDO");

                winprint(STDOUTPUT,4,2,tituto);
                winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
                getchar();
                continue;
            }
            break;
        }

        while(cant <= 0 || cant >= Almacen[ped].existentes){
            input(tituto,BOLD FRGB(185, 251, 192) "Cantidad",cantidad,evaluarNumero);
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
        Carrito[productosPedidos].cantidad = cant;
        cp(Carrito[productosPedidos].nombre, Almacen[ped].nombre);
        Carrito = realloc(Carrito, ++productosPedidos);
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

    nuevoPedido.productos = productosPedidos;
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
    input(tituto,BOLD FRGB(185, 251, 192) "INTRODUCE EL ID",ID,&evaluarNumero);
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
        if(menu.selected == 4) break;
        Funciones[menu.selected]();
    }
}

int registrarEntrega(){}
int modificarPedido(){}

int regresar(){
    return 1;
}