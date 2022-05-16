#ifndef SMARTIO_H
#define SMARTIO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include "sys.h"

typedef int (*delimitador)(void*);

//IO
// int evaluarNombreDeProducto(char* Src);
int evaluarNombreDelCliente(char* Src);
// int evaluarExistencia(int* Src);
// int evaluarPrecio(char* Src);
int evaluarInt(int* Dest);
int evaluarDouble(double* Dest);
int evaluarUbicacion(char* Src);
int evaluarNumeroTelefonico(char* Src);
// int evaluarNumero(char* Dest);
int evaluarCorreo(char* Des);

void cleanInput();

//STR
// int stringlen(const char* text);
// char* cp(char* dest, char* src);
// int cmp(char* dest, char* src);
// char* cat(char* dest, char* src);

//Conversiones
void int2str(int src, char* dest);
void double2str(double src, char* dest);

//File Manager
int getFileLines(char* filename);

//TEMP
int input(char* bg_titulo, char* titulo, void* dest, int (*funcion)(void*));
#endif