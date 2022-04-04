#include "../sys.h"

int digitos(int n){
    return floor(log10(n) + 1);
}

int modificarExistentes(){
    struct Productos* src = newProductos();
    struct Producto* Producto;
    loadAlmacen(src);

    char id[10];
    input("MODIFICAR PRODUCTO","INDEX DEL PRODUCTO A MODIFICAR",id,&evaluarExistencia);
    int idx;
    sscanf(id,"%i",&idx);
    if(idx < 0 || idx > getProductosSize(src)){
        printinthemiddle(STDOUTPUT,getcols(STDOUTPUT)/2,"NO PUEDES MODIFICAR UN PRODUCTO INEXISTENTE",BOLD);
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presione cualquier tecla para continuar >",DIM);
        getchar();
        return 0;
    }

    char sum[10];
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

    char id[10];
    input("MODIFICAR PRODUCTO","INDEX DEL PRODUCTO A MODIFICAR",id,&evaluarExistencia);
    int idx;
    sscanf(id,"%i",&idx);
    if(idx < 0 || idx > getProductosSize(src)){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"NO PUEDES MODIFICAR UN PRODUCTO INEXISTENTE",BOLD);
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presione cualquier tecla para continuar >",DIM);
        getchar();
        return 0;
    }

    char sum[10];
    input("MODIFICAR PRODUCTO","CANTIDAD A SUMAR",sum, &evaluarExistencia);
    int s;
    sscanf(sum,"%i",&s);
    modExistencia(src,idx,s,'A');
    remove("Almacen");
    saveAlmacen(src);
}

int nuevoProducto(){
    struct Productos* src = newProductos();
    struct Producto* Producto;
    loadAlmacen(src);

    char nombre[7];
    char existencia[10];
    char precio[10];
    char ubicacion[2];
    input("AÑADIR PRODUCTO","MODELO",nombre,&evaluarNombre);
    input("AÑADIR PRODUCTO","EXISTENCIA",existencia,&evaluarExistencia);
    input("AÑADIR PRODUCTO","PRECIO",precio,&evaluarPrecio);
    input("AÑADIR PRODUCTO","UBICACIÓN",ubicacion,&evaluarUbicacion);

    int existentes;
    double precios;
    char ubi;

    sscanf(existencia, "%i",&existentes);
    sscanf(precio,"%lf", &precios);
    sscanf(ubicacion,"%c",&ubi);

    addProduct(src,nombre,existentes,precios,ubi);
    remove("Almacen");
    saveAlmacen(src);

    box(STDOUTPUT,DIM);
    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,"AÑADIDO EXITOSO",BOLD);
    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presione cualquier tecla para continuar >",DIM);
    getchar();
}

int actualizarAlmacen(){
    MENU* menu;
    char* opciones[] = {
        "Sumar Existentes",
        "Modificar Existentes",
        "Agregar Producto",
        "Regresar"
    };

    Funciones Funciones[] = {
        sumarExistentes,
        modificarExistentes,
        nuevoProducto,
        regresar
    };
    menu = newMenu(STDOUTPUT,(getrows(STDOUTPUT) - 7)/2, (getcols(STDOUTPUT) - 30) / 2 ,30,4, opciones,4, Funciones);

    printmenu();
    focusMenu(menu);
}

// Acciones
int consultarAlmacen(){
    struct Productos* Almacen = newProductos();
    struct Producto* Producto;
    loadAlmacen(Almacen);

    //Para alinear la info, obtenemos la cantidad mas ge;
    int mayor_existencia = 1, mayor_precio = 1;
    for(int i = 0; i < getProductosSize(Almacen); i++){
        Producto = getProductoByIndex(Almacen, i);
        if( getProductoExistentes(Producto) > mayor_existencia )
            mayor_existencia = getProductoExistentes(Producto) ;
        if( getProductoPrecio(Producto) > mayor_precio )
            mayor_precio = getProductoPrecio(Producto);
    }

    int digitos_existentes = 5 > digitos(mayor_existencia) ? 5 : digitos(mayor_existencia);
    int digitos_precio = 15 > digitos(mayor_precio) ? 15 : digitos(mayor_precio);

    printf(CLEAR);

    //Imprimimos la tabla
    box(STDOUTPUT,DIM);
    printinthemiddle(STDOUTPUT,1," ALMACEN ", INVERSE);
    int ancho = 6 + 1 + digitos_existentes + 1 + digitos_precio + 1 + 10;
    ancho = (getcols(STDOUTPUT) - ancho)/2;
    winprint(STDOUTPUT,ancho, 4, "MODELO", BOLD);
    ancho += 7;
    winprint(STDOUTPUT,ancho, 4, "TOTAL", BOLD);
    ancho += digitos_existentes + 1;
    winprint(STDOUTPUT,ancho, 4, "PRECIO UNITARIO", BOLD);
    ancho += digitos_precio + 1;
    winprint(STDOUTPUT,ancho, 4, "UBICACIÓN EN ALMACEN", BOLD);

    for(int i = 0; i < getProductosSize(Almacen); i++ ){
        Producto = getProductoByIndex(Almacen,i);
        ancho = 6 + 1 + digitos_existentes + 1 + digitos_precio + 1 + 10;
        ancho = (getcols(STDOUTPUT) - ancho)/2;
        winprint(STDOUTPUT,ancho, 5 + i, getProductoName(Producto), NONE);
        ancho += 7;

        char* total = malloc(50 + 1);
        sprintf(total,"%i",getProductoExistentes(Producto));
        
        winprint(STDOUTPUT,ancho, 5 + i, total, NONE);
        ancho += digitos_existentes + 1;

        sprintf(total,"$%.2f",getProductoPrecio(Producto));
        winprint(STDOUTPUT,ancho, 5 + i, total, NONE);
        ancho += digitos_precio + 1;

        sprintf(total,"Estante %c",getProductoEstante(Producto));
        winprint(STDOUTPUT,ancho, 5 + i, total, NONE);
    }
    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT) - 2,"< Presiona cualquier tecla para continuar >",DIM);
    getchar();
}

int salir(){
    exit(0);
};