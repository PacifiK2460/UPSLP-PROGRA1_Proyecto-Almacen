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

//STR
int len(char* text);
char * cp(char* dest, char* src);
int cmp(char* dest, char* src);
char * strcat(char *dest, char *src);

//Conversiones
char* int2str(int src);
char* double2str(double src);
#endif