#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "IO.h"
#include "win.h"

#define randrang(max, min) (rand() % (max - min + 1)) + min;

enum ERRORES { OK, ERROR, FATAL_ERROR };

//Interfaz
    void consultarAlmacen();
    void actualizarAlmacen();

    void registrarPedido();
    void consultarPedido();
    void registrarEntrega();
    void modificarPedido();

//Logica
    int digitos(int n);
    int sumarExistentes();
    void nuevoProducto();
    void salir();

//Carrito
    //Carrito
    typedef struct Carrito Carrito;
    struct Carrito* newCarrito();
    int getCarritoSize(struct Carrito* Src);

    //Detalle
    typedef struct Detalle Detalle;
    struct Detalle* newDetalle();struct Detalle* getDetalleByIndex(struct Carrito* Src, int index);
    char* getDetalleNombre(struct Detalle* Src);
    int getDetalleCantidad(struct Detalle* Src);
    int appendDetalle(struct Detalle* Src, struct Carrito* Dest);
    int addDetalle(struct Carrito* Dest, char* nombre, int cantidad);

//Pedido
    typedef struct Pedido Pedido;
    struct Pedido* newPedido();
    struct Pedido* getPedidoByIndex(struct Pedidos* Src, int index);
    int getPedidoNumero(struct Pedido* Src);
    char getPedidoEstado(struct Pedido* Src);
    char* getPedidoNombre(struct Pedido* Src);
    char* getPedidoTelefono(struct Pedido* Src);
    char* getPedidoCorreo(struct Pedido* Src);
    struct Carrito* getPedidoCarrito(struct Pedido* Src);

//Pedidos
    typedef struct Pedidos Pedidos;
    struct Pedidos* newPedidos();
    int getPedidosSize(struct Pedidos* Src);
    int appendPedido(struct Pedido* Src, struct Pedidos* Dest);
    int addPedido(struct Pedidos* Dest, char estado, char* nombre_del_cliente, char* telefono_del_cliente, char* correo, struct Carrito* Carrito, int id);
    int savePedidos(struct Pedidos* Src);
    int loadPedidos(struct Pedidos* Dest);

    //Logica
    void input(char* bg_titulo, char* titulo, char* dest, int delimitar ( int (*f)(char*) ));
    void mostrarPedidosPor(char tipo);
    void pedidosActivos();
    void pedidosEntregados();
    void pedidosCancelados();
    void buscarID(char* ID);
    void numeroDePedido();
    void regresar();

//Producto
    typedef struct Producto Producto;
    struct Producto* newProducto();
    struct Producto* getProductoByName(struct Productos* Src, char* name);
    char* getProductoName(struct Producto* Src);
    int getProductoExistentes(struct Producto* Src);
    double getProductoPrecio(struct Producto* Src);
    char getProductoEstante(struct Producto* Src);
    struct Producto* getProductoByIndex(struct Productos* Src, int index);
    int appendProduct(struct Producto* Src, struct Productos* Dest);

//Productos
    typedef struct Productos Productos;
    struct Productos* newProductos();
    int getProductosSize(struct Productos* Src);
    int modExistencia(struct Productos* Src, int index,int cant,char op);
    int addProduct(struct Productos* Dest,char* nombre, int existentes, double precio, char estante);
    int loadAlmacen(struct Productos* Dest);
    int saveAlmacen(struct Productos* Dest);
#endif