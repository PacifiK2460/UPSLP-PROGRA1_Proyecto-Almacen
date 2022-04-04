#include "../sys.h"

struct Productos{
    struct Producto* Head;
    struct Producto* temp;
    int size;
};

struct Productos* newProductos(){
    struct Productos* temp = (struct Productos*)calloc(1,sizeof(struct Productos));
    if(temp == NULL) return NULL;
    temp->Head = NULL;
    temp->size = 0;
    temp->temp = NULL;

    return temp;
}

int getProductosSize(struct Productos* Src){
    if(Src == NULL) return ERROR;
    return Src->size;
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
    else if(op == 'S') Src->temp->existentes = cant;
    else return ERROR;

    return OK;
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