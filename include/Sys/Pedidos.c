#include "../sys.h"

int getPedidosSize(){
    return getFileLines("Pedidos");
}

int appendPedido(Pedido Src){
    FILE* file;
    int fila = 0;
    file = fopen("Pedidos", "a+");
    if(file == NULL) return -1;

    fprintf(file,
        "%i %c %s %s %s %i ",
        Src.numero, Src.estado, Src.nombre_de_cliente,
        Src.telefono_de_cliente, Src.correo, Src.productos
    );

    for(int producto = 0; producto < Src.productos; producto++){
        fprintf(file,
        "%s %i ", Src.Detalles[producto].nombre, Src.Detalles[producto].cantidad);
    }

    fprintf(file,"\n");

    fclose(file);
    return 1;
}

//TODOS
int loadPedidoFile(Pedido Destination[]){
    FILE* file;
    int fila = 0;
    file = fopen("Pedidos", "a+");
    if(file == NULL) return -1;

    for(Pedido Temp; fscanf(file,
    "%i %c %s %s %s %i ",&Temp.numero, &Temp.estado, &Temp.nombre_de_cliente,
    &Temp.telefono_de_cliente, &Temp.correo, &Temp.productos) == 6; ){
        Destination[fila].numero = Temp.numero;
        Destination[fila].estado = Temp.estado;

        strcpy(Destination[fila].nombre_de_cliente, Temp.nombre_de_cliente);
        strcpy(Destination[fila].telefono_de_cliente, Temp.telefono_de_cliente);
        strcpy(Destination[fila].correo, Temp.correo);

        Destination[fila].productos = Temp.productos;

        Destination[fila].Detalles = malloc(Temp.productos * sizeof(*Destination[fila].Detalles));

        for(int producto=0; producto < Destination[fila].productos; producto++){
            Detalle ProductoBuffer;
            if(fscanf(file, "%s %i \n", &ProductoBuffer.nombre, &ProductoBuffer.cantidad) != 2) break;
            strcpy(Destination[fila].Detalles[producto].nombre, ProductoBuffer.nombre);
            Destination[fila].Detalles[producto].cantidad = ProductoBuffer.cantidad;

        }
        fila++;
    }
    fclose(file);
    return 1;
}

int savePedidoFile(Pedido Source[], int filas){
    remove("Pedidos");
    FILE* file;
    file = fopen("Pedidos","w+");
    if(file == NULL) return -1;
    for(int fila = 0; fila < filas; fila++){
        fprintf(file,"%i %c %s %s %s %i ",Source[fila].numero,
        Source[fila].estado, Source[fila].nombre_de_cliente,
        Source[fila].telefono_de_cliente, Source[fila].correo,
        Source[fila].productos);
        
        for(int producto = 0; producto < Source[fila].productos; producto++){
            fprintf(file,"%s %i ",Source[fila].Detalles[producto].nombre,
            Source[fila].Detalles[producto].cantidad);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 1;
}

void imprimirPedido(Pedido Src, int x, int y){
    //Declaramos info
    char RowBuffer1[100] = "Pedido: ";
    char RowBuffer2[100] = "ID: ";
    char RowBuffer3[100] = "NOMBRE DEL CLIENTE: ";
    char RowBuffer4[100] = "TÉLEFONO: ";
    char RowBuffer5[100] = "CORREO: ";

    //Acomodamos la info
    {

        switch (Src.estado)
        {
            case 'A':
                strcat(RowBuffer1,"\e[1;93m");
                strcat(RowBuffer1,"Activo");
                break;
            
            case 'E':
                strcat(RowBuffer1,"\e[1;92m");
                strcat(RowBuffer1,"Entregado");
                break;
            case 'C':
                strcat(RowBuffer1,"\e[1;91m");
                strcat(RowBuffer1,"Cancelado");
                break;
        }
        strcat(RowBuffer1, RESET);
        strcat(RowBuffer2, BOLD);
        strcat(RowBuffer3, BOLD);
        strcat(RowBuffer4, BOLD);
        strcat(RowBuffer5, BOLD);

        char temp[100] = {0};
        int2str(Src.numero, temp);
        strcat(RowBuffer2, temp);

        strcat(RowBuffer3, Src.nombre_de_cliente);
        strcat(RowBuffer4, Src.telefono_de_cliente);
        strcat(RowBuffer5, Src.correo);

        strcat(RowBuffer2, RESET);
        strcat(RowBuffer3, RESET);
        strcat(RowBuffer4, RESET);
        strcat(RowBuffer5, RESET);

    }

    //Imprimimos esa info
    {
        winprint(STDOUTPUT, x, y++, RowBuffer1);
        winprint(STDOUTPUT, x, y++, RowBuffer2);
        winprint(STDOUTPUT, x, y++, RowBuffer3);
        winprint(STDOUTPUT, x, y++, RowBuffer4);
        winprint(STDOUTPUT, x, y++, RowBuffer5);
    }

    imprimirCarrito(Src, -1, y+2);
}