/*
 * clientes.c
 *
 *  Created on: 12 oct. 2020
 *      Author: Estefania
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 51
#define LASTNAME_SIZE 51
#define CUIT_SIZE 12
#define QTY_CUSTOMER 100
#include "utn.h"
#include "clientes.h"


/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param array Customer* Pointer to array of Customers
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*
*/
int cli_initArray(Customer* array, int len)
{
	int retorno = -1;
	if(array != NULL && len>0)
	{
		for(int i=0; i< len; i++)
		{
			array[i].isEmpty=1;
			retorno=0;
		}
	}
	return retorno;
}

/** \brief get one empty slot from de array
*
* \param array Customer* Pointer to array of Customers
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - or empty position if Ok
*
*/
int cli_findEmptySlot(Customer* array, int len)
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

/** \brief add in a existing list of Customers the values received as parameters
* in the first empty position
* \param list Customer*
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
int cli_addNew(Customer* array, int len, int* id, int index)
{
	int retorno=-1;
	Customer buffer;
	index=cli_findEmptySlot(array, len);
	if(array != NULL && len > 0 && id != NULL && index >=0 && index <= len)
	{
		if(utn_getDescripcion(buffer.name, NAME_SIZE ,"Ingrese nombre: ", "\nError, tiene un reintento: ", 1) == 0 &&
		   utn_getDescripcion(buffer.lastName, LASTNAME_SIZE,"Ingrese apellido: ", "\nError, tiene un reintento: ", 1) == 0 &&
		   utn_getDni(buffer.cuit, CUIT_SIZE ,"Ingrese cuit: ", "\nError, tiene un reintento: ", 1) == 0
		   )
		{
			retorno=0;
			buffer.isEmpty=0;
			buffer.id=(*id);
			array[index]=buffer;
			(*id)++;

			printf("\nID   |NAME            |LAST NAME       |CUIT\n");
			cli_printOne(&array[index]);
		}
	}
	return retorno;
}

/** \brief print one Customer
*
* \param array Customer*
*\return void
*/
int cli_printOne(Customer* array)
{
	int retorno=0;
	if(array != NULL)
	{
		printf("%-4i |%-15s |%-15s |%-11s \n", array->id, array->name, array->lastName, array->cuit);
		retorno=0;
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
int cli_printArray(Customer* array, int len)
{
	if(array != NULL && len>0)
	{
		printf("ID   |NAME            |LAST NAME       |CUIT\n");
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].isEmpty==0)
			{
				cli_printOne(&array[i]);
			}
		}
	}
	return 0;
}
/** \brief find an Customer by Id and returns the index position in array.
*
* \param list Customer*
* \param len int
* \param id int
* \return Return Customer index position or (-1) if [Invalid length or NULL
pointer received or Customer not found]
*
*/
int cli_findById(Customer* array, int len, int value)
{
	int retorno=-1;

	if(array != NULL && len >0 && value >= 0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].id==value)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}
