/*
 * informes.c
 *
 *  Created on: 12 oct. 2020
 *      Author: Estefania
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "clientes.h"
#include "avisos.h"
#include "informes.h"
#define NAME_SIZE 51
#define LASTNAME_SIZE 51
#define QTY_CUSTOMER 100
#define QTY_PUBLICATION 1000

/** \brief count active Publication
*
* \param array Publication*
* \param pubLen int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
*/
int info_paused(Publication* arrayPub, int pubLen)
{
	int counter=0;
	int retorno=-1;
	if(arrayPub != NULL && pubLen >0)
	{
		for(int i=0 ; i<pubLen ; i++)
		{
			if(arrayPub[i].isPaused == 1 && arrayPub[i].isEmpty == 0)
			{
				counter++;
			}
		}
		retorno=0;
	}
	printf("\nHay %i avisos en pausa", counter);
	return retorno;
}

/** \brief print one customer accord to publication ID
*
* \param arrayPub Publication*
* \param lenPubli int
* \param arrayCust Customer*
* \param lenCust int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
*/
int info_printOneCustByPubliID(Publication* arrayPub, int lenPubli, Customer* arrayCust, int lenCust, int idPubli)
{
	int retorno=-1;
	if(arrayPub != NULL && lenPubli>0 && arrayCust != NULL)
	{
		for(int i=0 ; i< lenPubli ; i++)
		{
			if(arrayPub[i].idPubli == idPubli)
			{
				retorno=arrayPub[i].idClient;
			}
		}

	}
	if(retorno != -1)
	{
		for(int i=0 ; i< lenCust ; i++)
		{
			if(arrayCust[i].id == retorno)
			{
				printf("\nEsta publicacion pertenece a: \n");
				cli_printOne(&arrayCust[i]);
				break;
			}
		}
	}
	return retorno;
}
/** \brief print customers whit their publications
*
* \param arrayPub Publication*
* \param lenPubli int
* \param arrayCust Customer*
* \param lenCust int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
*/
int info_printCustAndPubs(Publication* arrayPub, int lenPubli, Customer* arrayCust, int lenCust)
{
	int retorno =-1;

	pub_sortArray(arrayPub,lenPubli);
	if(arrayPub != NULL && arrayCust != NULL && lenPubli >0 && lenCust >0)
	{
		for(int i=0 ; i< lenCust ; i++)
		{
			if(arrayCust[i].isEmpty==0)
			{
				printf("ID   |NAME            |LAST NAME       |CUIT\n");
				cli_printOne(&arrayCust[i]);
				for(int j=0 ; j<lenPubli ; j++)
				{
					if(arrayPub[j].isEmpty == 0 && arrayPub[j].isPaused ==0 && arrayCust[i].id==arrayPub[j].idClient)
					{
						printf("ID   |ID publicidad   |RUBRO           |TEXTO\n");
						pub_printOne(&arrayPub[j]);
					}
				} // for j
			}

		}//for i
		retorno=0;
	}//first if

	return retorno;
}


/** \brief in process
*
* \param
* \param
* \param
* \param
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a Customer] - (0) if Ok
*
*/

void info_mostPublish(Publication* arrayPub, int lenPubli, Customer* arrayCust, int lenCust)
{
	int maximo;
	int cantidad;
	int idMaximo;
	int flag;

	if(arrayPub != NULL && lenPubli>0 && arrayCust != NULL && lenCust>0)
	{
		for (int i=0 ; i<lenCust ; i++)
		{
			if(arrayPub[i].isEmpty == 0)
			{
				cantidad=pub_contador(arrayPub, lenPubli, arrayPub[i].idClient);
				fflush(stdin);
				if(flag==0)
				{
					maximo=cantidad;
					idMaximo=i;
					flag=1;
				}
				if(cantidad > maximo)
				{
					maximo=cantidad;
					idMaximo=i;
				}
			}
		}
	}
	if(maximo>0)
	{
		printf("Cliente con mas publicaciones:");
		info_printOneCustByPubliID(arrayPub, lenPubli, arrayCust, lenCust,idMaximo );
	}
	else
	{
		printf("No hay clientes con publicaciones registradas");
	}

}


void info_maxRubro(Publication* arrayPub, int lenPubli, Customer* arrayCust, int lenCust)
{
	int maximo;
	int cantidad;
	int rubroMaximo;
	int flag;

	if(arrayPub != NULL && lenPubli>0 && arrayCust != NULL && lenCust>0)
	{
		for (int i=0 ; i<lenCust ; i++)
		{
			if(arrayPub[i].isEmpty == 0)
			{
				cantidad=pub_contadorRubro(arrayPub, lenPubli, arrayPub[i].rubro);
				fflush(stdin);
				if(flag==0)
				{
					maximo=cantidad;
					rubroMaximo=arrayPub[i].rubro;
					flag=1;
				}
				if(cantidad > maximo)
				{
					maximo=cantidad;
					rubroMaximo=arrayPub[i].rubro;
				}
			}
		}
	}
	if(maximo>0)
	{
		printf("Rubro con mas publicaciones: %i", rubroMaximo);
	}
	else
	{
		printf("No hay clientes con publicaciones registradas");
	}

}




