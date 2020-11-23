/*
 * Afiche.h
 *
 *  Created on: 23 nov. 2020
 *      Author: 54113
 */

#ifndef AFICHE_H_
#define AFICHE_H_

#define NOMBREAFICHE_LEN 128

typedef struct
{
    int idCliente;
    int idAfiche;
    int cantidad;
    char zona[NOMBREAFICHE_LEN];
    char nombreArchivo[NOMBREAFICHE_LEN];
    int aCobrar;
}Afiche;

Afiche* afiche_new();
Afiche* afiche_newParametros(char* idCliStr,char* idAfiStr,char* cantidadStr, char* nombreArchivoStr, char* zonaStr, char* aCobrarStr);

int afi_Add(Afiche* this[]);
void afi_detele(Afiche* this);

int afi_setId(Afiche* this,int id);
int afi_getId(Afiche* this,int* id);
int afi_setIdTxt(Afiche* this,char* id);
int afi_getIdTxt(Afiche* this,char* id);

int afi_setIdCliente(Afiche* this,int id);
int afi_getIdCliente(Afiche* this,int* id);
int afi_setIdClienteTxt(Afiche* this,char* id);
int afi_getIdClienteTxt(Afiche* this,char* id);

int afi_setNombreArchivo(Afiche* this,char* nombre);
int afi_getNombreArchivo(Afiche* this,char* nombre);

int afi_setZona(Afiche* this,char* zona);
int afi_getZona(Afiche* this,char* zona);

int afi_setCantidad(Afiche* this,int cantidad);
int afi_setCantidadTxt(Afiche* this,char* cantidad);
int afi_getCantidad(Afiche* this,int* cantidad);
int afi_getCantidadTxt(Afiche* this,char* cantidad);

int afi_setACobrar(Afiche* this,int ACobrar);
int afi_setACobrarTxt(Afiche* this,char* ACobrar);
int afi_getACobrar(Afiche* this,int* ACobrar);
int afi_getACobrarTxt(Afiche* this,char* ACobrar);

#endif /* AFICHE_H_ */
