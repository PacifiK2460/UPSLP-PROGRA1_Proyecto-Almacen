#ifndef SMARTIO_H
#define SMARTIO_H

#include <stdio.h>

#define size(a) sizeof(a)/sizeof(a[0])

#define Nombre(src) evaluarNombre(src, size(src))
#define Existencia(src) evaluarExistencia(src, size(src))
#define Precio(src) evaluarPrecio(src, size(src))
#define Ubicacion(src) evaluarUbicacion(src, size(src))
#define Correo(src) evaluarCorreo(src, size(src))
#define Numero(src) evaluarNumero(src, size(src))

int evaluarNombre(char* Src, int size);
int evaluarExistencia(char* Src, int size);
int evaluarPrecio(char* Src, int size);
int evaluarUbicacion(char* Src, int size);
int evaluarCorreo(char* Des, int size);
int evaluarNumero(char* Dest, int size);

#endif