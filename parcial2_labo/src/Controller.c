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
/** \brief recibe un cuit y verifica que no se haya ingresado
 *
 * \param pArrayListClientes LinkedList*
 * \param char* cuitVerificar cuit a verificar
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
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
	//else printf("No corre loadFromText"); // control
	fclose(pFile);
	return retorno;
}

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
    	printf("\nError, no hay clientes cargados");
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
	Cliente* auxCliente;
	char nombre[NOMBRE_LEN];
	char apellido[NOMBRE_LEN];
	char cuit[CUIT_LEN];
	int id;

	if(path!=NULL && pArrayListClientes!=NULL)
	{
		nuevoArchivo = fopen(path,"w+");
		for(i=0; i<ll_len(pArrayListClientes); i++)
		{
			auxCliente=(Cliente*)ll_get(pArrayListClientes,i);
			cli_getId(auxCliente,&id);
			cli_getNombre(auxCliente,nombre);
			cli_getApellido(auxCliente,apellido);
			cli_getCuit(auxCliente,cuit);
			fprintf(nuevoArchivo,"%d,%s,%s,%s\n",id,nombre,apellido,cuit);
			retorno =0;
		}
		fclose(nuevoArchivo);
	}
    return retorno;
}

/** \brief se obtene un ID por parametro y devuelve la posicion en la que se encuentra
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
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
	else printf("\nNo corre loadFromTextAfiche");
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
int controller_printAfiche(LinkedList* pArrayListAfiches)
{
    int i;
    int limite=ll_len(pArrayListAfiches);
    Afiche* auxAfiche;
    auxAfiche = afiche_new();
    if(pArrayListAfiches!=NULL && limite>0)
    {
		printf("\n\nID cli|ID afi|Cantidad  |Nombre archivo          |Zona               |1 A cobrar - 0 cobrada");
		for(i= 0; i < limite; i++)
		{
			auxAfiche=ll_get(pArrayListAfiches, i);
			if(auxAfiche->idAfiche > 0)
			{
				printf("\n%-4d  |%-4d  |%-6d    |%-15s         |%-20s|%-2i", auxAfiche->idCliente, auxAfiche->idAfiche,auxAfiche->cantidad ,auxAfiche->nombreArchivo, auxAfiche->zona, auxAfiche->aCobrar);
			}
		}
    }
    else
    {
    	printf("\nError, no hay clientes cargados");
    }
    return 0;
}
/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListClientes LinkedList*
 * \return 0 si (OK) / -1 si (ERROR)
 *
 */
