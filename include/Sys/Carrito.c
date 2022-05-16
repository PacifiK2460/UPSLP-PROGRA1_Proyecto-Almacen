#include "../sys.h"

void imprimirCarrito(Pedido Pedido, int x, int y){
    TABLE carritoTable;
    prepareTableData(&carritoTable, 4, Pedido.productos+1);
    //TABLE* carritoTable = newTable(4, Pedido.productos+1);
    double total = 0;
    tableSetHeaders(&carritoTable, (char*[]){
        "MODELO",
        "CANTIDAD",
        "PRECIO UNITARIO",
        "SUBTOTAL"
    });

    char *precio;
    char *sub;
    char *cant;
    char empty[] = "  ";
    for(int fila = 0; fila < Pedido.productos; fila++){
        Producto temp = getProductoByName(Pedido.Detalles[fila].nombre);
        total += temp.precioUnitario * Pedido.Detalles[fila].cantidad;

        precio = malloc(30);
        sub = malloc(30);
        cant = malloc(30);

        double2str(temp.precioUnitario, precio);
        double2str(temp.precioUnitario * (double)Pedido.Detalles[fila].cantidad, sub); 
        int2str(Pedido.Detalles[fila].cantidad, cant);

        tableAppendRow(&carritoTable,
            Pedido.Detalles[fila].nombre,
            cant,
            precio,
            sub
        );
    }

    precio = malloc(30);
    double2str(total, precio);
    tableAppendRow(&carritoTable,
        empty,
        empty,
        "TOTAL",
        precio
    );

    printTable(&carritoTable,x,y);

}