/** \brief Remove a Customer by Id (put isEmpty Flag in 1)
*
* \param array Customer*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
*/
int cli_remove(Customer* array, int len, int id)
{
	int retorno=-1;
	if(array != NULL && len > 0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].id == id && array[i].isEmpty==0)
			{
				array[i].isEmpty=1;
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief sort the array  by name
* \param array Customer*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
 */
int cli_sortArray(Customer* array, int len)
{
	int flagSwap;
	int retorno=-1;
	Customer buffer;

	if(array != NULL && len > 0)
	{
		do
		{
			flagSwap = 0;
			for(int i=0;i<len-1;i++)
			{
				if(array[i].isEmpty==1 || array[i+1].isEmpty==1)
					{
						continue;
					}
					if(strncmp(array[i].name,array[i+1].name,NAME_SIZE) > 0)
					{
						flagSwap = 1;
						buffer = array[i];
						array[i] = array[i+1];
						array[i+1]=buffer;
					}
				/*	else if(strncmp(array[i].name,array[i+1].name,NAME_SIZE) == 0)
					{
						if(array[i].sector > array[i+1].sector)
						{
							flagSwap = 1;
							buffer = array[i];
							array[i] = array[i+1];
							array[i+1]=buffer;
						}
					}*/
			}
			len--;
		}while(flagSwap);
	}
	return retorno;
}
/**
 * \brief sort the array by name
* \param array Customer*
* \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
 */
int cli_sortByName(Customer* array,int len)
{
	int retorno = -1;
	int flagSwap;
	Customer buffer;
	if(array != NULL && len > 0)
	{
		do
		{
			flagSwap = 0;
			for(int i=0;i<len-1;i++)
			{
				if(array[i].isEmpty==1 || array[i+1].isEmpty==1)
				{
					continue;
				}
				if(strncmp(array[i].name,array[i+1].name,NAME_SIZE) > 0)
				{
					flagSwap = 1;
					buffer = array[i];
					array[i] = array[i+1];
					array[i+1]=buffer;
				}
			}
			len--;
		}while(flagSwap);
		retorno=0;
	}
	return retorno;
}

/** \brief update an array position
*
* \param list Customer*
* \param len int
* \param value int
* \return Return Customer index position or (-1) if [Invalid length or NULL
pointer received or Customer not found]
*
*/
int cli_update(Customer* array, int len, int value)
{
	int retorno=-1;
	int update;
	Customer buffer;

	if(array != NULL && len>=0)
	{
		for(int i=0 ; i<len ; i++)
		{
			if(array[i].id == value && array[i].isEmpty == 0 && !utn_getNumero(&update, "\nQue desea modificar?\n"
															"1. Nombre\n"
															"2. Apellido\n"
															"3. Cuit\n"
															"4. Salir\n"
															"Igrese su opcion: ", "\nError, no esta dentro del rango, reintente: ", 1, 4, 1))
			{
				switch(update)
				{
				case 1:
					if(!utn_getDescripcion(buffer.name, NAME_SIZE, "\nReingrese nombre: ", "\nError, no esta dentro del rango, reintente: ", 1))
					{
						strcpy(buffer.lastName,array[i].lastName);
						strcpy(buffer.cuit,array[i].cuit);
						buffer.id=array[i].id;
						array[i]=buffer;
						array[i].isEmpty=0;
						retorno=0;
						printf("Nombre modificado -");
					}
					break;

				case 2:
					if(!utn_getDescripcion(buffer.lastName, NAME_SIZE, "\nReingrese apellido: ", "\nError, no esta dentro del rango, reintente: ", 1))
					{
						strcpy(buffer.name,array[i].name);
						strcpy(buffer.cuit,array[i].cuit);
						buffer.id=array[i].id;
						array[i]=buffer;
						array[i].isEmpty=0;
						retorno=0;
						printf("Apellido modificado -");
					}
					break;

				case 3:
					if(!utn_getDni(buffer.cuit, CUIT_SIZE ,"Ingrese cuit: ", "\nError, tiene un reintento: ", 1))
					{
						strcpy(buffer.name,array[i].name);
						strcpy(buffer.lastName,array[i].lastName);
						buffer.id=array[i].id;
						array[i]=buffer;
						array[i].isEmpty=0;
						retorno=0;
						printf("CUIT modificado -");
					}
					break;
				}
			}//if
		}//for

	}
	return retorno;
}
/** \brief upload information for testing
*
* \param list Customer*
* \param len int
* param index int
* \param id int
* param name char
* param lastName char
* param salary float
* param sector int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
*/
int cli_hardcode(Customer* array,int len, int index, int* id,char* name,char* lastName, char* cuit)
{
	int retorno = -1;
	Customer bufferCustomer;

	if(array != NULL && len > 0 && index < len && index >= 0 && id != NULL)
	{
			strncpy(bufferCustomer.name,name,NAME_SIZE);
			strncpy(bufferCustomer.lastName,lastName,LASTNAME_SIZE);
			strncpy(bufferCustomer.cuit,cuit,CUIT_SIZE);
			retorno = 0;
			bufferCustomer.id = *id;
			bufferCustomer.isEmpty = 0;
			array[index] = bufferCustomer;
			(*id)++;
	}
	return retorno;
}



