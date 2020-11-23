#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Cliente.h"
#include "controller.h"
#include "utn.h"
#include "parser.h"
#include "Afiche.h"

#define NOMBREAFICHE_LEN 128
#define NOMBRE_LEN 51
#define CUIT_LEN 12

static int controller_validaCuit(LinkedList* pArrayListClientes, char* cuitVerificar);

static int controller_validaCuit(LinkedList* pArrayListClientes, char* cuitVerificar)
{
	int retorno=-1;
	char cuitAux[CUIT_LEN];
	Cliente* auxCliente;

	if(pArrayListClientes != NULL)
	{
		for(int i=0; i<ll_len(pArrayListClientes); i++)
		{
			auxCliente = ll_get(pArrayListClientes,i);
			cli_getCuit(auxCliente, cuitAux);
			if(strncmp(cuitVerificar, cuitAux, CUIT_LEN) == 0)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/** \brief Ordenamiento de Clientes por ID
 *
 * \param void* pCliente1
 * \param void* pCliente2
 * \return 0
 *
 */
int controller_ordenaId(void* pCliente1, void* pCliente2)
{
    if(((Cliente*)pCliente1)->id > ((Cliente*)pCliente2)->id)
    {
        return 1;
    }
    if(((Cliente*)pCliente1)->id < ((Cliente*)pCliente2)->id)
    {
        return -1;
    }
    return 0;
}
/** \brief Carga los datos de los clientes desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListClientes)
{
	int retorno=-1;
	FILE* pFile;
	pFile= fopen(path, "r+");
	if(!parser_ClienteFromText(pFile, pArrayListClientes))
	{
		retorno =0;
		printf("\nLista de empleados cargada con exito");
	}
	else printf("No corre loadFromText");
	fclose(pFile);
	return retorno;
}

/** \brief Carga los datos de los clientes desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return int
 *

int controller_loadFromBinary(char* path , LinkedList* pArrayListClientes)
{
	int retorno=-1;
	FILE* pFile= fopen(path, "r+");
	if(!parser_ClienteFromBinary(pFile,pArrayListClientes))
	{
		retorno = 0;
		printf("\nLista en binario cargada con exito.\n");

	}
	else printf("\nNo se pudo cargar la lista en binario.\n");
	fclose(pFile);
    return retorno;
}
*/
/** \brief Alta de cliente
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
int controller_addCliente(LinkedList* pArrayListClientes)
{
	int retorno=-1;
	Cliente* auxCliente=NULL;
	char nombre[NOMBRE_LEN];
	char apellido[NOMBRE_LEN];
	char cuit[CUIT_LEN];
	int auxId=ll_len(pArrayListClientes);
	if(pArrayListClientes !=NULL)
	{
		auxCliente=cliente_new();
		if(auxCliente!=NULL)
		{
			if(!utn_getNombre(nombre,NOMBRE_LEN,"\nIngrese nombre: ","\nError solo letras, reintente: ",2) &&
			   !utn_getNombre(apellido,NOMBRE_LEN,"\nIngrese apellido: ","\nError solo letras, reintente: ",2) &&
			   !utn_getDni(cuit,CUIT_LEN,"\nIngrese CUIT: ","\nError solo letras, reintente: ",2))
			{
					cli_setId(auxCliente, auxId);
					cli_setNombre(auxCliente,nombre);
					cli_setApellido(auxCliente,apellido);
					cli_setCuit(auxCliente,cuit);
					if(controller_validaCuit(pArrayListClientes,cuit )!=0)
					{
						retorno=0;
						ll_add(pArrayListClientes,auxCliente);
						printf("\nCliente cargado correctamente"
							"\nID   |Nombre          |Apellido        |CUIT"
							"\n%-4d |%-15s |%-15s |%-14s", auxId, nombre, apellido, cuit);
					}
					else
					{
						printf("Error, ese CUIT ya existe, no se pudo cargar el cliente");
					}

			}
		}
	}
	return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
int controller_editCliente(LinkedList* pArrayListClientes)
{
	int retorno=-1;
	int limite=ll_len(pArrayListClientes);
	int auxId;
	int opciones;
	Cliente* auxCliente;

	if(pArrayListClientes!=NULL && limite>0 &&
		!utn_getNumero(&auxId,"\nIngrese el ID del Cliente a modificar: ", "\nError, reintente: ", 0,limite,2))
	{
		auxCliente = ll_get(pArrayListClientes, auxId-1);
		if(!cli_getId(auxCliente, &auxId))
		{
			retorno=0;
			do
			{
				utn_getNumero(&opciones,"\nElija opcion a modificar"
										"\n1. Nombre"
										"\n2. Apellido"
										"\n3. CUIT"
										"\n4. Volver al menu anterior\n", "\nError, reintente:", 1, 4, 2);
				switch(opciones)
				{
					case 1:
						utn_getDescripcion(auxCliente->nombre, NOMBRE_LEN, "\nIngrese nombre del empleado: ", "Error, reintente: \n", 1);
					break;
					case 2:
						utn_getDescripcion(auxCliente->apellido, NOMBRE_LEN, "\nIngrese apellido del empleado: ", "Error, reintente: \n", 1);
					break;
					case 3:
						utn_getDescripcion(auxCliente->cuit, NOMBRE_LEN, "\nIngrese CUIT del empleado: ", "Error, reintente: \n", 1);
					break;
				}//switch
			}while(opciones!=4);
		}
		else
		{
			printf("Error, ID no encontrado");
		}
	}//PRIMER IF
	else
	{
		printf("Error, no hay clientes cargados");
	}
    return retorno;
}

/** \brief Baja de cliente
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return (-1) si hubo ERROR
 * 			(0) si funciono correctamente
 *
 */
int controller_removeCliente(LinkedList* pArrayListClientes)
{
	int retorno = -1;
	int auxId;
	int respuesta;
	int len=ll_len(pArrayListClientes);
	Cliente* auxCliente;
	Cliente* cliente;
	if(!utn_getNumero(&auxId,"\n\nIngrese ID del cliente a eliminar: ","\nError verifique los datos ingresados",0,len,2))
	{
		auxCliente=ll_get(pArrayListClientes, auxId-1);
	    for(int i=0; i<=len; i++)
	    {
	    	cliente = ll_get(pArrayListClientes, i);
	        if((auxCliente)->id == (*cliente).id)
	        {
				utn_getNumero(&respuesta, "Desea eliminar?"
									"\nIngrese 1 para proceder "
									"\nIngrese 2 para cancelar ", "\nError, reintente", 1,2,1);
				if(respuesta == 1)
				{
					cli_delete(cliente);
					ll_remove(pArrayListClientes, auxId-1);
					printf("\nEmpleado eliminado con exito\n");
					retorno=0;
					break;
				}
				else if(respuesta==2)
				{
					printf("Se cancela eliminacion del ID %i\n", auxId);
					break;
				}
	        }
	    }
	}
	return retorno;
}
/** \brief Listar clientes
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0
 *
 */
int controller_ListCliente(LinkedList* pArrayListClientes)
{
    int i;
    int limite=ll_len(pArrayListClientes);
    Cliente* auxCliente;
    auxCliente = cliente_new();
    if(pArrayListClientes!=NULL && limite>=0)
    {
		printf("\n\nID   |Nombre          |Apellido        |CUIT");
		for(i= 0; i < limite; i++)
		{
			auxCliente=ll_get(pArrayListClientes, i);
			if(auxCliente->id > 0)
			{
				printf("\n%-4d |%-15s |%-15s |%-14s", auxCliente->id, auxCliente->nombre, auxCliente->apellido, auxCliente->cuit);
			}
		}
    }
    else
    {
    	printf("Error, no hay clientes cargados");
    }
    return 0;
}
/** \brief Ordenar clientes
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
int controller_sortCliente(LinkedList* pArrayListClientes)
{
	int retorno = -1;
	if(pArrayListClientes != NULL)
	{
		if(!ll_sort(pArrayListClientes,cli_ordenaNombre,1))
		{
			retorno = 0;
			printf("\nLista ordenada con exito.\n");
			controller_ListCliente(pArrayListClientes);
		}
		else printf("\nError, la lista no se pudo ordenar\n");
	}
	return retorno;
}
/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListClientes)
{
	int retorno=-1;
	FILE* nuevoArchivo;
	int i;
	Cliente* auxiliarEmployee;
	char nombre[NOMBRE_LEN];
	char apellido[NOMBRE_LEN];
	char cuit[CUIT_LEN];
	int id;

	if(path!=NULL && pArrayListClientes!=NULL)
	{
		nuevoArchivo = fopen(path,"w+");
		for(i=0; i<ll_len(pArrayListClientes); i++)
		{
			auxiliarEmployee=(Cliente*)ll_get(pArrayListClientes,i);
			cli_getId(auxiliarEmployee,&id);
			cli_getNombre(auxiliarEmployee,nombre);
			cli_getApellido(auxiliarEmployee,apellido);
			cli_getCuit(auxiliarEmployee,cuit);
			fprintf(nuevoArchivo,"%d,%s,%s,%s\n",id,nombre,apellido,cuit);
			retorno =0;
		}
		fclose(nuevoArchivo);
	}
    return retorno;
}


/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *

int controller_saveAsBinary(char* path , LinkedList* pArrayListClientes)
{
	Cliente* auxCliente;
	FILE* pFile;
	int retorno =-1;
	if(path != NULL && pArrayListClientes != NULL)
	{
		pFile=fopen(path,"w+");
		for(int i=0; i<ll_len(pArrayListClientes); i++)
		{
			auxCliente=(Cliente*)ll_get(pArrayListClientes, i);
			fwrite(auxCliente, sizeof(Cliente), 1, pFile);
		}
		retorno=0;
	}
	fclose(pFile);
    return retorno;
}
 */

int controller_retornaIdCliente(LinkedList* pArrayListClientes)
{
	int retorno=-1;
	int idAux;
	int idBuscar;
	Cliente* auxCliente;

	if(pArrayListClientes != NULL &&
		!utn_getNumero(&idBuscar, "\nIngrese ID del cliente", "\nError en el ingreso, reintente: ", 1, ll_len(pArrayListClientes), 2))
	{
		for(int i=0; i<ll_len(pArrayListClientes); i++)
		{
			auxCliente = ll_get(pArrayListClientes,i);
			cli_getId(auxCliente, &idAux);

			if( idAux == idBuscar)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
//-------------------------------------------------------------------------------------------
//-----------------------------------------CONTROLLER AFICHES--------------------------------
//-------------------------------------------------------------------------------------------
/** \brief Alta de afiche
 *
 * \param path char*
 * \param pArrayListAfiches LinkedList*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
int controller_addAfiche(LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes)
{
	int retorno=-1;
	Afiche* auxAfiche=NULL;
	int auxIdAfiche=ll_len(pArrayListAfiches);
	int auxIdCliente;
	char nombreArchivo[NOMBREAFICHE_LEN];
	char zona[NOMBREAFICHE_LEN];
	int cantidad;
	int aCobrar=1;

	if(pArrayListAfiches !=NULL)
	{
		auxIdCliente=controller_retornaIdCliente(pArrayListClientes);
		if(auxIdCliente != -1)
		{
			auxAfiche=afiche_new();
		}
		else printf("\nError, ID de cliente no localizado");

		if(auxAfiche!=NULL && auxIdCliente != -1)
		{
			if(!utn_getNombre(nombreArchivo,NOMBRE_LEN,"\nIngrese nombre del archivo: ","\nError solo letras, reintente: ",2) &&
			   !utn_getNombre(zona,NOMBRE_LEN,"\nIngrese zona (CABA, ZONA SUR, ZONA OESTE): ","\nError solo letras, reintente: ",2) &&
			   !utn_getNumero(&cantidad,"\nIngrese la cantidad de afiches que desea comprar: ", "Error, reintente: ", 1, 5000, 2))
			{
					afi_setId(auxAfiche, auxIdAfiche);
					afi_setIdCliente(auxAfiche, auxIdCliente);
					afi_setNombreArchivo(auxAfiche,nombreArchivo);
					afi_setZona(auxAfiche,zona);
					afi_setCantidad(auxAfiche,cantidad);
					afi_setACobrar(auxAfiche, aCobrar);
					retorno=0;
					ll_add(pArrayListClientes,auxAfiche);
					printf("\nSolicitud de afiches cargada correctamente bajo el ID: %d", auxIdAfiche);
			}
		}
	}
	return retorno;
}

/** \brief Guarda los datos de los afiches en el archivo ventas.txt (modo texto).
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
int controller_saveAficheAsText(char* path , LinkedList* pArrayListAfiches)
{
	int retorno=-1;
	FILE* pFile;
	Afiche* auxAfiche;
	char nombreArchivo[NOMBREAFICHE_LEN];
	char zona[NOMBRE_LEN];
	int cantidad;
	int idAfiche;
	int idCliente;
	int aCobrar;

	if(path!=NULL && pArrayListAfiches!=NULL)
	{
		pFile = fopen(path,"w+");
		for(int i=0; i<ll_len(pArrayListAfiches); i++)
		{
			auxAfiche=(Afiche*)ll_get(pArrayListAfiches,i);
			afi_getIdCliente(auxAfiche,&idCliente);
			afi_getId(auxAfiche, &idAfiche);
			afi_getCantidad(auxAfiche,&cantidad);
			afi_getNombreArchivo(auxAfiche,nombreArchivo);
			afi_getZona(auxAfiche,zona);
			afi_getACobrar(auxAfiche,&aCobrar);
			fprintf(pFile,"%i,%i,%i,%s,%s,%i\n",idAfiche,idCliente,cantidad,nombreArchivo,zona ,aCobrar);
			retorno =0;
		}
		fclose(pFile);
	}
    return retorno;
}

/** \brief Carga los datos de los afiches desde el archivo ventas.txt (modo texto).
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
int controller_loadAficheFromText(char* path , LinkedList* pArrayListAfiches)
{
	int retorno=-1;
	FILE* pFile;
	pFile= fopen(path, "r+");
	if(!parser_AficheFromText(pFile, pArrayListAfiches))
	{
		retorno =0;
		printf("\nLista de afiches cargada con exito");
	}
	else printf("No corre loadFromText");
	fclose(pFile);
	return retorno;
}

/** \brief Listar clientes
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0
 *
 */
int controller_ListAfiche(LinkedList* pArrayListAfiches)
{
    int i;
    int limite=ll_len(pArrayListAfiches);
    Afiche* auxAfiche;
    auxAfiche = afiche_new();
    if(pArrayListAfiches!=NULL && limite>0)
    {
		printf("\n\nID cli|ID afi|Cantidad  |Nombre archivo     |Zona           |A cobrar");
		for(i= 0; i < limite; i++)
		{
			auxAfiche=ll_get(pArrayListAfiches, i);
			if(auxAfiche->idAfiche > 0)
			{
				printf("\n%-4d  |%-4d  |%-6d    |%-15s    |%-15s|%-2i", auxAfiche->idCliente, auxAfiche->idAfiche,auxAfiche->cantidad ,auxAfiche->nombreArchivo, auxAfiche->zona, auxAfiche->aCobrar);
			}
		}
    }
    else
    {
    	printf("Error, no hay clientes cargados");
    }
    return 0;
}
