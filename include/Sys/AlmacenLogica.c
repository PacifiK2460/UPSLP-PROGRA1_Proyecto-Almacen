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

    char nombre[7] = {0};
    char existencia[10] = {0};
    char precio[10] = {0};
    char ubicacion[2] = {0};
    input("AÑADIR PRODUCTO","MODELO",nombre,&evaluarNombre);
    input("AÑADIR PRODUCTO","EXISTENCIA",existencia,&evaluarExistencia);
    input("AÑADIR PRODUCTO","PRECIO",precio,&evaluarPrecio);
    input("AÑADIR PRODUCTO","UBICACIÓN",ubicacion,&evaluarUbicacion);

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

    box(STDOUTPUT);
    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"AÑADIDO EXITOSO");
    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presione cualquier tecla para continuar >");
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

    //Preparamos la información para meterla a la tabla
    char*** data = prepareTableData(getProductosSize(Almacen),4);
    for(int i = 0; i < getProductosSize(Almacen); i++){
        int j = 0;
        Producto = getProductoByIndex(Almacen,i);
        char est = getProductoEstante(Producto);
        
        setTableData(i, j++,data,getProductoName(Producto));
        setTableData(i, j++,data,int2str(getProductoExistentes(Producto))); //
        setTableData(i, j++,data,double2str(getProductoPrecio(Producto)));//
        setTableData(i, j++,data,&est);
    }

    //Imprimimos lo demas
    printf(CLEAR);
    winprint(STDOUTPUT,4,2,BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
                            RESET "  " RESET
                            BRGB(16,158,94) FRGB(255,255,255) " CONSULTAR DE ALMACEN " );
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " regresar "); 

    //Impresion de la tabla
    // int ancho = 6 + 1 + digitos_existentes + 1 + digitos_precio + 1 + 10;
    // ancho = (getcols(STDOUTPUT) - ancho)/2;
    // winprint(STDOUTPUT,ancho, 4, "MODELO");
    // ancho += 7;
    // winprint(STDOUTPUT,ancho, 4, "TOTAL");
    // ancho += digitos_existentes + 1;
    // winprint(STDOUTPUT,ancho, 4, "PRECIO UNITARIO");
    // ancho += digitos_precio + 1;
    // winprint(STDOUTPUT,ancho, 4, "UBICACIÓN EN ALMACEN");

    // for(int i = 0; i < getProductosSize(Almacen); i++ ){
    //     Producto = getProductoByIndex(Almacen,i);
    //     ancho = 6 + 1 + digitos_existentes + 1 + digitos_precio + 1 + 10;
    //     ancho = (getcols(STDOUTPUT) - ancho)/2;
    //     winprint(STDOUTPUT,ancho, 5 + i, getProductoName(Producto));
    //     ancho += 7;

    //     char* total = malloc(50 + 1);
    //     sprintf(total,"%i",getProductoExistentes(Producto));
        
    //     winprint(STDOUTPUT,ancho, 5 + i, total);
    //     ancho += digitos_existentes + 1;

    //     sprintf(total,"$%.2f",getProductoPrecio(Producto));
    //     winprint(STDOUTPUT,ancho, 5 + i, total);
    //     ancho += digitos_precio + 1;

    //     sprintf(total,"Estante %c",getProductoEstante(Producto));
    //     winprint(STDOUTPUT,ancho, 5 + i, total);
    // }
    getchar();
}

int salir(){
    printf("\e[?1049l");
    printf(SHOW_CURSOR);
    printf(RESET);
    exit(0);
};