#include "../sys.h"

// Estructuras de la interfaz
struct Producto{
    char nombre[7];
    int existentes;
    double precioUnitario;
    char estante;

    struct Producto* next;
};

struct Productos{
    struct Producto* Head;
    struct Producto* temp;
    int size;
};

char* getName(struct Producto* Src){
    return Src->nombre;
}

int getExistentes(struct Producto* Src){
    return Src->existentes;
}

double getPrice(struct Producto* Src){
    return Src->precioUnitario;
}

char getEstante(struct Producto* Src){
    return Src->estante;
}

struct Productos* newProductos(){
    struct Productos* temp = (struct Productos*)calloc(1,sizeof(struct Productos));
    if(temp == NULL) return NULL;
    temp->Head = NULL;
    temp->size = 0;
    temp->temp = NULL;

    return temp;
}

struct Producto* newProducto(){
    struct Producto* temp = (struct Producto*)calloc(1,sizeof(struct Producto));
    if(temp == NULL) return NULL;
    temp->next = NULL;
    return temp;
}

int getSize(struct Productos* Src){
    if(Src == NULL) return ERROR;
    return Src->size;
}

struct Producto* getItem(struct Productos* Src, int index){
    if(Src == NULL) return NULL;
    if(index > getSize(Src) || index < 0) return NULL;
    if(index == 0) return Src->Head;

    Src->temp = Src->Head;
    while (index >= 1){
        Src->temp = Src->temp->next;
        index -= 1;
    }

    return Src->temp;
}

int removeProduct(struct Productos* Src, int index){
    if(Src == NULL) return ERROR;
    if(index > getSize(Src) || index < 0) return ERROR;

    if(index == 0){
        Src->temp = Src->Head->next;
        free(Src->Head);
        Src->Head = Src->temp;
        return OK;
    }

    Src->temp = Src->Head;
    while(index > 0){
        Src->temp = Src->temp->next;
        index -= 1;
    }

    struct Producto* supertemp;
    supertemp = Src->temp->next;
    Src->temp->next = Src->temp->next->next;
    free(supertemp);

    return OK;
}

