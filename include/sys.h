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
    typedef struct Pedidos Pedidos;
    typedef struct Producto Producto;
    typedef struct Productos Productos;
    typedef struct Pedido Pedido;
    typedef struct Carrito Carrito;
    typedef struct Detalle Detalle;
    struct Producto* getProductoByIndex(struct Productos* Src, int index);
    int getProductosSize(struct Productos* Src);
    struct Producto* getProductoByName(struct Productos* Src, char* name);
    int modExistencia(struct Productos* Src, int index,int cant,char op);
    int addProduct(struct Productos* Dest,char* nombre, int existentes, double precio, char estante);
    int loadAlmacen(struct Productos* Dest);
    int saveAlmacen(struct Productos* Dest);
    int appendProduct(struct Producto* Src, struct Productos* Dest);

//Producto
    char* getProductoName(struct Producto* Src);
    int getProductoExistentes(struct Producto* Src);
    double getProductoPrecio(struct Producto* Src);
    char getProductoEstante(struct Producto* Src);

//Interfaz
    int consultarAlmacen();
    int actualizarAlmacen();
    int registrarPedido();
    int consultarPedido();
    int registrarEntrega();
    int modificarPedido();
    int regresar();

//Pedidos
    struct Pedidos* newPedidos();
    int getPedidosSize(struct Pedidos* Src);
    struct Pedido* getPedidoByIndex(struct Pedidos* Src, int index);
    int appendPedido(struct Pedido* Src, struct Pedidos* Dest);
    int savePedidos(struct Pedidos* Src);
    int loadPedidos(struct Pedidos* Dest);
    struct Pedido* getPedidosHead(struct Pedidos* Src);

    //Logica
    void input(char* bg_titulo, char* titulo, char* dest, int (*funcion)(char*));
    int mostrarPedidosPor(char tipo);
    int pedidosActivos();
    int pedidosEntregados();
    int pedidosCancelados();
    int buscarID(char* ID);
    int numeroDePedido();

//Pedido
    struct Pedido* newPedido();
    int getPedidoNumero(struct Pedido* Src);
    char getPedidoEstado(struct Pedido* Src);
    char* getPedidoNombre(struct Pedido* Src);
    char* getPedidoTelefono(struct Pedido* Src);
    char* getPedidoCorreo(struct Pedido* Src);
    struct Carrito* getPedidoCarrito(struct Pedido* Src);

//Carrito
    //Carrito
    struct Carrito* newCarrito();
    int getCarritoSize(struct Carrito* Src);

    //Detalle
    struct Detalle* newDetalle();struct Detalle* getDetalleByIndex(struct Carrito* Src, int index);
    char* getDetalleNombre(struct Detalle* Src);
    int getDetalleCantidad(struct Detalle* Src);
    int appendDetalle(struct Detalle* Src, struct Carrito* Dest);
    int addDetalle(struct Carrito* Dest, char* nombre, int cantidad);

    int addPedido(struct Pedidos* Dest, char estado, char* nombre_del_cliente, char* telefono_del_cliente, char* correo, struct Carrito* Carrito, int id);

//Logica
    int digitos(int n);
    int sumarExistentes();
    int nuevoProducto();
    int salir();

#define newProducto() malloc(sizeof(struct Producto*))
#define newProductos() malloc(sizeof(struct Productos*))

#endif