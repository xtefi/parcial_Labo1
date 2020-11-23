#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cliente.h"
#include "utn.h"
#define NOMBRE_LEN 51
#define CUIT_LEN 12

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
Cliente* cliente_new(void)
{
	return (Cliente*) malloc(sizeof(Cliente));
}
/**
*\brief Se realiza el alta de un elemento desde consola
*\param pArrayListEmployee Es el array para ingresar elemento
*\return Retorna 0 si logra agregar elemento sino retorna -1
*/
Cliente* cliente_newParametros(char* idStr,char* nombreStr,char* apellidoStr, char* cuitStr)
{
	Cliente* this = NULL;
	this = cliente_new();

	if(this!= NULL && idStr != NULL && nombreStr != NULL && apellidoStr != NULL && cuitStr != NULL)
	{
		cli_setIdTxt(this, idStr) ;
		cli_setNombre(this,nombreStr);
		cli_setApellido(this, apellidoStr);
		cli_setCuit(this,cuitStr);
	}
	else printf("Anda mal cliente_nuevo");
	return this;
}
/* No estamos usando binario
Cliente* cli_newParametrosBin(Cliente this)
{
	Cliente* auxEmpleado;
	auxEmpleado = cliente_new();
	cli_setId(auxEmpleado, this.id);
	cli_setNombre(auxEmpleado, this.nombre);
	cli_setApellido(auxEmpleado, this.apellido);
	cli_setCuit(auxEmpleado, this.cuit);

	    return auxEmpleado;
}

*/
/** \brief libera un espacio de memoria ocupado por un elemento
 *
 * \param void
 * \return void
 *
 */
void cli_delete(Cliente* this)
{
	if( this != NULL)
	{
		free(this);
	}
}
//------------------------------------------NOMBRE-------------------------------

/**
*\brief Se setea el nombre del elemento
*\param this Es el elemento
*\param nombre Es el nombre para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int cli_setNombre(Cliente* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		if(esDescripcion(nombre, NOMBRE_LEN))
		{
			strncpy(this->nombre, nombre, NOMBRE_LEN);
			retorno = 0;
		}
	}
	return retorno;
}

/**
*\brief Se obtiene el nombre del elemento
*\param this Es el elemento
*\param nombre Es el nombre que se obtiene
*\return Retorna 0 si obtiene elemento sino retorna -1
*/
int cli_getNombre(Cliente* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		retorno = 0;
		strncpy(nombre, this->nombre, NOMBRE_LEN);
	}
	return retorno;
}

//------------------------------------------ID-------------------------------

/**
*\brief Se setea el ID del elemento
*\param this Es el elemento
*\param id Es el ID para setear
*\return Retorna 0 si setea sino -1
*/
int cli_setId(Cliente* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		this->id=id;
	}
	return retorno;
}
/**
*\brief Se setea el ID del elemento como texto
*\param this Es el elemento
*\param id Es el ID para setear
*\return Retorna 0 si setea sino -1
*/
int cli_setIdTxt(Cliente* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		this->id= atoi(id);
	}
	return retorno;
}
/**
*\brief Se obtiene el ID del elemento
*\param this Es el elemento
*\param id Es el ID que se obtiene
*\return Retorna 0 si obtiene sino retorna -1
*/
int cli_getId(Cliente* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		(*id)=this->id;
	}
	return retorno;
}
/**
*\brief Se obtiene el ID del elemento como texto
*\param this Es el elemento
*\param id Es el ID que se obtiene
*\return Retorna 0 si obtiene sino retorna -1
*/
int cli_getIdTxt(Cliente* this,char* id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		sprintf(id,"%d",this->id);
	}
	return retorno;
}
//------------------------------------------APELLIDO-------------------------------

/**
*\brief Se setea el apellido del elemento
*\param this Es el elemento
*\param apellido Es el nombre para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int cli_setApellido(Cliente* this,char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL)
	{
		if(esDescripcion(apellido, NOMBRE_LEN))
		{
			strncpy(this->apellido, apellido, NOMBRE_LEN);
			retorno = 0;
		}
	}
	return retorno;
}

/**
*\brief Se obtiene el apellido del elemento
*\param this Es el elemento
*\param apellido Es el nombre que se obtiene
*\return Retorna 0 si obtiene elemento sino retorna -1
*/
int cli_getApellido(Cliente* this,char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL)
	{
		retorno = 0;
		strncpy(apellido, this->apellido, NOMBRE_LEN);
	}
	return retorno;
}
//------------------------------------------CUIT-------------------------------

/**
*\brief Se setea el cuit del elemento
*\param this Es el elemento
*\param cuit Es el nombre para setear
*\return Retorna 0 si setea elemento sino retorna -1
*/
int cli_setCuit(Cliente* this,char* cuit)
{
	int retorno = -1;
	if(this != NULL && cuit != NULL)
	{
		strncpy(this->cuit, cuit, CUIT_LEN);
		retorno = 0;
	}
	return retorno;
}

/**
*\brief Se obtiene el cuit del elemento
*\param this Es el elemento
*\param cuit Es el nombre que se obtiene
*\return Retorna 0 si obtiene elemento sino retorna -1
*/
int cli_getCuit(Cliente* this,char* cuit)
{
	int retorno = -1;
	if(this != NULL && cuit != NULL)
	{
		retorno = 0;
		strncpy(cuit, this->cuit, CUIT_LEN);
	}
	return retorno;
}



int cli_ordenaNombre(void* this1, void* this2)
{
	int retorno = 0;
	char nombre1[128];
	char nombre2[128];
	Cliente* empAux1= NULL;
	Cliente* empAux2= NULL;
	if(this1 != NULL && this2!= NULL)
	{
		empAux1= (Cliente*)this1;
		empAux2= (Cliente*)this2;
		if(cli_getNombre(empAux1,nombre1)==0 && cli_getNombre(empAux2,nombre2)==0)
		{
			if(strcmpi(nombre1, nombre2) > 0)
			{
				retorno = 1;
			}
			if(strcmpi(nombre1, nombre2) < 0)
			{
				retorno = -1;
			}
		}
	}
	return retorno;
}

