#include "../sys.h"

int digitos(int n){
    return floor(log10(n) + 1);
}

int modificar(char accion){
    //struct Productos* src = newProductos();
    //struct Producto* Producto;
    int productos = getAlmacenSize();
    Producto Almacen[productos];

    if(productos == -1 ||loadAlmacenFile(Almacen) == -1){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al leer el archivo" RESET);
        getchar();
        return 1;
    }

    if(productos == 0){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No hay productos por listar" RESET);
        getchar();
        return 1;
    }

    char id[10] = {0};
    input("MODIFICAR PRODUCTO","INDEX DEL PRODUCTO A MODIFICAR",id,&evaluarExistencia);
    int idx;
    sscanf(id,"%i",&idx);
    if(idx < 0 || idx > productos){
        printinthemiddle(STDOUTPUT,getcols(STDOUTPUT)/2,"NO PUEDES MODIFICAR UN PRODUCTO INEXISTENTE");
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presione cualquier tecla para continuar >");
        getchar();
        return 0;
    }

    char sum[10] = {0};
    char titulo[100];
    strcat(titulo,"CANTIDAD A ");
    if(accion == 's'){
        strcat(titulo,"SUMAR");
    } else {
        strcat(titulo,"PONER");
    }
    input("MODIFICAR PRODUCTO",titulo,sum, &evaluarExistencia);
    int s;
    sscanf(sum,"%i",&s);
    if(accion == 's') Almacen[idx].existentes += s;
    else Almacen[idx].existentes = s;
    //Almacen[idx].existentes += s;
    //modExistencia(src,idx,s,'S');

    if(saveAlmacenFile(Almacen) == -1){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al guardar el archivo, el progreso se perdio" RESET);
    }
}

int modificarExistentes(){
    modificar('p');
}

int sumarExistentes(){
    modificar('s');
}

int nuevoProducto(){
    int productos = getAlmacenSize();
    Producto Almacen[productos];

    char titulo[] = BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
                    RESET "  " RESET
                    BRGB(75,75,75) FRGB(255,255,255) " ACTUALIZACIÓN DE ALMACEN "
                    RESET "  " RESET
                    BRGB(16,158,94) FRGB(255,255,255) " AGREGAR PRODUCTO ";

    printf(CLEAR);
    winprint(STDOUTPUT,4,2, titulo);

    char nombre[7] = {0};
    char existencia[10] = {0};
    char precio[10] = {0};
    char ubicacion[2] = {0};
    input(titulo,BOLD FRGB(185, 251, 192) "MODELO",nombre,&evaluarNombre);
    input(titulo,BOLD FRGB(185, 251, 192) "EXISTENCIA",existencia,&evaluarExistencia);
    input(titulo,BOLD FRGB(185, 251, 192) "PRECIO",precio,&evaluarPrecio);
    input(titulo,BOLD FRGB(185, 251, 192) "UBICACIÓN",ubicacion,&evaluarUbicacion);

    int existentes;
    double precios;
    char ubi;

    sscanf(existencia, "%i",&existentes);
    sscanf(precio,"%lf", &precios);
    ubi = ubicacion[0];

    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar ");
    
    if(appendAlmacenProduct(nombre,existentes,precios,ubi) == -1){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "Hubo un error al guardar el archivo, el progreso se perdio" RESET);
    }

    // addProduct(src,nombre,existentes,precios,ubi);
    // remove("Almacen");
    // saveAlmacen(src);
    // free(src);

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "AÑADIDO EXITOSO" RESET);
    getchar();
    return 1;
}

int actualizarAlmacen(){
    MENU* menu;
    char* opciones[] = {
        "Sumar Existentes",
        "Modificar Existentes",
        "Agregar Producto",
        "Regresar"
    };
    char* descripcines[] = {
        "Suma la cantidad ingresada al producto seleccionado",
        "Establece la cantidad ingresada al producto selecccionado",
        "Crea un nuevo espacio en el almacen",
        "Regresa al menu principal"
    };
    Funciones Funciones[] = {
        sumarExistentes,
        modificarExistentes,
        nuevoProducto,
        regresar
    };

    menu = newMenu(STDOUTPUT,4, 4,30,4, opciones,descripcines,4);
    int respuesta;

    while(1){
        printf(CLEAR);
        winprint(STDOUTPUT,4,2,BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
                                RESET "  " RESET
                                BRGB(16,158,94) FRGB(255,255,255) " ACTUALIZACIÓN DE ALMACEN " );
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-3,RESET FRGB(185, 251, 192)  "↓↑"     RESET DIM  " Arriba / Abajo ");
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "enter"  RESET DIM  " Seleccionar "); 
        if((respuesta = focusMenu(menu)) == 3) break;
        Funciones[respuesta]();
    }
}

// Acciones
int consultarAlmacen(){
    int productos = getAlmacenSize();
    Producto Almacen[productos];

    //Imprimimos / UI
    {
        printf(CLEAR);
        winprint(STDOUTPUT,4,2,
            BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
            RESET "  " RESET
            BRGB(16,158,94) FRGB(255,255,255) " CONSULTAR DE ALMACEN " );
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar "); 

        if(productos == -1 ||loadAlmacenFile(Almacen) == -1){
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
    
    TABLE* dataTable = newTable(4,productos);
    //Agregamos las cabeceras a la tabla
    tableSetHeaders(dataTable,(char*[]){
        "Nombre",
        "Existentes",
        "Precio",
        "Estante"
    });

    //Agregamos la info a la tabla
    for(int fila = 0; fila < productos; fila++){
        //Producto = getProductoByIndex(&Almacen,fila);

        char existentes[30];
        int2str(Almacen[fila].existentes, existentes);
        //int2str(getProductoExistentes(Producto), existentes);
        char precio[30];
        double2str(Almacen[fila].precioUnitario, precio);
        //double2str(getProductoPrecio(Producto), precio);
        //char est = getProductoEstante(Producto);

        tableAppendRow(dataTable,
            Almacen[fila].nombre,
            existentes,
            precio,
            &(Almacen[fila].estante)
        );
    }
    //prepareTableData(filas,4,headers,data);
    //char*** data = prepareTableData(filas,4,headers);
    // for(int i = 0, j = 0, fila = 1; i < filas-1; i++, j = 0, fila++){
    //     Producto = getProductoByIndex(Almacen,i);
        
    //     setTableData(data[fila][j++],getProductoName(Producto));
    //     setTableData(data[fila][j++],existentes);
    //     setTableData(data[fila][j++],precio);
    //     setTableData(data[fila][j++],&est);
    // }

    printTable(dataTable,(getcols(STDOUTPUT) - getTotalToerico(dataTable))/2,4);
    
    // for(int i=0; i<filas;i++){
    //     free(data[i]);
    // }
    //freeTable(dataTable);
    //free(Almacen);
    //free(Producto);
    getchar();
}

int salir(){
    printf("\e[?1049l");
    printf(SHOW_CURSOR);
    printf(RESET);
    exit(0);
};