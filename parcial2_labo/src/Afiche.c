/*
 * Afiche.c
 *
 *  Created on: 23 nov. 2020
 *      Author: 54113
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Afiche.h"
#include "utn.h"
#include "Cliente.h"
#define NOMBREAFICHE_LEN 128

static int esDescripcion(char* cadena,int longitud);
/**
 * \brief Verifica si la cadena ingresada es una descripcion valida
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 */
static int esDescripcion(char* cadena,int longitud)
{
	int retorno = 1;
	if(cadena != NULL && longitud > 0)
	{
		for(int i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '.' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ) && (cadena[i] < '0' || cadena[i] > '9' ) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/** \brief reserva un espacio de memoria
 *
 * \param void
 * return Retorna el elemento si reserva memoria sino NULL
 *
 */
Afiche* afiche_new(void)
{
	return (Afiche*) malloc(sizeof(Afiche));
}
/**
*\brief Se realiza el alta de un elemento desde consola
*\param pArrayListEmployee Es el array para ingresar elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
Afiche* afiche_newParametros(char* idCliStr,char* idAfiStr,char* cantidadStr, char* nombreArchivoStr, char* zonaStr, char* aCobrarStr)
{
	Afiche* this = NULL;
	this = afiche_new();

	if(this!= NULL && idCliStr != NULL && idAfiStr != NULL && cantidadStr != NULL && nombreArchivoStr != NULL && zonaStr != NULL && aCobrarStr != NULL)
	{
		afi_setIdClienteTxt(this,idCliStr);
		afi_setIdTxt(this, idAfiStr) ;
		afi_setNombreArchivo(this,nombreArchivoStr);
		afi_setZona(this, zonaStr);
		afi_setCantidadTxt(this,cantidadStr);
		afi_setACobrarTxt(this,aCobrarStr);
	}
	else printf("\nAnda mal afiche nuevo param");
	return this;
}

/** \brief libera un espacio de memoria ocupado por un elemento
 *
 * \param void
 * \return void
 *
 */
void afi_detele(Afiche* this)
{
	if( this != NULL)
	{
		free(this);
	}
}


//------------------------------------------ID AFICHE-------------------------------

/**
*\brief Se setea el ID del elemento
*\param this Es el elemento
*\param id Es el ID para setear
*\return Retorna 0 si setea sino -1
*/
int afi_setId(Afiche* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
			retorno = 0;
			this->idAfiche=id;
	}
	return retorno;
}
/**
*\brief Se setea el ID del elemento como texto
*\param this Es el elemento
*\param id Es el ID para setear
*\return Retorna 0 si setea sino -1
*/
int afi_setIdTxt(Afiche* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
			retorno = 0;
			this->idAfiche= atoi(id);
	}
	return retorno;
}
/**
*\brief Se obtiene el ID del elemento
*\param this Es el elemento
*\param id Es el ID que se obtiene
*\return Retorna 0 si obtiene sino retorna -1
*/
int afi_getId(Afiche* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		(*id)=this->idAfiche;
	}
	return retorno;
}
/**
*\brief Se obtiene el ID del elemento como texto
*\param this Es el elemento
*\param id Es el ID que se obtiene
*\return Retorna 0 si obtiene sino retorna -1
*/
int afi_getIdTxt(Afiche* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		sprintf(id,"%d",this->idAfiche);
	}
	return retorno;
}

//------------------------------------------ID CLIENTE-------------------------------

/**
*\brief Se setea el idCliente del elemento
*\param this Es el elemento
*\param idCliente Es el ID para setear
*\return Retorna 0 si setea sino -1
*/
int afi_setIdCliente(Afiche* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
			retorno = 0;
			this->idCliente=id;
	}
	return retorno;
}
/**
*\brief Se setea el idCliente del elemento como texto
*\param this Es el elemento
*\param idCliente Es el ID para setear
*\return Retorna 0 si setea sino -1
*/
int afi_setIdClienteTxt(Afiche* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		this->idCliente= atoi(id);
	}
	return retorno;
}
/**
*\brief Se obtiene el idCliente del elemento
*\param this Es el elemento
*\param idCliente Es el ID que se obtiene
*\return Retorna 0 si obtiene sino retorna -1
*/
int afi_getIdCliente(Afiche* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
			retorno = 0;
			(*id)=this->idCliente;
	}
	return retorno;
}
/**
*\brief Se obtiene el idCliente del elemento como texto
*\param this Es el elemento
*\param idCliente Es el ID que se obtiene
*\return Retorna 0 si obtiene sino retorna -1
*/
int afi_getIdClienteTxt(Afiche* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		sprintf(id,"%d",this->idCliente);
	}
	return retorno;
}

//------------------------------------------NOMBRE ARCHIVO-------------------------------

/**
*\brief Se setea el nombreArchivo del elemento
*\param this Es el elemento
*\param nombre Es el nombre para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_setNombreArchivo(Afiche* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(esDescripcion(nombre, NOMBREAFICHE_LEN))
		{
			strncpy(this->nombreArchivo, nombre, NOMBREAFICHE_LEN);
			retorno = 0;
		}
	}
	return retorno;
}

/**
*\brief Se obtiene el nombreArchivo del elemento
*\param this Es el elemento
*\param nombre Es el nombre que se obtiene
*\return Retorna 0 si obtiene elemento sino retorna -1
*/
int afi_getNombreArchivo(Afiche* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre, this->nombreArchivo, NOMBREAFICHE_LEN);
	}
	return retorno;
}

//------------------------------------------ZONA-------------------------------

