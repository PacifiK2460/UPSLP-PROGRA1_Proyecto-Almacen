//#include "include/sys.h"
#include <stdio.h>

int plus_one = [](const int x){
    return x + 1;
}

int main(){
    // struct Productos* Almacen = newProductos();
    // loadAlmacen(Almacen);
    // // addProduct(Almacen,"EST123", 1000,4599,L'A');
    // // addProduct(Almacen,"EST456", 980,7000,L'B');
    // // addProduct(Almacen,"EST789", 3000,5699,L'C');
    // // saveAlmacen(Almacen);
    // for(int i = 0; i < getSize(Almacen); i++ ) {
    //     printf("%s | %i | %c\n", getName(getItem(Almacen,i)), getExistentes(getItem(Almacen,i)), getEstante(getItem(Almacen,i)));
    // }

    printf("%i",plus_one(2));
}
