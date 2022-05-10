#include "../sys.h"

typedef struct FILA{
    char** columna;
}FILA;

int digitos(int n){
    return floor(log10(n) + 1);
}

int listarProductos(char* titulo, Producto Almacen[], int productos){
    //Pedimos el producto
    NEW_SCREEN();
    MENU itemSeleccionado;
    char* nombres[productos];
    char** ids= (char**)malloc(productos * sizeof(char**));

    printf(CLEAR);

    for(int i=0; i < productos; i++){
        ids[i] = malloc(20);
        cp(ids[i], "Existentes: ");
        
        nombres[i] = Almacen[i].nombre;

        char temp[5] = {0};
        int2str(Almacen[i].existentes, temp);

        cat(ids[i], temp);
    }

    setMenuData(&itemSeleccionado,STDOUTPUT,4,4,7,nombres,ids);

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

int modificar(char accion){
    //struct Productos* src = newProductos();
    //struct Producto* Producto;
    NEW_SCREEN();
    int productos = getAlmacenSize();
    Producto Almacen[productos];

    char titulo[] = BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
                    RESET "  " RESET
                    BRGB(75,75,75) FRGB(255,255,255) " ACTUALIZACIÓN DE ALMACEN "
                    RESET "  " RESET
                    BRGB(16,158,94) FRGB(255,255,255) " MODIFICAR PRODUCTO ";

    winprint(STDOUTPUT,4,2, titulo);
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " continuar ");

    {// File Reading
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

    int idx;
    do{
        idx = listarProductos(titulo, Almacen, productos);
        if(idx == -1) break;
        if(idx < 0 || idx > productos-1){
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No puedes modificar un producto inexistente");
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
            getchar();
            continue;
        }
        break;
    }while(1);
    if(idx == -1) return 0;

    char sum[10] = {0};
    char titulo2[100] = BOLD FRGB(185, 251, 192) "CANTIDAD A ";
    //cat(titulo2,BOLD FRGB(185, 251, 192) "CANTIDAD A ");
    if(accion == 's'){
        cat(titulo2,"SUMAR");
    } else {
        cat(titulo2,"PONER");
    }
    int s;
    while(1){
        input(titulo,titulo2,sum, &evaluarExistencia);
        sscanf(sum,"%i",&s);
        if(s > 0) break;

        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM  "Agrega productos mayores a 0" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
        getchar();
    }
    
    if(accion == 's') Almacen[idx].existentes += s;
    else Almacen[idx].existentes = s;
    //Almacen[idx].existentes += s;
    //modExistencia(src,idx,s,'S');

    printf(CLEAR);
    winprint(STDOUTPUT,4,2, titulo);

    if(saveAlmacenFile(Almacen, productos) == -1){
        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM  "Hubo un error al guardar el archivo, el progreso se perdio" RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " finalizar ");
        getchar();
        return 0;
    }

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM  "Cambios guardados correctamente" RESET);
    winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " finalizar ");
    getchar();

    return 1;
}

int modificarExistentes(){
    return modificar('p');
}

int sumarExistentes(){
    return modificar('s');
}

