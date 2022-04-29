#include "../sys.h"

void imprimirCarrito(Pedido Pedido, int x, int y){
    TABLE* carritoTable = newTable(4, Pedido.productos);
    tableSetHeaders(carritoTable, (char*[]){
        "MODELO",
        "CANTIDAD",
        "PRECIO UNITARIO",
        "SUBTOTAL"
    });

    char *precio;
    char *sub;
    char *cant;
    for(int fila = 0; fila < Pedido.productos; fila++){
        Producto temp = getProductoByName(Pedido.Detalles[fila].nombre);

        precio = malloc(30);
        sub = malloc(30);
        cant = malloc(30);

        double2str(temp.precioUnitario, precio);
        double2str(temp.precioUnitario * Pedido.Detalles[fila].cantidad, sub); 
        int2str(Pedido.Detalles[fila].cantidad, cant);

        tableAppendRow(carritoTable,
            Pedido.Detalles[fila].nombre,
            cant,
            precio,
            sub
        );
    }

    if(x == -1){
        x = (getcols(STDOUTPUT) - getTotalToerico(carritoTable))/2;
    }

    printTable(carritoTable,x,y);

}
