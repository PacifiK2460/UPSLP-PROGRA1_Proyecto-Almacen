#ifndef SMARTIO_H
#define SMARTIO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//IO
int evaluarNombre(char* Src);
int evaluarExistencia(char* Src);
int evaluarPrecio(char* Src);
int evaluarUbicacion(char* Src);
int evaluarCorreo(char* Des);
int evaluarNumero(char* Dest);
int evaluarNombreDelCliente(char* Src);

//STR
int stringlen(char* text);
char* cp(char* dest, char* src);
int cmp(char* dest, char* src);
char* cat(char* dest, char* src);

//Conversiones
void int2str(int src, char* dest);
void double2str(double src, char* dest);

//File Manager
int getFileLines(char* filename);
#endif