/**
*\brief Se setea el nombreArchivo del elemento
*\param this Es el elemento
*\param nombre Es el nombre para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_setZona(Afiche* this,char* zona)
{
	int retorno = -1;
	if(this != NULL && zona != NULL)
	{
		if(esDescripcion(zona, NOMBREAFICHE_LEN))
		{
			strncpy(this->zona, zona, NOMBREAFICHE_LEN);
			retorno = 0;
		}
	}
	return retorno;
}

/**
*\brief Se obtiene el nombreArchivo del elemento
*\param this Es el elemento
*\param nombre Es el nombre que se obtiene
*\return Retorna 0 si obtiene elemento sino retorna -1
*/
int afi_getZona(Afiche* this,char* zona)
{
	int retorno = -1;
	if(this != NULL && zona != NULL)
	{
		retorno = 0;
		strncpy(zona, this->zona, NOMBREAFICHE_LEN);
	}
	return retorno;
}
//------------------------------------------CANTIDAD-------------------------------

/**
*\brief Se setea cantidad del elemento
*\param this Es el elemento
*\param cantidad Es la cantidad de productos para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_setCantidad(Afiche* this,int cantidad)
{
	int retorno = -1;
	if(this != NULL && cantidad >= 0)
	{
		retorno = 0;
		this->cantidad=cantidad;
	}
	return retorno;
}
/**
*\brief Se setea cantidad del elemento
*\param this Es el elemento
*\param cantidad Es la cantidad de productos para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_setCantidadTxt(Afiche* this,char* cantidad)
{
	int retorno = -1;
	if(this != NULL && cantidad >= 0)
	{
		retorno = 0;
		this->cantidad=atoi(cantidad);
	}
	return retorno;
}

/**
*\brief Se obtienen cantidad del elemento
*\param this Es el elemento
*\param cantidad Es la cantidad de productos que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_getCantidad(Afiche* this,int* cantidad)
{
	int retorno = -1;
	if(this != NULL &&  cantidad>= 0)
	{
		retorno = 0;
		(*cantidad)=this->cantidad;
	}
	return retorno;
}
/**
*\brief Se obtienen cantidad del elemento como texto
*\param this Es el elemento
*\param cantidad Es la cantidad de productos que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_getCantidadTxt(Afiche* this,char* cantidad)
{
	int retorno = -1;
	if(this != NULL && cantidad >= 0)
	{
		retorno = 0;
		sprintf(cantidad,"%d",this->cantidad);
	}
	return retorno;
}
/**
*\brief base para comparar el campo de dos elementos
*\param this1 primer elemento
*\param this2 segundo elemento
*\return retorna 1 si el primer elemento es mayor, -1 si el segundo elemento es mayor, caso contrario retorna 0
*/

//------------------------------------------A COBRAR-------------------------------

/**
*\brief Se setea ACobrar del elemento
*\param this Es el elemento
*\param ACobrar Es la cantidad de ACobrar para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_setACobrar(Afiche* this,int ACobrar)
{
	int retorno = -1;
	if(this != NULL && ACobrar >= 0)
	{
		retorno = 0;
		this->aCobrar=ACobrar;
	}
	return retorno;
}
/**
*\brief Se setea ACobrar del elemento
*\param this Es el elemento
*\param ACobrar Es la cantidad de ACobrar para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_setACobrarTxt(Afiche* this,char* ACobrar)
{
	int retorno = -1;
	if(this != NULL && ACobrar >= 0)
	{
		retorno = 0;
		this->aCobrar=atoi(ACobrar);

	}
	return retorno;
}

/**
*\brief Se obtienen ACobrar del elemento
*\param this Es el elemento
*\param ACobrar Es la cantidad de ACobrar que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_getACobrar(Afiche* this,int* ACobrar)
{
	int retorno = -1;
	if(this != NULL &&  ACobrar>= 0)
	{
		retorno = 0;
		(*ACobrar)=this->aCobrar;
	}
	return retorno;
}
/**
*\brief Se obtienen ACobrar del elemento como texto
*\param this Es el elemento
*\param ACobrar Es la cantidad de ACobrar que se obtiene
*\return Retorna 0 si setea elemento sino retorna -1
*/
int afi_getACobrarTxt(Afiche* this,char* ACobrar)
{
	int retorno = -1;
	if(this != NULL && ACobrar >= 0)
	{
		retorno = 0;
		sprintf(ACobrar,"%d",this->aCobrar);
	}
	return retorno;
}

//-----------------------CALCULOS------------------------------------
//---------------------------------------------------------------------

int afi_obtenerACobrar(void* elemento)
{
	int retorno = -1;
	Afiche* auxiliarElemento = (Afiche*)elemento;
	int auxCobrar;

	if(elemento != NULL)
	{
		afi_getACobrar(auxiliarElemento,&auxCobrar);
		if(auxCobrar == 1)
		{
			retorno = 1;
		}
		else if(auxCobrar == 0)
		{
			retorno = 0;
		}
	}
	return retorno;
}


int afi_obtieneCobradas(void* elemento)
{
	int retorno = -1;
	Afiche* auxiliarElemento = (Afiche*)elemento;
	int auxCobrar;

	if(elemento != NULL)
	{
		afi_getACobrar(auxiliarElemento,&auxCobrar);
		if(auxCobrar == 1)
		{
			retorno = 0;
		}
		else if(auxCobrar == 0)
		{
			retorno = 1;
		}
	}
	return retorno;
}

int afi_mayorCantidadVenta(void* pElemento)
{
	Afiche* auxAfiche = (Afiche*)pElemento;
	int auxCantidad;
	int valorMax;
	int flag=0;
	if(auxAfiche != NULL)
	{
		afi_getCantidad(auxAfiche,&auxCantidad);
		if(flag==0)
		{
			valorMax = auxCantidad;
			flag=1;
		}
		if (valorMax < auxCantidad)
		{
			valorMax = auxCantidad;
		}
	}
	return valorMax;
}