int nuevoProducto(){
    int productos = getAlmacenSize();
    Producto Almacen[productos];
    loadAlmacenFile(Almacen);
    char titulo[] = BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
                    RESET "  " RESET
                    BRGB(75,75,75) FRGB(255,255,255) " ACTUALIZACIÓN DE ALMACEN "
                    RESET "  " RESET
                    BRGB(16,158,94) FRGB(255,255,255) " AGREGAR PRODUCTO ";

    char nombre[7] = {0};
    char existencia[10] = {0};
    char precio[10] = {0};
    char ubicacion[2] = {0};
    do{
        printf(CLEAR);
        winprint(STDOUTPUT,4,2, titulo);
        input(titulo,BOLD FRGB(185, 251, 192) "MODELO",nombre,&evaluarNombreDeProducto);
        if ( getProductoByName(nombre).existentes != -1 ){
            winprint(STDOUTPUT,4,2, titulo);
            printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No puedes agregar productos repetidos." RESET);
            winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
            getchar();
            winprint(STDOUTPUT,4,2, titulo);
            continue;
        }
        break;
    }while(1);
    
    int existentes;
    double precios;
    char ubi;
    while(1){
        printf(CLEAR);
        winprint(STDOUTPUT,4,2, titulo);
        input(titulo,BOLD FRGB(185, 251, 192) "EXISTENCIA",existencia,&evaluarExistencia);
        sscanf(existencia, "%i",&existentes);

        if(existentes > 0) break;

        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No puedes agregar productos repetidos." RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
        getchar();
    }

    while(1){
        printf(CLEAR);
        winprint(STDOUTPUT,4,2, titulo);
        input(titulo,BOLD FRGB(185, 251, 192) "PRECIO",precio,&evaluarPrecio);
        sscanf(precio,"%lf", &precios);
        if(precios > 0) break;

        printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)/2,DIM "No puedes poner precios negativos." RESET);
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "cualquier tecla"  RESET DIM  " reintentar ");
        getchar();
    }

    input(titulo,BOLD FRGB(185, 251, 192) "UBICACIÓN",ubicacion,&evaluarUbicacion);

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
    //MENU* menu;
    NEW_SCREEN();
    Funciones Funciones[] = {
        sumarExistentes,
        modificarExistentes,
        nuevoProducto,
        regresar
    };

    MENU menu;
    setMenuData(&menu,NULL,4,4,4,
        (char*[]){
            "Sumar Existentes",
            "Modificar Existentes",
            "Agregar Producto",
            "Regresar"
        },
        (char*[]){
            "Suma la cantidad ingresada al producto seleccionado",
            "Establece la cantidad ingresada al producto selecccionado",
            "Crea un nuevo espacio en el almacen",
            "Regresa al menu principal"
        }
    );


    while(1){
        printf(CLEAR);
        winprint(STDOUTPUT,4,2,BRGB(75,75,75) FRGB(255,255,255) " MENU PRINCIPAL "
                                RESET "  " RESET
                                BRGB(16,158,94) FRGB(255,255,255) " ACTUALIZACIÓN DE ALMACEN " );
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-3,RESET FRGB(185, 251, 192)  "↓↑"     RESET DIM  " Arriba / Abajo ");
        winprint(STDOUTPUT,4,getrows(STDOUTPUT)-2,RESET FRGB(185, 251, 192)  "enter"  RESET DIM  " Seleccionar "); 
        focusMenu(&menu);
        if(menu.selected == 3 || menu.selected == -1) break;
        Funciones[menu.selected]();
    }
    CLOSE_SCREEN();
}

// Acciones
int consultarAlmacen(){
    NEW_SCREEN();
    int productos = getAlmacenSize();
    Producto Almacen[productos];

    //Imprimimos / UI
    {
        //printf(CLEAR);
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
    char* existentes;
    char* precio;
    char* estante;
    for(int fila = 0; fila < productos; fila++){
        //Producto = getProductoByIndex(&Almacen,fila);

        existentes = (char*)malloc(30 * sizeof(char));
        precio = (char*)malloc(30 * sizeof(char));
        estante = (char*)malloc(2 * sizeof(char));
        int2str(Almacen[fila].existentes, existentes);
        double2str(Almacen[fila].precioUnitario, precio);

        estante[0] = Almacen[fila].estante;
        estante[1] = '\0';
        //double2str(getProductoPrecio(Producto), precio);
        //char est = getProductoEstante(Producto);


        tableAppendRow(dataTable,
            Almacen[fila].nombre,
            existentes,
            precio,
            estante
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

    printTable(dataTable, -1,4);
    
    // for(int i=0; i<filas;i++){
    //     free(data[i]);
    // }
    //freeTable(dataTable);
    //free(Almacen);
    //free(Producto);
    getchar();
    CLOSE_SCREEN();
}

int salir(){
    printf("\e[?1049l");
    printf(SHOW_CURSOR);
    printf(RESET);
    atexit(reset_tty);
    exit(0);
};