int controller_editAfiche(LinkedList* pArrayListAfiches)
{
	int retorno=-1;
	int auxId;
	int opciones;
	char auxNombreArchivo[125];
	char auxZona[125];
	int auxCantidad;
	Afiche* auxAfiche;

	if(pArrayListAfiches!= NULL)
	{
		controller_printAfiche(pArrayListAfiches);
		auxId=controller_retornaIdAfiche(pArrayListAfiches);
		if(auxId != -1)
		{
			auxAfiche = ll_get(pArrayListAfiches, auxId);
			retorno=0;
			do
			{
				utn_getNumero(&opciones,"\nElija opcion a modificar"
										"\n1. Nombre"
										"\n2. Cantidad"
										"\n3. Zona"
										"\n4. Volver al menu anterior\n", "\nError, reintente:", 1, 4, 2);
				switch(opciones)
				{
					case 1:
						utn_getDescripcion(auxNombreArchivo, NOMBRE_LEN, "\nIngrese nombre del archivo: ", "\nError, reintente: ", 1);
						afi_setNombreArchivo(auxAfiche, auxNombreArchivo);
					break;

					case 2:
						utn_getNumero(&auxCantidad, "\nIngrese nueva cantidad: ", "\nError, reintente: ", 1, 5000,1);
						afi_setCantidad(auxAfiche, auxCantidad);
					break;

					case 3:
						utn_getDescripcion(auxZona, NOMBRE_LEN, "\nIngrese nueva zona: ", "\nError, reintente: ", 1);
						afi_setZona(auxAfiche, auxZona);
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


int controller_retornaIdAfiche(LinkedList* pArrayListAfiches)
{
	int retorno=-1;
	int idAux;
	int idBuscar;
	Afiche* auxAfiche;

	if(pArrayListAfiches != NULL &&
		!utn_getNumero(&idBuscar, "\nIngrese ID del afiche", "\nError en el ingreso, reintente: ", 1, ll_len(pArrayListAfiches), 2))
	{
		for(int i=0; i<ll_len(pArrayListAfiches); i++)
		{
			auxAfiche = ll_get(pArrayListAfiches,i);
			afi_getId(auxAfiche, &idAux);

			if( idAux == idBuscar)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/** \brief edita campo "aCobrar" del afiche
 *
 * \param pArrayListAfiches LinkedList*
 * \param pArrayListClientes LinkedList*
 * \return void
 *
 */
void controller_cobrarVentas(LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes)
{
	Afiche* auxAfiche;
	int auxiliarId=controller_filtraListaAfichesConClientes(pArrayListAfiches,pArrayListClientes);

	if(auxiliarId != -1)
	{
		auxAfiche=ll_get(pArrayListAfiches,auxiliarId );
		int confirma;
		if(auxAfiche != NULL &&
		   !utn_getNumero(&confirma, "\nDesea cambiar la publicacion al estado cobrada? 1 para SI, 2 para NO", "\nERROR, 1 para SI, 2 para NO", 1, 2, 2))
		{
			if(confirma == 1)
			{
				afi_setACobrar(auxAfiche, 0);
			}
			else
			{
				printf("\nSe cancela la cobranza");
			}
		}
	}
}

/** \brief filtra afiches en estado "a cobrar", pide ID de afiche e imprime cliente asociado
 *
 * \param pArrayListAfiches LinkedList*
 * \param pArrayListClientes LinkedList*
 * \return direccion de ID afiche si (OK) / -1 si (ERROR)
 *
 */
int controller_filtraListaAfichesConClientes(LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes)
{
	Afiche* auxAfiche;
	Cliente* auxCliente;
	int auxIdAfiche;
	int auxIdCliente;
	int verificadorID;
	int retorno=-1;
	LinkedList* listaFiltrada=ll_filter(pArrayListAfiches,afi_obtenerACobrar);
	if(pArrayListClientes != NULL && listaFiltrada != NULL)
	{
		controller_printAfiche(listaFiltrada);
		auxIdAfiche=controller_retornaIdAfiche(listaFiltrada);

		if(auxIdAfiche != -1)
		{
			auxAfiche=ll_get(listaFiltrada,auxIdAfiche);
			auxIdCliente=auxAfiche->idCliente;

			for(int i=0; i<ll_len(pArrayListClientes); i++)
			{
				auxCliente=ll_get(pArrayListClientes, i);
				cli_getId(auxCliente,&verificadorID);

				if(auxIdCliente == verificadorID)
				{
					printf("\n La publicacion pertenece a %s %s Nro CUIT: %s", auxCliente->nombre, auxCliente->apellido, auxCliente->cuit);
					retorno=auxIdAfiche;
					break;
				}
			}
		}
		else
		{
			printf("Error, no se localizó el ID del afiche en cuentas a cobrar");
		}
	}
	return retorno;
}



int controller_filtraCobradas(char* path, LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes)
{
	Cliente* auxCliente;
	Afiche* auxAfiche;
	int auxIdAfi;
	int auxIdCli;
	int retorno= -1;
	FILE* pFile;
	char nombre[125];
	char apellido[125];
	char cuit[125];
	int a=0;
	LinkedList* listaFiltrada=ll_filter(pArrayListAfiches,afi_obtenerACobrar);

	if(listaFiltrada != NULL && pArrayListClientes != NULL)
	{
		pFile=fopen(path,"w+");
		for(int i=0; i<ll_len(pArrayListClientes); i++)
		{
			auxCliente=ll_get(pArrayListClientes, i);
			cli_getId(auxCliente, &auxIdCli);
			a=0;
			for(int j=0; j<ll_len(listaFiltrada); j++)
			{
				auxAfiche=ll_get(listaFiltrada, j);
				afi_getIdCliente(auxAfiche,&auxIdAfi);

				if(auxIdCli == auxIdAfi)
				{
					a++;//=ll_reduceInt(listaFiltrada, afi_obtenerACobrar);
				}
			}
			if(a>0)
			{
				printf("\nID CLI: %i   ID AFI: %i  %i",auxIdCli,auxIdAfi,a); // para control
				cli_getId(auxCliente,&auxIdCli);
				cli_getNombre(auxCliente,nombre);
				cli_getApellido(auxCliente,apellido);
				cli_getCuit(auxCliente,cuit);
				fprintf(pFile,"%d,%s %s,Cuit: %s, Cuentas a cobrar: %i\n",auxIdCli,nombre,apellido,cuit, a);
			}
		}
		fclose(pFile);
	}
	return retorno;
}

int controller_filtraSinCobrar(char* path, LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes)
{
	Cliente* auxCliente;
	Afiche* auxAfiche;
	int auxIdAfi;
	int auxIdCli;
	int retorno= -1;
	FILE* pFile;
	char nombre[125];
	char apellido[125];
	char cuit[125];
	int a=0;
	LinkedList* listaFiltrada=ll_filter(pArrayListAfiches, afi_obtieneCobradas);

	if(listaFiltrada != NULL && pArrayListClientes != NULL)
	{
		pFile=fopen(path,"w+");
		for(int i=0; i<ll_len(pArrayListClientes); i++)
		{
			auxCliente=ll_get(pArrayListClientes, i);
			cli_getId(auxCliente, &auxIdCli);
			a=0;
			for(int j=0; j<ll_len(listaFiltrada); j++)
			{
				auxAfiche=ll_get(listaFiltrada, j);
				afi_getIdCliente(auxAfiche,&auxIdAfi);

				if(auxIdCli == auxIdAfi)
				{
					a++;//=ll_reduceInt(listaFiltrada, afi_obtenerACobrar);
				}
			}
			if(a>0)
			{
				printf("\nID CLI: %i   ID AFI: %i  %i",auxIdCli,auxIdAfi,a); // para control
				cli_getId(auxCliente,&auxIdCli);
				cli_getNombre(auxCliente,nombre);
				cli_getApellido(auxCliente,apellido);
				cli_getCuit(auxCliente,cuit);
				fprintf(pFile,"%d,%s %s,Cuit: %s, Cuentas cobradas: %i\n",auxIdCli,nombre,apellido,cuit, a);
			}
		}
		fclose(pFile);
	}
	return retorno;
}

int controller_mayorVentas(LinkedList* pArrayListAfiches, LinkedList* pArrayListClientes)
{
	Afiche* auxAfiche;
	Cliente* auxCliente;
	int retorno = -1;
	int auxIdCli;
	int auxIdAfi;
	int auxCantidad;
	char nombre[125];
	char apellido[125];
	char cuit[125];
	int idAfi;
	char nombre2[125];
	char apellido2[125];
	int mayor;
	int menor;

	if(pArrayListAfiches != NULL && pArrayListClientes != NULL)
	{
		for(int i=0; i<ll_len(pArrayListClientes); i++)
		{
			auxCliente=ll_get(pArrayListClientes, i);
			cli_getId(auxCliente, &auxIdCli);

			for(int j=0; j<ll_len(pArrayListAfiches); j++)
			{
				auxAfiche=ll_get(pArrayListAfiches, j);
				afi_getIdCliente(auxAfiche,&auxIdAfi);
				afi_getCantidad(auxAfiche,&auxCantidad);

				if(auxIdCli == auxIdAfi)
				{
					if(j==0)
					{
						mayor=auxCantidad;
						menor=auxCantidad;
					}
					if(auxCantidad>mayor)
					{
						mayor=auxCantidad;
						cli_getNombre(auxCliente, nombre);
						cli_getApellido(auxCliente, apellido);
						cli_getCuit(auxCliente, cuit);
						afi_getId(auxAfiche, &idAfi);
					}
					else if(menor>auxCantidad)
					{
						menor=auxCantidad;
						cli_getNombre(auxCliente, nombre2);
						cli_getApellido(auxCliente, apellido2);
					}
				}
			}
		}
		printf("Cliente con mayor cantidad de ventas: %s %s Cuit del cliente: %s ID de la venta: %i\n", nombre, apellido, cuit, idAfi);
		printf("Cliente con menor cantidad de ventas: %s %s\n", nombre2, apellido2);
	}
		return retorno;
}

