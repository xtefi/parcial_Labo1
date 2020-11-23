#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "parser.h"
#include "Cliente.h"
#include "Afiche.h"

/** \brief Parsea los datos los datos de los empleados desde archivo (modo texto).
 *
 * \param path char*
 * \param pArrayListCliente LinkedList*
 * \return int
 *
 */
int parser_ClienteFromText(FILE* pFile , LinkedList* pArrayListCliente)
{
	int retorno = -1;
	char auxId[5000];
	char auxNombre[5000];
	char auxApellido[5000];
	char auxCuit[5000];
	Cliente* pCliente;

	if(pArrayListCliente != NULL && pFile != NULL)
	{
		do
		{
			fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxNombre, auxApellido, auxCuit);
			pCliente = cliente_newParametros(auxId, auxNombre,auxApellido,auxCuit);
			if(pCliente != NULL)
			{
				retorno = 0;
				ll_add(pArrayListCliente,pCliente);
			}
		}while(!feof(pFile));
	}
	else printf("\nAnda mal el parser");
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde archivo (modo texto).
 *
 * \param path char*
 * \param pArrayListCliente LinkedList*
 * \return int
 *
 */
int parser_AficheFromText(FILE* pFile , LinkedList* pArrayListAfiches)
{
	int retorno = -1;
	char auxIdCliente[5000];
	char auxIdAfiche[5000];
	char auxCantidad[5000];
	char auxNombreArchivo[5000];
	char auxZona[5000];
	char auxACobrar[5000];
	Cliente* pAfiche;

	if(pArrayListAfiches != NULL && pFile != NULL)
	{
		do
		{
			fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", auxIdCliente, auxIdAfiche, auxCantidad, auxNombreArchivo,auxZona, auxACobrar);
			pAfiche = afiche_newParametros(auxIdCliente, auxIdAfiche, auxCantidad, auxNombreArchivo,auxZona, auxACobrar);
			if(pAfiche != NULL)
			{
				retorno = 0;
				ll_add(pArrayListAfiches,pAfiche);
			}
		}while(!feof(pFile));
	}
	else printf("\nAnda mal el parser");
    return retorno;
}

