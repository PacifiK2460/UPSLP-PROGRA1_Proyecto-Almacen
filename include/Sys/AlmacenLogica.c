#include "../sys.h"

int digitos(int n){
    return floor(log10(n) + 1);
}

int modificarExistentes(){
    struct Productos* src = newProductos();
    struct Producto* Producto;
    loadAlmacen(src);

    char id[10] = {0};
    input("MODIFICAR PRODUCTO","INDEX DEL PRODUCTO A MODIFICAR",id,&evaluarExistencia);
    int idx;
    sscanf(id,"%i",&idx);
    if(idx < 0 || idx > getProductosSize(src)){
        printinthemiddle(STDOUTPUT,getcols(STDOUTPUT)/2,"NO PUEDES MODIFICAR UN PRODUCTO INEXISTENTE");
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presione cualquier tecla para continuar >");
        getchar();
        return 0;
    }

    char sum[10] = {0};
    input("MODIFICAR PRODUCTO","CANTIDAD A PONER",sum, &evaluarExistencia);
    int s;
    sscanf(sum,"%i",&s);
    modExistencia(src,idx,s,'S');

    remove("Almacen");
    saveAlmacen(src);
}

int sumarExistentes(){
    struct Productos* src = newProductos();
    struct Producto* Producto;
    loadAlmacen(src);

    char id[10] = {0};
    input("MODIFICAR PRODUCTO","INDEX DEL PRODUCTO A MODIFICAR",id,&evaluarExistencia);
    int idx;
    sscanf(id,"%i",&idx);
    if(idx < 0 || idx > getProductosSize(src)){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"NO PUEDES MODIFICAR UN PRODUCTO INEXISTENTE");
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presione cualquier tecla para continuar >");
        getchar();
        return 0;
    }

    char sum[10] = {0};
    input("MODIFICAR PRODUCTO","CANTIDAD A SUMAR",sum, &evaluarExistencia);
    int s;
    sscanf(sum,"%i",&s);
    modExistencia(src,idx,s,'A');
    remove("Almacen");
    saveAlmacen(src);
}

int nuevoProducto(){
    struct Productos* src = newProductos();
    loadAlmacen(src);

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

    addProduct(src,nombre,existentes,precios,ubi);
    remove("Almacen");
    saveAlmacen(src);
    free(src);

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "AÑADIDO EXITOSO" RESET);
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar ");
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
    struct Productos* Almacen = newProductos();
    struct Producto* Producto;
    loadAlmacen(Almacen);

    //Imprimimos lo demas
    printf(CLEAR);
    winprint(STDOUTPUT,4,2,BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
                            RESET "  " RESET
                            BRGB(16,158,94) FRGB(255,255,255) " CONSULTAR DE ALMACEN " );
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar "); 

    if(getProductosSize(Almacen) == 0){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No hay productos por listar" RESET);
        getchar();
        return 1;
    }

    //Preparamos la información para meterla a la tabla
    char* headers[] = {
        "Nombre",
        "Existentes",
        "Precio",
        "Estante"
    };
    char* ** data = prepareTableData(getProductosSize(Almacen)+1,4,headers);
    for(int i = 0, j = 0, fila = 1; i < getProductosSize(Almacen); i++, j = 0, fila++){
        Producto = getProductoByIndex(Almacen,i);
        char est = getProductoEstante(Producto);
        
        setTableData(fila, j++,data,getProductoName(Producto));
        setTableData(fila, j++,data,int2str(getProductoExistentes(Producto)));
        setTableData(fila, j++,data,double2str(getProductoPrecio(Producto)));
        setTableData(fila, j++,data,&est);
    }

    TABLE* dataTable = newTable(4,getProductosSize(Almacen),data);
    int total = getTotal(dataTable);
    printTable(dataTable, (getcols(STDOUTPUT) - total)/2, 4);
    getchar();
}

int salir(){
    printf("\e[?1049l");
    printf(SHOW_CURSOR);
    printf(RESET);
    exit(0);
};