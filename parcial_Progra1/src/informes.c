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

int info_printPubs(Customer* arrayCust, int custLen, Publication* arrayPub, int pubLen)
{
	int retorno=-1;
	char lista_Cuit[QTY_CUSTOMER][CUIT_SIZE];
	int flagCuit;
	int indiceCuit=0;
	int i;
	int j;


	for(i=0; i<QTY_CUSTOMER; i++)
	{
		flagCuit=0;
		if(arrayCust[i].isEmpty)
		{
			continue;
		}
		for(j=0 ; j<indiceCuit; j++)
		{
			if(strncpy(arrayCust[i].cuit, lista_Cuit[j], CUIT_SIZE)==0)
			{
				flagCuit=1;
				break;
			}
		}
		if(flagCuit==0)
		{
			strncpy(arrayCust[i].cuit, lista_Cuit[j], CUIT_SIZE);
			indiceCuit++;

		}
	}
	for(j=0 ; j<indiceCuit; j++)
	{
		printf("Clientes - Cuit %s\n", lista_Cuit[j]);
	}

	return retorno;
}
