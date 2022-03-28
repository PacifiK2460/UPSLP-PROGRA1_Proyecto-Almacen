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

void salir();

//Almacen
typedef struct Productos Productos;
typedef struct Producto Producto;
typedef struct Pedidos Pedidos;

struct Productos* newProductos();
struct Producto* newProducto();
struct Producto* getItem(struct Productos* Src, int index);
int addProduct(struct Productos* Src,char* nombre, int existentes, double precio, char estante,int id);
int getSize(struct Productos* Src);
int saveAlmacen(struct Productos* Dest);
int loadAlmacen(struct Productos* Dest);

char* getName(struct Producto* Src);
int getExistentes(struct Producto* Src);
double getPrice(struct Producto* Src);
char getEstante(struct Producto* Src);
//Pedidos

#endif