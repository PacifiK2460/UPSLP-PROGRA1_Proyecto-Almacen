#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "IO.h"
#include "win.h"

#define randrang(max, min) (rand() % (max - min + 1)) + min;

enum ERRORES { OK, ERROR, FATAL_ERROR };

typedef int (*delimitador)(char*);

//Productos
    typedef struct _Producto{
        char nombre[7];
        int existentes;
        double precioUnitario;
        char estante;
    }Producto;

    typedef struct _Detalle{
        char nombre[7];
        int cantidad;
    }Detalle;

    typedef struct _Pedido{
        int numero;
        char estado;
        char nombre_de_cliente[51];
        char telefono_de_cliente[11];
        char correo[51];
        
        Detalle Detalles[];
    }Pedido;

    //New
    int getAlmacenSize();
    int loadAlmacenFile(Producto Destination[]);
    int saveAlmacenFile(Producto Source[]);
    int appendAlmacenProduct(char* nombre, int existentes, double precio, char estante);

    //DEPRECATED
    Producto getProductoByIndex(Productos Src, int index);
    int getProductosSize(Productos* Src);
    Producto getProductoByName(Productos* Src, char* name);
    int modExistencia(Productos* Src, int index,int cant,char op);
    int addProduct(Productos* Dest,char* nombre, int existentes, double precio, char estante);
    int loadAlmacen(Productos* Dest);
    int saveAlmacen(Productos* Dest);
    int appendProduct(Producto* Src, Productos* Dest);

//Producto
    char* getProductoName(Producto* Src);
    int getProductoExistentes(Producto* Src);
    double getProductoPrecio(Producto* Src);
    char getProductoEstante(Producto* Src);

//Interfaz
    int consultarAlmacen();
    int actualizarAlmacen();
    int registrarPedido();
    int consultarPedido();
    int registrarEntrega();
    int modificarPedido();
    int regresar();

//Pedidos
    Pedidos* newPedidos();
    int getPedidosSize(Pedidos* Src);
    Pedido* getPedidoByIndex(Pedidos* Src, int index);
    int appendPedido(Pedido* Src, Pedidos* Dest);
    int savePedidos(Pedidos* Src);
    int loadPedidos(Pedidos* Dest);
    Pedido* getPedidosHead(Pedidos* Src);

    //Logica
    void input(char* bg_titulo, char* titulo, char* dest, int (*funcion)(char*));
    int mostrarPedidosPor(char tipo);
    int pedidosActivos();
    int pedidosEntregados();
    int pedidosCancelados();
    int buscarID(char* ID);
    int numeroDePedido();

//Pedido
    Pedido* newPedido();
    int getPedidoNumero(Pedido* Src);
    char getPedidoEstado(Pedido* Src);
    char* getPedidoNombre(Pedido* Src);
    char* getPedidoTelefono(Pedido* Src);
    char* getPedidoCorreo(Pedido* Src);
    Carrito* getPedidoCarrito(Pedido* Src);

//Carrito
    //Carrito
    Carrito* newCarrito();
    int getCarritoSize(Carrito* Src);

    //Detalle
    Detalle* newDetalle();
    Detalle* getDetalleByIndex(Carrito* Src, int index);
    char* getDetalleNombre(Detalle* Src);
    int getDetalleCantidad(Detalle* Src);
    int appendDetalle(Detalle* Src, Carrito* Dest);
    int addDetalle(Carrito* Dest, char* nombre, int cantidad);

    int addPedido(Pedidos* Dest, char estado, char* nombre_del_cliente, char* telefono_del_cliente, char* correo, struct Carrito* Carrito, int id);

//Logica
    int digitos(int n);
    int sumarExistentes();
    int nuevoProducto();
    int salir();

#define newProducto() malloc(sizeof(Producto))
#define newProductos() malloc(sizeof(Productos))

#endif