int appendProduct(struct Producto* Src, struct Productos* Dest){
    if(Dest == NULL) return ERROR;

    if(getSize(Dest) == 0){
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

int loadAlmacen(struct Productos* Dest){
    if(Dest == NULL) return ERROR;

    FILE* file = fopen("Almacen", "rb");
    if(file == NULL){
        return ERROR;
    }

    struct Producto* buffer;
    buffer = newProducto();

    while(fread(buffer,sizeof(struct Producto),1,file) == 1){
        buffer->next = NULL;
        appendProduct(buffer,Dest);
        buffer = newProducto();
    }

    fclose(file);
    return OK;
}

int saveAlmacen(struct Productos* Dest){
    if(Dest == NULL) return ERROR;
    FILE* file = fopen("Almacen","wb");

    if(file == NULL) return ERROR;
    for(int i = 0; i < getSize(Dest); i++){
        fwrite(getItem(Dest,i),sizeof(struct Producto),1,file);
    }

    fclose(file);
    return OK;
}

int modExistencia(struct Productos* Src, int index,int cant,char op){
    if(Src == NULL) return ERROR;
    if(index > getSize(Src) || index < 0) return ERROR;

    Src->temp = Src->Head;
    while(index > 0){
        Src->temp = Src->temp->next;
        index -= 1;
    }

    if(op == 'A') Src->temp->existentes += cant;
    else if(op == 'S') Src->temp->estante = cant;
    else return ERROR;

    return OK;
}

int modificarExistentes(){
    struct Productos* src = newProductos();
    struct Producto* Producto;
    loadAlmacen(src);
}

int sumarExistentes(){
    struct Productos* src = newProductos();
    struct Producto* Producto;
    loadAlmacen(src);
}

int addProduct(struct Productos* Dest,char* nombre, int existentes, double precio, char estante){
    struct Producto* new = newProducto();
    if(new == NULL) return ERROR;
    strcpy(new->nombre, nombre);
    new->existentes = existentes;
    new->precioUnitario = precio;
    new->estante = estante;
    return appendProduct(new,Dest);
}

int digitos(int n){
    return floor(log10(n) + 1);
}

void input(struct Productos* src, char* bg_titulo, char* titulo, char* dest, int delimitar ( int (*f)(char*) )){
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

void nuevoProducto(){
    struct Productos* src = newProductos();
    struct Producto* Producto;
    loadAlmacen(src);

    char nombre[7];
    char existencia[10];
    char precio[10];
    char ubicacion[2];
    input(src,"AÑADIR PRODUCTO","MODELO",nombre,evaluarNombre);
    input(src,"AÑADIR PRODUCTO","EXISTENCIA",existencia,evaluarExistencia);
    input(src,"AÑADIR PRODUCTO","PRECIO",precio,evaluarPrecio);
    input(src,"AÑADIR PRODUCTO","UBICACIÓN",ubicacion,evaluarUbicacion);

    int existentes;
    double precios;
    char ubi;

    sscanf(existencia, "%i",&existentes);
    sscanf(precio,"%d", &precios);
    ubi = ubicacion[0];

    addProduct(src,nombre,existentes,precios,ubi);
    remove("Almacen");
    saveAlmacen(src);

    box(STDOUTPUT,DIM);
    printinthemiddle(STDOUTPUT,getcols(STDOUTPUT)/2,"AÑADIDO EXITOSO",BOLD);

    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT)-2,"< Presione cualquier tecla para continuar >",DIM);
    getchar();
}

// Acciones
void consultarAlmacen(){
    struct Productos* Almacen = newProductos();
    struct Producto* Producto;
    loadAlmacen(Almacen);

    //Para alinear la info, obtenemos la cantidad mas grande;
    int mayor_existencia = 1, mayor_precio = 1;
    for(int i = 0; i < getSize(Almacen); i++){
        if( getItem(Almacen,i)->existentes > mayor_existencia )
            mayor_existencia = getItem(Almacen,i)->existentes;
        if( getItem(Almacen,i)->precioUnitario > mayor_precio )
            mayor_precio = getItem(Almacen,i)->precioUnitario;
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

    for(int i = 0; i < getSize(Almacen); i++ ){
        Producto = getItem(Almacen,i);
        ancho = 6 + 1 + digitos_existentes + 1 + digitos_precio + 1 + 10;
        ancho = (getcols(STDOUTPUT) - ancho)/2;
        winprint(STDOUTPUT,ancho, 5 + i, getName(Producto), NONE);
        ancho += 7;

        char* total = malloc(50 + 1);
        sprintf(total,"%i",getExistentes(Producto));
        
        winprint(STDOUTPUT,ancho, 5 + i, total, NONE);
        ancho += digitos_existentes + 1;

        sprintf(total,"$%.2f",getPrice(Producto));
        winprint(STDOUTPUT,ancho, 5 + i, total, NONE);
        ancho += digitos_precio + 1;

        sprintf(total,"Estante %c",getEstante(Producto));
        winprint(STDOUTPUT,ancho, 5 + i, total, NONE);
    }
    printinthemiddle(STDOUTPUT,getrows(STDOUTPUT) - 2,"< Presiona cualquier tecla para continuar >",DIM);
    getchar();
}

void salirmenu(){
    return;
}

void actualizarAlmacen(){
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
        salirmenu
    };
    menu = newMenu(STDOUTPUT,(getrows(STDOUTPUT) - 7)/2, (getcols(STDOUTPUT) - 30) / 2 ,30,4, opciones,4, Funciones);

    printmenu();
    focusMenu(menu);
}
void registrarEntrega(){}
void modificarPedido(){}

void salir(){
    printf("FUNCION SALIR!");
    exit(0);
};