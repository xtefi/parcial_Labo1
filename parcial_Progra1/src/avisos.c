/*
 * avisos.c
 *
 *  Created on: 12 oct. 2020
 *      Author: Estefania
 */

/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param array Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "clientes.h"
#include "avisos.h"

#define QTY_CUSTOMER 100
#define QTY_PUBLICATION 1000
#define TEXT_LEN 65



int pub_initArray(Publication* array, int len)
{
	int retorno = -1;
	if(array != NULL && len>0)
	{
		for(int i=0; i< len; i++)
		{
			array[i].isEmpty=1;
			array[i].isPaused=1;
			retorno=0;
		}

	}
	return retorno;
}

/** \brief get one empty slot from de array
*
* \param array Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - or empty position if Ok
*
*/
int pub_findEmptySlot(Publication* array, int len)
{
	int retorno=-1;
	if(array != NULL && len >0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].isEmpty==1)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}



/** \brief add in a existing list of employees the values received as parameters
* in the first empty position
* \param list employee*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param salary float
* \param sector int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space]
*
*/
int pub_addNew(Publication* array, int len, int index, int* id, int idCust)
{
	int retorno=-1;
	Publication buffer;

	if(array != NULL && len > 0 && id != NULL && index >=0 && index <= len)
	{
		if(utn_getNumero(&buffer.rubro, "Ingrese rubro de la publicacion: ", "Error, reintente: ", 1, 100, 1) == 0 &&
			utn_getDescripcion(buffer.text, TEXT_LEN ,"Ingrese texto a publicar: \n", "\nError, tiene un reintento: ", 1) == 0)
		{
			retorno=0;
			buffer.idClient=idCust;
			buffer.isEmpty=0;
			buffer.idPubli=(*id);
			buffer.isPaused=0;
			array[index]=buffer;
			(*id)++;
			printf("ID   |ID clte |RUBRO |TEXTO\n");
			pub_printOne(&array[index]);
		}
	}
	return retorno;
}

/** \brief print one employee
*
* \param array Employee*
*\return 0
*/
int pub_printOne(Publication* array)
{
	if(array != NULL)
	{
		printf("%-4i |%-15i |%-15i |%-15s\n", array->idClient,array->idPubli, array->rubro, array->text);
	}
	return 0;
}


/** \brief find an Employee by Id and returns the index position in array.
*
* \param list Employee*
* \param len int
* \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*
*/
int pub_findById(Publication* array, int len, int value)
{
	int retorno=-1;
	if(array != NULL && len >0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].idPubli==value)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}
/** \brief pause a publication by Id (put isPaused Flag in 1)
*
* \param array Employee*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*
*/
int pub_pause(Publication* array, int len, int idPubli)
{
	int retorno=-1;
	if(array != NULL && len > 0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].idPubli == idPubli && array[i].isEmpty==0 && array[i].isPaused==0)
			{

				//cli_printOne(array[i].idClient);
				array[i].isEmpty=0;
				array[i].isPaused=1;
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

/** \brief unpause a publication by Id (put isPaused Flag in 0)
*
* \param array Employee*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*
*/

int pub_unPause(Publication* array, int len, int idPubli)
{
	int retorno=-1;
	if(array != NULL && len > 0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].idPubli == idPubli && array[i].isEmpty==0 && array[i].isPaused==1)
			{
				array[i].isEmpty=0;
				array[i].isPaused=0;
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

/** \brief upload information for testing
*
* \param list Customer*
* \param len int
* param index int
* \param idPub int
* \param idCli int
* param rubro int
* param text char
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
*/
int pub_hardcode(Publication* array,int len, int index, int* idPub, int idCli, int rubro, char* text)
{
	int retorno = -1;
	Publication bufferPub;

	if(array != NULL && len > 0 && index < len && index >= 0 && idPub != NULL)
	{

		bufferPub.rubro=rubro;
		strncpy(bufferPub.text,text,TEXT_LEN);
		retorno = 0;
		bufferPub.idClient=idCli;
		bufferPub.idPubli = *idPub;
		bufferPub.isEmpty = 0;
		bufferPub.isPaused=0;
		array[index] = bufferPub;
		(*idPub)++;
	}
	return retorno;
}

/** \brief print the content of Customers array
*
* \param array Customer*
* \param len int
* \return int
*
*/
int pub_printArray(Publication* array, int len)
{
	if(array != NULL && len>0)
	{
		printf("ID   |ID publicidad   |RUBRO           |TEXTO\n");
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].isEmpty==0)
			{
				pub_printOne(&array[i]);
			}
		}
	}
	return 0;
}

/** \brief print the content of Customers array while isPaused (0)
*
* \param array Customer*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*/
int pub_printActive(Publication* array, int len)
{
	int retorno=-1;
	if(array != NULL && len>0)
	{
		printf("ID   |ID publicidad   |RUBRO           |TEXTO\n");
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].isEmpty==0 && array[i].isPaused==0)
			{
				pub_printOne(&array[i]);
			}
		}
		retorno=0;
	}
	return retorno;
}

/** \brief print the content of Customers array while isPaused (-1)
*
* \param array Customer*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*/
int pub_printInactive(Publication* array, int len)
{
	int retorno=-1;
	if(array != NULL && len>0)
	{
		printf("ID   |ID publicidad   |RUBRO           |TEXTO\n");
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].isEmpty==0 && array[i].isPaused==1)
			{
				pub_printOne(&array[i]);
				retorno =0;
			}
		}
	}
	return retorno;
}

/** \brief print the content of Publication by customer ID (-1)
*
* \param array Publication*
* \param len int
* \param idCust int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*/
int pub_printByCustId(Publication* array, int len, int idCust)
{
	int retorno=-1;
	if(array != NULL && len>0)
	{
		printf("Publicaciones activas: \nID   |ID publicidad   |RUBRO           |TEXTO\n");
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].isEmpty==0 && array[i].idClient == idCust)
			{
				pub_printOne(&array[i]);
				retorno =0;
			}
		}
	}
	return retorno;
}
/** \brief Remove all the publications from one customer by customer Id (put isEmpty Flag in 1)
*
* \param array Publiation*
* \param len int
* \param idCust int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
*/
int pub_eraseByCustId(Publication* array, int len, int idCust)
{
	int retorno=-1;
	if(array != NULL && len > 0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].idPubli == idCust && array[i].isEmpty==0)
			{
				array[i].isEmpty=1;
				array[i].isPaused=1;
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief sort the array by id
* \param array Customer*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
 */
int pub_sortArray(Publication* arrayPub, int len)
{
	int flagSwap;
	int retorno=-1;
	Publication buffer;

	if(arrayPub != NULL && len > 0)
	{
		do
		{
			flagSwap = 0;
			for(int i=0;i<len-1;i++)
			{
				if((arrayPub[i].isEmpty==1 || arrayPub[i+1].isEmpty==1) && (arrayPub[i].isPaused == 1 || arrayPub[i+1].isPaused == 1))
				{
					continue;
				}
				if(arrayPub[i].idClient > arrayPub[i+1].idClient)
				{
					flagSwap = 1;
					buffer = arrayPub[i];
					arrayPub[i] = arrayPub[i+1];
					arrayPub[i+1]=buffer;
				}
			}
			len--;
		}while(flagSwap);
	}
	return retorno;
}
