#ifndef SMARTIO_H
#define SMARTIO_

#include <stdio.h>

#define size(x) sizeof(x)/sizeof(x[0])

int getText(char* Dest, int size);
int evaluarNombre(char* Src);
int evaluarExistencia(char* Src);
int evaluarPrecio(char* Src);
int evaluarUbicacion(char* Src);

int getNombre(char* Dest);
int getTel(char* Dest);
int evaluarCorreo(char* Dest);
int evaluarPedidos(char* Dest);

#endif